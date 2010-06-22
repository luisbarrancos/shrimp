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
#include <QtOpenGL>

#include <math.h>

#include "scene_view.h"


scene_view::scene_view (QWidget* parent, services* services_instance, opengl_view* opengl_view_instance) :
	QGLWidget (parent),
	m_services (services_instance),
	m_opengl_view (opengl_view_instance)
{
}

scene_view::~scene_view()
{
}


QSize scene_view::sizeHint() const
{
	return QSize (500, 500);
}


void scene_view::initializeGL()
{
}


void scene_view::paintGL()
{
	m_opengl_view->draw_scene (true, 400, 400);
}


void scene_view::resizeGL (int width, int height)
{
}


void scene_view::mousePressEvent (QMouseEvent * event)
{
}


void scene_view::mouseMoveEvent (QMouseEvent * event)
{
}


