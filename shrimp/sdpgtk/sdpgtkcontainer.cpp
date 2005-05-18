
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

#include "sdpgtkcontainer.h"
#include "sdpgtkutility.h"

sdpGtkContainer::sdpGtkContainer() : sdpGtkWidget()
{
}

sdpGtkContainer::sdpGtkContainer(GtkContainer* Container) : sdpGtkWidget(GTK_WIDGET(Container))
{
}

bool sdpGtkContainer::CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);
	
	const gint border_width = sdpxml::GetAttribute(Element, "border-width", 0);
	sdpGtkMarkAttribute(Document, Element, "border-width");
	SetBorderWidth(border_width);
	
	return sdpGtkWidget::CreateOptions(ObjectContainer, Document, Element);
}

void sdpGtkContainer::Attach(GtkWidget* Widget)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_container_add(*this, Widget);
}

void sdpGtkContainer::Attach(sdpGtkWidget& Widget)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	Attach((GtkWidget*)Widget);
}

void sdpGtkContainer::Remove(GtkWidget* Widget)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_container_remove(*this, Widget);
}

void sdpGtkContainer::Remove(sdpGtkWidget& Widget)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	Remove((GtkWidget*)Widget);
}

void sdpGtkContainer::SetBorderWidth(guint BorderWidth)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_container_set_border_width(*this, BorderWidth);
}

bool sdpGtkContainer::AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), false);

	g_assert(Child);

	Attach(GTK_WIDGET(Child->Object()));

	return true;
}
