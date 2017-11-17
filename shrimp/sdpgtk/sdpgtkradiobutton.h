#ifndef SDPGTKRADIOBUTTON_H
#define SDPGTKRADIOBUTTON_H

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
		\brief Declares the sdpGtkRadioButton class, which encapsulates a GtkRadioButton widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkcheckbutton.h"

///////////////////////////////////////////////////////////////////////////
// sdpGtkRadioButton

/// Encapsulates a GtkRadioButton widget
class sdpGtkRadioButton : public sdpGtkCheckButton
{
public:
	/// Standard constructor
	sdpGtkRadioButton();
	/// Attaches this instance to an existing GtkRadioButton widget
	sdpGtkRadioButton(GtkRadioButton* RadioButton);

	/// Creates a new GtkRadioButton
	bool Create(GSList* Group);
	/// Creates a new GtkRadioButton
	bool Create(GSList* Group, SDPCSTRING Label);
	/// Creates a new GtkRadioButton from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Casts this instance into a GtkRadioButton pointer
	operator GtkRadioButton*() { return GTK_RADIO_BUTTON(m_Object); }
};

#endif // SDPGTKRADIOBUTTON_H

