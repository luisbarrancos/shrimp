#ifndef SDPGTKMENU_H
#define SDPGTKMENU_H

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
		\brief Declares the sdpGtkMenu class, which encapsulates a GtkMenu widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkmenushell.h"

///////////////////////////////////////////////////////////////
// sdpGtkMenu

/// Encapsulates a GtkMenu widget
class sdpGtkMenu : public sdpGtkMenuShell
{
public:
	/// Standard constructor
	sdpGtkMenu();
	/// Attaches this instance to an existing GtkMenu widget
	sdpGtkMenu(GtkMenu* Menu);

	/// Creates a new GtkMenu widget
	bool Create();
	/// Creates a new GtkMenu widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	bool CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);
	bool AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child);

	// Operations ...
	void Append(GtkWidget* Item);
	void Prepend(GtkWidget* Item);
	void Insert(GtkWidget* Item, gint Position);

	void Popup(const guint Button);
	void SetTitle(SDPCSTRING Title);

	/// Casts this instance into a GtkMenu pointer
	operator GtkMenu*() { return GTK_MENU(m_Object); }
};



#endif // SDPGTKMENU_H
