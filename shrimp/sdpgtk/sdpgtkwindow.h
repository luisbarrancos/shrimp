#ifndef SDPGTKWINDOW_H
#define SDPGTKWINDOW_H

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
		\brief Declares the sdpGtkWindow class, which encapsulates a GtkWindow widget
		\author Timothy M. Shead (tshead@k-3d.com)
		\author Dan Erikson <derikson@montana.com>
*/

#include "sdpgtkbin.h"

/// Encapsulates a GtkWindow widget
class sdpGtkWindow : public sdpGtkBin
{
public:
	/// Standard constructor
	sdpGtkWindow();
	/// Attaches this instance to an existing GtkWindow widget
	sdpGtkWindow(GtkWindow* Window);

	/// Creates a new GtkWindow widget
	bool Create(GtkWindowType Type);
	/// Creates a new GtkWindow widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	bool CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Sets the text in the window titlebar
	void SetTitle(SDPCSTRING Title);
	/// Controls which widget has the keyboard focus
	void SetFocus(GtkWidget* Widget);
	/// Controls which widget is the default
	void SetDefault(GtkWidget* Widget);
	/// Sets the window policies for user resizing
	void SetPolicy(gint AllowShrink, gint AllowGrow, gint AutoShrink);
	/// Sets the window position
	void SetPosition(GtkWindowPosition Position);
	/// Sets the window's default size
	void SetDefaultSize(gint Width, gint Height);
	/// Sets the window modality
	void SetModal(bool Modal);
	/// Makes the window transient
	void SetTransientFor(GtkWindow* Window);
	/// Sets the window type
	void SetWindowType(GtkWindowType Type);
	/// Gets the window type
	GtkWindowType GetWindowType();

	/// Casts this instance into a GtkWindow pointer
	operator GtkWindow*() { return GTK_WINDOW(m_Object); }
};

#endif // SDPGTKWINDOW_H

