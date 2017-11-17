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

#include "iopad.h"

IOPad::IOPad()
{
	parent = 0;
	type = "float";
	types.insert("float");
}

void IOPad::draw(GdkPixmap* pixmap, GdkGC* gc, int zoom)
{
	int x = (int)(zoom*(xpos + 0.08));
	int y = (int)(zoom*(ypos + 0.08));
	int w = (int)(zoom*(xsize - 0.16));
	int h = (int)(zoom*(ysize - 0.16));

	if(isConnectable())
		gdk_rgb_gc_set_foreground(gc, 0xdddddd);
	else
		gdk_rgb_gc_set_foreground(gc, 0xc0c0c0);

	gdk_draw_rectangle(pixmap, gc, TRUE, x, y, w, h);

	gdk_rgb_gc_set_foreground(gc, 0xfcfcfc);
	gdk_draw_line(pixmap, gc, x, y, x + w, y);
	gdk_draw_line(pixmap, gc, x, y, x, y + h);

	gdk_rgb_gc_set_foreground(gc, 0x777777);
	gdk_draw_line(pixmap, gc, x, y + h, x + w, y + h);
	gdk_draw_line(pixmap, gc, x + w, y, x + w, y + h);

	if(type != std::string("float"))
	{
		int y0 = (int)(y + 0.3*zoom);
		int y1 = (int)(y + 0.6*zoom);
		int h0 = (int)(h * 0.333);

		if(type == std::string("color"))
		{
			gdk_rgb_gc_set_foreground(gc, 0xdd0000);
			gdk_draw_rectangle(pixmap, gc, TRUE, x+1, y+1, w-2, h0);
			gdk_rgb_gc_set_foreground(gc, 0x00aa00);
			gdk_draw_rectangle(pixmap, gc, TRUE, x+1, y0+1, w-2, h0);
			gdk_rgb_gc_set_foreground(gc, 0x0000bb);
			gdk_draw_rectangle(pixmap, gc, TRUE, x+1, y1+1, w-2, h0);
		}
		else if(type == std::string("string"))
		{
			int x0 = (int)(x + 0.3*zoom);
			int x1 = (int)(x + 0.6*zoom);

			gdk_rgb_gc_set_foreground(gc, 0xfcfcfc);
			gdk_draw_line(pixmap, gc, x0-1, y0, x0-1, y1);
			gdk_draw_line(pixmap, gc, x1-1, y0, x1-1, y1);

			gdk_rgb_gc_set_foreground(gc, 0x777777);
			gdk_draw_line(pixmap, gc, x0, y0, x0, y1);
			gdk_draw_line(pixmap, gc, x1, y0, x1, y1);
		}
		else
		{
			gdk_rgb_gc_set_foreground(gc, 0xfcfcfc);
			gdk_draw_line(pixmap, gc, x+1, y0-1, x+w-2, y0-1);
			gdk_draw_line(pixmap, gc, x+1, y1-1, x+w-2, y1-1);

			gdk_rgb_gc_set_foreground(gc, 0x777777);
			gdk_draw_line(pixmap, gc, x+1, y0, x+w-2, y0);
			gdk_draw_line(pixmap, gc, x+1, y1, x+w-2, y1);
		}
	}

	if(isInput())
	{
		InputPad* inpad = (InputPad*) this;
		if(inpad->isShaderVar() && inpad->isConnectable())
		{
			int x0 = (int)(x + 0.33*zoom);
			int y0 = (int)(y + 0.33*zoom);
			int w0 = (int)(w * 0.333);
			int h0 = (int)(h * 0.333);

			gdk_rgb_gc_set_foreground(gc, 0x000066);
			gdk_draw_rectangle(pixmap, gc, TRUE, x0,y0,w0,h0);
		}
		if(inpad->isMultiPad())
		{
			int x0 = (int)(x + 0.4*zoom);

			gdk_rgb_gc_set_foreground(gc, 0x404040);
			gdk_draw_line(pixmap, gc, x+1, y+1, x0, y+h-1);
			gdk_draw_line(pixmap, gc, x0, y+h-1, x+w-1, y+1);
		}
	}
}

bool IOPad::changeType(std::string new_type)
{
	if(types.count(new_type))
		return(changeBlockType(parent, new_type));
	else
		return false;
}


/***************** OutputPad ****************/

// Return whether or not this pad minds if the parent block changes type
bool OutputPad::canChangeType(std::string new_type)
{
	if(types.size() == 1)
		return true;

	if(type == new_type)
		return true;

	if(links == 0 && types.count(new_type))
		return true;

	return false;
}

// Change type if it can
void OutputPad::suggestType(std::string new_type)
{
	if(links == 0 && types.count(new_type))
		type = new_type;
}


/***************** InputPad *****************/

InputPad::InputPad()
{
	is_shader_var = false;
	use_string_val = false;
	setDecodedValue(1.0);

	is_multipad = false;
	is_copy = false;
	separator = ", ";

	connection = 0;
}

void InputPad::connect(OutputPad* op)
{
	g_assert(op != 0);

	connection = op;
	op->ref();
}

void InputPad::disconnect()
{
	if(connection != 0)
		connection->unref();

	connection = 0;
}

//this also updates the string value
void InputPad::setDecodedValue(sdpVector3 v)
{
	decoded_val = v;

	if(type == "string")
		return;

	if(type == "float")
		string_val = sdpToString<double>(v[0]);
	else
		string_val = type + "(" +
			std::string(sdpToString<double>(v[0]) + ", "
				+ sdpToString<double>(v[1]) + ", "
				+ sdpToString<double>(v[2])) + ")";

	use_string_val = false;
}

void InputPad::setStringValue(std::string v)
{
	string_val = v;

	use_string_val = true;
}

void InputPad::setType(std::string new_type)
{
	type = new_type;
	if(type == "string")
		use_string_val = true;
	else if(!use_string_val)
		//update string version
		setDecodedValue(decoded_val);
}

//return whether or not this pad minds if the parent block changes type
bool InputPad::canChangeType(std::string new_type)
{
	if(types.size() == 1)
		return true;

	if(type == new_type)
		return true;

	if(isConnectable() && types.count(new_type))
		return true;

	return false;
}

void InputPad::suggestType(std::string new_type)
{
	if(isConnectable() && types.count(new_type))
		type = new_type;
}


