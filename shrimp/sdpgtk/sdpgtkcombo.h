#ifndef SDPGTKCOMBO_H
#define SDPGTKCOMBO_H

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
		\brief Declares the sdpGtkCombo class, which encapsulates a GtkCombo widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkhbox.h"
#include "sdpgtkentry.h"

////////////////////////////////////////////////////////////////////////////////////////
// sdpGtkCombo

/// Encapsulates a GtkCombo widget
class sdpGtkCombo : public sdpGtkHBox
{
public:
	/// Standard constructor
	sdpGtkCombo();
	/// Attaches this instance to an existing GtkCombo widget
	sdpGtkCombo(GtkCombo* Combo);

	/// Creates a new GtkCombo widget
	bool Create();
	/// Creates a new GtkCombo widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Returns the entry widget for this combo
	sdpGtkEntry Entry();

	/// Sets the combo's selected text
	void SetEntryText(SDPCSTRING Text);
	/// Returns the combo's selected text
	SDPCSTRING GetEntryText();

	/// Initializes the combo with an array of strings
	void SetList(sdpStringArray& List);
	/// Initializes the combo with a GList of strings
	void SetList(GList* List);

	/// Casts this instance to a GtkCombo pointer
	operator GtkCombo*() { return GTK_COMBO(m_Object); }
};

#endif // SDPGTKCOMBO_H

