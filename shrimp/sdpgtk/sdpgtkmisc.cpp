
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

#include "sdpgtkmisc.h"
#include "sdpgtkutility.h"

//////////////////////////////////////////////////////////////////////
// sdpGtkMisc

sdpGtkMisc::sdpGtkMisc() : sdpGtkWidget()
{
}

sdpGtkMisc::sdpGtkMisc(GtkMisc* Misc) : sdpGtkWidget(GTK_WIDGET(Misc))
{
}

bool sdpGtkMisc::CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	// Alignment ...
	const sdpVector2 alignment = sdpxml::GetAttribute(Element, "alignment", sdpVector2(0.5, 0.5));
	sdpGtkMarkAttribute(Document, Element, "alignment");
	SetAlignment(alignment[0], alignment[1]);

	const sdpVector2 labelpadding = sdpxml::GetAttribute(Element, "labelpadding", sdpVector2(0.0, 0.0));
	sdpGtkMarkAttribute(Document, Element, "labelpadding");
	SetPadding(gint(labelpadding[0]), gint(labelpadding[1]));

	return sdpGtkWidget::CreateOptions(ObjectContainer, Document, Element);
}

void sdpGtkMisc::SetAlignment(gfloat XAlignment, gfloat YAlignment)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_misc_set_alignment(*this, XAlignment, YAlignment);
}

void sdpGtkMisc::SetPadding(gint XPad, gint YPad)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_misc_set_padding(*this, XPad, YPad);
}
