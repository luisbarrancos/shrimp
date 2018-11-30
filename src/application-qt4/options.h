
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

#ifndef OPTIONS_H
#define OPTIONS_H

#include "src/services.h"

#include <QDialog>

namespace Ui
{
class optionsDialog;
}

class options : public QDialog
{
    Q_OBJECT

  public:
    explicit options(
        QWidget* parent,
        services* shrimpServicesInstance,
        general_options& optionsInstances);
    ~options() override;

  public slots:
    void changeRenderer(const QString& rendererName);
    void cancelButton();
    void okButton();

  private:
    Ui::optionsDialog* ui;
    services* shrimpServices;
    general_options& preferences;

    void setupRendererCombo(const std::string& rendererCode);

    void setupDisplayCombo(
        const std::string& rendererCode,
        const std::string& rendererDisplay);

    void setupSceneCombo();

    void setupPixelFilterCombo(
        const std::string& rendererCode,
        const std::string& pixelFilter);

    bool isDouble(const QString& textValue, const QString& fieldName);
};

#endif // OPTIONS_H
