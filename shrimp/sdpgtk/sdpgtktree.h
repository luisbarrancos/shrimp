#ifndef SDPGTKTREE_H
#define SDPGTKTREE_H

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
		\brief Declares the sdpGtkTree class, which encapsulates a GtkTree widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkcontainer.h"

///////////////////////////////////////////////////////////////////////
// sdpGtkTree

/// Encapsulates a GtkTree widget
class sdpGtkTree : public sdpGtkContainer
{
public:
	/// Standard constructor
	sdpGtkTree();
	/// Attaches this instance to an existing GtkTree widget
	sdpGtkTree(GtkTree* Tree);

	/// Creates a new GtkTree widget
	bool Create();
	/// Creates a new GtkTree widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	bool AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child);

	/// Appends an item to the tree
	void AppendItem(GtkWidget* Item);
	/// Prepends an item to the tree
	void PrependItem(GtkWidget* Item);
	/// Inserts an item at the specified index
	void InsertItem(GtkWidget* Item, gint Position);
	
	/// Removes a range of items
	void ClearItems(gint Start, gint End);
	
	/// Selects an item
	void SelectItem(gint Item);
	/// Deselects an item
	void DeselectItem(gint Item);
	
	/// Selects a child tree
	void SelectChild(GtkWidget* Child);
	/// Deselects a child tree
	void DeselectChild(GtkWidget* Child);

	/// Returns the position of an item
	gint ChildPosition(GtkWidget* Child);
			
	/// Sets the tree selection mode
	void SetSelectionMode(GtkSelectionMode Mode);
	/// Sets the visibility of lines
	void SetLines(bool Visible);


	/// Casts this instance into a GtkTree pointer
	operator GtkTree*() { return GTK_TREE(m_Object); }
};



#endif // SDPGTKTREE_H

