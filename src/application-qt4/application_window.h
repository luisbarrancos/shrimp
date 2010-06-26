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


#ifndef application_window_h
#define application_window_h


#include "scene_view.h"

#include "../services.h"
#include "../opengl_view/opengl_view.h"
#include "../shading/scene.h"

#include <QWidget>


class application_window : public QWidget
{
	Q_OBJECT

public:
	application_window (services* services_instance);

private:
	// shrimp services
	services* m_services;

	// OpenGL view of current scene
	scene_view* m_scene_view;
};


#endif // application_window_h

