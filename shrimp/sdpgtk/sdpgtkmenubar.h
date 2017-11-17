#ifndef SDPGTKMENUBAR_H
#define SDPGTKMENUBAR_H

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
		\brief Declares the sdpGtkMenuBar class, which encapsulates a GtkMenuBar widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkmenushell.h"

//////////////////////////////////////////////////////////////
// sdpGtkMenuBar

/// Encapsulates a GtkMenuBar widget
class sdpGtkMenuBar : public sdpGtkMenuShell
{
public:
	/// Standard constructor
	sdpGtkMenuBar();
	/// Attaches this instance to an existing GtkMenuBar widget
	sdpGtkMenuBar(GtkMenuBar* MenuBar);

	/// Creates a new GtkMenuBar widget
	bool Create();
	/// Creates a new GtkMenuBar widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	bool CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);
	bool AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child);

	// Operations ...
	void Append(GtkWidget* Item);
	void Prepend(GtkWidget* Item);
	void Insert(GtkWidget* Item, gint Position);

	/// Sets the menu bar shadow type
	void SetShadowType(GtkShadowType ShadowType);

	/// Casts this instance into a GtkMenuBar pointer
	operator GtkMenuBar*() { return GTK_MENU_BAR(m_Object); }
};



#endif // SDPGTKMENUBAR_H
