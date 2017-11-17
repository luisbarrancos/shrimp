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
#include "sdpgtkloopevents.h"

///////////////////////////////////////////////////////////////////////////////
// sdpGtkEventQuit ('quit')

sdpGtkEventQuit::sdpGtkEventQuit(SDPCSTRING EventType, SDPCSTRING EventName, bool After, sdpGtkObjectContainer* EventContainer) : 
	sdpGtkLoopEvent(EventType, EventName, After, EventContainer)
{
	// By default, the event should only be called once ...
	m_Result = false;
}

void sdpGtkEventQuit::Connect()
{
  m_EventHandler = gtk_quit_add(gtk_main_level(), RawEvent, gpointer(this));
}

void sdpGtkEventQuit::Disconnect()
{
	// Sanity checks ...
	g_assert(m_EventHandler);

	gtk_quit_remove(m_EventHandler);
	m_EventHandler = 0;
}

///////////////////////////////////////////////////////////////////////////////
// sdpGtkEventTimeout ('timeout')

sdpGtkEventTimeout::sdpGtkEventTimeout(SDPCSTRING EventType, SDPCSTRING EventName, bool After, sdpGtkObjectContainer* EventContainer) : 
	sdpGtkLoopEvent(EventType, EventName, After, EventContainer)
{
	// By default, the event should be called indefinitely ...
	m_Result = true;
	m_Duration = 0;
}

void sdpGtkEventTimeout::Connect()
{
  m_EventHandler = gtk_timeout_add(m_Duration, RawEvent, gpointer(this));
}

void sdpGtkEventTimeout::Disconnect()
{
	// Sanity checks ...
	g_assert(m_EventHandler);

	gtk_timeout_remove(m_EventHandler);
	m_EventHandler = 0;
}

gulong sdpGtkEventTimeout::Duration()
{
	return m_Duration;
}

void sdpGtkEventTimeout::SetDuration(gulong Duration)
{
	m_Duration = Duration;
}

///////////////////////////////////////////////////////////////////////////////
// sdpGtkEventIdle ('idle')

sdpGtkEventIdle::sdpGtkEventIdle(SDPCSTRING EventType, SDPCSTRING EventName, bool After, sdpGtkObjectContainer* EventContainer) : 
	sdpGtkLoopEvent(EventType, EventName, After, EventContainer)
{
	// By default, the event should be called indefinitely ...
	m_Result = true;
}

void sdpGtkEventIdle::Connect()
{
  m_EventHandler = gtk_idle_add(RawEvent, gpointer(this));
}

void sdpGtkEventIdle::Disconnect()
{
	// Sanity checks ...
	g_assert(m_EventHandler);

	gtk_idle_remove(m_EventHandler);
	m_EventHandler = 0;
}

