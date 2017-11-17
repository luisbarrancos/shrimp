#ifndef SDPGTKSOCKET_H
#define SDPGTKSOCKET_H

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
		\brief Declares class sdpGtkSocket which encapsulates a GtkSocket widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkcontainer.h"

/// Encapsulates a GtkSocket widget
class sdpGtkSocket : public sdpGtkContainer
{
public:
	/// Standard constructor
	sdpGtkSocket();
	/// Attaches this instance to an existing GtkSocket widget
	sdpGtkSocket(GtkSocket* Socket);

	/// Creates the underlying GtkSocket widget
	bool Create();
	/// Creates the underlying GtkSocket widget from GTKML (XML)
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);
	
	/// Returns the socket ID
	guint32 SocketID();
	/// Returns "true" if a plug is in the socket
	bool Plugged();
	/// "Capture" an existing window
	void Steal(guint32 WindowID);

	/// Casts this instance to a GtkSocket pointer
	operator GtkSocket*() { return GTK_SOCKET(m_Object); }
};

#endif // SDPGTKSOCKET_H

