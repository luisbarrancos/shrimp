#ifndef SDPGTKTREEITEM_H
#define SDPGTKTREEITEM_H

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
		\brief Declares the sdpGtkTreeItem class, which encapsulates a GtkTreeItem widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkitem.h"

////////////////////////////////////////////////////////////////////////
// sdpGtkTreeItem

/// Encapsulates a GtkTreeItem widget
class sdpGtkTreeItem : public sdpGtkItem
{
public:
	/// Standard constructor
	sdpGtkTreeItem();
	/// Attaches this instance to an existing GtkTreeItem widget
	sdpGtkTreeItem(GtkTreeItem* TreeItem);

	/// Creates a new GtkTreeItem widget
	bool Create();
	/// Creates a new GtkTreeItem widget with a label
	bool Create(SDPCSTRING Label);
	/// Creates a new GtkTreeItem widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	bool AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child);

	/// Sets the child tree for this item
	void SetSubTree(GtkWidget* Widget);
	/// Removes any children from this item
	void RemoveSubTree();
	/// Selects this item
	void Select();
	/// Deselects this item
	void Deselect();
	/// Expands this item
	void Expand();
	/// Collapses this item
	void Collapse();

	/// Casts this instance into a GtkTreeItem pointer
	operator GtkTreeItem*() { return GTK_TREE_ITEM(m_Object); }
};

#endif // SDPGTKTREEITEM_H

