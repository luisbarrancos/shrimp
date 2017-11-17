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
		\brief Implements the sdpGtkClipboard class, which makes it easy to synchronously retrieve data from the clipboard (primary X selection)
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkclipboard.h"
#include "sdpgtkevents.h"
#include "sdpgtkutility.h"

#ifdef	SDPWIN32
#include <windows.h>
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////
// sdpGtkClipboard

sdpGtkClipboard::sdpGtkClipboard() :
	sdpGtkClipboardBase(),
	m_Waiting(false),
	m_ContainsData(false)
{
	// Create and load our UI template ...
	std::istringstream uitemplate(
		"<gtkml>"
			"<window type=\"toplevel\" show=\"false\">"
				"<event signal=\"selection-received\" name=\"selectionreceived\"/>"
			"</window>"
		"</gtkml>\n");

	g_return_if_fail(Load(uitemplate, ""));
}

sdpGtkClipboard::~sdpGtkClipboard()
{
	RootWidget().Destroy();
}

bool sdpGtkClipboard::StartSelection()
{
	// Get ready to loop, waiting for results ...
	m_Waiting = true;
	// Don't assume success until we're sure ...
	m_ContainsData = false;

	// Start the selection process ...
	g_return_val_if_fail(RequestSelection(), false);

	// Enter our loop, waiting for results ...
	while(m_Waiting)
		sdpGtkHandlePendingEvents();

	return m_ContainsData;
}

void sdpGtkClipboard::OnEvent(sdpGtkEvent* Event)
{
	// Sanity checks ...
	g_assert(Event);

	if(Event->Name() == "selectionreceived")
		{
			m_Waiting = false;
			m_ContainsData = ReceiveSelection(Event);
		}
	else
		sdpGtkClipboardBase::OnEvent(Event);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// sdpGtkClipboardText

const sdpString& sdpGtkClipboardText::GetText()
{
	StartSelection();
	return m_Text;
}

bool sdpGtkClipboardText::RequestSelection()
{
	// Cleanup leftovers ...
	m_Text.clear();

#ifdef SDPWIN32

	g_return_val_if_fail(OpenClipboard(0), false);
	g_return_val_if_fail(GetClipboardData(CF_TEXT), false);

	m_Text = static_cast<char*>(GetClipboardData(CF_TEXT));

	g_return_val_if_fail(CloseClipboard(), false);

	m_Waiting = false;
	m_ContainsData = true;

#else // SDPWIN32

	// Request the primary X selection as text ...
	g_return_val_if_fail(gtk_selection_convert(RootWidget(), gdk_atom_intern("CLIPBOARD", false), gdk_atom_intern("STRING", false), GDK_CURRENT_TIME), false);

#endif // !SDPWIN32

	return true;
}

bool sdpGtkClipboardText::ReceiveSelection(sdpGtkEvent* Event)
{
	// Get the selection as text ...
	sdpGtkEventWidgetSelectionReceived* event = static_cast<sdpGtkEventWidgetSelectionReceived*>(Event);
	GtkSelectionData* selection = event->Selection();
	g_return_val_if_fail(selection->length >= 0, false);

	m_Text = reinterpret_cast<char*>(selection->data);

	return true;
}


