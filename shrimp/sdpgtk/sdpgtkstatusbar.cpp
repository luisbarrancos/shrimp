
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



#include "sdpgtkstatusbar.h"


////////////////////////////////////////////////////////////////////////////////////////
// sdpGtkStatusbar

sdpGtkStatusbar::sdpGtkStatusbar() : sdpGtkHBox()
{
}

sdpGtkStatusbar::sdpGtkStatusbar(GtkStatusbar* Statusbar) : sdpGtkHBox(GTK_HBOX(Statusbar))
{
}

bool sdpGtkStatusbar::Create()
{
	m_Object = GTK_OBJECT(gtk_statusbar_new());
	return Attached();
}

bool sdpGtkStatusbar::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	return Create();
}

guint sdpGtkStatusbar::GetContextID(SDPCSTRING Description)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return gtk_statusbar_get_context_id(*this, Description);
}

guint sdpGtkStatusbar::Push(guint ContextID, SDPCSTRING Text)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return gtk_statusbar_push(*this, ContextID, Text);
}

void sdpGtkStatusbar::Pop(guint ContextID)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_statusbar_pop(*this, ContextID);
}

void sdpGtkStatusbar::Remove(guint ContextID, guint MessageID)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_statusbar_remove(*this, ContextID, MessageID);
}


