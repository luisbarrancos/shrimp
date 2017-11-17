
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

#include "sdpgtkdrawingarea.h"
#include "sdpgtkutility.h"

#include <iostream>

sdpGtkDrawingArea::sdpGtkDrawingArea() : sdpGtkWidget()
{
}

sdpGtkDrawingArea::sdpGtkDrawingArea(GtkDrawingArea* DrawingArea) : sdpGtkWidget(GTK_WIDGET(DrawingArea))
{
}

bool sdpGtkDrawingArea::Create()
{
	m_Object = GTK_OBJECT(gtk_drawing_area_new());
	return Attached();
}

bool sdpGtkDrawingArea::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	// Create the widget ...
	return Create();
}


bool sdpGtkDrawingArea::CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	// Handle options ...
	const gint width = sdpxml::GetAttribute(Element, "width", 0);
	sdpGtkMarkAttribute(Document, Element, "width");
	
	const gint height = sdpxml::GetAttribute(Element, "height", 0);
	sdpGtkMarkAttribute(Document, Element, "height");

	// If we have both, set sizes ...
	if(width && height)
		SetSize(width, height);

	return sdpGtkWidget::CreateOptions(ObjectContainer, Document, Element);
}

void sdpGtkDrawingArea::SetSize(gint Width, gint Height)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_drawing_area_size(*this, Width, Height);
}

