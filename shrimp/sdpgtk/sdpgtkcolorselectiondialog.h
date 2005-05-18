#ifndef SDPGTKCOLORSELECTIONDIALOG_H
#define SDPGTKCOLORSELECTIONDIALOG_H

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
		\brief Declares the sdpGtkColorSelectionDialog class, which encapsulates a GtkColorSelectionDialog widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkwindow.h"
#include "sdpgtkcolorselection.h"
#include "sdpgtkbutton.h"

////////////////////////////////////////////////////////////////////////////////////////////////
// sdpGtkColorSelectionDialog

/// Encapsulates a GtkColorSelectionDialog widget
class sdpGtkColorSelectionDialog : public sdpGtkWindow
{
public:
	/// Standard constructor
	sdpGtkColorSelectionDialog();
	/// Attaches this instance to an existing GtkColorSelectionDialog widget
	sdpGtkColorSelectionDialog(GtkColorSelectionDialog* ColorSelectionDialog);

	/// Creates a new GtkColorSelectionDialog widget
	bool Create(SDPCSTRING Title);
	/// Creates a new GtkColorSelectionDialog widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Returns the dialog's underlying sdpGtkColorSelection
	sdpGtkColorSelection Selection() { return sdpGtkColorSelection(GTK_COLOR_SELECTION(GTK_COLOR_SELECTION_DIALOG(m_Object)->colorsel)); }

	/// Returns this dialog's OK button
	sdpGtkButton OKButton();
	/// Returns this dialog's Cancel button
	sdpGtkButton CancelButton();
	/// Returns this dialog's Reset button
	sdpGtkButton ResetButton();
	/// Returns this dialog's Help button
	sdpGtkButton HelpButton();

	/// Casts this instance to a GtkColorSelectionDialog pointer
	operator GtkColorSelectionDialog*() { return GTK_COLOR_SELECTION_DIALOG(m_Object); }
};

#endif // SDPGTKCOLORSELECTIONDIALOG_H
