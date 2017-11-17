
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


#ifndef _image_handling_h_
#define _image_handling_h_

#include "tiffImage.h"

#include "../interfaces/i_opengl_texture.h"

#include <fltk/SharedImage.h>

#include <tiffio.h>


void initialize_fltk_image_handlers();


class opengl_texture : public i_opengl_texture
{
public:
	opengl_texture();
	~opengl_texture();

	void set_file(const char* filename);

	int width();
	int height();
	int format();

	uchar* data();

private:
	fltk::SharedImage* image;

	int image_width;
	int image_height;
	int image_format;
};

#endif // _image_handling_h_

