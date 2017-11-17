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

#ifndef RENDEROPTIONS_H
#define RENDEROPTIONS_H

#include "modaldialog.h"

#include <sdpxml/sdpxml.h>

class RenderOptions :
	public ModalDialog
{
public:
	RenderOptions();

	void setShaderPath(std::string path)
	{
		shader_path = path;
		compileCommand = "slc -I" + shader_path + " %s";
	}
	void setDefaults();

	std::string getCompiler(){ return compileCommand; }
	std::string getRenderer(){ return renderCommand; }
	void writeRIB(std::string filename, std::string name, std::string type);

	void readPrefs(sdpxml::Element* renderprefs);
	void writePrefs(sdpxml::Element& renderprefs);

private:
	bool Load();

	void OnEvent(sdpGtkEvent* event);
	void OnOK();
	void OnShapeChange(std::string name);
	void OnColourPressEvent();
	void OnColourConfigureEvent();
	void OnColourExposeEvent(sdpGtkEvent* event);
	void drawColour();
	void updateColour();
	void updateShape();

	std::string shader_path;

	std::string compileCommand;
	std::string renderCommand;
	double colour[4];
	double new_colour[4];
	int xRes;
	int yRes;
	int xPixelSamples;
	int yPixelSamples;
	std::string shape;
	std::string new_shape;

	GdkGC* gc;
	GdkPixmap* pixmap;
};

#endif // RENDEROPTIONS_H

