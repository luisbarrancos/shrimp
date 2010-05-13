
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


#include "image_handling.h"

#include <fltk/ask.h>
#include <cstring>


fltk::SharedImage* tiff_handler(const char* name, uchar* header, int headerlen);

void initialize_fltk_image_handlers()
{
	fltk::SharedImage::set_cache_size (4096);

	// TIFF image handler
	fltk::SharedImage::add_handler (tiff_handler);
}


fltk::SharedImage* tiff_handler(const char* name, uchar* header, int headerlen)
{
	if (memcmp(header, "II*", 3) != 0)
		return 0;

	fltk::SharedImage* tiffImage = new fltk::tiffImage(name);
	if (!name || !tiffImage)
	{
		fltk::alert("Can't open TIFF file!");
		return 0;
	}

	return tiffImage;
}


