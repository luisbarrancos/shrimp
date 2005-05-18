#ifndef SDPGTKCHECKBUTTON_H
#define SDPGTKCHECKBUTTON_H

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
		\brief Declares the sdpGtkCheckButton class, which encapsulates a GtkCheckButton widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtktogglebutton.h"

///////////////////////////////////////////////////////////////////////////
// sdpGtkCheckButton

/// Encapsulates a GtkCheckButton widget
class sdpGtkCheckButton : public sdpGtkToggleButton
{
public:
	/// Standard constructor
	sdpGtkCheckButton();
	/// Attaches this instance to an existing GtkCheckButton
	sdpGtkCheckButton(GtkCheckButton* CheckButton);

	/// Creates a new GtkCheckButton
	bool Create();
	/// Creates a new GtkCheckButton with a label
	bool Create(SDPCSTRING Label);
	/// Creates a new GtkCheckButton from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Casts this instance to a GtkCheckButton pointer
	operator GtkCheckButton*() { return GTK_CHECK_BUTTON(m_Object); }
};

#endif // SDPGTKCHECKBUTTON_H
