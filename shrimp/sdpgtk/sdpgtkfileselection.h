#ifndef SDPGTKFILESELECTION_H
#define SDPGTKFILESELECTION_H

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
		\brief Declares the sdpGtkFileSelection class, which encapsulates a GtkFileSelection widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkwindow.h"
#include "sdpgtkbutton.h"

////////////////////////////////////////////////////////////////////////////////////////////////
// sdpGtkFileSelection

/// Encapsulates a GtkFileSelection widget
class sdpGtkFileSelection : public sdpGtkWindow
{
public:
	/// Standard constructor
	sdpGtkFileSelection();
	/// Attaches this instance to an existing GtkFileSelection
	sdpGtkFileSelection(GtkFileSelection* FileSelection);

	/// Creates a new GtkFileSelection
	bool Create(SDPCSTRING Title);
	/// Creates a new GtkFileSelection from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Sets the initial filepath
	void SetFilePath(SDPCSTRING FilePath);
	/// Returns the filepath selected by the user
	sdpString GetFilePath();

	void CompletePath(SDPCSTRING Pattern);

	void ShowFileOpButtons();
	void HideFileOpButtons();

	/// Returns the OK button
	sdpGtkButton OKButton();
	/// Returns the Cancel button
	sdpGtkButton CancelButton();
	/// Returns the Help button
	sdpGtkButton HelpButton();

	/// Casts this instance into a GtkFileSelection pointer
	operator GtkFileSelection*() { return GTK_FILE_SELECTION(m_Object); }
};

#endif // SDPGTKFILESELECTION_H

