
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


#ifndef _i_opengl_texture_h_
#define _i_opengl_texture_h_

class i_opengl_texture
{
public:
	virtual void set_file(const char* filename) {}

	virtual int width() { return 0; }
	virtual int height() { return 0; }
	virtual int format() { return 0; }

	virtual uchar* data() { return 0; }
};


#endif // _i_opengl_texture_h_

