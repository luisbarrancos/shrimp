#ifndef SDPGTKEVENT_H
#define SDPGTKEVENT_H

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
		\brief Declares the sdpGtkEvent class, which is the base class for SDPGTK events
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkobject.h"
#include "sdpgtkobjectcontainer.h"

#ifdef	SDPWIN32
#undef	CreateEvent
#endif //SDPWIN32

// Forward class declarations
class sdpGtkObjectEvent;
class sdpGtkLoopEvent;

///////////////////////////////////////////////////////////////////
// sdpGtkEvent

/// Base class for all SDPGTK events
class sdpGtkEvent
{
public:
	sdpGtkEvent(SDPCSTRING EventSignal, SDPCSTRING EventName, bool After, sdpGtkObjectContainer* EventContainer);
	virtual ~sdpGtkEvent();

	/// Static function for creating event instances based on their type
	static sdpGtkEvent* CreateEvent(SDPCSTRING EventSignal, SDPCSTRING EventName, bool After, sdpGtkObjectContainer* EventContainer, GtkObject* EventObject);

	/// Returns the event signal type
	const sdpString& Signal() { return m_EventSignal; }
	/// Returns the event name
	const sdpString& Name() { return m_EventName; }
	/// Returns the event container
	const sdpGtkObjectContainer* Container() { return m_EventContainer; }
	/// Returns the event handler id
	const guint Handler() { return m_EventHandler; }

	/// Connects the event to the GTK+ event machanisms (implement in derived classes)
	virtual void Connect() = 0;
	/// Disconnects the event from GTK+
	virtual void Disconnect() = 0;

	/// Tests whether this is an sdpGtkObjectEvent
	bool  IsObjectEvent();
	/// Tests whether this is an sdpGtkLoopEvent
	bool IsLoopEvent();
 
	/// Casts this event to an sdpGtkObjectEvent
	operator sdpGtkObjectEvent* () { g_assert(IsObjectEvent()); return (sdpGtkObjectEvent*)this; }
	/// Casts this event to an sdpGtkLoopEvent
	operator sdpGtkLoopEvent*() { g_assert(IsLoopEvent()); return (sdpGtkLoopEvent*)this; }
			
// Machine-generated type-cast operators for all event types ...
#include "sdpgtkeventscasting.h"

protected:
	/// Stores the event signal
	const sdpString m_EventSignal;
	/// Stores the event name
	const sdpString m_EventName;
	/// Stores whether we want to be signalled before or after the default handler
	const bool m_After;
	/// Stores the container that owns this event
	sdpGtkObjectContainer* const m_EventContainer;
	/// Stores the event handler id
	guint m_EventHandler;
};

///////////////////////////////////////////////////////////////////////
// sdpGtkObjectEvent

/// Base class for the majority of GTK+ object and widget-related events
class sdpGtkObjectEvent : public sdpGtkEvent
{
public:
	sdpGtkObjectEvent(SDPCSTRING EventSignal, SDPCSTRING EventName, bool After, sdpGtkObjectContainer* EventContainer, GtkObject* EventObject);
	
	/// Returns the event object
	const GtkObject* Object() { return m_EventObject; }

	/// Disconnects the event from GTK+
	void Disconnect();
	/// Blocks this event from being signalled
	virtual void Block();
	/// Restores normal signalling of this event
	virtual void Unblock();

protected:
	/// Stores the GTK+ object associated with this event
	GtkObject* m_EventObject;
};

//////////////////////////////////////////////////////////////////////
// sdpGtkLoopEvent

/// Base class for quit, timeout, and idle events
class sdpGtkLoopEvent : public sdpGtkEvent
{
public:
	sdpGtkLoopEvent(SDPCSTRING EventSignal, SDPCSTRING EventName, bool After, sdpGtkObjectContainer* EventContainer);

	/// The main event function
  gint Event();

	/// The raw event function (called by the GTK+ signal mechanism)
  static gint RawEvent(gpointer EventData);

	/// Returns the result
	bool Result();
	void SetResult(bool Result);

protected:
	/// The event result
	bool m_Result;
};



#endif // SDPGTKEVENT_H

