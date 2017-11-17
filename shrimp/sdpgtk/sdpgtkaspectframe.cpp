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

#include "sdpgtkaspectframe.h"
#include "sdpgtkutility.h"

sdpGtkAspectFrame::sdpGtkAspectFrame() : sdpGtkFrame()
{
}

sdpGtkAspectFrame::sdpGtkAspectFrame(GtkAspectFrame* Frame) : sdpGtkFrame(GTK_FRAME(Frame))
{
}

bool sdpGtkAspectFrame::Create(SDPCSTRING Label, gdouble XAlignment, gdouble YAlignment, gdouble Ratio, bool IgnoreRatio)
{
	// We don't assert on our label because we allow empties ...

	m_Object = GTK_OBJECT(gtk_aspect_frame_new(Label, XAlignment, YAlignment, Ratio, IgnoreRatio));
	return Attached();
}

bool sdpGtkAspectFrame::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	// X alignment ...
	const gdouble xalign = sdpxml::GetAttribute(Element, "xalign", 0.5);
	sdpGtkMarkAttribute(Document, Element, "xalign");

	// Y alignment ...
	const gdouble yalign = sdpxml::GetAttribute(Element, "yalign", 0.5);
	sdpGtkMarkAttribute(Document, Element, "yalign");

	// Ratio ...
	const gdouble ratio = sdpxml::GetAttribute(Element, "ratio", 1.0);
	sdpGtkMarkAttribute(Document, Element, "ratio");

	// Ignore ratio ...
	const bool ignoreratio = sdpxml::GetAttribute(Element, "ignoreratio", false);
	sdpGtkMarkAttribute(Document, Element, "ignoreratio");

	// Create the control ...
	return Create(sdpGtkInternationalText(Document, Element), xalign, yalign, ratio, ignoreratio);
}

void sdpGtkAspectFrame::Set(gdouble XAlignment, gdouble YAlignment, gdouble Ratio, bool IgnoreRatio)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_aspect_frame_set(*this, XAlignment, YAlignment, Ratio, IgnoreRatio);
}

