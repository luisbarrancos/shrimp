
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

#include "block_info.h"
#include "ui_block_info.h"

#include "src/miscellaneous/logging.h"

#include <QMessageBox>

block_info::block_info(
    QWidget* parent,
    services* shrimpServicesInstance,
    shader_block* block)
    : QDialog(parent)
    , ui(new Ui::blockInfoDialog)
    , shrimpServices(shrimpServicesInstance)
    , editedBlock(block)
{
    ui->setupUi(this);

    log() << aspect << "Block Info dialog" << std::endl;

    // set values
    ui->nameLineEdit->setText(QString::fromStdString(block->name()));
    ui->descriptionTextEdit->setText(QString::fromStdString(block->m_description));
    ui->usageTextEdit->setText(QString::fromStdString(block->m_usage));
    ui->authorsLineEdit->setText(QString::fromStdString(block->m_author));

    // connect events
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancelButton()));
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(okButton()));
}

block_info::~block_info() = default;

void block_info::cancelButton()
{
    close();
}

void block_info::okButton()
{
    log() << aspect << "Save block info" << std::endl;

    QString newName     = ui->nameLineEdit->text();
    QString description = ui->descriptionTextEdit->toPlainText();
    QString usage       = ui->usageTextEdit->toPlainText();
    QString authors     = ui->authorsLineEdit->text();

    // check name
    if (newName.toStdString() == editedBlock->name())
    {
        // name didn't change
    }
    else if (newName.isEmpty())
    {
        // can't rename to an empty string
        QMessageBox msgBox(this);
        msgBox.setInformativeText(QString::fromStdString("New name cannot be empty!"));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();

        // try again
        return;
    }
    else
    {
        // check whether the name already exists
        const std::string uniqueName =
            shrimpServices->get_unique_block_name(newName.toStdString());
        if (uniqueName == newName.toStdString())
        {
            // new name is unique, save it
            shrimpServices->set_block_name(editedBlock, newName.toStdString());
        }
        else
        {
            QMessageBox msgBox(this);
            msgBox.setInformativeText(
                QString::fromStdString("This name already exists."));
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();

            // suggest new name
            ui->nameLineEdit->setText(QString::fromStdString(uniqueName));
            return;
        }
    }

    // save other values
    editedBlock->m_description = description.toStdString();
    editedBlock->m_usage       = usage.toStdString();
    editedBlock->m_author      = authors.toStdString();

    close();
}
