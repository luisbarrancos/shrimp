#ifndef SDPGTKMENUITEM_H
#define SDPGTKMENUITEM_H

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
		\brief Declares the sdpGtkMenuItem class, which encapsulates a GtkMenuItem widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkitem.h"

///////////////////////////////////////////////////////////////
// sdpGtkMenuItem

/// Encapsulates a GtkMenuItem widget
class sdpGtkMenuItem : public sdpGtkItem
{
public:
	/// Standard constructor
	sdpGtkMenuItem();
	/// Attaches this instance to an existing GtkMenuItem widget
	sdpGtkMenuItem(GtkMenuItem* MenuItem);

	/// Creates a new GtkMenuItem widget
	bool Create();
	/// Creates a new GtkMenuItem widget with a label
	bool Create(SDPCSTRING Label);
	/// Creates a new GtkMenuItem widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	bool AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child);

	// Operations ...
	void SetSubmenu(GtkWidget* Submenu);
	void RemoveSubmenu();
	void SetSubmenuPlacement(GtkSubmenuPlacement Placement);
	void Configure(bool ShowToggleIndicator, bool ShowSubmenuIndidicator);

	void Select();
	void Deselect();
	void Activate();
	void RightJustify();

	/// Manually select (open sub-menus of) this menu as if the user had done it
	void InteractiveSelect();
	/// Manually activate this menu item as if the user had done it
	void InteractiveActivate();

	/// Casts this instance into a GtkMenuItem pointer
	operator GtkMenuItem*() { return GTK_MENU_ITEM(m_Object); }
};



#endif // SDPGTKMENUITEM_H

