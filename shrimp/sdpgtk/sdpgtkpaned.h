#ifndef SDPGTKPANED_H
#define SDPGTKPANED_H

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
		\brief Declares the sdpGtkPaned class, which encapsulates a GtkPaned widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkcontainer.h"

////////////////////////////////////////////////////////////////////////////////////////
// sdpGtkPaned

/// Encapsulates a GtkPaned widget
class sdpGtkPaned : public sdpGtkContainer
{
public:
	/// Standard constructor
	sdpGtkPaned();
	/// Attaches this instance to an existing GtkPaned widget
	sdpGtkPaned(GtkPaned* Paned);

	/// Sets the resizing handle size
	void SetHandleSize(guint16 HandleSize);
	/// Sets the gutter size between panes
	void SetGutterSize(guint16 GutterSize);
	/// Sets the gutter position between panes
	void SetPosition(gint Position);
	/// Adds a widget to the top(left) pane
	void AddTopLeft(GtkWidget* Widget);
	/// Adds a widget to the bottom(right) pane
	void AddBottomRight(GtkWidget* Widget);

	void PackTopLeft(GtkWidget* Widget, bool Resize, bool Shrink);
	void PackBottomRight(GtkWidget* Widget, bool Resize, bool Shrink);

	bool CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);
	bool AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child);

	/// Casts this instance into a GtkPaned pointer
	operator GtkPaned*() { return GTK_PANED(m_Object); }

protected:
	/// Keeps track of how many children have been added ...
	gulong m_ChildCount;
};



#endif // SDPGTKPANED_H
