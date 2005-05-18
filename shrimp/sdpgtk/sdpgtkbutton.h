#ifndef SDPGTKBUTTON_H
#define SDPGTKBUTTON_H

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
		\brief Declares the sdpGtkButton class, which encapsulates a GtkButton widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkbin.h"

///////////////////////////////////////////////////////////////////////////
// sdpGtkButton

/// Encapsulates a GtkButton widget
class sdpGtkButton : public sdpGtkBin
{
public:
	/// Standard constructor
	sdpGtkButton();
	/// Attaches this instance to an existing GtkButton widget
	sdpGtkButton(GtkButton* Button);

	/// Creates a new GtkButton
	bool Create();
	/// Creates a new GtkButton with a child label
	bool Create(SDPCSTRING Label);
	/// Creates a new GtkButton from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);
	
	bool CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Sets the button relief style
	void SetRelief(GtkReliefStyle Style);
	/// Returns the button relief style
	GtkReliefStyle GetRelief();

	/// Visibly presses the button, and sends a signal
	void InteractiveActivate();

	/// Casts this instance to a GtkButton pointer
	operator GtkButton*() { return GTK_BUTTON(m_Object); }
};



#endif // SDPGTKBUTTON_H

