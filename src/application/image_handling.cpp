
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

#include "../miscellaneous/logging.h"

#include <fltk/ask.h>
#include <fltk/gl.h>
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


opengl_texture::opengl_texture()
{
}


void opengl_texture::set_file(const char* filename)
{
	image = fltk::SharedImage::get(filename);
	if (image == 0)
	{
		log() << error << "Couldn't open image: " << filename << std::endl;
		return;
	}

	image->fetch_if_needed();

	// Process only RGB images
	int depth = image->depth();
	if (depth != 3 && depth != 4)
	{
		log() << error << "Only RGB and RGBA images are supported (" << filename << "), image's depth = " << image->depth() << std::endl;
		return;
	}

	if (depth == 3)
	{
		image_format = GL_RGB;
	}
	else if (depth == 4)
	{
		image_format = GL_RGBA;
	}

	image_width = image->width();
	image_height = image->height();
}


int opengl_texture::width()
{
	return image_width;
}


int opengl_texture::height()
{
	return image_height;
}


int opengl_texture::format()
{
	return image_format;
}


uchar* opengl_texture::data()
{
	if (image == 0)
	{
		return 0;
	}

	return image->buffer();
}


opengl_texture::~opengl_texture()
{
	if (image != 0)
	{
		image->destroy();
	}
}


