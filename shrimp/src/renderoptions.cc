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

#include "renderoptions.h"

#include <sdpgtk/sdpgtkevents.h>
#include <sdpgtk/sdpgtkcolorselector.h>

#include <fstream>

RenderOptions::RenderOptions()
{
	compileCommand = "slc -I" + shader_path + " %s";
	renderCommand = "rendrib -d 4 %s";
	xRes = yRes = 128;
	xPixelSamples = yPixelSamples = 1;
	colour[0] = colour[1] = colour[2] = colour[3] = 1.0;
	shape = "sphere";

	gc = 0;
	pixmap = 0;
}

bool RenderOptions::Load()
{
	sdpGtkObjectContainer::Load(guifile);

	Entry("compile").SetText(compileCommand);
	Entry("render").SetText(renderCommand);

	SpinButton("xres").SetValue(xRes);
	SpinButton("yres").SetValue(yRes);
	SpinButton("xpix").SetValue(xPixelSamples);
	SpinButton("ypix").SetValue(yPixelSamples);


	GtkWidget* colourButton = (GtkWidget*)Widget("colour");
	gtk_widget_set_events(colourButton, GDK_EXPOSURE_MASK | GDK_BUTTON_PRESS_MASK);

	for(int i = 0; i < 4; i++)
		new_colour[i] = colour[i];

	new_shape = shape;
	updateShape();

	RootWidget().Show();
	return true;
}

void RenderOptions::OnEvent(sdpGtkEvent* event)
{
	if(event->Name() == "oncolourpressevent")
		OnColourPressEvent();
	else if(event->Name() == "oncolourconfigureevent")
		OnColourConfigureEvent();
	else if(event->Name() == "oncolourexposeevent")
		OnColourExposeEvent(event);
	else if(event->Name() == "onsetdefaults")
		setDefaults();
	else if(event->Name().size() > 7 &&
			event->Name().left(7) == "onshape")
		OnShapeChange(event->Name());
	else
		ModalDialog::OnEvent(event);
}

void RenderOptions::OnOK()
{
	compileCommand = Entry("compile").GetText();
	renderCommand = Entry("render").GetText();

	SpinButton("xres").GetValue(xRes);
	SpinButton("yres").GetValue(yRes);
	SpinButton("xpix").GetValue(xPixelSamples);
	SpinButton("ypix").GetValue(yPixelSamples);

	shape = new_shape;

	for(int i = 0; i < 4; i++)
		colour[i] = new_colour[i];

	ModalDialog::OnOK();
}

void RenderOptions::OnShapeChange(std::string name)
{
	sdpString name2(name);
	new_shape = name2.right(name2.length() - 7);
}

void RenderOptions::OnColourPressEvent()
{
	sdpVector3 col(new_colour);
	sdpGtkColorSelector cs("Colour Selection", col);
	cs.DoModal();
	if(cs.OK())
	{
		col = cs.Color();
		for(int i = 0; i < 3; i++)
			new_colour[i] = col[i];
		updateColour();
	}
}

void RenderOptions::OnColourConfigureEvent()
{
	GtkWidget* col = static_cast<GtkWidget*>(Widget("colour"));

	if(gc == 0)
	{
		GdkWindow* win = gtk_widget_get_parent_window(col);
		gc = gdk_gc_new(win);
	}

	if(pixmap)
		gdk_pixmap_unref(pixmap);

	pixmap = gdk_pixmap_new(col->window, col->allocation.width, col->allocation.height, -1);

	drawColour();
}

void RenderOptions::OnColourExposeEvent(sdpGtkEvent* event)
{
	sdpGtkEventWidgetExposeEvent* gtkEvent =
		static_cast<sdpGtkEventWidgetExposeEvent*>(event);

	GdkEventExpose* e = (GdkEventExpose*)gtkEvent->Event();

	GtkWidget* col = (GtkWidget*)Widget("colour");
	gdk_draw_pixmap(col->window, gc, pixmap,
					e->area.x, e->area.y,
					e->area.x, e->area.y,
					e->area.width, e->area.height);
}

void RenderOptions::drawColour()
{
	GtkWidget* col = static_cast<GtkWidget*>(Widget("colour"));
	guint32 c;
	c = (int)(255*new_colour[0]);
	c *= 256;
	c |= (int)(255*new_colour[1]);
	c *= 256;
	c |= (int)(255*new_colour[2]);

	gdk_rgb_gc_set_foreground(gc, c);
	gdk_draw_rectangle(pixmap, gc, TRUE, 0, 0,
						col->allocation.width,
						col->allocation.height);
}

void RenderOptions::updateColour()
{
	drawColour();

	GtkWidget* col = static_cast<GtkWidget*>(Widget("colour"));

	GdkRectangle area;
	area.x = area.y = 0;
	area.width = col->allocation.width;
	area.height = col->allocation.height;
	gtk_widget_draw(col, &area);
}

void RenderOptions::updateShape()
{
	if(new_shape == "sphere")
		OptionMenu("shape").SetHistory(0);
	else if(new_shape == "cylinder")
		OptionMenu("shape").SetHistory(1);
	else if(new_shape == "cube")
		OptionMenu("shape").SetHistory(2);
	else if(new_shape == "cone")
		OptionMenu("shape").SetHistory(3);
	else if(new_shape == "plane")
		OptionMenu("shape").SetHistory(4);
}

void RenderOptions::setDefaults()
{
	std::string compile = "slc -I" + shader_path + " %s";
	std::string render = "rendrib -d 4 %s";

	Entry("compile").SetText(compile);
	Entry("render").SetText(render);

	SpinButton("xres").SetValue(128);
	SpinButton("yres").SetValue(128);
	SpinButton("xpix").SetValue(1);
	SpinButton("ypix").SetValue(1);

	new_colour[0] = new_colour[1] = new_colour[2] = new_colour[3] = 1.0;
	new_shape = "sphere";

	updateColour();
	updateShape();
}

void RenderOptions::writeRIB(std::string filename, std::string name, std::string type)
{
	std::ofstream file(filename.c_str());

	file << "#Shrimp test file\n";
	file << "Format " + sdpToString<int>(xRes) + " " + sdpToString<int>(yRes) + " 1\n";
	file << "PixelSamples " + sdpToString<int>(xPixelSamples) + " " + sdpToString<int>(yPixelSamples) + "\n";
	file << "ShadingRate 2\nFrameBegin 1\n";

	std::string tmpdir = sdpGetTempDirectory();
	std::string tmptif = sdpAppendPath(tmpdir.c_str(), "preview.tif");

	file << "Display \"" + tmptif + "\" \"file\" \"rgb\"\n";
	file << "Projection \"perspective\" \"fov\" 40\n";
	file << "WorldBegin\n";
	file << "LightSource \"ambientlight\" 0 \"intensity\" [ 0.15 ] \"lightcolor\" [1 1 1]\n";
	file << "LightSource \"distantlight\" 1 \"intensity\" [ 1.3 ] \"lightcolor\" [ 1 1 1 ] \"from\" [ -1 1 -1 ] \"to\" [ 0 0 0 ]\n";
	file << "LightSource \"distantlight\" 2 \"intensity\" [ 0.65 ] \"lightcolor\" [ 1 1 1 ] \"from\" [ 1 1 1 ] \"to\" [ 0 0 0 ]\n";
	file << "LightSource \"distantlight\" 3 \"intensity\" [ 0.59 ] \"lightcolor\" [ 1 1 1 ] \"from\" [ 1 -1 -1 ] \"to\" [ 0 0 0 ]\n";

	if(type == "surface")
	{
		file << "Surface \"" + name + "\"\n";
	}
	else if(type == "displacement")
	{
		file << "Surface \"plastic\"\n";
		file << "Displacement \"" + name + "\"\n";
		file << "Attribute \"render\" \"truedisplacement\" 1\n";
		file << "Attribute \"displacementbound\" \"sphere\" 0.5\n";
		file << "Attribute \"render\" \"patch_multiplier\" 1.0\n";
	}

	file << "Color [ " + sdpToString<double>(colour[0]) + " " +
						sdpToString<double>(colour[1]) + " " +
						sdpToString<double>(colour[2]) + " ]\n";

	file << "Translate 0 0 3\n";
	if(shape == "sphere")
	{
		file << "Rotate -90 1 0 0\n";
		file << "Sphere 0.8 -0.8 0.8 360\n";
	}
	else if(shape == "cylinder")
	{
		file << "Rotate -90 1 0 0\n";
		file << "Cylinder 0.5 -0.8 0.8 360\n";
	}
	else if(shape == "cube")
	{
		file << "Rotate -30 1 0 0\n";
		file << "Rotate 30 0 1 0\n";
		file << "PointsPolygons[4 4 4 4 4 4] [0 4 5 1 1 5 6 2 2 6 7 3 3 7 4 0 0 1 2 3 7 6 5 4]\n";
		file << "\t\"P\"[-0.6 0.6 -0.6 0.6 0.6 -0.6 0.6 0.6 0.6 -0.6 0.6 0.6 -0.6 -0.6 -0.6 0.6 -0.6 -0.6 0.6 -0.6 0.6 -0.6 -0.6 0.6]\n";
	}
	else if(shape == "cone")
	{
		file << "Translate 0 -0.8 0\n";
		file << "Rotate -90 1 0 0\n";
		file << "Cone 1.8 0.6 360\n";
	}
	else if(shape == "plane")
	{
		file << "Scale 2 2 2\n";
		file << "PointsPolygons[4] [ 0 1 2 3 ]\n";
		file << "\t\"P\"[ -0.5 -0.5 0 0.5 -0.5 0 0.5 0.5 0 -0.5 0.5 0 ]\n";
	}

	file << "WorldEnd\n";
	file << "FrameEnd\n";

	file.close();
}

void RenderOptions::readPrefs(sdpxml::Element* renderprefs)
{
	for(sdpxml::AttributeCollection::iterator attr = renderprefs->Attributes().begin(); attr != renderprefs->Attributes().end(); attr++)
	{
		if(attr->Name() == "resolution")
		{
			sdpVector2 res = sdpxml::GetAttribute(*renderprefs, "resolution", sdpVector2(0, 0));
			xRes = (int)res[0];
			yRes = (int)res[1];
		}
		else if(attr->Name() == "pixelres")
		{
			sdpVector2 res = sdpxml::GetAttribute(*renderprefs, "pixelres", sdpVector2(0, 0));
			xPixelSamples = (int)res[0];
			yPixelSamples = (int)res[1];
		}
		else if(attr->Name() == "colour")
		{
			sdpVector3 col = sdpxml::GetAttribute(*renderprefs, "colour", sdpVector3(0, 0, 0));
			colour[0] = (double)col[0];
			colour[1] = (double)col[1];
			colour[2] = (double)col[2];
		}
		else if(attr->Name() == "shape")
			shape = attr->Value();
		else if(attr->Name() == "compile")
			compileCommand = attr->Value();
		else if(attr->Name() == "render")
			renderCommand = attr->Value();
	}
}

void RenderOptions::writePrefs(sdpxml::Element& renderprefs)
{
	renderprefs.Attributes().push_back(sdpxml::Attribute("resolution", std::string(sdpToString<int>(xRes)) + " " + std::string(sdpToString<int>(yRes))));
	renderprefs.Attributes().push_back(sdpxml::Attribute("pixelres", std::string(sdpToString<int>(xPixelSamples)) + " " + std::string(sdpToString<int>(yPixelSamples))));
	renderprefs.Attributes().push_back(sdpxml::Attribute("colour", std::string(sdpToString<double>(colour[0])) + " " + std::string(sdpToString<double>(colour[1])) + " " + std::string(sdpToString<double>(colour[2]))));
	renderprefs.Attributes().push_back(sdpxml::Attribute("shape", shape));
	renderprefs.Attributes().push_back(sdpxml::Attribute("compile", compileCommand));
	renderprefs.Attributes().push_back(sdpxml::Attribute("render", renderCommand));
}


