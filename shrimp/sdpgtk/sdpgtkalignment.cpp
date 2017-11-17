
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



#include "sdpgtkalignment.h"
#include "sdpgtkutility.h"

sdpGtkAlignment::sdpGtkAlignment() : sdpGtkBin()
{
}

sdpGtkAlignment::sdpGtkAlignment(GtkAlignment* Alignment) : sdpGtkBin(GTK_BIN(Alignment))
{
}

bool sdpGtkAlignment::Create(gfloat XAlign, gfloat YAlign, gfloat XScale, gfloat YScale)
{
	m_Object = GTK_OBJECT(gtk_alignment_new(XAlign, YAlign, XScale, YScale));
	return Attached();
}

bool sdpGtkAlignment::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	// Get attributes ...
	const gfloat xalign = sdpxml::GetAttribute(Element, "xalign", 0.5);
	sdpGtkMarkAttribute(Document, Element, "xalign");

	const gfloat yalign = sdpxml::GetAttribute(Element, "yalign", 0.5);
	sdpGtkMarkAttribute(Document, Element, "yalign");

	const gfloat xscale = sdpxml::GetAttribute(Element, "xscale", 1.0);
	sdpGtkMarkAttribute(Document, Element, "xscale");

	const gfloat yscale = sdpxml::GetAttribute(Element, "yscale", 1.0);
	sdpGtkMarkAttribute(Document, Element, "yscale");

	// Create the control ...
	return Create(xalign, yalign, xscale, yscale);
}

void sdpGtkAlignment::SetAlignment(gfloat XAlign, gfloat YAlign, gfloat XScale, gfloat YScale)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_alignment_set(*this, XAlign, YAlign, XScale, YScale);
}
