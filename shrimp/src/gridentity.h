//============================================================================
//
// Shrimp Shader Generator
// Copyright (C) 2000-2004 Andy Gill
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
//============================================================================

#ifndef GRIDENTITY_H
#define GRIDENTITY_H

#include <gdk/gdk.h>

#include <string>

class GridEntity
{
public:
	GridEntity()
	{
		name = "no name";
		description = "no description";
		xpos = ypos = 0;
		xsize = ysize = 1;
	}

	virtual ~GridEntity() {}

	virtual void draw(GdkPixmap* pixmap, GdkGC* gc, int zoom) = 0;

	const std::string getName() { return name; }
	virtual void setName(const std::string& new_name) { name = new_name; }

	std::string getDesc() { return description; }
	void setDesc(std::string newDesc) { description = newDesc; }

	int getXPos() { return xpos; }
	int getYPos() { return ypos; }
	virtual void setPos(const int x, const int y) { xpos = x; ypos = y; }

	int getXSize() { return xsize; }
	int getYSize() { return ysize; }
	virtual void setSize(const int x, const int y) { xsize = x; ysize = y; }

	virtual bool isIOPad() = 0;

protected:
	std::string name;
	std::string description;
	int xpos;
	int ypos;
	int xsize;
	int ysize;
};

#endif // GRIDENTITY_H

