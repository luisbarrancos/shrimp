// SDPTypes Library
// Copyright © 1995-2003, Timothy M. Shead
//
// Contact: tshead@k-3d.com
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

/** \file
		\brief Implements templates, functions, and classes for manipulating files in a platform-independant manner
		\author Tim Shead (tshead@k-3d.com)
*/

#include "sdptypes.h"

#include <stdio.h>
#include <algorithm>

#ifdef SDPWIN32
#include <direct.h>
#include <io.h>
#ifndef SDPMINGW32
#define popen _popen
#define read _read
#define PATH_MAX _MAX_PATH
#endif
#endif	// SDPWIN32

#ifdef SDPUNIX
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#endif // SDPUNIX

#include <sys/stat.h>

// Safely returns an environment variable ...
sdpString sdpGetEnv(SDPCSTRING EnvironmentVariable)
{

	const gchar* variable = g_getenv(EnvironmentVariable);
	if(variable)
		return sdpString(variable);

	return sdpString();
}

// Safely returns the current working directory ...
sdpString sdpGetCurrentDirectory()
{
	gchar* buffer = g_get_current_dir();
	sdpString result(buffer);
	g_free(buffer);
	return result;
}

// Safely returns the user's home directory ...
sdpString sdpGetHomeDirectory()
{
	return sdpString(g_get_home_dir());
}

// Safely returns the user's temp directory ...
sdpString sdpGetTempDirectory()
{
	return sdpString(g_get_tmp_dir());
}

// Cross-platform method for creating a directory
bool sdpCreateDirectory(SDPCSTRING Path)
{
	sdpString path(sdpMakeNativeFilePath(Path));

#if defined (SDPMICROSOFT) || defined (SDPMINGW32)
	return CreateDirectory(path, 0) ? true : false;
#else // SDPMICROSOFT || SDPMINGW32
	return 0 == mkdir(path, 0777) ? true : false;
#endif // !(SDPMICROSOFT || SDPMINGW32)
}

bool sdpFileExists(SDPCSTRING Path)
{
	// Sanity checks ...
	g_return_val_if_string_fail(Path, false);

	struct stat statistics;
	return (-1 == stat(Path, &statistics)) ? false : true;
}

bool sdpFileModificationTime(SDPCSTRING Path, GTime& ModificationTime)
{
	// Sanity checks ...
	g_return_val_if_string_fail(Path, false);

	struct stat statistics;
	if(-1 == stat(Path, &statistics))
		return false;

	ModificationTime = statistics.st_mtime;

	return true;
}

// Force a filepath to the native filesystem's format (convert slashes as needed) ...
sdpString sdpMakeNativeFilePath(SDPCSTRING FilePath)
{
	static const char foreign_dir_separator = (G_DIR_SEPARATOR == '/') ? '\\' : '/';
	static const char native_dir_separator = G_DIR_SEPARATOR;

	sdpString filepath(FilePath);
	std::replace(filepath.begin(), filepath.end(), foreign_dir_separator, native_dir_separator);

	return filepath;
}

// Force a filepath to a POSIX format (slashes go *forward*) ...
sdpString sdpMakePosixFilePath(SDPCSTRING FilePath)
{
	static const char non_posix_dir_separator = '\\';
	static const char posix_dir_separator = '/';

	sdpString filepath(FilePath);
	std::replace(filepath.begin(), filepath.end(), non_posix_dir_separator, posix_dir_separator);

	return filepath;
}

// Returns the directory components of a path, or "." ...
sdpString sdpDirectory(SDPCSTRING FilePath)
{
	gchar* buffer = g_dirname(sdpMakeNativeFilePath(FilePath));
	sdpString result(buffer);
	g_free(buffer);

	return result;
}

// Returns the file components of a path ...
sdpString sdpFile(SDPCSTRING FilePath)
{
	return sdpString(g_basename(sdpMakeNativeFilePath(FilePath)));
}

// Append three path components, handle some special cases:
sdpString sdpAppendPath(SDPCSTRING Path1, SDPCSTRING Path2, SDPCSTRING Path3)
{
	return sdpAppendPath(Path1, sdpAppendPath(Path2, Path3));
}

// Append to a path, handle some special cases:
sdpString sdpAppendPath(SDPCSTRING Path1, SDPCSTRING Path2)
{
	// Convert pointers to string objects ...
	sdpString path1(sdpMakeNativeFilePath(Path1));
	sdpString path2(sdpMakeNativeFilePath(Path2));

	// If the first path is empty, ignore it ...
	if(!path1.size())
		return path2;

	// If the second path is empty, ignore it ...
	if(!path2.size())
		return path1;

	// The second path is absolute, so ignore the first ...
	if(g_path_is_absolute(path2))
		return path2;

	// The second path is ".", so ignore it ...
	if(path2 == ".")
		return path1;

	// Combine the two paths ...
	if(path1[path1.size()-1] == G_DIR_SEPARATOR)
		return path1 + path2;
	else
		return path1 + G_DIR_SEPARATOR + path2;
}


