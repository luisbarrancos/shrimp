
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

#include "sdpgtklabel.h"
#include "sdpgtkutility.h"

/////////////////////////////////////////////////////////////////////////////
// sdpGtkLabel

sdpGtkLabel::sdpGtkLabel() : sdpGtkMisc()
{
}

sdpGtkLabel::sdpGtkLabel(GtkLabel* Label) : sdpGtkMisc(GTK_MISC(Label))
{
}

bool sdpGtkLabel::Create(SDPCSTRING Text)
{
	// Sanity checks ...
	g_assert(Text);

	m_Object = GTK_OBJECT(gtk_label_new(Text));
	return Attached();
}

bool sdpGtkLabel::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	return Create(sdpGtkInternationalText(Document, Element));
}

void sdpGtkLabel::SetText(sdpString Text)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	g_assert(Text);

	gtk_label_set_text(*this, Text);
}

void sdpGtkLabel::SetLineWrap(bool Wrap)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_label_set_line_wrap(*this, Wrap);
}


