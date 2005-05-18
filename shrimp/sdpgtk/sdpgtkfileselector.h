#ifndef SDPGTKFILESELECTOR_H
#define SDPGTKFILESELECTOR_H

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

#include "sdpgtkobjectcontainer.h"

/////////////////////////////////////////////////////////////////////////////////////
// sdpGtkFileSelector

/// A standard modal file selection dialog
class sdpGtkFileSelector : public sdpGtkObjectContainer
{
public:
	sdpGtkFileSelector(SDPCSTRING Title, SDPCSTRING FilePath);

	/// Starts the modal loop
	void DoModal();
	/// Starts the modal loop
	void DoModal(GtkWindow* TransientOwner);
	/// Starts the modal loop
	void DoModal(sdpGtkWindow& TransientOwner);

	/// Returns true if the user selected a file
	bool OK() const;
	/// Returns true if the user cancelled file selection
	bool Cancelled() const;
	/// Returns the dialog title
	sdpString Title() const;
	/// Returns the full filepath selected by the user
	sdpString FilePath() const;

protected:
	/// Loads the UI and creates the appropriate GTK+ widgets
	bool Load();

	/// Handles GTK+ events
	void OnEvent(sdpGtkEvent* Event);

	/// Called when the user clicks the WM close button
	virtual void OnDelete(sdpGtkEvent* Event);
	/// Called when the GTK+ widgets are about to be destroyed
	virtual void OnDestroy();
	/// Called when the user selects a file
	virtual void OnOK();
	/// Called when the user cancels file selection
	virtual void OnCancel();
	/// Called when the user clicks the "Help" button
	virtual void OnHelp();

	/// Stores whether a file was selected or cancelled
	bool m_OK;
	/// Stores the dialog title
	sdpString m_Title;
	/// Stores the filepath chosen by the user
	sdpString m_FilePath;
};

#endif // SDPGTKFILESELECTOR_H

