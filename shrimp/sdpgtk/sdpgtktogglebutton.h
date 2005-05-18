#ifndef SDPGTKTOGGLEBUTTON_H
#define SDPGTKTOGGLEBUTTON_H

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
		\brief Declares the sdpGtkToggleButton class, which encapsulates a GtkToggleButton widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkbutton.h"

///////////////////////////////////////////////////////////////////////////
// sdpGtkToggleButton

/// Encapsulates a GtkToggleButton widget
class sdpGtkToggleButton : public sdpGtkButton
{
public:
	/// Standard constructor
	sdpGtkToggleButton();
	/// Attaches this instance to an existing GtkToggleButton widget
	sdpGtkToggleButton(GtkToggleButton* ToggleButton);

	/// Creates a new GtkToggleButton widget
	bool Create();
	/// Creates a new GtkToggleButton widget
	bool Create(SDPCSTRING Label);
	/// Creates a new GtkToggleButton widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Sets the toggled / not-toggled state of the button
	void SetState(bool State);
	/// Returns the button state
	bool GetState();

	/// Visibly toggles the button and sends a signal
	void InteractiveToggle();

	/// Casts this instance into a GtkToggleButton pointer
	operator GtkToggleButton*() { return GTK_TOGGLE_BUTTON(m_Object); }
};


#endif // SDPGTKTOGGLEBUTTON_H

