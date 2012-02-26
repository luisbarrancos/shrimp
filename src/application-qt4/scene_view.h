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


#ifndef scene_view_h
#define scene_view_h


#include "../opengl_view/opengl_view.h"
#include "../services.h"

#include <QGLWidget>


class scene_view :
	public QGLWidget,
	public opengl_view
{
public:
	Q_OBJECT

	services* m_services;

public:
	scene_view (services* services_instance);
	~scene_view();

	QSize sizeHint() const;
        void redraw();

protected:
	void initializeGL();
	void paintGL();
	void resizeGL (int width, int height);
	void mousePressEvent (QMouseEvent * event);
	void mouseMoveEvent (QMouseEvent * event);

};


#endif // scene_view_h

