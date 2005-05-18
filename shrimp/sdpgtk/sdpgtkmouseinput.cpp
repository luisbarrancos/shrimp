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
		\brief Implements the sdpGtkMouseInput class, which converts mouse & button input into a set of standardized logical events
		\author Tim Shead (tshead@k-3d.com)
*/

#include "sdpgtkmouseinput.h"
#include "sdpgtkevents.h"

/////////////////////////////////////////////////////////////////////////////
// sdpGtkMouseInput

sdpGtkMouseInput::sdpGtkMouseInput()
{
	m_Dragging = false;
	m_Buttons[1] = false;
	m_Buttons[2] = false;
	m_Buttons[3] = false;
}

sdpGtkMouseInput::~sdpGtkMouseInput()
{
}

void sdpGtkMouseInput::RawButtonDown(sdpGtkEvent* Event)
{
	// Sanity checks ...
	g_assert(Event);
	sdpGtkEventWidgetButtonPressEvent* const event = static_cast<sdpGtkEventWidgetButtonPressEvent*>(Event);
	event->SetResult(true);

	// Get the pointer position so we can send it along ...
	int x, y;
	GdkModifierType modifiers;
	gdk_window_get_pointer(event->Event()->window, &x, &y, &modifiers);

	RawButtonDown(event->Event()->type, event->Event()->button, modifiers, sdpVector2(gdouble(x), gdouble(y)));
}

void sdpGtkMouseInput::RawButtonDown(GtkWidget* Widget, GdkEventType EventType, guint Button, GdkModifierType Modifiers)
{
	// Sanity checks ...
	g_assert(Widget);
	
	// Get the pointer position so we can send it along ...
	int x, y;
	GdkModifierType modifiers; // Ignored, since it's being supplied by the caller, above ...
	gdk_window_get_pointer(Widget->window, &x, &y, &modifiers);

	RawButtonDown(EventType, Button, Modifiers, sdpVector2(gdouble(x), gdouble(y)));
}

void sdpGtkMouseInput::RawButtonDown(GdkEventType EventType, guint Button, GdkModifierType Modifiers, sdpVector2 CurrentMouse)
{
	// Cache the mouse coordinates ...
	m_CurrentMouse = CurrentMouse;
	
	// If it's a double-click, send the event and clear our state; we don't send low-level events because double-clicks don't get a button-up event ...
	if(EventType == GDK_2BUTTON_PRESS)
		{
			// Generate events ...
			switch(Button)
				{
					case 1:
						OnLButtonDoubleClick(Modifiers, m_CurrentMouse);
						break;
					case 2:
						OnMButtonDoubleClick(Modifiers, m_CurrentMouse);
						break;
					case 3:
						OnRButtonDoubleClick(Modifiers, m_CurrentMouse);
						break;
				}

			m_Dragging = false;
			ClearButtons();
		}
	// Otherwise it's the beginning of a single-click ...
	else
		{
			// If there aren't any other buttons pressed, record our starting point ...
			if(!Buttons())
				m_StartMouse = m_LastMouse = m_CurrentMouse;

			// Record which button was pressed ...
			m_Buttons[Button] = true;
	
			// Generate events ...
			switch(Button)
				{
					case 1:
						OnLButtonDown(Modifiers, m_CurrentMouse);
						break;
					case 2:
						OnMButtonDown(Modifiers, m_CurrentMouse);
						break;
					case 3:
						OnRButtonDown(Modifiers, m_CurrentMouse);
						break;
				}
		}
}

void sdpGtkMouseInput::RawMouseMove(sdpGtkEvent* Event)
{
	// Sanity checks ...
	g_assert(Event);
	sdpGtkEventWidgetMotionNotifyEvent* event = static_cast<sdpGtkEventWidgetMotionNotifyEvent*>(Event);

	// Get the pointer position  ...
	int x, y;
	GdkModifierType modifiers;
	gdk_window_get_pointer(event->Event()->window, &x, &y, &modifiers);
		
	RawMouseMove(event->Event()->window, modifiers, sdpVector2(gdouble(x), gdouble(y)));
}

void sdpGtkMouseInput::RawMouseMove(GtkWidget* Widget, GdkModifierType Modifiers)
{
	// Sanity checks ...
	g_assert(Widget);
	
	// Get the pointer position  ...
	int x, y;
	GdkModifierType modifiers;	// Ignored; we use the modifiers supplied by the caller, above
	gdk_window_get_pointer(Widget->window, &x, &y, &modifiers);
		
	RawMouseMove(Widget->window, Modifiers, sdpVector2(gdouble(x), gdouble(y)));
}

void sdpGtkMouseInput::RawMouseMove(GdkWindow* Window, GdkModifierType Modifiers, sdpVector2 CurrentMouse)
{
	// We don't assert on Window, because it's optional (only required for pointer grab purposes)

	// Cache current and previous mouse positions ...
	m_LastMouse = m_CurrentMouse;
	m_CurrentMouse = CurrentMouse;

	// If we're already dragging, send drag events ...
	if(m_Dragging)
		{
			if(m_Buttons[1] && m_Buttons[3])
				OnLRButtonDrag(Modifiers, m_CurrentMouse, m_LastMouse, m_StartMouse);
			else if(m_Buttons[1])
				OnLButtonDrag(Modifiers, m_CurrentMouse, m_LastMouse, m_StartMouse);
			else if(m_Buttons[2])
				OnMButtonDrag(Modifiers, m_CurrentMouse, m_LastMouse, m_StartMouse);
			else if(m_Buttons[3])
				OnRButtonDrag(Modifiers, m_CurrentMouse, m_LastMouse, m_StartMouse);
		}

	// Otherwise, see if we should start dragging ...
	else
		{
			// Got any buttons down?
			if(Buttons())
				{
					// Has the mouse moved far away enough from the point where a button was clicked?
					if((m_CurrentMouse - m_StartMouse).Length() > 4.0)
						{
							// Grab mouse events ...
							if(Window)
								gdk_pointer_grab(Window, FALSE, GdkEventMask(GDK_POINTER_MOTION_MASK | GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK), 0, 0, GDK_CURRENT_TIME);

							m_Dragging = true;

							if(m_Buttons[1] && m_Buttons[3])
								OnLRButtonStartDrag(Modifiers, m_CurrentMouse);
							else if(m_Buttons[1])
								OnLButtonStartDrag(Modifiers, m_CurrentMouse);
							else if(m_Buttons[2])
								OnMButtonStartDrag(Modifiers, m_CurrentMouse);
							else if(m_Buttons[3])
								OnRButtonStartDrag(Modifiers, m_CurrentMouse);
						}
				}
			// No, so it's just a plain mouse move event ...
			else
				{
					OnMouseMove(Modifiers, m_CurrentMouse);
				}
		}
}

void sdpGtkMouseInput::RawButtonUp(sdpGtkEvent* Event)
{
	// Sanity checks ...
	g_assert(Event);
	sdpGtkEventWidgetButtonReleaseEvent* const event = static_cast<sdpGtkEventWidgetButtonReleaseEvent*>(Event);
	event->SetResult(true);
	
	// Get the pointer position so we can send it along ...
	int x, y;
	GdkModifierType modifiers;
	gdk_window_get_pointer(event->Event()->window, &x, &y, &modifiers);
	
	RawButtonUp(event->Event()->button, modifiers, sdpVector2(gdouble(x), gdouble(y)));
}

void sdpGtkMouseInput::RawButtonUp(GtkWidget* Widget, guint Button, GdkModifierType Modifiers)
{
	// Sanity checks ...
	g_assert(Widget);
	
	// Get the pointer position so we can send it along ...
	int x, y;
	GdkModifierType modifiers; // Ignored; we use the modifiers supplied by the caller, instead
	gdk_window_get_pointer(Widget->window, &x, &y, &modifiers);
	
	RawButtonUp(Button, Modifiers, sdpVector2(gdouble(x), gdouble(y)));
}

void sdpGtkMouseInput::RawButtonUp(guint Button, GdkModifierType Modifiers, sdpVector2 CurrentMouse)
{
	// Cache the current mouse position ...
	m_CurrentMouse = CurrentMouse;

	// Generate low-level events ...
	switch(Button)
		{
			case 1:
				OnLButtonUp(Modifiers, m_CurrentMouse);
				break;
			case 2:
				OnMButtonUp(Modifiers, m_CurrentMouse);
				break;
			case 3:
				OnRButtonUp(Modifiers, m_CurrentMouse);
				break;
		}

	// If we our state was cleared, we're done ...
	if(!Buttons())
		return;

	// If we were dragging ...
	if(m_Dragging)
		{
			// Release mouse events ...
			gdk_pointer_ungrab(GDK_CURRENT_TIME);

			if(m_Buttons[1] && m_Buttons[3])
				OnLRButtonEndDrag(Modifiers, m_CurrentMouse, m_LastMouse, m_StartMouse);
			else if(m_Buttons[1])
				OnLButtonEndDrag(Modifiers, m_CurrentMouse, m_LastMouse, m_StartMouse);
			else if(m_Buttons[2])
				OnMButtonEndDrag(Modifiers, m_CurrentMouse, m_LastMouse, m_StartMouse);
			else if(m_Buttons[3])
				OnRButtonEndDrag(Modifiers, m_CurrentMouse, m_LastMouse, m_StartMouse);

			m_Dragging = false;
		}

	// ... otherwise, it's a click ...
	else
		{
			switch(Button)
				{
					case 1:
						OnLButtonClick(Modifiers, m_CurrentMouse);
						break;
					case 2:
						OnMButtonClick(Modifiers, m_CurrentMouse);
						break;
					case 3:
						OnRButtonClick(Modifiers, m_CurrentMouse);
						break;
				}
		}
		
	ClearButtons();
}

bool sdpGtkMouseInput::Buttons()
{
	for(ButtonStateIterator button = m_Buttons.begin(); button != m_Buttons.end(); button++)
		if(button->second == true)
			return true;
			
	return false;
}

void sdpGtkMouseInput::ClearButtons()
{
	for(ButtonStateIterator button = m_Buttons.begin(); button != m_Buttons.end(); button++)
		button->second = false;
}

void sdpGtkMouseInput::OnMouseMove(GdkModifierType Modifiers, const sdpVector2 CurrentMouse)
{
}

void sdpGtkMouseInput::OnLButtonDown(GdkModifierType Modifiers, const sdpVector2 CurrentMouse)
{
}

void sdpGtkMouseInput::OnLButtonUp(GdkModifierType Modifiers, const sdpVector2 CurrentMouse)
{
}

void sdpGtkMouseInput::OnLButtonClick(GdkModifierType Modifiers, const sdpVector2 CurrentMouse)
{
}

void sdpGtkMouseInput::OnLButtonDoubleClick(GdkModifierType Modifiers, const sdpVector2 CurrentMouse)
{
}

void sdpGtkMouseInput::OnLButtonStartDrag(GdkModifierType Modifiers, const sdpVector2 CurrentMouse)
{
}

void sdpGtkMouseInput::OnLButtonDrag(GdkModifierType Modifiers, const sdpVector2 CurrentMouse, const sdpVector2 LastMouse, const sdpVector2 StartMouse)
{
}

void sdpGtkMouseInput::OnLButtonEndDrag(GdkModifierType Modifiers, const sdpVector2 CurrentMouse, const sdpVector2 LastMouse, const sdpVector2 StartMouse)
{
}

void sdpGtkMouseInput::OnMButtonDown(GdkModifierType Modifiers, const sdpVector2 CurrentMouse)
{
}

void sdpGtkMouseInput::OnMButtonUp(GdkModifierType Modifiers, const sdpVector2 CurrentMouse)
{
}

void sdpGtkMouseInput::OnMButtonClick(GdkModifierType Modifiers, const sdpVector2 CurrentMouse)
{
}

void sdpGtkMouseInput::OnMButtonDoubleClick(GdkModifierType Modifiers, const sdpVector2 CurrentMouse)
{
}

void sdpGtkMouseInput::OnMButtonStartDrag(GdkModifierType Modifiers, const sdpVector2 CurrentMouse)
{
}

void sdpGtkMouseInput::OnMButtonDrag(GdkModifierType Modifiers, const sdpVector2 CurrentMouse, const sdpVector2 LastMouse, const sdpVector2 StartMouse)
{
}

void sdpGtkMouseInput::OnMButtonEndDrag(GdkModifierType Modifiers, const sdpVector2 CurrentMouse, const sdpVector2 LastMouse, const sdpVector2 StartMouse)
{
}

void sdpGtkMouseInput::OnRButtonDown(GdkModifierType Modifiers, const sdpVector2 CurrentMouse)
{
}

void sdpGtkMouseInput::OnRButtonUp(GdkModifierType Modifiers, const sdpVector2 CurrentMouse)
{
}

void sdpGtkMouseInput::OnRButtonClick(GdkModifierType Modifiers, const sdpVector2 CurrentMouse)
{
}

void sdpGtkMouseInput::OnRButtonDoubleClick(GdkModifierType Modifiers, const sdpVector2 CurrentMouse)
{
}

void sdpGtkMouseInput::OnRButtonStartDrag(GdkModifierType Modifiers, const sdpVector2 CurrentMouse)
{
}

void sdpGtkMouseInput::OnRButtonDrag(GdkModifierType Modifiers, const sdpVector2 CurrentMouse, const sdpVector2 LastMouse, const sdpVector2 StartMouse)
{
}

void sdpGtkMouseInput::OnRButtonEndDrag(GdkModifierType Modifiers, const sdpVector2 CurrentMouse, const sdpVector2 LastMouse, const sdpVector2 StartMouse)
{
}

void sdpGtkMouseInput::OnLRButtonStartDrag(GdkModifierType Modifiers, const sdpVector2 CurrentMouse)
{
}

void sdpGtkMouseInput::OnLRButtonDrag(GdkModifierType Modifiers, const sdpVector2 CurrentMouse, const sdpVector2 LastMouse, const sdpVector2 StartMouse)
{
}

void sdpGtkMouseInput::OnLRButtonEndDrag(GdkModifierType Modifiers, const sdpVector2 CurrentMouse, const sdpVector2 LastMouse, const sdpVector2 StartMouse)
{
}


