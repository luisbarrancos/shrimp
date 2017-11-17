
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

#include "sdpgtkframe.h"
#include "sdpgtkutility.h"

sdpGtkFrame::sdpGtkFrame() : sdpGtkBin()
{
}

sdpGtkFrame::sdpGtkFrame(GtkFrame* Frame) : sdpGtkBin(GTK_BIN(Frame))
{
}

bool sdpGtkFrame::Create()
{
	m_Object = GTK_OBJECT(gtk_frame_new(0));
	return Attached();
}

bool sdpGtkFrame::Create(SDPCSTRING Label)
{
	// Sanity checks ...
	g_assert(Label);

	m_Object = GTK_OBJECT(gtk_frame_new(Label));
	return Attached();
}

bool sdpGtkFrame::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	// Create the control ...
	const sdpString text(sdpGtkInternationalText(Document, Element));
	return text.size() ? Create(text) : Create();
}

bool sdpGtkFrame::CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Alignment ...
	const sdpVector2 labelalignment = sdpxml::GetAttribute(Element, "labelalignment", sdpVector2(0.0, 0.0));
	sdpGtkMarkAttribute(Document, Element, "labelalignment");
	SetLabelAlignment(labelalignment[0], labelalignment[1]);

	// Shadow type ...
	SetShadowType(sdpGtkGetShadowType(Document, Element, GTK_SHADOW_ETCHED_IN));

	return sdpGtkBin::CreateOptions(ObjectContainer, Document, Element);
}

void sdpGtkFrame::SetLabel(SDPCSTRING Label)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_frame_set_label(*this, Label);
}

void sdpGtkFrame::SetLabelAlignment(gdouble Horizontal, gdouble Vertical)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_frame_set_label_align(*this, gfloat(Horizontal), gfloat(Vertical));
}

void sdpGtkFrame::SetShadowType(GtkShadowType ShadowType)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_frame_set_shadow_type(*this, ShadowType);
}
