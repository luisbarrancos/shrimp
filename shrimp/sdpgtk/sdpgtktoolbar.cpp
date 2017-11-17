
// SDPGTK Library
// Copyright © 1995-2003, Timothy M. Shead
//
// Contact: tshead@k-3d.com
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#include "sdpgtktoolbar.h"
#include "sdpgtkutility.h"

////////////////////////////////////////////////////////////////////////////////////////
// sdpGtkToolbar

sdpGtkToolbar::sdpGtkToolbar() : sdpGtkContainer()
{
}

sdpGtkToolbar::sdpGtkToolbar(GtkToolbar* Toolbar) : sdpGtkContainer(GTK_CONTAINER(Toolbar))
{
}

bool sdpGtkToolbar::Create(GtkOrientation Orientation, GtkToolbarStyle Style)
{
	m_Object = GTK_OBJECT(gtk_toolbar_new(Orientation, Style));
	return Attached();
}

bool sdpGtkToolbar::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	// Toolbar orientation ...
	const sdpString orientationtext = sdpxml::GetAttribute<sdpString>(Element, "orientation", "horizontal");
	sdpGtkMarkAttribute(Document, Element, "orientation");

	GtkOrientation orientation = GTK_ORIENTATION_HORIZONTAL;
	if(orientationtext == "horizontal")
		orientation = GTK_ORIENTATION_HORIZONTAL;
	else if(orientationtext == "vertical")
		orientation = GTK_ORIENTATION_VERTICAL;

	// Toolbar style ...
	const sdpString styletext = sdpxml::GetAttribute<sdpString>(Element, "style", "icons");
	sdpGtkMarkAttribute(Document, Element, "style");

	GtkToolbarStyle style = GTK_TOOLBAR_ICONS;
	if(styletext == "icons")
		style = GTK_TOOLBAR_ICONS;
	else if(styletext == "text")
		style = GTK_TOOLBAR_TEXT;
	else if(styletext == "both")
		style = GTK_TOOLBAR_BOTH;

	return Create(orientation, style);
}

bool sdpGtkToolbar::AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child)
{
	// Sanity checks ...
	g_assert(Child);

	const sdpString toolbartip = sdpxml::GetAttribute<sdpString>(ChildElement, "toolbartip", "");
	sdpGtkMarkAttribute(Document, ChildElement, "toolbartip");

	Append(GTK_WIDGET(Child->Object()), toolbartip, "");

	return true;
}

GtkWidget* sdpGtkToolbar::Append(SDPCSTRING Text, SDPCSTRING Tooltip, SDPCSTRING PrivateTooltip, GtkWidget* Icon, GtkSignalFunc Callback, gpointer UserData)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return gtk_toolbar_append_item(*this, Text, Tooltip, PrivateTooltip, Icon, Callback, UserData);
}

GtkWidget* sdpGtkToolbar::Append(GtkToolbarChildType Type, GtkWidget* Widget, SDPCSTRING Text, SDPCSTRING Tooltip, SDPCSTRING PrivateTooltip, GtkWidget* Icon, GtkSignalFunc Callback, gpointer UserData)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return gtk_toolbar_append_element(*this, Type, Widget, Text, Tooltip, PrivateTooltip, Icon, Callback, UserData);
}

void sdpGtkToolbar::Append(GtkWidget* Widget, SDPCSTRING Tooltip, SDPCSTRING PrivateTooltip)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_toolbar_append_widget(*this, Widget, Tooltip, PrivateTooltip);
}

void sdpGtkToolbar::AppendSpace()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_toolbar_append_space(*this);
}

GtkWidget* sdpGtkToolbar::Prepend(SDPCSTRING Text, SDPCSTRING Tooltip, SDPCSTRING PrivateTooltip, GtkWidget* Icon, GtkSignalFunc Callback, gpointer UserData)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return gtk_toolbar_prepend_item(*this, Text, Tooltip, PrivateTooltip, Icon, Callback, UserData);
}

GtkWidget* sdpGtkToolbar::Prepend(GtkToolbarChildType Type, GtkWidget* Widget, SDPCSTRING Text, SDPCSTRING Tooltip, SDPCSTRING PrivateTooltip, GtkWidget* Icon, GtkSignalFunc Callback, gpointer UserData)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return gtk_toolbar_prepend_element(*this, Type, Widget, Text, Tooltip, PrivateTooltip, Icon, Callback, UserData);
}

void sdpGtkToolbar::Prepend(GtkWidget* Widget, SDPCSTRING Tooltip, SDPCSTRING PrivateTooltip)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_toolbar_prepend_widget(*this, Widget, Tooltip, PrivateTooltip);
}

void sdpGtkToolbar::PrependSpace()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_toolbar_prepend_space(*this);
}

GtkWidget* sdpGtkToolbar::Insert(SDPCSTRING Text, SDPCSTRING Tooltip, SDPCSTRING PrivateTooltip, GtkWidget* Icon, GtkSignalFunc Callback, gpointer UserData, gint Position)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return gtk_toolbar_insert_item(*this, Text, Tooltip, PrivateTooltip, Icon, Callback, UserData, Position);
}

GtkWidget* sdpGtkToolbar::Insert(GtkToolbarChildType Type, GtkWidget* Widget, SDPCSTRING Text, SDPCSTRING Tooltip, SDPCSTRING PrivateTooltip, GtkWidget* Icon, GtkSignalFunc Callback, gpointer UserData, gint Position)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return gtk_toolbar_insert_element(*this, Type, Widget, Text, Tooltip, PrivateTooltip, Icon, Callback, UserData, Position);
}

void sdpGtkToolbar::Insert(GtkWidget* Widget, SDPCSTRING Tooltip, SDPCSTRING PrivateTooltip, gint Position)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_toolbar_insert_widget(*this, Widget, Tooltip, PrivateTooltip, Position);
}

void sdpGtkToolbar::InsertSpace(gint Position)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_toolbar_insert_space(*this, Position);
}

void sdpGtkToolbar::SetOrientation(GtkOrientation Orientation)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_toolbar_set_orientation(*this, Orientation);
}

void sdpGtkToolbar::SetStyle(GtkToolbarStyle Style)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_toolbar_set_style(*this, Style);
}

void sdpGtkToolbar::SetSpaceSize(gint SpaceSize)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_toolbar_set_space_size(*this, SpaceSize);
}

void sdpGtkToolbar::SetSpaceStyle(GtkToolbarSpaceStyle Style)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_toolbar_set_space_style(*this, Style);
}

void sdpGtkToolbar::EnableTooltips(gint Enable)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_toolbar_set_tooltips(*this, Enable);
}

void sdpGtkToolbar::SetButtonRelief(GtkReliefStyle Relief)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_toolbar_set_button_relief(*this, Relief);
}

GtkReliefStyle sdpGtkToolbar::GetButtonRelief()
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), GtkReliefStyle(-1));

	return gtk_toolbar_get_button_relief(*this);
}

