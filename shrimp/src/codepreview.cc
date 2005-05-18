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

#include "codepreview.h"

#include <fstream>

bool CodePreview::Load()
{
	sdpGtkObjectContainer::Load(guifile);

	Window("window").SetTitle(shader_name.c_str());
	Text("text").SetEditable(false);
	Text("text").SetWordWrap(true);

	std::ifstream file(file_name.c_str(), std::ios::in | std::ios::binary);
	char buffer[1024];
	GdkFont* font = gdk_font_load("-*-courier-medium-r-normal--*-120-*-*-*-*-iso8859-1");
	GdkColor white, black;
	white.red = white.green = white.blue = 65535;
	black.red = black.green = black.blue = 0;

	do
	{
		file.read(buffer, sizeof buffer);

		// output buffer to text widget
		Text("text").Insert(font, &black, &white, buffer, file.gcount());

	} while(file.gcount() == sizeof buffer);

	RootWidget().Show();

	return true;
}


