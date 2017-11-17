
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

#include "sdpgtktreeitem.h"
#include "sdpgtkutility.h"

///////////////////////////////////////////////////////////////
// sdpGtkTreeItem

sdpGtkTreeItem::sdpGtkTreeItem() : sdpGtkItem()
{
}

sdpGtkTreeItem::sdpGtkTreeItem(GtkTreeItem* TreeItem) : sdpGtkItem(GTK_ITEM(TreeItem))
{
}

bool sdpGtkTreeItem::Create()
{
	m_Object = GTK_OBJECT(gtk_tree_item_new());
	return Attached();
}

bool sdpGtkTreeItem::Create(SDPCSTRING Label)
{
	// Sanity checks ...
	g_assert(Label);

	m_Object = GTK_OBJECT(gtk_tree_item_new_with_label(Label));
	return Attached();
}

bool sdpGtkTreeItem::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	const sdpString text(sdpGtkInternationalText(Document, Element));
	return text.size() ? Create(text) : Create();
}

bool sdpGtkTreeItem::AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child)
{
	// Sanity checks ...
	g_assert(Child);

	SetSubTree(GTK_WIDGET(Child->Object()));

	return true;
}

void sdpGtkTreeItem::SetSubTree(GtkWidget* Widget)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_tree_item_set_subtree(*this, Widget);	
}

void sdpGtkTreeItem::RemoveSubTree()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_tree_item_remove_subtree(*this);
}

void sdpGtkTreeItem::Select()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_tree_item_select(*this);
}

void sdpGtkTreeItem::Deselect()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_tree_item_deselect(*this);
}

void sdpGtkTreeItem::Expand()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_tree_item_expand(*this);
}

void sdpGtkTreeItem::Collapse()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_tree_item_collapse(*this);
}


