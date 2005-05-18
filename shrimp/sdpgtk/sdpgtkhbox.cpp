
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

#include "sdpgtkhbox.h"
#include "sdpgtkutility.h"

////////////////////////////////////////////////////////////////////////////////////////
// sdpGtkHBox

sdpGtkHBox::sdpGtkHBox() : sdpGtkBox()
{
}

sdpGtkHBox::sdpGtkHBox(GtkHBox* HBox) : sdpGtkBox(GTK_BOX(HBox))
{
}

bool sdpGtkHBox::Create(bool Homogenous, gint Spacing)
{
	m_Object = GTK_OBJECT(gtk_hbox_new(Homogenous, Spacing));
	return Attached();
}

bool sdpGtkHBox::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	return Create(true, 0);
}


