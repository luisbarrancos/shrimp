#ifndef SDPGTKSTATUSBAR_H
#define SDPGTKSTATUSBAR_H

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
		\brief Declares the sdpGtkStatusbar class, which encapsulates a GtkStatusbar widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkhbox.h"

////////////////////////////////////////////////////////////////////////////////////////
// sdpGtkStatusbar

/// Encapsulates a GtkStatusbar widget
class sdpGtkStatusbar : public sdpGtkHBox
{
public:
	/// Standard constructor
	sdpGtkStatusbar();
	/// Attaches this instance to an existing GtkStatusbar widget
	sdpGtkStatusbar(GtkStatusbar* Statusbar);

	/// Creates a new GtkStatusbar widget
	bool Create();
	/// Creates a new GtkStatusbar widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Creates a new context
	guint GetContextID(SDPCSTRING Description);
	/// Pushes a new message
	guint Push(guint ContextID, SDPCSTRING Text);
	/// Popss the top message
	void Pop(guint ContextID);
	/// Removes all messages associated with the given context
	void Remove(guint ContextID, guint MessageID); 

	/// Casts this instance into a GtkStatusbar pointer
	operator GtkStatusbar*() { return GTK_STATUSBAR(m_Object); }
};



#endif // SDPGTKSTATUSBAR_H

