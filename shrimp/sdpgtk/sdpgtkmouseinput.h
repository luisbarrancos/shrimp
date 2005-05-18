#ifndef SDPGTKMOUSEINPUT_H
#define SDPGTKMOUSEINPUT_H

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
		\brief Declares the sdpGtkMouseInput class, which converts mouse & button input into a set of standardized logical events
		\author Tim Shead (tshead@k-3d.com)
*/

#include "sdpgtkevent.h"
#include <map>

/////////////////////////////////////////////////////////////////////////////
// sdpGtkMouseInput

/// Converts mouse & button input into a set of standardized logical events
class sdpGtkMouseInput
{
public:
	sdpGtkMouseInput();
	virtual ~sdpGtkMouseInput();

protected:
	// If you want to process regular SDPGTK events, call the following:

	/// Called when the user presses a mouse button
	void RawButtonDown(sdpGtkEvent* Event);
	/// Called when the mouse moves
	void RawMouseMove(sdpGtkEvent* Event);
	/// Called when the user releases a mouse button
	void RawButtonUp(sdpGtkEvent* Event);


	// If you're synthesizing simulated user events, use the following:
	
	/// Called when the user presses a mouse button
	void RawButtonDown(GtkWidget* Widget, GdkEventType EventType, guint Button, GdkModifierType Modifiers);
	/// Called when the mouse moves
	void RawMouseMove(GtkWidget* Widget, GdkModifierType Modifiers);
	/// Called when the user releases a mouse button
	void RawButtonUp(GtkWidget* Widget, guint Button, GdkModifierType Modifiers);


	// This is where the real work takes place:

	/// Called when the user presses a mouse button
	void RawButtonDown(GdkEventType EventType, guint Button, GdkModifierType Modifiers, sdpVector2 CurrentMouse);
	/// Called when the mouse moves
	void RawMouseMove(GdkWindow* Window, GdkModifierType Modifiers, sdpVector2 CurrentMouse);
	/// Called when the user releases a mouse button
	void RawButtonUp(guint Button, GdkModifierType Modifiers, sdpVector2 CurrentMouse);



	// Standard logical user input events that you can override in derived classes ...
	virtual void OnMouseMove(GdkModifierType Modifiers, const sdpVector2 CurrentMouse);
	
	virtual void OnLButtonDown(GdkModifierType Modifiers, const sdpVector2 CurrentMouse);
	virtual void OnLButtonUp(GdkModifierType Modifiers, const sdpVector2 CurrentMouse);	
	virtual void OnLButtonClick(GdkModifierType Modifiers, const sdpVector2 CurrentMouse);
	virtual void OnLButtonDoubleClick(GdkModifierType Modifiers, const sdpVector2 CurrentMouse);
	virtual void OnLButtonStartDrag(GdkModifierType Modifiers, const sdpVector2 CurrentMouse);
	virtual void OnLButtonDrag(GdkModifierType Modifiers, const sdpVector2 CurrentMouse, const sdpVector2 LastMouse, const sdpVector2 StartMouse);
	virtual void OnLButtonEndDrag(GdkModifierType Modifiers, const sdpVector2 CurrentMouse, const sdpVector2 LastMouse, const sdpVector2 StartMouse);

	virtual void OnMButtonDown(GdkModifierType Modifiers, const sdpVector2 CurrentMouse);	
	virtual void OnMButtonUp(GdkModifierType Modifiers, const sdpVector2 CurrentMouse);	
	virtual void OnMButtonClick(GdkModifierType Modifiers, const sdpVector2 CurrentMouse);
	virtual void OnMButtonDoubleClick(GdkModifierType Modifiers, const sdpVector2 CurrentMouse);
	virtual void OnMButtonStartDrag(GdkModifierType Modifiers, const sdpVector2 CurrentMouse);
	virtual void OnMButtonDrag(GdkModifierType Modifiers, const sdpVector2 CurrentMouse, const sdpVector2 LastMouse, const sdpVector2 StartMouse);
	virtual void OnMButtonEndDrag(GdkModifierType Modifiers, const sdpVector2 CurrentMouse, const sdpVector2 LastMouse, const sdpVector2 StartMouse);

	virtual void OnRButtonDown(GdkModifierType Modifiers, const sdpVector2 CurrentMouse);	
	virtual void OnRButtonUp(GdkModifierType Modifiers, const sdpVector2 CurrentMouse);	
	virtual void OnRButtonClick(GdkModifierType Modifiers, const sdpVector2 CurrentMouse);
	virtual void OnRButtonDoubleClick(GdkModifierType Modifiers, const sdpVector2 CurrentMouse);
	virtual void OnRButtonStartDrag(GdkModifierType Modifiers, const sdpVector2 CurrentMouse);
	virtual void OnRButtonDrag(GdkModifierType Modifiers, const sdpVector2 CurrentMouse, const sdpVector2 LastMouse, const sdpVector2 StartMouse);
	virtual void OnRButtonEndDrag(GdkModifierType Modifiers, const sdpVector2 CurrentMouse, const sdpVector2 LastMouse, const sdpVector2 StartMouse);

	virtual void OnLRButtonStartDrag(GdkModifierType Modifiers, const sdpVector2 CurrentMouse);
	virtual void OnLRButtonDrag(GdkModifierType Modifiers, const sdpVector2 CurrentMouse, const sdpVector2 LastMouse, const sdpVector2 StartMouse);
	virtual void OnLRButtonEndDrag(GdkModifierType Modifiers, const sdpVector2 CurrentMouse, const sdpVector2 LastMouse, const sdpVector2 StartMouse);

private:
	/// Returns "true" if there are ANY mouse buttons down
	bool Buttons();
	/// Clears any mouse button flags
	void ClearButtons();
	
	/// Stores the current drag state
	bool m_Dragging;
	/// Stores the mouse coordinates when dragging began
	sdpVector2 m_StartMouse;
	/// Stores the previous mouse coordinates 
	sdpVector2 m_LastMouse;
	/// Stores the current mouse coordinates
	sdpVector2 m_CurrentMouse;
	/// Stores the mouse button states
	typedef std::map<guint, bool> ButtonState;
	typedef ButtonState::iterator ButtonStateIterator;
	ButtonState m_Buttons;
};

#endif // SDPGTKMOUSEINPUT_H
