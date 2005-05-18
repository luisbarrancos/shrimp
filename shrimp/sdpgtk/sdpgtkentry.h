#ifndef SDPGTKENTRY_H
#define SDPGTKENTRY_H

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
		\brief Declares the sdpGtkEntry class for encapsulating a GtkEditable widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkeditable.h"

/// Encapsulates a GtkEditable widget
class sdpGtkEntry : public sdpGtkEditable
{
public:
	/// Standard constructor
	sdpGtkEntry();
	/// Attaches this instance to an existing GtkEntry widget
	sdpGtkEntry(GtkEntry* Entry);

	/// Creates a new GtkEntry widget
	bool Create();
	/// Creates a new GtkEntry widget that limits the maximum number of characters that can be entered
	bool Create(guint16 MaxLength);
	/// Creates a new GtkEntry widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	bool CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Sets the widget text
	void SetText(sdpString Text);

	/// Sets the cursor position
	void SetPosition(gint Position);
	/// Selects a region of text
	void SelectRegion(gint Start, gint End);
	/// Controls whether the text is visible
	void SetVisible(bool Visible);
	/// Controls whether the text is editable or read-only
	void SetEditable(bool Editable);
	/// Sets the maximum number of characters that can be entered
	void SetMaxLength(guint16 MaxLength);

	/// Casts this instance into a GtkEntry pointer
	operator GtkEntry*() { return GTK_ENTRY(m_Object); }
};

#endif // SDPGTKENTRY_H

