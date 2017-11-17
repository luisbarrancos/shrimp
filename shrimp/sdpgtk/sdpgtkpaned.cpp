
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

#include "sdpgtkpaned.h"
#include "sdpgtkutility.h"

#include <iostream>

////////////////////////////////////////////////////////////////////////////////////////
// sdpGtkPaned

sdpGtkPaned::sdpGtkPaned() : sdpGtkContainer()
{
	m_ChildCount = 0;
}

sdpGtkPaned::sdpGtkPaned(GtkPaned* Paned) : sdpGtkContainer(GTK_CONTAINER(Paned))
{
	m_ChildCount = 0;
}

void sdpGtkPaned::SetHandleSize(guint16 HandleSize)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_paned_set_handle_size(*this, HandleSize);
}

void sdpGtkPaned::SetGutterSize(guint16 GutterSize)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_paned_set_gutter_size(*this, GutterSize);
}

void sdpGtkPaned::SetPosition(gint Position)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_paned_set_position(*this, Position);
}

void sdpGtkPaned::AddTopLeft(GtkWidget* Widget)
{
	// Sanity checks ...
	g_assert(Widget);
	g_return_if_fail(Attached());

	gtk_paned_add1(*this, Widget);
}

void sdpGtkPaned::AddBottomRight(GtkWidget* Widget)
{
	// Sanity checks ...
	g_assert(Widget);
	g_return_if_fail(Attached());

	gtk_paned_add2(*this, Widget);
}

void sdpGtkPaned::PackTopLeft(GtkWidget* Widget, bool Resize, bool Shrink)
{
	// Sanity checks ...
	g_assert(Widget);
	g_return_if_fail(Attached());

	gtk_paned_pack1(*this, Widget, Resize, Shrink);
}

void sdpGtkPaned::PackBottomRight(GtkWidget* Widget, bool Resize, bool Shrink)
{
	// Sanity checks ...
	g_assert(Widget);
	g_return_if_fail(Attached());

	gtk_paned_pack2(*this, Widget, Resize, Shrink);
}

bool sdpGtkPaned::CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), false);

	// Handle ...
	const gushort handle = sdpxml::GetAttribute(Element, "handle", 5);
	sdpGtkMarkAttribute(Document, Element, "handle");
	SetHandleSize(handle);

	// Gutter ...
	const gushort gutter = sdpxml::GetAttribute(Element, "gutter", 5);
	sdpGtkMarkAttribute(Document, Element, "gutter");
	SetGutterSize(gutter);

	// Call the base-class implementation ...
	return sdpGtkContainer::CreateOptions(ObjectContainer, Document, Element);
}

bool sdpGtkPaned::AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child)
{
	// Sanity checks ...
	g_assert(Child);

	// Should the child be resized with the paned?
	const bool resize = sdpxml::GetAttribute(ChildElement, "resize", true);
	sdpGtkMarkAttribute(Document, ChildElement, "resize");
	
	// Should the child be shrunk below a minimum size?
	const bool shrink = sdpxml::GetAttribute(ChildElement, "shrink", false);
	sdpGtkMarkAttribute(Document, ChildElement, "shrink");

	// Figure out which pane to add this child to ...
	if(0 == m_ChildCount)
		PackTopLeft(GTK_WIDGET(Child->Object()), resize, shrink);
	else if(1 == m_ChildCount)
		PackBottomRight(GTK_WIDGET(Child->Object()), resize, shrink);
	else
		std::cout << "sdpGtk: tried to add too many children to <hpaned> or <vpaned> ... excess children will be ignored" << std::endl;

	m_ChildCount++;

	return true;
}


