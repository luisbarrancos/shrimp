#ifndef SDPGTKLISTITEM_H
#define SDPGTKLISTITEM_H

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
		\brief Declares the sdpGtkListItem class, which encapsulates a GtkListItem widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkitem.h"

////////////////////////////////////////////////////////////////////////
// sdpGtkListItem

/// Encapsulates a GtkListItem widget
class sdpGtkListItem : public sdpGtkItem
{
public:
	/// Standard constructor
	sdpGtkListItem();
	/// Attaches this instance to an existing GtkListItem widget
	sdpGtkListItem(GtkListItem* ListItem);

	/// Creates a new GtkListItem widget
	bool Create();
	/// Creates a new GtkListItem widget with a label
	bool Create(SDPCSTRING Label);
	/// Creates a new GtkListItem widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Selects this item
	void Select();
	/// Deselects this item
	void Deselect();

	/// Casts this instance into a GtkListItem pointer
	operator GtkListItem*() { return GTK_LIST_ITEM(m_Object); }
};

#endif // SDPGTKLISTITEM_H
