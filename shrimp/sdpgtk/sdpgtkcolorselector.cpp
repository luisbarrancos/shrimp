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
		\brief Implements the sdpGtkColorSelector class, a standard color selection dialog
		\author Tim Shead (tshead@k-3d.com)
*/

#include "sdpgtkcolorselector.h"
#include "sdpgtkevents.h"
#include "sdpgtkutility.h"

/////////////////////////////////////////////////////////////////////////
// sdpGtkColorSelector

sdpGtkColorSelector::sdpGtkColorSelector(SDPCSTRING Title, sdpVector3 Color) :
	m_OK(false),
	m_Color(Color)
{
	// Load the GTKML document ...
	sdpString dialogtemplate="<gtkml><colorselectiondialog/></gtkml>\n";
	g_return_if_fail(sdpGtkObjectContainer::Load(dialogtemplate, "sdpGtkColorSelector"));

	// Set the title ...
	RootWindow().SetTitle(Title);

	// Hide the help button ...
	RootColorSelectionDialog().HelpButton().Hide();

	// Our other dialogs don't set a default button ...
	RootWindow().SetDefault(0);

	// Map some events ...
	MapEvent("delete-event", "ondelete", false, RootObject(), true);
	MapEvent("destroy", "ondestroy", false, RootObject(), true);
	MapEvent("clicked", "onok", false, RootColorSelectionDialog().OKButton(), true);
	MapEvent("clicked", "oncancel", false, RootColorSelectionDialog().CancelButton(), true);
	MapEvent("color-changed", "oncolorchanged", false, RootColorSelectionDialog().Selection(), true);

	// Set the initial color ...
	sdpGtkHandlePendingEvents(); // This gives the color selection a chance to initialize its gc properly, before we try to set the color
	RootColorSelectionDialog().Selection().SetColor(m_Color);

	RootWidget().Show();
}

bool sdpGtkColorSelector::OK()
{
	return m_OK;
}

bool sdpGtkColorSelector::Cancelled()
{
	return !m_OK;
}

SDPCSTRING sdpGtkColorSelector::Title()
{
	return m_Title;
}

sdpVector3 sdpGtkColorSelector::Color()
{
	return m_Color;
}

// Custom event handling ...
void sdpGtkColorSelector::OnEvent(sdpGtkEvent* Event)
{
	// Sanity checks ...
	g_assert(Event);

	if(Event->Name() == "oncolorchanged")
		RawOnColorChanged();
	else if(Event->Name() == "ondelete")
		OnDelete(Event);
	else if(Event->Name() == "ondestroy")
		OnDestroy();
	else if(Event->Name() == "onok")
		OnOK();
	else if(Event->Name() == "oncancel")
		OnCancel();
	else if(Event->Name() == "onhelp")
		OnHelp();
	else
		sdpGtkObjectContainer::OnEvent(Event);
}

// Called anytime the color changes ...
void sdpGtkColorSelector::RawOnColorChanged()
{
	// This is a hack since GTK+ seems to call this event twice ...
	sdpVector3 newcolor;
	RootColorSelectionDialog().Selection().GetColor(newcolor);
	
	if(newcolor != m_Color)
		OnColorChanged();
}

// Called anytime the color changes ...
void sdpGtkColorSelector::OnColorChanged()
{
	RootColorSelectionDialog().Selection().GetColor(m_Color);
}

// Called when the user hits the WM "close" button ...
void sdpGtkColorSelector::OnDelete(sdpGtkEvent* Event)
{
	// Sanity checks ...
	g_assert(Event);

	// Don't allow the window to close ... treat it like a cancel, instead ...
	((sdpGtkEventWidgetDeleteEvent*)Event)->SetResult(true);
	
	OnCancel();
}

// Called when we're going away ...
void sdpGtkColorSelector::OnDestroy()
{
	// No more events from this point forward ...
	DisconnectAllEvents();

	// Let the modal loop end ...
	CancelModal();
}

// Called when the user hits the standard "OK" button ...
void sdpGtkColorSelector::OnOK()
{
	m_OK = true;
	RootWidget().Destroy();
}

// Called when the user hits the standard "Cancel" button ...
void sdpGtkColorSelector::OnCancel()
{
	m_OK = false;
	RootWidget().Destroy();
}

// Called when the user hits the standard "Help" button ...
void sdpGtkColorSelector::OnHelp()
{
}


