
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


#ifndef SHADER_PROPERTIES_H
#define SHADER_PROPERTIES_H

#include <QDialog>

namespace Ui {
    class shaderPropertiesDialog;
}


class shader_properties: public QDialog
{
    Q_OBJECT

public:
    explicit shader_properties(QWidget *parent = 0);
    ~shader_properties();

private:
    Ui::shaderPropertiesDialog *ui;
};

#endif // SHADER_PROPERTIES_H
