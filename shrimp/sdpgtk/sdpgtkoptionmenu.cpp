
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



#include <string.h>
#include "sdpgtkoptionmenu.h"

///////////////////////////////////////////////////////////////////////////
// sdpGtkOptionMenu

sdpGtkOptionMenu::sdpGtkOptionMenu() : sdpGtkButton()
{
}

sdpGtkOptionMenu::sdpGtkOptionMenu(GtkOptionMenu* OptionMenu) : sdpGtkButton(GTK_BUTTON(OptionMenu))
{
}

bool sdpGtkOptionMenu::Create()
{
	m_Object = GTK_OBJECT(gtk_option_menu_new());
	return Attached();
}

bool sdpGtkOptionMenu::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	return Create();
}

bool sdpGtkOptionMenu::AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), false);
	g_assert(ObjectContainer);
	g_assert(Child);

	SetMenu(GTK_WIDGET(Child->Object()));

	return true;
}

GtkWidget* sdpGtkOptionMenu::GetMenu()
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);
	
	return gtk_option_menu_get_menu(*this);
}

void sdpGtkOptionMenu::SetMenu(GtkWidget* Menu)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	
	gtk_option_menu_set_menu(*this, Menu);
}

void sdpGtkOptionMenu::RemoveMenu()
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	
	gtk_option_menu_remove_menu(*this);
}

void sdpGtkOptionMenu::SetHistory(guint Index)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	
	gtk_option_menu_set_history(*this, Index);
}


