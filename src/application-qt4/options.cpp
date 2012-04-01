
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


#include "options.h"
#include "ui_options.h"

#include "src/miscellaneous/logging.h"

#include <QMessageBox>

options::options (QWidget *parent, services* shrimpServicesInstance, general_options& optionsInstances) :
    QDialog (parent),
    ui (new Ui::optionsDialog),
    shrimpServices (shrimpServicesInstance),
    preferences (optionsInstances)
{
    ui->setupUi (this);

    log() << aspect << "Options dialog" << std::endl;

    // set values
    ui->splashScreenCheckBox->setChecked (preferences.m_splash_screen);
    setupRendererCombo(preferences.m_renderer_code);
    ui->rendererCodeLineEdit->setText (QString::fromStdString (preferences.m_renderer_code));
    ui->shaderCompilationLineEdit->setText (QString::fromStdString (preferences.m_shader_compiler));
    ui->shaderExtensionLineEdit->setText (QString::fromStdString (preferences.m_compiled_shader_extension));
    ui->renderingCommandLineEdit->setText (QString::fromStdString (preferences.m_renderer));
    setupDisplayCombo(preferences.m_renderer_code, preferences.m_renderer_display);

    setupSceneCombo();
    ui->renderWidthLineEdit->setText (QString::number (preferences.m_output_width));
    ui->renderHeightLineEdit->setText (QString::number (preferences.m_output_height));
    ui->shadingRateLineEdit->setText (QString::number (preferences.m_shading_rate));
    ui->pixelSamplesXLineEdit->setText (QString::number (preferences.m_samples_x));
    ui->pixelSamplesYLineEdit->setText (QString::number (preferences.m_samples_y));
    setupPixelFilterCombo(preferences.m_renderer_code, preferences.m_pixel_filter);
    ui->filterWidthSLineEdit->setText (QString::number (preferences.m_filter_width_s));
    ui->filterWidthTLineEdit->setText (QString::number (preferences.m_filter_width_t));
    ui->helpReaderLineEdit->setText (QString::fromStdString (preferences.m_help_reader));

    // connect events
    QObject::connect (ui->rendererComboBox, SIGNAL(activated(QString)), SLOT(changeRenderer(QString)));
    QObject::connect (ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancelButton()));
    QObject::connect (ui->okButton, SIGNAL(clicked()), this, SLOT(okButton()));
}


options::~options()
{

}


void options::setupRendererCombo(const std::string& rendererCode)
{
    unsigned long currentMenuNumber = 0;
    unsigned long rendererIndex = 0;

    general_options::renderers_t renderers = preferences.get_renderer_list();
    for (general_options::renderers_t::iterator renderer = renderers.begin(); renderer != renderers.end(); ++renderer, ++currentMenuNumber)
    {
        ui->rendererComboBox->addItem(QString::fromStdString(renderer->second.name));

        if (renderer->first == rendererCode)
        {
            rendererIndex = currentMenuNumber;
        }
    }

    // select renderer and corresponding display list
    ui->rendererComboBox->setCurrentIndex (rendererIndex);
}


void options::setupDisplayCombo(const std::string& rendererCode, const std::string& rendererDisplay)
{
    unsigned long currentMenuNumber = 0;
    unsigned long displayIndex = 0;

    general_options::renderers_t renderers = preferences.get_renderer_list();
    general_options::renderers_t::iterator renderer = renderers.find (rendererCode);
    if (renderer != renderers.end())
    {
        ui->displayComboBox->clear();
        for (general_options::displays_t::const_iterator display = renderer->second.displays.begin(); display != renderer->second.displays.end(); ++display, ++currentMenuNumber)
        {
            ui->displayComboBox->addItem (QString::fromStdString (*display));

            if (*display == rendererDisplay)
            {
                displayIndex = currentMenuNumber;
            }
        }

        // select display
        ui->displayComboBox->setCurrentIndex (displayIndex);
    }
}


void options::setupSceneCombo()
{
    unsigned long currentMenuNumber = 0;
    unsigned long sceneIndex = 0;

    general_options::scenes_t scenes = preferences.get_scene_list();
    for (general_options::scenes_t::iterator scene = scenes.begin(); scene != scenes.end(); ++scene, ++currentMenuNumber)
    {
        ui->sceneComboBox->addItem (QString::fromStdString(scene->name));

        if (scene->name == preferences.m_scene)
        {
            sceneIndex = currentMenuNumber;
        }
    }

    // select scene
    ui->sceneComboBox->setCurrentIndex (sceneIndex);
}


void options::setupPixelFilterCombo(const std::string& rendererCode, const std::string& pixelFilter)
{
    unsigned long currentMenuNumber = 0;
    unsigned long sceneIndex = 0;

    general_options::renderers_t renderers = preferences.get_renderer_list();
    general_options::renderers_t::iterator renderer = renderers.find (rendererCode);
    if (renderer != renderers.end())
    {
        ui->pixelFilterComboBox->clear();
        for (general_options::filters_t::const_iterator filter = renderer->second.filter_type.begin(); filter != renderer->second.filter_type.end(); ++filter, ++currentMenuNumber)
        {
            ui->pixelFilterComboBox->addItem (QString::fromStdString (*filter));

            if (*filter == pixelFilter)
            {
                sceneIndex = currentMenuNumber;
            }
        }

        // select filter
        ui->pixelFilterComboBox->setCurrentIndex (sceneIndex);
    }
}


void options::changeRenderer(const QString& rendererName)
{
    log() << aspect << "Change renderer to " << rendererName.toStdString() << std::endl;

    for (general_options::renderers_t::iterator renderer = preferences.m_renderers.begin(); renderer != preferences.m_renderers.end(); ++renderer)
    {
        if (renderer->second.name == rendererName.toStdString())
        {
            const std::string rendererCode = renderer->first;

            ui->rendererCodeLineEdit->setText (QString::fromStdString (rendererCode));
            ui->shaderCompilationLineEdit->setText (QString::fromStdString (renderer->second.shader_compiler));
            ui->shaderExtensionLineEdit->setText (QString::fromStdString (renderer->second.compiled_shader_extension));
            ui->renderingCommandLineEdit->setText (QString::fromStdString (renderer->second.renderer_command));

            setupDisplayCombo (rendererCode, "");
            setupPixelFilterCombo (rendererCode, "");
        }
    }
}


void options::cancelButton()
{
    close();
}


void options::okButton()
{
    log() << aspect << "Saving options" << std::endl;

    // save values
    preferences.m_splash_screen = ui->splashScreenCheckBox->checkState();
    preferences.m_renderer_code = ui->rendererCodeLineEdit->text().toStdString();
    preferences.m_shader_compiler = ui->shaderCompilationLineEdit->text().toStdString();
    preferences.m_compiled_shader_extension = ui->shaderExtensionLineEdit->text().toStdString();
    preferences.m_renderer = ui->renderingCommandLineEdit->text().toStdString();
    preferences.m_renderer_display = ui->displayComboBox->currentText().toStdString();

    preferences.m_scene = ui->sceneComboBox->currentText().toStdString();
    if (!isDouble (ui->renderWidthLineEdit->text(), "Render width")) return;
    preferences.m_output_width = ui->renderWidthLineEdit->text().toDouble();
    if (!isDouble (ui->renderHeightLineEdit->text(), "Render height")) return;
    preferences.m_output_height = ui->renderHeightLineEdit->text().toDouble();
    if (!isDouble (ui->shadingRateLineEdit->text(), "Shading rate")) return;
    preferences.m_shading_rate = ui->shadingRateLineEdit->text().toDouble();
    if (!isDouble (ui->pixelSamplesXLineEdit->text(), "Pixel samples x")) return;
    preferences.m_samples_x = ui->pixelSamplesXLineEdit->text().toDouble();
    if (!isDouble (ui->pixelSamplesYLineEdit->text(), "Pixel samples y")) return;
    preferences.m_samples_y = ui->pixelSamplesYLineEdit->text().toDouble();
    preferences.m_pixel_filter = ui->pixelFilterComboBox->currentText().toStdString();
    if (!isDouble (ui->filterWidthSLineEdit->text(), "Filter width s")) return;
    preferences.m_filter_width_s = ui->filterWidthSLineEdit->text().toDouble();
    if (!isDouble (ui->filterWidthTLineEdit->text(), "Filter width t")) return;
    preferences.m_filter_width_t = ui->filterWidthTLineEdit->text().toDouble();

    preferences.m_help_reader = ui->helpReaderLineEdit->text().toStdString();

    preferences.save();

    close();
}


bool options::isDouble(const QString& textValue, const QString& fieldName)
{
    bool success = false;
    double value = textValue.toDouble (&success);

    if (!success)
    {
        QMessageBox msgBox;
        msgBox.setText("Error:");
        msgBox.setInformativeText(fieldName + " '" + textValue + "' is not a number");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }

    return success;
}


