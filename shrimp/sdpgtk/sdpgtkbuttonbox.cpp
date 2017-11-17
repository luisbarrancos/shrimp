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

/** \file
	\author Timothy M. Shead <tshead@k-3d.com>
	\author Dan Erikson <derikson@montana.com>
*/

#include "sdpgtkbuttonbox.h"
#include "sdpgtkutility.h"


////////////////////////////////////////////////////////////////////////////////////////
// sdpGtkButtonBox

sdpGtkButtonBox::sdpGtkButtonBox() : sdpGtkBox()
{
}

sdpGtkButtonBox::sdpGtkButtonBox(GtkButtonBox* ButtonBox) : sdpGtkBox(GTK_BOX(ButtonBox))
{
}

bool sdpGtkButtonBox::CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	// Layout ...
	const sdpString layouttext = sdpxml::GetAttribute<sdpString>(Element, "layout", "spread");
	sdpGtkMarkAttribute(Document, Element, "layout");
	
	GtkButtonBoxStyle layout = GTK_BUTTONBOX_SPREAD;
	if(layouttext == "spread")
		layout = GTK_BUTTONBOX_SPREAD;
	else if(layouttext == "edge")
		layout = GTK_BUTTONBOX_EDGE;
	else if(layouttext == "start")
		layout = GTK_BUTTONBOX_START;
	else if(layouttext == "end")
		layout = GTK_BUTTONBOX_END;
	else
		g_return_val_if_fail(0, false);

	SetLayout(layout);

	// Child padding ...
	const sdpVector2 childpadding = sdpxml::GetAttribute(Element, "childpadding", sdpVector2(0.0, 0.0));
	sdpGtkMarkAttribute(Document, Element, "childpadding");
	SetChildPadding(gint(childpadding[0]), gint(childpadding[1]));

	return sdpGtkBox::CreateOptions(ObjectContainer, Document, Element);
}

void sdpGtkButtonBox::GetChildSize(gint* MinWidth, gint* MinHeight)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_button_box_get_child_size(*this, MinWidth, MinHeight);
}

void sdpGtkButtonBox::SetChildSize(gint MinWidth, gint MinHeight)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_button_box_set_child_size(*this, MinWidth, MinHeight);
}

void sdpGtkButtonBox::GetChildPadding(gint* PadX, gint* PadY)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_button_box_get_child_ipadding(*this, PadX, PadY);
}

void sdpGtkButtonBox::SetChildPadding(gint PadX, gint PadY)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_button_box_set_child_ipadding(*this, PadX, PadY);
}

gint sdpGtkButtonBox::GetSpacing()
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), -1);

	return gtk_button_box_get_spacing(*this);
}

void sdpGtkButtonBox::SetSpacing(gint Spacing)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_button_box_set_spacing(*this, Spacing);
}

GtkButtonBoxStyle sdpGtkButtonBox::GetLayout()
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), GtkButtonBoxStyle(-1));

	return gtk_button_box_get_layout(*this);
}

void sdpGtkButtonBox::SetLayout(GtkButtonBoxStyle Style)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_button_box_set_layout(*this, Style);
}


