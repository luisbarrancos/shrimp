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

#include "sdpgtkfileselector.h"
#include "sdpgtkevents.h"

sdpGtkFileSelector::sdpGtkFileSelector(SDPCSTRING Title, SDPCSTRING FilePath) :
	m_OK(false),
	m_Title(Title),
	m_FilePath(FilePath)
{
}

bool sdpGtkFileSelector::OK() const
{
	return m_OK;
}

bool sdpGtkFileSelector::Cancelled() const
{
	return !m_OK;
}

sdpString sdpGtkFileSelector::Title() const
{
	return m_Title;
}

sdpString sdpGtkFileSelector::FilePath() const
{
	return m_FilePath;
}

void sdpGtkFileSelector::DoModal()
{
	// Load the user interface ...
	g_return_if_fail(Load());

	// Enter our modal loop ...
	sdpGtkObjectContainer::DoModal();
}

void sdpGtkFileSelector::DoModal(GtkWindow* TransientOwner)
{
	// Load the user interface ...
	g_return_if_fail(Load());

	// Enter our modal loop ...
	sdpGtkObjectContainer::DoModal(TransientOwner);
}

void sdpGtkFileSelector::DoModal(sdpGtkWindow& TransientOwner)
{
	// Load the user interface ...
	g_return_if_fail(Load());

	// Enter our modal loop ...
	sdpGtkObjectContainer::DoModal(TransientOwner);
}

// UI creation ...
bool sdpGtkFileSelector::Load()
{
	// Load the GTKML document ...
	std::istringstream dialogtemplate("<gtkml><fileselection/></gtkml>\n");
	g_return_val_if_fail(sdpGtkObjectContainer::Load(dialogtemplate, ""), false);

	// Throw the title into our titlebar ...
	RootWindow().SetTitle(m_Title);

	// Set the initial filepath ...
	RootFileSelection().SetFilePath(m_FilePath);

	// Map some events ...
	MapEvent("delete-event", "ondelete", false, RootObject(), true);
	MapEvent("destroy", "ondestroy", false, RootObject(), true);
	MapEvent("clicked", "onok", false, RootFileSelection().OKButton(), true);
	MapEvent("clicked", "oncancel", false, RootFileSelection().CancelButton(), true);

	return true;
}

// Custom event handling ...
void sdpGtkFileSelector::OnEvent(sdpGtkEvent* Event)
{
	// Sanity checks ...
	g_assert(Event);

	if(Event->Name() == "ondelete")
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

// Called when the user hits the WM "close" button ...
void sdpGtkFileSelector::OnDelete(sdpGtkEvent* Event)
{
	// Sanity checks ...
	g_assert(Event);

	// Don't allow the window to close ... treat it like a cancel, instead ...
	((sdpGtkEventWidgetDeleteEvent*)Event)->SetResult(true);

	OnCancel();
}

// Called when we're going away ...
void sdpGtkFileSelector::OnDestroy()
{
	// No more events from this point forward ...
	DisconnectAllEvents();

	// Let the modal loop end ...
	CancelModal();
}

// Called when the user hits the standard "OK" button ...
void sdpGtkFileSelector::OnOK()
{
	// Grab the user's filepath ...
	m_FilePath = RootFileSelection().GetFilePath();

	m_OK = true;
	RootWidget().Destroy();

}

// Called when the user hits the standard "Cancel" button ...
void sdpGtkFileSelector::OnCancel()
{
	m_OK = false;
	RootWidget().Destroy();

}

// Called when the user hits the standard "Help" button ...
void sdpGtkFileSelector::OnHelp()
{
}


