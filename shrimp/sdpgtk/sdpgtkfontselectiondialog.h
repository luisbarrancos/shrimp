#ifndef SDPGTKFONTSELECTIONDIALOG_H
#define SDPGTKFONTSELECTIONDIALOG_H

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
		\brief Declares the sdpGtkFontSelectionDialog class, which encapsulates a GtkFontSelectionDialog widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkwindow.h"
#include "sdpgtkfontselection.h"
#include "sdpgtkbutton.h"

////////////////////////////////////////////////////////////////////////////////////////////////
// sdpGtkFontSelectionDialog

/// Encapsulates a GtkFontSelectionDialog widget
class sdpGtkFontSelectionDialog : public sdpGtkWindow
{
public:
	/// Standard constructor
	sdpGtkFontSelectionDialog();
	/// Attaches this instance to an existing GtkFontSelectionDialog widget
	sdpGtkFontSelectionDialog(GtkFontSelectionDialog* FontSelectionDialog);

	/// Creates a new GtkFontSelectionDialog widget
	bool Create(SDPCSTRING Title);
	/// Creates a new GtkFontSelectionDialog widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Returns the font selection for this dialog
	sdpGtkFontSelection Selection() { return sdpGtkFontSelection(GTK_FONT_SELECTION(GTK_FONT_SELECTION_DIALOG(m_Object)->fontsel)); }

	/// Returns the OK button
	sdpGtkButton OKButton();
	/// Returns the Cancel button
	sdpGtkButton CancelButton();
	/// Returns the Apply button
	sdpGtkButton ApplyButton();

	/// Casts this instance into a GtkFontSelectionDialog pointer
	operator GtkFontSelectionDialog*() { return GTK_FONT_SELECTION_DIALOG(m_Object); }
};

#endif // SDPGTKFONTSELECTIONDIALOG_H
