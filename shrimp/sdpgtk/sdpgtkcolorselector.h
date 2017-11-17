#ifndef SDPGTKCOLORSELECTOR_H
#define SDPGTKCOLORSELECTOR_H

// SDPGTK
// Copyright © 1995-2003, Timothy M. Shead
//
// Contact: tshead@k-3d.com
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public
// License along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

/** \file
		\brief Declares the sdpGtkColorSelector class, a standard color selection dialog
		\author Tim Shead (tshead@k-3d.com)
*/

#include "sdpgtkobjectcontainer.h"

///////////////////////////////////////////////////////////////////////////
// sdpGtkColorSelector

/// A standard color selection dialog
class sdpGtkColorSelector : public sdpGtkObjectContainer
{
public:
	sdpGtkColorSelector(SDPCSTRING Title, sdpVector3 Color);

	/// Returns true if the user selected a color
	bool OK();
	/// Returns true if the user cancelled color selection
	bool Cancelled();
	/// Returns the dialog title
	SDPCSTRING Title();
	/// Returns the color selected by the user
	sdpVector3 Color();

protected:
	/// Handles GTK+ events
	void OnEvent(sdpGtkEvent* Event);

	/// Called anytime the color changes
	virtual void OnColorChanged();
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
	/// Stores the color chosen by the user
	sdpVector3 m_Color;
	
private:
	void RawOnColorChanged();
};

////////////////////////////////////////////////////////////////////////////////
// sdpGtkFeedbackColorSelector

/// Implements a color selection template that provides realtime feedback to a functor object as the user chooses colors
template<class Type>
class sdpGtkFeedbackColorSelector : public sdpGtkColorSelector
{
public:
	sdpGtkFeedbackColorSelector(SDPCSTRING Title, sdpVector3 Color, Type& Functor) : sdpGtkColorSelector(Title, Color), m_Functor(Functor) {}
	
protected:
	void OnColorChanged()
	{
		sdpGtkColorSelector::OnColorChanged();
		m_Functor.HandleColor(m_Color);
	}

	Type& m_Functor;
};

#endif // SDPGTKCOLORSELECTOR_H

