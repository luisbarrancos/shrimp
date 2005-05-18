
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

#include "sdpgtkmenu.h"
#include "sdpgtkutility.h"

//////////////////////////////////////////////////////////////
// sdpGtkMenu

sdpGtkMenu::sdpGtkMenu() : sdpGtkMenuShell()
{
}

sdpGtkMenu::sdpGtkMenu(GtkMenu* Menu) : sdpGtkMenuShell(GTK_MENU_SHELL(Menu))
{
}

bool sdpGtkMenu::Create()
{
	m_Object = GTK_OBJECT(gtk_menu_new());
	return Attached();
}

bool sdpGtkMenu::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	return Create();
}

bool sdpGtkMenu::CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	const sdpString title = sdpxml::GetAttribute<sdpString>(Element, "title", "");
	sdpGtkMarkAttribute(Document, Element, "title");
	if(title.size())
		SetTitle(title);

	return sdpGtkMenuShell::CreateOptions(ObjectContainer, Document, Element);
}

bool sdpGtkMenu::AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child)
{
	Append(GTK_WIDGET(Child->Object()));
	return true;
}

void sdpGtkMenu::Append(GtkWidget* Item)
{
	// Sanity checks ..
	g_assert(Item);
	g_return_if_fail(Attached());

	gtk_menu_append(*this, Item);
}

void sdpGtkMenu::Prepend(GtkWidget* Item)
{
	// Sanity checks ..
	g_assert(Item);
	g_return_if_fail(Attached());

	gtk_menu_prepend(*this, Item);
}

void sdpGtkMenu::Insert(GtkWidget* Item, gint Position)
{
	// Sanity checks ..
	g_assert(Item);
	g_return_if_fail(Attached());

	gtk_menu_insert(*this, Item, Position);
}

void sdpGtkMenu::Popup(const guint Button)
{
	// Sanity checks ..
	g_return_if_fail(Attached());
	gtk_menu_popup(*this, 0, 0, 0, 0, Button, GDK_CURRENT_TIME);
}

void sdpGtkMenu::SetTitle(SDPCSTRING Title)
{
	// Sanity checks ...
	g_assert_string(Title);
	g_return_if_fail(Attached());

	gtk_menu_set_title(*this, Title);
}


