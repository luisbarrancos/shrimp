
/*
    Copyright 2012, Romain Behar <romainbehar@users.sourceforge.net>

    This file is part of Shrimp 2.

    Shrimp 2 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Shrimp 2 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Shrimp 2.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "block_input_output.h"
#include "ui_block_input_output.h"

#include "src/miscellaneous/logging.h"

#include <QColorDialog>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

block_input_output::block_input_output(
    QWidget* parent,
    services* shrimpServicesInstance,
    const std::string& dialogType,
    shader_block* block,
    const std::string& property)
    : QDialog(parent)
    , ui(new Ui::blockInputOutputDialog)
    , shrimpServices(shrimpServicesInstance)
    , ioDialogType(dialogType)
    , editedBlock(block)
    , editedProperty(property)
{
    ui->setupUi(this);

    log() << aspect << "Block Input/Output dialog" << std::endl;

    // configure dialog
    if (ioDialogType == "addOutput" || ioDialogType == "editOutput")
    {
        // update controls and tooltips
        ui->nameLineEdit->setToolTip("Output name");
        ui->storageTypeComboBox->setToolTip("Output variable storage type");
        ui->typeComboBox->setToolTip("Output type");
        ui->shaderParameterCheckBox->setText("Shader output");
        ui->shaderParameterCheckBox->setToolTip(
            "Make it a shader output for message passing");
        ui->descriptionTextEdit->setToolTip("Output description");

        // remove default value line
        ui->defaultValueLabel->hide();
        ui->defaultValueLineEdit->hide();
        ui->colorButton->hide();
        ui->fileButton->hide();
    }

    if (ioDialogType == "addInput")
    {
        setWindowTitle("Add Input");
    }
    else if (ioDialogType == "addOutput")
    {
        setWindowTitle("Add Output");
    }
    else if (ioDialogType == "editInput")
    {
        setWindowTitle("Edit Input");

        // set name as read-only
        ui->nameLineEdit->setReadOnly(true);

        // change label
        ui->defaultValueLabel->setText("Value");

        // change button
        ui->okButton->setText("Save");
    }
    else if (ioDialogType == "editOutput")
    {
        setWindowTitle("Edit Output");

        // set name as read-only
        ui->nameLineEdit->setReadOnly(true);

        // change button
        ui->okButton->setText("Save");
    }
    else
    {
        log() << error << "Unknown dialog type: " << ioDialogType << std::endl;
    }

    // hide array parameters
    ui->arraySizeSpinBox->hide();
    ui->arrayTypeComboBox->hide();

    // setup combos
    types_t storageTypes = get_property_storage_types();
    for (auto& storageType : storageTypes)
    {
        ui->storageTypeComboBox->addItem(QString::fromStdString(storageType));
    }

    types_t types = get_property_types();
    for (auto& type : types)
    {
        ui->typeComboBox->addItem(QString::fromStdString(type));
    }

    types_t arrayTypes = get_array_types();
    for (auto& arrayType : arrayTypes)
    {
        ui->arrayTypeComboBox->addItem(QString::fromStdString(arrayType));
    }

    // set values
    if (ioDialogType == "editInput")
    {
        const std::string& typeName(editedBlock->get_input_type(editedProperty));
        setValues(
            editedProperty,
            editedBlock->get_input_storage(editedProperty),
            typeName,
            editedBlock->get_input_type_extension(editedProperty),
            editedBlock->get_input_type_extension_size(editedProperty),
            editedBlock->is_shader_parameter(editedProperty),
            editedBlock->get_input_description(editedProperty));

        QString defaultValue(
            QString::fromStdString(editedBlock->get_input_value(editedProperty)));
        if (typeName == std::string("string"))
        {
            if (defaultValue.startsWith('"'))
            {
                defaultValue.remove(0, 1);
            }
            if (defaultValue.endsWith('"'))
            {
                defaultValue.remove(defaultValue.length() - 1, 1);
            }
        }
        ui->defaultValueLineEdit->setText(defaultValue);
    }
    else if (ioDialogType == "editOutput")
    {
        setValues(
            editedProperty,
            editedBlock->get_output_storage(editedProperty),
            editedBlock->get_output_type(editedProperty),
            editedBlock->get_output_type_extension(editedProperty),
            editedBlock->get_output_type_extension_size(editedProperty),
            editedBlock->is_shader_output(editedProperty),
            editedBlock->get_output_description(editedProperty));
    }

    // connect events
    connect(
        ui->typeComboBox, SIGNAL(activated(QString)), this, SLOT(typeChange(QString)));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancelButton()));
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(okButton()));
}

block_input_output::~block_input_output() = default;

void block_input_output::typeChange(const QString& typeName)
{
    bool enableArray = (typeName == "array");
    if (enableArray)
    {
        ui->arraySizeSpinBox->show();
        ui->arrayTypeComboBox->show();
    }
    else
    {
        ui->arraySizeSpinBox->hide();
        ui->arrayTypeComboBox->hide();
    }
}

void block_input_output::cancelButton()
{
    close();
}

void block_input_output::okButton()
{
    log() << aspect << "Add block input/output" << std::endl;

    QString name = ui->nameLineEdit->text();
    QString storageName =
        ui->storageTypeComboBox->itemText(ui->storageTypeComboBox->currentIndex());
    QString typeName = ui->typeComboBox->itemText(ui->typeComboBox->currentIndex());
    int arraySize    = ui->arraySizeSpinBox->value();
    QString arrayType =
        ui->arrayTypeComboBox->itemText(ui->arrayTypeComboBox->currentIndex());
    QString defaultValue       = ui->defaultValueLineEdit->text();
    bool shaderParameterOutput = ui->shaderParameterCheckBox->checkState();
    QString description        = ui->descriptionTextEdit->toPlainText();

    QString typeExtension = arrayType + ":" + QString::number(arraySize);

    //TODO: check that the default value matches the input type

    if (typeName == "string")
    {
        if (!defaultValue.startsWith('"'))
        {
            defaultValue.push_front('"');
        }
        if (!defaultValue.endsWith('"'))
        {
            defaultValue.push_back('"');
        }
    }

    if (ioDialogType == "addInput" || ioDialogType == "addOutput")
    {
        QString errorMessage;
        if (name.isEmpty())
        {
            // forbid empty names
            QString padType = (ioDialogType == "AddInput")
                                  ? "Input"
                                  : ((ioDialogType == "AddOutput") ? "Output" : "");
            errorMessage = QString("The " + padType + " name cannot be empty!");
        }
        else if (editedBlock->is_input(name.toStdString()))
        {
            // an input with the same name already exists
            errorMessage = QString("An input with this name already exists!");
        }
        else if (editedBlock->is_output(name.toStdString()))
        {
            // an input with the same name already exists
            errorMessage = QString("An output with this name already exists!");
        }

        if (!errorMessage.isEmpty())
        {
            QMessageBox msgBox(this);
            msgBox.setInformativeText(errorMessage);
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();

            // try again
            return;
        }
    }

    // add
    if (ioDialogType == "addInput")
    {
        log() << aspect << "Add input: " << name.toStdString() << std::endl;
        editedBlock->add_input(
            name.toStdString(),
            typeName.toStdString(),
            typeExtension.toStdString(),
            storageName.toStdString(),
            description.toStdString(),
            defaultValue.toStdString(),
            "",
            shaderParameterOutput);
    }
    else if (ioDialogType == "addOutput")
    {
        log() << aspect << "Add output: " << name.toStdString() << std::endl;
        editedBlock->add_output(
            name.toStdString(),
            typeName.toStdString(),
            typeExtension.toStdString(),
            storageName.toStdString(),
            description.toStdString(),
            shaderParameterOutput);
    }
    else if (ioDialogType == "editInput")
    {
        log() << aspect << "Save input: " << name.toStdString() << std::endl;

        editedBlock->set_input_value(name.toStdString(), defaultValue.toStdString());
        editedBlock->set_input_storage(name.toStdString(), storageName.toStdString());
        editedBlock->set_input_type(name.toStdString(), typeName.toStdString());
        editedBlock
            ->set_input_type_extension(name.toStdString(), typeExtension.toStdString());
        editedBlock->set_shader_parameter(name.toStdString(), shaderParameterOutput);
        editedBlock->set_input_description(name.toStdString(), description.toStdString());
    }
    else if (ioDialogType == "editOutput")
    {
        log() << error << "Save output: " << name.toStdString() << std::endl;

        editedBlock->set_output_storage(name.toStdString(), storageName.toStdString());
        editedBlock->set_output_type(name.toStdString(), typeName.toStdString());
        editedBlock
            ->set_output_type_extension(name.toStdString(), typeExtension.toStdString());
        editedBlock->set_shader_output(name.toStdString(), shaderParameterOutput);
        editedBlock
            ->set_output_description(name.toStdString(), description.toStdString());
    }
    else
    {
        log() << error << "Unknown io type: " << ioDialogType << std::endl;
    }

    close();
}

void block_input_output::setValues(
    const std::string& name,
    const std::string& storageTypeName,
    const std::string& typeName,
    const std::string& arrayTypeName,
    const int arraySize,
    const bool shaderParameterOutput,
    const std::string& description)
{
    ui->nameLineEdit->setText(QString::fromStdString(name));

    int storageTypeIndex =
        ui->storageTypeComboBox->findText(QString::fromStdString(storageTypeName));
    if (storageTypeIndex != -1)
    {
        ui->storageTypeComboBox->setCurrentIndex(storageTypeIndex);
    }

    int typeIndex = ui->typeComboBox->findText(QString::fromStdString(typeName));
    if (typeIndex != -1)
    {
        ui->typeComboBox->setCurrentIndex(typeIndex);

        if (typeName == "array")
        {
            ui->arraySizeSpinBox->show();
            ui->arrayTypeComboBox->show();

            ui->arraySizeSpinBox->setValue(arraySize);

            int arrayTypeIndex =
                ui->arrayTypeComboBox->findText(QString::fromStdString(arrayTypeName));
            if (arrayTypeIndex != -1)
            {
                ui->arrayTypeComboBox->setCurrentIndex(arrayTypeIndex);
            }
        }
    }

    ui->shaderParameterCheckBox->setChecked(shaderParameterOutput);
    ui->descriptionTextEdit->setPlainText(QString::fromStdString(description));
}

void block_input_output::on_fileButton_clicked()
{
    const QString& fileName(QFileDialog::getOpenFileName(
        this,
        tr("Select Texture"),
        QDir::homePath(),
        tr("Image Files (*.exr *.tif);;All (*.*)")));
    if (fileName.isEmpty() || !QFile::exists(fileName))
    {
        return;
    }
    ui->defaultValueLineEdit->setText(fileName);

    int typeIndex = ui->typeComboBox->findText("string");
    if (typeIndex != -1)
    {
        ui->typeComboBox->setCurrentIndex(typeIndex);
    }
}

void block_input_output::on_colorButton_clicked()
{
    const QColor& color(QColorDialog::getColor(Qt::gray, this));
    if (!color.isValid())
    {
        return;
    }

    const QString& colorName(QString("color(%1, %2, %3)")
                                 .arg(color.redF())
                                 .arg(color.greenF())
                                 .arg(color.blueF()));
    ui->defaultValueLineEdit->setText(colorName);

    int typeIndex = ui->typeComboBox->findText("color");
    if (typeIndex != -1)
    {
        ui->typeComboBox->setCurrentIndex(typeIndex);
    }
}
