
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

#include "sdpgtkmenubar.h"
#include "sdpgtkutility.h"

//////////////////////////////////////////////////////////////
// sdpGtkMenuBar

sdpGtkMenuBar::sdpGtkMenuBar() : sdpGtkMenuShell()
{
}

sdpGtkMenuBar::sdpGtkMenuBar(GtkMenuBar* MenuBar) : sdpGtkMenuShell(GTK_MENU_SHELL(MenuBar))
{
}

bool sdpGtkMenuBar::Create()
{
	m_Object = GTK_OBJECT(gtk_menu_bar_new());
	return Attached();
}

bool sdpGtkMenuBar::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	return Create();
}


bool sdpGtkMenuBar::CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	// Shadow type ...
	SetShadowType(sdpGtkGetShadowType(Document, Element, GTK_SHADOW_ETCHED_IN));

	// Call the base-class implementation ...
	return sdpGtkMenuShell::CreateOptions(ObjectContainer, Document, Element);
}

bool sdpGtkMenuBar::AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child)
{
	Append(GTK_WIDGET(Child->Object()));
	return true;
}

void sdpGtkMenuBar::Append(GtkWidget* Item)
{
	// Sanity checks ...
	g_assert(Item);
	g_return_if_fail(Attached());

	gtk_menu_bar_append(*this, Item);
}

void sdpGtkMenuBar::Prepend(GtkWidget* Item)
{
	// Sanity checks ...
	g_assert(Item);
	g_return_if_fail(Attached());

	gtk_menu_bar_prepend(*this, Item);
}

void sdpGtkMenuBar::Insert(GtkWidget* Item, gint Position)
{
	// Sanity checks ...
	g_assert(Item);
	g_return_if_fail(Attached());

	gtk_menu_bar_insert(*this, Item, Position);
}

void sdpGtkMenuBar::SetShadowType(GtkShadowType ShadowType)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_menu_bar_set_shadow_type(*this, ShadowType);
}
