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

#include <sdpgtk/sdpgtkevents.h>
#include <sdpgtk/sdpgtkcolorselector.h>

#include "ioproperties.h"

IOProperties::IOProperties(IOPad* p)
{
	pad = p;
	new_type = pad->getType();

	gc = 0;
	pixmap = 0;
}

bool IOProperties::Load()
{
	sdpGtkObjectContainer::Load(guifile);

	Label("name").SetText(pad->getName());
	Label("desc").SetLineWrap(true);
	Label("desc").SetText(pad->getDesc());

	std::string type = pad->getType();
	if(type == "float")
		OptionMenu("typemenu").SetHistory(0);
	else if(type == "point")
		OptionMenu("typemenu").SetHistory(1);
	else if(type == "vector")
		OptionMenu("typemenu").SetHistory(2);
	else if(type == "normal")
		OptionMenu("typemenu").SetHistory(3);
	else if(type == "color")
		OptionMenu("typemenu").SetHistory(4);
	else if(type == "string")
		OptionMenu("typemenu").SetHistory(5);

	if(!pad->supportsType("float"))
		Widget("float").Hide();
	if(!pad->supportsType("point"))
		Widget("point").Hide();
	if(!pad->supportsType(std::string("vector")))
		Widget("vector").Hide();
	if(!pad->supportsType(std::string("normal")))
		Widget("normal").Hide();
	if(!pad->supportsType(std::string("color")))
		Widget("color").Hide();
	if(!pad->supportsType(std::string("string")))
		Widget("string").Hide();

	if(pad->isInput())
	{
		InputPad* in = (InputPad*) pad;
		Widget("inputonly").SetSensitive(in->isConnectable());
		decoded_val = in->getDecodedValue();
		setVectorValue(decoded_val);
		Entry("stringval").SetText(in->getStringValue());
		if(in->usesStringValue())
		{
			CheckButton("usesstring").SetState(true);
			Widget("decodedval").SetSensitive(false);
		}
		else
		{
			CheckButton("usesstring").SetState(false);
			Widget("stringval").SetSensitive(false);
		}

		setSensitivity(in->getType());

		GtkWidget* colourButton = (GtkWidget*)Widget("colour");
		gtk_widget_set_events(colourButton, GDK_EXPOSURE_MASK | GDK_BUTTON_PRESS_MASK);

		CheckButton("shadervar").SetState(in->isShaderVar());
	}
	else
		Widget("inputonly").Hide();

	RootWidget().Show();
	return true;
}

void IOProperties::OnEvent(sdpGtkEvent* event)
{
	if(event->Name() == "onusestringtoggle")
		OnUseStringToggle();
	else if(event->Name() == "oncolourpressevent")
		OnColourPressEvent();
	else if(event->Name() == "oncolourconfigureevent")
		OnColourConfigureEvent();
	else if(event->Name() == "oncolourexposeevent")
		OnColourExposeEvent(event);
	else if(event->Name().size() > 6 && event->Name().left(6) == "ontype")
		OnTypeChange(event->Name());
	else
		ModalDialog::OnEvent(event);
}

void IOProperties::OnTypeChange(std::string name)
{
	//remove first 6 characters
	sdpString name2(name);
	new_type = name2.right(name2.length() - 6);
	setSensitivity(new_type);
	setVectorValue(decoded_val);
}

void IOProperties::OnUseStringToggle()
{
	if(CheckButton("usesstring").GetState())
	{
		Widget("stringval").SetSensitive(true);
		Widget("decodedval").SetSensitive(false);
	}
	else
	{
		Widget("decodedval").SetSensitive(true);
		Widget("stringval").SetSensitive(false);
	}
}

void IOProperties::OnOK()
{
	//do nothing if fail.
	pad->changeType(new_type);

	if(pad->isInput())
	{
		InputPad* in = (InputPad*) pad;
		if(CheckButton("usesstring").GetState())
		{
			in->usesStringValue(true);
			in->setStringValue(std::string(Entry("stringval").GetText()));
		}
		else
		{
			in->usesStringValue(false);
			getVectorValue(decoded_val);
			in->setDecodedValue(decoded_val);
		}

		in->setShaderVar(CheckButton("shadervar").GetState());
	}

	ModalDialog::OnOK();
}

void IOProperties::OnColourPressEvent()
{
	if(CheckButton("usesstring").GetState())
		return;

	sdpVector3 col(decoded_val);
	sdpGtkColorSelector cs("Colour Selection", col);
	cs.DoModal();
	if(cs.OK())
	{
		col = cs.Color();
		for(int i=0; i<3; i++)
			decoded_val[i] = col[i];
		updateColour();
		setVectorValue(decoded_val);
	}
}

void IOProperties::OnColourConfigureEvent()
{
	GtkWidget* col = (GtkWidget*)Widget("colour");
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

void IOProperties::OnColourExposeEvent(sdpGtkEvent* event)
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

void IOProperties::drawColour()
{
	GtkWidget* col = (GtkWidget*)Widget("colour");
	guint32 c;
	c = (int)(255*decoded_val[0]);
	c *= 256;
	c |= (int)(255*decoded_val[1]);
	c *= 256;
	c |= (int)(255*decoded_val[2]);

	gdk_rgb_gc_set_foreground(gc, c);
	gdk_draw_rectangle(pixmap, gc, TRUE, 0, 0,
						col->allocation.width,
						col->allocation.height);
}

void IOProperties::updateColour()
{
	drawColour();

	GtkWidget* col = (GtkWidget*)Widget("colour");
	GdkRectangle area;
	area.x = area.y = 0;
	area.width = col->allocation.width;
	area.height = col->allocation.height;
	gtk_widget_draw(col, &area);
}

void IOProperties::setSensitivity(std::string type)
{
	if(type == "string")
	{
		Widget("decodedval").SetSensitive(false);
		Widget("stringval").SetSensitive(true);
	}
	else if(type == "float")
	{
		Widget("vectorvalue").Show();
		Widget("xinput").SetSensitive(true);
		Widget("yinput").SetSensitive(false);
		Widget("zinput").SetSensitive(false);
		Widget("colourinput").Hide();
	}
	else if(type == "color")
	{
		Widget("colourinput").Show();
		Widget("vectorvalue").Hide();
	}
	else
	{
		Widget("vectorvalue").Show();
		Widget("xinput").SetSensitive(true);
		Widget("yinput").SetSensitive(true);
		Widget("zinput").SetSensitive(true);
		Widget("colourinput").Hide();
	}
}

void IOProperties::setVectorValue(sdpVector3 v)
{
	SpinButton("xvalue").SetValue(v[0]);
	SpinButton("yvalue").SetValue(v[1]);
	SpinButton("zvalue").SetValue(v[2]);
}

void IOProperties::getVectorValue(sdpVector3& v)
{
	SpinButton("xvalue").GetValue(v[0]);
	SpinButton("yvalue").GetValue(v[1]);
	SpinButton("zvalue").GetValue(v[2]);
}


