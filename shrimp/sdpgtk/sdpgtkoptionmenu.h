#ifndef SDPGTKOPTIONMENU_H
#define SDPGTKOPTIONMENU_H

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

/** \file
		\brief Declares the sdpGtkOptionMenu class, which encapsulates a GtkOptionMenu widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkbutton.h"

///////////////////////////////////////////////////////////////////////////
// sdpGtkOptionMenu

/// Encapsulates a GtkOptionMenu widget
class sdpGtkOptionMenu : public sdpGtkButton
{
public:
	/// Standard constructor
	sdpGtkOptionMenu();
	/// Attaches this instance to an existing GtkOptionMenu widget
	sdpGtkOptionMenu(GtkOptionMenu* OptionMenu);

	/// Creates a new GtkOptionMenu widget
	bool Create();
	/// Creates a new GtkOptionMenu widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	bool AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child);

	/// Returns the child menu
	GtkWidget* GetMenu();
	/// Sets the child menu
	void SetMenu(GtkWidget* Menu);
	/// Removes the child menu
	void RemoveMenu();
	/// Sets the currently-selected menu item
	void SetHistory(guint Index);

	/// Casts this instance into a GtkOptionMenu pointer
	operator GtkOptionMenu*() { return GTK_OPTION_MENU(m_Object); }
};


#endif // SDPGTKOPTIONMENU_H

