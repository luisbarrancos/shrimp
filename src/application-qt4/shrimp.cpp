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


#include "system_functions.h"

#include "../miscellaneous/logging.h"
#include "../opengl_view/opengl_view.h"
#include "../services.h"

#include <QApplication>

#include <memory>

#include "application_window.h"


int qt_frontend(int argc, char** argv, services* services_instance);

// Launch Qt and Shrimp's main window
int main (int argc, char *argv[])
{
	// set up log system
	log_level_t level = ERROR;
	std::auto_ptr<std::streambuf> filter_level (new filter_by_level_buf (level, log()));

/*
	log() << error << "LOG = ERROR" << std::endl;
	log() << warning << "LOG = WARNING" << std::endl;
	log() << info << "LOG = INFO" << std::endl;
	log() << debug << "LOG = DEBUG" << std::endl;
	log() << aspect << "LOG = ASPECT" << std::endl;
*/

	log() << aspect << "Starting Shrimp" << std::endl;

	// create system function instance (FLTK dependent)
	i_system_functions* system_instance = new system_functions();

	// create services
	services* services_instance = new services(system_instance);

	// run Qt front end
	return qt_frontend (argc, argv, services_instance);
}


int qt_frontend (int argc, char** argv, services* services_instance)
{
	opengl_view* opengl_view_instance = new opengl_view (services_instance);


	QApplication app(argc, argv);
	application_window window (services_instance, opengl_view_instance);
	window.show();
	return app.exec();
}


