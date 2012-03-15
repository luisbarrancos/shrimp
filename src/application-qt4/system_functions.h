
/*
    Copyright 2010-2012, Romain Behar <romainbehar@users.sourceforge.net>

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


#ifndef _system_functions_h_
#define _system_functions_h_

#include "../interfaces/i_system_functions.h"

#include <string>

class system_functions : public i_system_functions
{
public:
	// return user's data directory (home)
	std::string get_user_directory();

	// return temporary directory
	std::string get_temp_directory();

	// return absolute system path
	std::string get_absolute_path (const std::string& Path);

	// return the content of a directory (directories and files)
	std::vector<std::string> list_directory (const std::string& directory);

	// return true when the path is a directory
	bool is_directory (const std::string& path);

	// combine paths and files (add '/' or '\')
	std::string combine_paths (const std::string& path1, const std::string& path2);

        // return file extension ("test.xml" returns "xml")
	std::string get_file_extension (const std::string& file);

	// save text to a file
	void save_file (const std::string& destination, const std::string& content);

	// execute a command
	bool execute_command (const std::string& Command);

};

#endif // _system_functions_h_

