
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



#include "sdpgtkcombo.h"


////////////////////////////////////////////////////////////////////////////////////////
// sdpGtkCombo

sdpGtkCombo::sdpGtkCombo() : sdpGtkHBox()
{
}

sdpGtkCombo::sdpGtkCombo(GtkCombo* Combo) : sdpGtkHBox(GTK_HBOX(Combo))
{
}

bool sdpGtkCombo::Create()
{
	m_Object = GTK_OBJECT(gtk_combo_new());
	return Attached();
}

bool sdpGtkCombo::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	return Create();
}

sdpGtkEntry sdpGtkCombo::Entry()
{
	return sdpGtkEntry(GTK_ENTRY(GTK_COMBO(m_Object)->entry));
}

void sdpGtkCombo::SetEntryText(SDPCSTRING Text)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	g_assert(Text);

	Entry().SetText(Text);
}

SDPCSTRING sdpGtkCombo::GetEntryText()
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return Entry().GetText();
}

void sdpGtkCombo::SetList(sdpStringArray& List)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	GList* glist = 0;
	for(sdpStringArray::iterator i = List.begin(); i != List.end(); i++)
		glist = g_list_append(glist, (void*)(i->c_str()));

	SetList(glist);
}

void sdpGtkCombo::SetList(GList* List)
{
	// Sanity checks ...
	g_assert(List);
	g_return_if_fail(Attached());

	gtk_combo_set_popdown_strings(*this, List) ;
}

