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

#include "sdpgtkevent.h"
#include "sdpgtkloopevents.h"
#include "sdpgtkevents.h"

#include <iostream>

////////////////////////////////////////////////////////////////////
// sdpGtkEvent

sdpGtkEvent* sdpGtkEvent::CreateEvent(SDPCSTRING EventSignal, SDPCSTRING EventName, bool After, sdpGtkObjectContainer* EventContainer, GtkObject* EventObject)
{
	// Create a new event object, based on the type ...
	const sdpString signal(EventSignal);

	// Our "special" objects ...
	if(signal == "quit")
		return new sdpGtkEventQuit(EventSignal, EventName, After, EventContainer);
	if(signal == "timeout")
		return new sdpGtkEventTimeout(EventSignal, EventName, After, EventContainer);
	if(signal == "idle")
		return new sdpGtkEventIdle(EventSignal, EventName, After, EventContainer);

// Machine-generated code that instantiates "normal" event objects ...
#include "sdpgtkeventcreation.h"

	std::cout << "sdpGtkEvent::CreateEvent(): Unknown event signal \"" << signal << "\"!!!" << std::endl;

	return 0;
}

sdpGtkEvent::sdpGtkEvent(SDPCSTRING EventSignal, SDPCSTRING EventName, bool After, sdpGtkObjectContainer* EventContainer) :
	m_EventSignal(EventSignal),
	m_EventName(EventName),
	m_After(After),
	m_EventContainer(EventContainer),
	m_EventHandler(0)
{
	// Sanity checks ...
	g_assert_string(EventSignal);
	g_assert_string(EventName);
	g_assert(EventContainer);
}


sdpGtkEvent::~sdpGtkEvent()
{
}

bool sdpGtkEvent::IsObjectEvent()
{
	return !IsLoopEvent();
}

bool sdpGtkEvent::IsLoopEvent()
{
	return (m_EventSignal == "quit" || m_EventSignal == "timeout" || m_EventSignal == "idle");
}

/////////////////////////////////////////////////////////////////////
// sdpGtkObjectEvent

sdpGtkObjectEvent::sdpGtkObjectEvent(SDPCSTRING EventSignal, SDPCSTRING EventName, bool After, sdpGtkObjectContainer* EventContainer, GtkObject* EventObject) : 
	sdpGtkEvent(EventSignal, EventName, After, EventContainer),
	m_EventObject(EventObject)
{
	// Sanity checks ...
	g_assert(EventObject);
}

void sdpGtkObjectEvent::Disconnect()
{
	// Sanity checks ...
	g_assert(m_EventHandler);

	gtk_signal_disconnect(m_EventObject, m_EventHandler);
	m_EventHandler = 0;
}

void sdpGtkObjectEvent::Block()
{
	// Sanity checks ...
	g_assert(m_EventHandler);

	gtk_signal_handler_block(m_EventObject, m_EventHandler);
}

void sdpGtkObjectEvent::Unblock()
{
	// Sanity checks ...
	g_assert(m_EventHandler);

	gtk_signal_handler_unblock(m_EventObject, m_EventHandler);
}


///////////////////////////////////////////////////////////////////////
// sdpGtkLoopEvent

sdpGtkLoopEvent::sdpGtkLoopEvent(SDPCSTRING EventSignal, SDPCSTRING EventName, bool After, sdpGtkObjectContainer* EventContainer) : 
	sdpGtkEvent(EventSignal, EventName, After, EventContainer)
{
	g_return_if_fail(false == After);
}

gint sdpGtkLoopEvent::Event()
{
	m_EventContainer->OnEvent(this);
	return m_Result;
}

gint sdpGtkLoopEvent::RawEvent(gpointer EventData)
{
	return ((sdpGtkLoopEvent*)EventData)->Event();
}

bool sdpGtkLoopEvent::Result()
{
	return m_Result;
}

void sdpGtkLoopEvent::SetResult(bool Result)
{
	m_Result = Result;
}


