
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


#ifndef _i_system_functions_h_
#define _i_system_functions_h_

#include <string>

class i_system_functions
{
public:
	// return user's data directory (home)
	virtual std::string get_user_directory() { return std::string(); }

	// return temporary directory
	virtual std::string get_temp_directory() { return std::string(); }

	// return absolute system path
	virtual std::string get_absolute_path (const std::string& Path) { return std::string(); }

	// execute a system command
	virtual bool execute_command (const std::string& Command) { return false; }
};


#endif // _i_system_functions_h_

