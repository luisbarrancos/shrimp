
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

#ifndef BLOCK_INPUT_OUTPUT_H
#define BLOCK_INPUT_OUTPUT_H

#include "src/services.h"

#include <QDialog>

namespace Ui
{
class blockInputOutputDialog;
}

class block_input_output : public QDialog
{
    Q_OBJECT

  public:
    explicit block_input_output(
        QWidget* parent,
        services* shrimpServicesInstance,
        const std::string& dialogType,
        shader_block* block,
        const std::string& property = "");
    ~block_input_output() override;

  public slots:
    void typeChange(const QString& typeName);
    void cancelButton();
    void okButton();

    void on_fileButton_clicked();
    void on_colorButton_clicked();

  private:
    Ui::blockInputOutputDialog* ui;
    services* shrimpServices;

    const std::string ioDialogType;
    shader_block* editedBlock;
    const std::string editedProperty;

    void setValues(
        const std::string& name,
        const std::string& storageTypeName,
        const std::string& typeName,
        const std::string& arrayTypeName,
        const int arraySize,
        const bool shaderParameterOutput,
        const std::string& description);
};

#endif // BLOCK_INPUT_OUTPUT_H
