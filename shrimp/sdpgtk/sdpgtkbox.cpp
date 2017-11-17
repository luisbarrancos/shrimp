
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



#include "sdpgtkbox.h"
#include "sdpgtkutility.h"


////////////////////////////////////////////////////////////////////////////////////////
// sdpGtkBox

sdpGtkBox::sdpGtkBox() : sdpGtkContainer()
{
}

sdpGtkBox::sdpGtkBox(GtkBox* Box) : sdpGtkContainer(GTK_CONTAINER(Box))
{
}

bool sdpGtkBox::CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	const bool homogeneous = sdpxml::GetAttribute(Element, "homogeneous", true);
	sdpGtkMarkAttribute(Document, Element, "homogeneous");
	SetHomogeneous(homogeneous);

	const gint spacing = sdpxml::GetAttribute(Element, "spacing", 0);
	sdpGtkMarkAttribute(Document, Element, "spacing");
	SetSpacing(spacing);

	return sdpGtkContainer::CreateOptions(ObjectContainer, Document, Element);
}

void sdpGtkBox::PackStart(GtkWidget* Widget, bool Expand, bool Fill, guint Padding)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_box_pack_start(*this, Widget, Expand, Fill, Padding);
}

void sdpGtkBox::PackEnd(GtkWidget* Widget, bool Expand, bool Fill, guint Padding)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_box_pack_end(*this, Widget, Expand, Fill, Padding);
}

void sdpGtkBox::SetHomogeneous(bool Homogeneous)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_box_set_homogeneous(*this, Homogeneous);
}

void sdpGtkBox::SetSpacing(gint Spacing)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_box_set_spacing(*this, Spacing);
}

bool sdpGtkBox::AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), false);
	g_assert(Child);

	const sdpString pack = sdpxml::GetAttribute<sdpString>(ChildElement, "pack", "start");
	sdpGtkMarkAttribute(Document, ChildElement, "pack");

	const bool expand = sdpxml::GetAttribute(ChildElement, "expand", false);
	sdpGtkMarkAttribute(Document, ChildElement, "expand");

	const bool fill = sdpxml::GetAttribute(ChildElement, "fill", false);
	sdpGtkMarkAttribute(Document, ChildElement, "fill");

	const gint padding = sdpxml::GetAttribute(ChildElement, "padding", 0);
	sdpGtkMarkAttribute(Document, ChildElement, "padding");

	if(pack == "start")
		PackStart(GTK_WIDGET(Child->Object()), expand, fill, padding);
	else if(pack == "end")
		PackEnd(GTK_WIDGET(Child->Object()), expand, fill, padding);
	else
		g_return_val_if_fail(0, false);

	return true;
}


