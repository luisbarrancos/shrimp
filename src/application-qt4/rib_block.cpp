
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

#include "rib_block.h"
#include "ui_rib_block.h"

#include "src/miscellaneous/logging.h"

rib_block::rib_block(
    QWidget* parent,
    services* shrimpServicesInstance,
    rib_root_block* block)
    : QDialog(parent)
    , ui(new Ui::ribBlockDialog)
    , shrimpServices(shrimpServicesInstance)
    , editedBlock(block)
{
    ui->setupUi(this);

    log() << aspect << "RIB Block dialog" << std::endl;

    // set values
    ui->declarationsTextEdit->setPlainText(
        QString::fromStdString(editedBlock->get_general_statements()));
    ui->imagerLineEdit->setText(
        QString::fromStdString(editedBlock->get_imager_statement()));
    ui->aovCheckBox->setChecked(editedBlock->get_AOV());

    // connect events
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancelButton()));
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(okButton()));
}

rib_block::~rib_block() = default;

void rib_block::cancelButton()
{
    close();
}

void rib_block::okButton()
{
    log() << aspect << "Save RIB block" << std::endl;

    QString declarations = ui->declarationsTextEdit->toPlainText();
    QString imager       = ui->imagerLineEdit->text();
    bool aov             = ui->aovCheckBox->checkState();

    editedBlock->set_general_statements(declarations.toStdString());
    editedBlock->set_imager_statement(imager.toStdString());
    editedBlock->set_AOV(aov);

    close();
}
