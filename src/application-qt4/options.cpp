
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
    setupRendererCombo();
    ui->rendererCodeLineEdit->setText (QString::fromStdString (preferences.m_renderer_code));
    ui->shaderCompilationLineEdit->setText (QString::fromStdString (preferences.m_shader_compiler));
    ui->shaderExtensionLineEdit->setText (QString::fromStdString (preferences.m_compiled_shader_extension));
    ui->renderingCommandLineEdit->setText (QString::fromStdString (preferences.m_renderer));
    setupDisplayCombo();

    setupSceneCombo();
    ui->renderWidthLineEdit->setText (QString::fromStdString (string_cast (preferences.m_output_width)));
    ui->renderHeightLineEdit->setText (QString::fromStdString (string_cast (preferences.m_output_height)));
    ui->shadingRateLineEdit->setText (QString::fromStdString (string_cast (preferences.m_shading_rate)));
    ui->pixelSamplesXLineEdit->setText (QString::fromStdString (string_cast (preferences.m_samples_x)));
    ui->pixelSamplesYLineEdit->setText (QString::fromStdString (string_cast (preferences.m_samples_y)));
    setupPixelFilterCombo();
    ui->filterWidthSLineEdit->setText (QString::fromStdString (string_cast (preferences.m_filter_width_s)));
    ui->filterWidthTLineEdit->setText (QString::fromStdString (string_cast (preferences.m_filter_width_t)));
    ui->helpReaderLineEdit->setText (QString::fromStdString (preferences.m_help_reader));

    // connect events
    QObject::connect (ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancelButton()));
    QObject::connect (ui->okButton, SIGNAL(clicked()), this, SLOT(okButton()));
}


options::~options()
{

}


void options::setupRendererCombo()
{
    unsigned long currentMenuNumber = 0;
    unsigned long rendererIndex = 0;

    general_options::renderers_t  renderers = preferences.get_renderer_list();
    for (general_options::renderers_t::iterator renderer = renderers.begin(); renderer != renderers.end(); ++renderer, ++currentMenuNumber)
    {
        ui->rendererComboBox->addItem(QString::fromStdString(renderer->second.name));

        if (renderer->first == preferences.m_renderer_code)
        {
            rendererIndex = currentMenuNumber;
        }
    }

    // select renderer and corresponding display list
    ui->rendererComboBox->setCurrentIndex (rendererIndex);
}


void options::setupDisplayCombo()
{
    unsigned long currentMenuNumber = 0;
    unsigned long displayIndex = 0;

    general_options::renderers_t  renderers = preferences.get_renderer_list();
    general_options::renderers_t::iterator renderer = renderers.find (preferences.m_renderer_code);
    if (renderer != renderers.end())
    {
        ui->displayComboBox->clear();
        for (general_options::displays_t::const_iterator display = renderer->second.displays.begin(); display != renderer->second.displays.end(); ++display, ++currentMenuNumber)
        {
            ui->displayComboBox->addItem (QString::fromStdString (*display));

            if (*display == preferences.m_renderer_display)
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


void options::setupPixelFilterCombo()
{
    unsigned long currentMenuNumber = 0;
    unsigned long sceneIndex = 0;

    general_options::renderers_t  renderers = preferences.get_renderer_list();
    general_options::renderers_t::iterator renderer = renderers.find (preferences.m_renderer_code);
    if (renderer != renderers.end())
    {
        ui->pixelFilterComboBox->clear();
        for (general_options::filters_t::const_iterator filter = renderer->second.filter_type.begin(); filter != renderer->second.filter_type.end(); ++filter, ++currentMenuNumber)
        {
            ui->pixelFilterComboBox->addItem (QString::fromStdString (*filter));

            if (*filter == preferences.m_pixel_filter)
            {
                sceneIndex = currentMenuNumber;
            }
        }

        // select filter
        ui->pixelFilterComboBox->setCurrentIndex (sceneIndex);
    }
}


void options::cancelButton()
{
    close();
}


void options::okButton()
{
    close();
}


