#ifndef SDPGTKTOOLBAR_H
#define SDPGTKTOOLBAR_H

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
		\brief Declares the sdpGtkToolbar class, which encapsulates a GtkToolbar widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkcontainer.h"

////////////////////////////////////////////////////////////////////////////////////////
// sdpGtkToolbar

/// Encapsulates a GtkToolbar widget
class sdpGtkToolbar : public sdpGtkContainer
{
public:
	/// Standard constructor
	sdpGtkToolbar();
	/// Attaches this instance to an existing GtkToolbar widget
	sdpGtkToolbar(GtkToolbar* Toolbar);

	/// Creates a new GtkToolbar widget
	bool Create(GtkOrientation Orientation, GtkToolbarStyle Style);
	/// Creates a new GtkToolbar widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	bool AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child);

	// Operations ...
	GtkWidget* Append(SDPCSTRING Text, SDPCSTRING Tooltip, SDPCSTRING PrivateTooltip, GtkWidget* Icon, GtkSignalFunc Callback, gpointer UserData);
	GtkWidget* Append(GtkToolbarChildType Type, GtkWidget* Widget, SDPCSTRING Text, SDPCSTRING Tooltip, SDPCSTRING PrivateTooltip, GtkWidget* Icon, GtkSignalFunc Callback, gpointer UserData);
	void Append(GtkWidget* Widget, SDPCSTRING Tooltip, SDPCSTRING PrivateTooltip);
	void AppendSpace();

	GtkWidget* Prepend(SDPCSTRING Text, SDPCSTRING Tooltip, SDPCSTRING PrivateTooltip, GtkWidget* Icon, GtkSignalFunc Callback, gpointer UserData);
	GtkWidget* Prepend(GtkToolbarChildType Type, GtkWidget* Widget, SDPCSTRING Text, SDPCSTRING Tooltip, SDPCSTRING PrivateTooltip, GtkWidget* Icon, GtkSignalFunc Callback, gpointer UserData);
	void Prepend(GtkWidget* Widget, SDPCSTRING Tooltip, SDPCSTRING PrivateTooltip);
	void PrependSpace();

	GtkWidget* Insert(SDPCSTRING Text, SDPCSTRING Tooltip, SDPCSTRING PrivateTooltip, GtkWidget* Icon, GtkSignalFunc Callback, gpointer UserData, gint Position);
	GtkWidget* Insert(GtkToolbarChildType Type, GtkWidget* Widget, SDPCSTRING Text, SDPCSTRING Tooltip, SDPCSTRING PrivateTooltip, GtkWidget* Icon, GtkSignalFunc Callback, gpointer UserData, gint Position);
	void Insert(GtkWidget* Widget, SDPCSTRING Tooltip, SDPCSTRING PrivateTooltip, gint Position);
	void InsertSpace(gint Position);

	/// Sets the toolbar orientation
	void SetOrientation(GtkOrientation Orientation);
	/// Sets the toolbar style
	void SetStyle(GtkToolbarStyle Style);
	/// Sets the space between buttons
	void SetSpaceSize(gint SpaceSize);
	/// Sets the style of spaces between buttons
	void SetSpaceStyle(GtkToolbarSpaceStyle Style);
	/// Enables button tooltips
	void EnableTooltips(gint Enable);
	/// Sets the style of toolbar buttons
	void SetButtonRelief(GtkReliefStyle Relief);
	/// Returns the button style
	GtkReliefStyle GetButtonRelief();

	/// Casts this instance into a GtkToolbar pointer
	operator GtkToolbar*() { return GTK_TOOLBAR(m_Object); }
};

#endif // SDPGTKTOOLBAR_H

