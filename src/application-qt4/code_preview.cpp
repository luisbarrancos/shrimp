
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


#include "code_preview.h"
#include "ui_code_preview.h"

#include "src/miscellaneous/logging.h"

code_preview::code_preview(QWidget *parent, services* shrimpServicesInstance) :
    QDialog (parent),
    ui (new Ui::codePreviewDialog),
    shrimpServices (shrimpServicesInstance)
{
    ui->setupUi(this);

    log() << aspect << "Code Preview dialog" << std::endl;

    // show code
    QString shaderCode = QString::fromStdString(shrimpServices->show_code());
    ui->surfaceTextEdit->setText(shaderCode);

    // connect events
    QObject::connect(ui->okButton, SIGNAL(clicked()), this, SLOT(okButton()));
}


code_preview::~code_preview()
{

}


void code_preview::okButton()
{
    close();
}

