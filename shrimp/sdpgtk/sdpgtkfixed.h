#ifndef SDPGTKFIXED_H
#define SDPGTKFIXED_H

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
		\brief Declares the sdpGtkFixed class, which encapsulates a GtkFixed widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkcontainer.h"

/// Encapsulates a GtkFixed widget
class sdpGtkFixed : public sdpGtkContainer
{
public:
	/// Standard constructor
	sdpGtkFixed();
	/// Attaches this instance to an existing GtkFixed widget
	sdpGtkFixed(GtkFixed* Fixed);

	/// Creates a new GtkFixed widget
	bool Create();
	/// Creates a new GtkFixed widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);
	
	bool AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child);

	/// Attaches a child widget at the given position
	void Attach(GtkWidget* Widget, gint16 X, gint16 Y);
	/// Moves a child widget to the given position
	void Move(GtkWidget* Widget, gint16 X, gint16 Y);
	
	/// Casts this instance to a GtkFixed pointer
	operator GtkFixed*() { return GTK_FIXED(m_Object); }
};

#endif // SDPGTKFIXED_H
