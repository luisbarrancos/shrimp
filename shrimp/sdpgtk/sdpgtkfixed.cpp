
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


#include "sdpgtkfixed.h"
#include "sdpgtkutility.h"

sdpGtkFixed::sdpGtkFixed() : sdpGtkContainer()
{
}

sdpGtkFixed::sdpGtkFixed(GtkFixed* Fixed) : sdpGtkContainer(GTK_CONTAINER(Fixed))
{
}

bool sdpGtkFixed::Create()
{
	m_Object = GTK_OBJECT(gtk_fixed_new());
	return Attached();
}

bool sdpGtkFixed::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	// Create the widget ...
	return Create();
}

bool sdpGtkFixed::AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child)
{
	const sdpVector2 position = sdpxml::GetAttribute(ChildElement, "position", sdpVector2(0.0, 0.0));
	sdpGtkMarkAttribute(Document, ChildElement, "position");

	Attach(GTK_WIDGET(Child->Object()), gint(position[0]), gint(position[1]));
	return true;
}

void sdpGtkFixed::Attach(GtkWidget* Widget, gint16 X, gint16 Y)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	g_assert(Widget);

	gtk_fixed_put(*this, Widget, X, Y);
}

void sdpGtkFixed::Move(GtkWidget* Widget, gint16 X, gint16 Y)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	g_assert(Widget);

	gtk_fixed_move(*this, Widget, X, Y);
}
