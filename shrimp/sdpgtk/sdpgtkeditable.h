#ifndef SDPGTKEDITABLE_H
#define SDPGTKEDITABLE_H

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
		\brief Declares the sdpGtkEditable class, for encapsulating a GtkEditable widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkwidget.h"

/// Encapsulates a GtkEditable widget
class sdpGtkEditable : public sdpGtkWidget
{
public:
	/// Standard constructor
	sdpGtkEditable();
	/// Attaches this instance to an existing GtkEditable widget
	sdpGtkEditable(GtkEditable* Editable);

	/// Sets the cursor position
	void SetPosition(gint Position);
	/// Returns the cursor position
	gint GetPosition();
	/// Selects a range of text
	void SelectRegion(gint Start, gint End);
	/// Deletes the selected range of text
	void DeleteSelection();
	/// Deletes a range of text
	void DeleteText(gint Start, gint End);
	/// Inserts text
	void InsertText(SDPCSTRING Text, gint TextLength, gint* Position);
	/// Sets the widget text contents
	void SetText(SDPCSTRING Text);
	/// Returns a range of text
	sdpString GetText(gint Start, gint End);
	/// Returns the widget text
	sdpString GetText();
	/// Cuts selected text to the clipboard
	void Cut();
	/// Copies selected text to the clipboard
	void Copy();
	/// Pastes text from the clipboard
	void Paste();
	/// Sets whether the widget is editable or read-only
	void SetEditable(gboolean Editable);

	/// Simulates a user entering text in the widget
	bool InteractiveSetText(SDPCSTRING Text, const gdouble Speed);

	/// Casts this instance to a GtkEditable pointer
	operator GtkEditable*() { return GTK_EDITABLE(m_Object); }
};

#endif // SDPGTKEDITABLE_H

