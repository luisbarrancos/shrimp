
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

#include "block_name.h"
#include "ui_block_name.h"

#include "src/miscellaneous/logging.h"

#include <QMessageBox>

block_name::block_name(
    QWidget* parent,
    services* shrimpServicesInstance,
    shader_block* block)
    : QDialog(parent)
    , ui(new Ui::blockNameDialog)
    , shrimpServices(shrimpServicesInstance)
    , editedBlock(block)
{
    ui->setupUi(this);

    log() << aspect << "Block Name dialog" << std::endl;

    // set values
    ui->blockNameLineEdit->setText(QString::fromStdString(block->name()));

    // connect events
    QObject::connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancelButton()));
    QObject::connect(ui->okButton, SIGNAL(clicked()), this, SLOT(okButton()));
}

block_name::~block_name() = default;

void block_name::cancelButton()
{
    close();
}

void block_name::okButton()
{
    log() << aspect << "Save block name" << std::endl;

    QString newName = ui->blockNameLineEdit->text();
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
            ui->blockNameLineEdit->setText(QString::fromStdString(uniqueName));
            return;
        }
    }

    close();
}
