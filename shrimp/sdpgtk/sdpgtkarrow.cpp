
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

#include "sdpgtkarrow.h"
#include "sdpgtkutility.h"
#include <iostream>

///////////////////////////////////////////////////////////////////////
// sdpGtkArrow

sdpGtkArrow::sdpGtkArrow() : sdpGtkMisc()
{
}

sdpGtkArrow::sdpGtkArrow(GtkArrow* Arrow) : sdpGtkMisc(GTK_MISC(Arrow))
{
}

bool sdpGtkArrow::Create(GtkArrowType ArrowType, GtkShadowType ShadowType)
{
	m_Object = GTK_OBJECT(gtk_arrow_new(ArrowType, ShadowType));
	return Attached();
}

bool sdpGtkArrow::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	// Arrow direction (required) ...
	const sdpString directiontext = sdpxml::GetAttribute<sdpString>(Element, "direction", "up");
	sdpGtkMarkAttribute(Document, Element, "direction");

	GtkArrowType direction = GTK_ARROW_UP;
	if(directiontext == "up")
		direction = GTK_ARROW_UP;
	else if(directiontext == "down")
		direction = GTK_ARROW_DOWN;
	else if(directiontext == "left")
		direction = GTK_ARROW_LEFT;
	else if(directiontext == "right")
		direction = GTK_ARROW_RIGHT;
	else
		std::cout << "Attribute [direction] contains unknown value at " << sdpxml::FileReference(Document, Element) << std::endl;

	return Create(direction, sdpGtkGetShadowType(Document, Element, GTK_SHADOW_ETCHED_IN));
}

void sdpGtkArrow::Set(GtkArrowType ArrowType, GtkShadowType ShadowType)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_arrow_set(*this, ArrowType, ShadowType);
}

