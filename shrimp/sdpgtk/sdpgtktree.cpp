
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

#include "sdpgtktree.h"

///////////////////////////////////////////////////////////////
// sdpGtkTree

sdpGtkTree::sdpGtkTree() : sdpGtkContainer()
{
}

sdpGtkTree::sdpGtkTree(GtkTree* Tree) : sdpGtkContainer(GTK_CONTAINER(Tree))
{
}

bool sdpGtkTree::Create()
{
	m_Object = GTK_OBJECT(gtk_tree_new());
	return Attached() ? true : false;
}

bool sdpGtkTree::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	return Create();
}

bool sdpGtkTree::AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child)
{
	// Sanity checks ...
	g_assert(ObjectContainer);
	g_assert(Child);
	
	AppendItem(GTK_WIDGET(Child->Object()));
	
	return true;
}

void sdpGtkTree::AppendItem(GtkWidget* Item)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	g_return_if_fail(Item);

	gtk_tree_append(*this, Item);
}

void sdpGtkTree::PrependItem(GtkWidget* Item)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	g_return_if_fail(Item);
	
	gtk_tree_prepend(*this, Item);
}

void sdpGtkTree::InsertItem(GtkWidget* Item, gint Position)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	g_return_if_fail(Item);
	
	gtk_tree_insert(*this, Item, Position);
}

void sdpGtkTree::ClearItems(gint Start, gint End)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	
	gtk_tree_clear_items(*this, Start, End);
}

void sdpGtkTree::SelectItem(gint Item)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	
	gtk_tree_select_item(*this, Item);
}

void sdpGtkTree::DeselectItem(gint Item)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	
	gtk_tree_unselect_item(*this, Item);
}

void sdpGtkTree::SelectChild(GtkWidget* Child)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	
	gtk_tree_select_child(*this, Child);
}

void sdpGtkTree::DeselectChild(GtkWidget* Child)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	
	gtk_tree_unselect_child(*this, Child);
}

gint sdpGtkTree::ChildPosition(GtkWidget* Child)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), -1);
	
	return gtk_tree_child_position(*this, Child);
}

void sdpGtkTree::SetSelectionMode(GtkSelectionMode Mode)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_tree_set_selection_mode(*this, Mode);	
}

void sdpGtkTree::SetLines(bool Visible)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	
	gtk_tree_set_view_lines(*this, Visible);
}




