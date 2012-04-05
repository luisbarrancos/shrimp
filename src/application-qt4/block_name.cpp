
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

block_name::block_name(QWidget* parent, services* shrimpServicesInstance) :
    QDialog (parent),
    ui (new Ui::blockNameDialog),
    shrimpServices (shrimpServicesInstance)
{
    ui->setupUi(this);

    log() << aspect << "Block Name dialog" << std::endl;

    // set values

    // connect events
    QObject::connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancelButton()));
    QObject::connect(ui->okButton, SIGNAL(clicked()), this, SLOT(okButton()));
}


block_name::~block_name()
{

}


void block_name::cancelButton()
{
    close();
}


void block_name::okButton()
{
    log() << aspect << "Save block name" << std::endl;

    close();
}

