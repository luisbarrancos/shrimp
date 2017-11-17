#ifndef SDPGTKLIST_H
#define SDPGTKLIST_H

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
		\brief Declares the sdpGtkList class, which encapsulates a GtkList widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkcontainer.h"

///////////////////////////////////////////////////////////////////////
// sdpGtkList

/// Encapsulates a GtkList widget
class sdpGtkList : public sdpGtkContainer
{
public:
	/// Standard constructor
	sdpGtkList();
	/// Attaches this instance to an existing GtkList widget
	sdpGtkList(GtkList* List);

	/// Creates a new GtkList widget
	bool Create();
	/// Creates a new GtkList widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Casts this instance into a GtkList pointer
	operator GtkList*() { return GTK_LIST(m_Object); }
};



#endif // SDPGTKLIST_H
