#ifndef SDPGTKLOOPEVENTS_H
#define SDPGTKLOOPEVENTS_H

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





#include "sdpgtkevent.h"

///////////////////////////////////////////////////////////////////////////////
// sdpGtkEventQuit ('quit')

class sdpGtkEventQuit : public sdpGtkLoopEvent
{
public:
  sdpGtkEventQuit(SDPCSTRING EventType, SDPCSTRING EventName, bool After, sdpGtkObjectContainer* EventOwner);

  void Connect();
	void Disconnect();
};

///////////////////////////////////////////////////////////////////////////////
// sdpGtkEventTimeout ('timeout')

class sdpGtkEventTimeout : public sdpGtkLoopEvent
{
public:
  sdpGtkEventTimeout(SDPCSTRING EventType, SDPCSTRING EventName, bool After, sdpGtkObjectContainer* EventOwner);

  void Connect();
	void Disconnect();

	gulong Duration();
	void SetDuration(gulong Duration);

protected:
	gulong m_Duration;
};

///////////////////////////////////////////////////////////////////////////////
// sdpGtkEventIdle ('idle')

class sdpGtkEventIdle : public sdpGtkLoopEvent
{
public:
  sdpGtkEventIdle(SDPCSTRING EventType, SDPCSTRING EventName, bool After, sdpGtkObjectContainer* EventOwner);

  void Connect();
	void Disconnect();
};


#endif // SDPGTKLOOPEVENTS_H
