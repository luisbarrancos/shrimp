
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

#include "sdpgtktext.h"
#include "sdpgtkutility.h"

sdpGtkText::sdpGtkText() : sdpGtkEditable()
{
}

sdpGtkText::sdpGtkText(GtkText* Text) : sdpGtkEditable(GTK_EDITABLE(Text))
{
}

bool sdpGtkText::Create()
{
	m_Object = GTK_OBJECT(gtk_text_new(0, 0));
	return Attached();
}

bool sdpGtkText::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	g_return_val_if_fail(Create(), false);
	
	const sdpString text(sdpGtkInternationalText(Document, Element));
	if(text.size())
		Insert(0, 0, 0, text, -1);
		
	return true;
}


bool sdpGtkText::CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	const bool wordwrap = sdpxml::GetAttribute(Element, "wordwrap", true);
	sdpGtkMarkAttribute(Document, Element, "wordwrap");
	SetWordWrap(wordwrap);
	
	const bool linewrap = sdpxml::GetAttribute(Element, "linewrap", true);
	sdpGtkMarkAttribute(Document, Element, "linewrap");
	SetLineWrap(linewrap);

	const bool editable = sdpxml::GetAttribute(Element, "editable", true);
	sdpGtkMarkAttribute(Document, Element, "editable");
	SetEditable(editable);

	return sdpGtkEditable::CreateOptions(ObjectContainer, Document, Element);
}

void sdpGtkText::SetEditable(bool Editable)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_text_set_editable(*this, Editable);
}

void sdpGtkText::SetWordWrap(bool WordWrap)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_text_set_word_wrap(*this, WordWrap);
}

void sdpGtkText::SetLineWrap(bool LineWrap)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	
	gtk_text_set_line_wrap(*this, LineWrap);
}

void sdpGtkText::SetPoint(guint Index)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_text_set_point(*this, Index);
}

guint sdpGtkText::GetPoint()
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return gtk_text_get_point(*this);
}

guint sdpGtkText::GetLength()
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return gtk_text_get_length(*this);
}

void sdpGtkText::Freeze()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_text_freeze(*this);
}

void sdpGtkText::Thaw()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_text_thaw(*this);
}

void sdpGtkText::Insert(GdkFont* Font, GdkColor* ForegroundColor, GdkColor* BackgroundColor, const char* Text, gint Length)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_text_insert(*this, Font, ForegroundColor, BackgroundColor, Text, Length);
}

gint sdpGtkText::BackwardDelete(guint Count)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), -1);

	return gtk_text_backward_delete(*this, Count);
}

gint sdpGtkText::ForwardDelete(guint Count)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), -1);

	return gtk_text_forward_delete(*this, Count);
}

