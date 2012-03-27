
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


#include "shader_properties.h"
#include "ui_shader_properties.h"

#include "src/miscellaneous/logging.h"

shader_properties::shader_properties(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::shaderPropertiesDialog)
{
    ui->setupUi(this);

    log() << aspect << "Shader Properties dialog" << std::endl;
}

shader_properties::~shader_properties()
{

}
