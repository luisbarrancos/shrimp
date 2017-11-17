
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

#include "sdpgtkentry.h"
#include "sdpgtkutility.h"

sdpGtkEntry::sdpGtkEntry() : sdpGtkEditable()
{
}

sdpGtkEntry::sdpGtkEntry(GtkEntry* Entry) : sdpGtkEditable(GTK_EDITABLE(Entry))
{
}

bool sdpGtkEntry::Create()
{
	m_Object = GTK_OBJECT(gtk_entry_new());
	return Attached();
}

bool sdpGtkEntry::Create(guint16 MaxLength)
{
	// Sanity checks ...
	g_assert(MaxLength);

	m_Object = GTK_OBJECT(gtk_entry_new_with_max_length(MaxLength));
	return Attached();
}

bool sdpGtkEntry::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	const gint maxlength = sdpxml::GetAttribute(Element, "maxlength", 0);
	sdpGtkMarkAttribute(Document, Element, "maxlength");

	if(maxlength)
		return Create(maxlength);

	g_return_val_if_fail(Create(), false);
	
	// Initialize our contents with the element text ...
	SetText(sdpGtkInternationalText(Document, Element));
	
	return true;
}

bool sdpGtkEntry::CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	const bool visible = sdpxml::GetAttribute(Element, "visible", true);
	sdpGtkMarkAttribute(Document, Element, "visible");
	SetVisible(visible);

	const bool editable = sdpxml::GetAttribute(Element, "editable", true);
	sdpGtkMarkAttribute(Document, Element, "editable");
	SetEditable(editable);

	return sdpGtkEditable::CreateOptions(ObjectContainer, Document, Element);
}

void sdpGtkEntry::SetText(sdpString Text)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_entry_set_text(*this, Text);
}

void sdpGtkEntry::SetPosition(gint Position)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_entry_set_position(*this, Position);
}

void sdpGtkEntry::SelectRegion(gint Start, gint End)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_entry_select_region(*this, Start, End);
}

void sdpGtkEntry::SetVisible(bool Visible)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_entry_set_visibility(*this, Visible);
}

void sdpGtkEntry::SetEditable(bool Editable)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_entry_set_editable(*this, Editable);
}

void sdpGtkEntry::SetMaxLength(guint16 MaxLength)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_entry_set_max_length(*this, MaxLength);
}


