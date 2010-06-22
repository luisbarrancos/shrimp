/*
    Copyright 2010, Romain Behar <romainbehar@users.sourceforge.net>

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


#include <QtGui>

#include "application_window.h"
#include "scene_view.h"


application_window::application_window (services* services_instance, opengl_view* opengl_view_instance) :
	m_services (services_instance),
	m_opengl_view (opengl_view_instance)
{
	m_scene_view = new scene_view (0, services_instance, opengl_view_instance);

	QHBoxLayout* mainLayout = new QHBoxLayout;
	mainLayout->addWidget (m_scene_view);
	setLayout (mainLayout);

	setWindowTitle(tr("Shrimp"));
}


