
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

#include "sdpgtkmenuitem.h"
#include "sdpgtkutility.h"

///////////////////////////////////////////////////////////////
// sdpGtkMenuItem

sdpGtkMenuItem::sdpGtkMenuItem() : sdpGtkItem()
{
}

sdpGtkMenuItem::sdpGtkMenuItem(GtkMenuItem* MenuItem) : sdpGtkItem(GTK_ITEM(MenuItem))
{
}

bool sdpGtkMenuItem::Create()
{
	m_Object = GTK_OBJECT(gtk_menu_item_new());
	return Attached();
}

bool sdpGtkMenuItem::Create(SDPCSTRING Label)
{
	// Sanity checks ...
	g_assert(Label);

	m_Object = GTK_OBJECT(gtk_menu_item_new_with_label(Label));
	return Attached();
}

bool sdpGtkMenuItem::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	const sdpString text(sdpGtkInternationalText(Document, Element));
	return text.size() ? Create(text) : Create();
}

bool sdpGtkMenuItem::AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child)
{
	// Sanity checks ...
	g_assert(Child);
	g_return_val_if_fail(Attached(), false);

	if(GTK_IS_MENU(Child->Object()))
		SetSubmenu(GTK_WIDGET(Child->Object()));
	else
		Attach(GTK_WIDGET(Child->Object()));

	if(GTK_IS_ACCEL_LABEL(Child->Object()))
		gtk_accel_label_set_accel_widget(GTK_ACCEL_LABEL(Child->Object()), GTK_WIDGET(Object()));

	return true;
}

void sdpGtkMenuItem::SetSubmenu(GtkWidget* Submenu)
{
	// Sanity checks ...
	g_assert(Submenu);
	g_return_if_fail(Attached());

	gtk_menu_item_set_submenu(*this, Submenu);
}

void sdpGtkMenuItem::RemoveSubmenu()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_menu_item_remove_submenu(*this);
}

void sdpGtkMenuItem::SetSubmenuPlacement(GtkSubmenuPlacement Placement)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_menu_item_set_placement(*this, Placement);
}

void sdpGtkMenuItem::Configure(bool ShowToggleIndicator, bool ShowSubmenuIndicator)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_menu_item_configure(*this, ShowToggleIndicator, ShowSubmenuIndicator);
}

void sdpGtkMenuItem::Select()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_menu_item_select(*this);
}

void sdpGtkMenuItem::Deselect()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_menu_item_deselect(*this);
}

void sdpGtkMenuItem::Activate()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_menu_item_activate(*this);
}

void sdpGtkMenuItem::RightJustify()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_menu_item_right_justify(*this);
}

void sdpGtkMenuItem::InteractiveSelect()
{
	Select();
	sdpGtkHandlePendingEvents();
	sdpGtkSleep(250);
}

void sdpGtkMenuItem::InteractiveActivate()
{
	Activate();
	sdpGtkHandlePendingEvents();
}


