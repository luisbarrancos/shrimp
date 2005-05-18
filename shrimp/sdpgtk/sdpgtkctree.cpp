
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

#include "sdpgtkctree.h"
#include "sdpgtkutility.h"

sdpGtkCTree::sdpGtkCTree() : sdpGtkCList()
{
}


sdpGtkCTree::sdpGtkCTree(GtkCTree* CTree) : sdpGtkCList(GTK_CLIST(CTree))
{
}

bool sdpGtkCTree::Create(gint Columns, gint TreeColumn)
{
	// Sanity checks ...
	g_assert(Columns > 0);
	g_assert(TreeColumn >= 0);
	g_assert(TreeColumn < Columns);

	m_Object = GTK_OBJECT(gtk_ctree_new(Columns, TreeColumn));
	return Attached();
}

bool sdpGtkCTree::Create(gint Columns, gint TreeColumn, SDPCSTRING Titles[])
{
	// Sanity checks ...
	g_assert(Columns > 0);
	g_assert(TreeColumn >= 0);
	g_assert(TreeColumn < Columns);
	g_assert(Titles);

	m_Object = GTK_OBJECT(gtk_ctree_new_with_titles(Columns, TreeColumn, const_cast<gchar**>(Titles)));
	return Attached();
}

bool sdpGtkCTree::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	const gint columns = sdpxml::GetAttribute(Element, "columns", 0);
	sdpGtkMarkAttribute(Document, Element, "columns");

	g_return_val_if_fail(columns, false);	// You MUST specify how many columns you want!

	const gint treecolumn = sdpxml::GetAttribute(Element, "treecolumn", -1);
	sdpGtkMarkAttribute(Document, Element, "treecolumn");

	g_return_val_if_fail(columns != -1, false);	// You MUST specify the tree column!!

	return Create(columns, treecolumn);
}

GtkCTreeNode* sdpGtkCTree::InsertNode(GtkCTreeNode* Parent, GtkCTreeNode* Sibling, SDPCSTRING Text[], guint8 Spacing, GdkPixmap* PixmapClosed, GdkBitmap* MaskClosed, GdkPixmap* PixmapOpened, GdkBitmap* MaskOpened, gboolean IsLeaf, gboolean Expanded)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return gtk_ctree_insert_node(*this, Parent, Sibling, const_cast<gchar**>(Text), Spacing, PixmapClosed, MaskClosed, PixmapOpened, MaskOpened, IsLeaf, Expanded);
}

void sdpGtkCTree::RemoveNode(GtkCTreeNode* Node)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_remove_node(*this, Node);
}

gboolean sdpGtkCTree::IsViewable(GtkCTreeNode* Node)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), false);

	return gtk_ctree_is_viewable(*this, Node);
}

GtkCTreeNode* sdpGtkCTree::Last(GtkCTreeNode* Node)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return gtk_ctree_last(*this, Node);
}

GtkCTreeNode* sdpGtkCTree::Node(GtkCTreeRow* Row)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return gtk_ctree_find_node_ptr(*this, Row);
}

GtkCTreeNode* sdpGtkCTree::Node(guint Row)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return gtk_ctree_node_nth(*this, Row);
}

gboolean sdpGtkCTree::IsAncestor(GtkCTreeNode* Node, GtkCTreeNode* Child)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), false);

	return gtk_ctree_is_ancestor(*this, Node, Child);
}

void sdpGtkCTree::Move(GtkCTreeNode* Node, GtkCTreeNode* NewParent, GtkCTreeNode* NewSibling)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_move(*this, Node, NewParent, NewSibling);
}

void sdpGtkCTree::Expand(GtkCTreeNode* Node)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_expand(*this, Node);
}

void sdpGtkCTree::ExpandRecursive(GtkCTreeNode* Node)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_expand_recursive(*this, Node);
}

void sdpGtkCTree::ExpandToDepth(GtkCTreeNode* Node, gint Depth)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_expand_to_depth(*this, Node, Depth);
}

void sdpGtkCTree::Collapse(GtkCTreeNode* Node)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_collapse(*this, Node);
}

void sdpGtkCTree::CollapseRecursive(GtkCTreeNode* Node)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_collapse_recursive(*this, Node);
}

void sdpGtkCTree::CollapseToDepth(GtkCTreeNode* Node, gint Depth)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_collapse_to_depth(*this, Node, Depth);
}

void sdpGtkCTree::ToggleExpansion(GtkCTreeNode* Node)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_toggle_expansion(*this, Node);
}

void sdpGtkCTree::ToggleExpansionRecursive(GtkCTreeNode* Node)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_toggle_expansion_recursive(*this, Node);
}

void sdpGtkCTree::Select(GtkCTreeNode* Node)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_select(*this, Node);
}

void sdpGtkCTree::SelectRecursive(GtkCTreeNode* Node)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_select_recursive(*this, Node);
}

void sdpGtkCTree::Unselect(GtkCTreeNode* Node)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_unselect(*this, Node);
}

void sdpGtkCTree::UnselectRecursive(GtkCTreeNode* Node)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_unselect_recursive(*this, Node);
}

void sdpGtkCTree::SetText(GtkCTreeNode* Node, gint Column, SDPCSTRING Text)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_node_set_text(*this, Node, Column, Text);
}

void sdpGtkCTree::SetPixmap(GtkCTreeNode* Node, gint Column, GdkPixmap* Pixmap, GdkBitmap* Mask)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_node_set_pixmap(*this, Node, Column, Pixmap, Mask);
}

void sdpGtkCTree::SetPixmapText(GtkCTreeNode* Node, gint Column, SDPCSTRING Text, guint8 Spacing, GdkPixmap* Pixmap, GdkBitmap* Mask)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_node_set_pixtext(*this, Node, Column, Text, Spacing, Pixmap, Mask);
}

void sdpGtkCTree::SetInfo(GtkCTreeNode* Node, SDPCSTRING Text, guint8 Spacing, GdkPixmap* PixmapClosed, GdkBitmap* MaskClosed, GdkPixmap* PixmapOpened, GdkBitmap* MaskOpened, gboolean IsLeaf, gboolean Expanded)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_set_node_info(*this, Node, Text, Spacing, PixmapClosed, MaskClosed, PixmapOpened, PixmapClosed, IsLeaf, Expanded);
}

void sdpGtkCTree::SetShift(GtkCTreeNode* Node, gint Column, gint Vertical, gint Horizontal)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_node_set_shift(*this, Node, Column, Vertical, Horizontal);
}

void sdpGtkCTree::SetSelectable(GtkCTreeNode* Node, gboolean Selectable)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_node_set_selectable(*this, Node, Selectable);
}

gboolean sdpGtkCTree::GetSelectable(GtkCTreeNode* Node)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), false);

	return gtk_ctree_node_get_selectable(*this, Node);
}

GtkCellType sdpGtkCTree::GetCellType(GtkCTreeNode* Node, gint Column)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), GtkCellType(-1));

	return gtk_ctree_node_get_cell_type(*this, Node, Column);
}

sdpString sdpGtkCTree::GetText(GtkCTreeNode* Node, gint Column)
{
	// Sanity checks ...
#ifdef	FAIL_ON_RET
	sdpString tmpResult;
	g_return_val_if_fail(Attached(), tmpResult);
#else
	g_return_val_if_fail(Attached(), sdpString());
#endif

	gchar* text = 0;
	gtk_ctree_node_get_text(*this, Node, Column, &text);
	
	return sdpString(text);
}

gint sdpGtkCTree::GetPixmap(GtkCTreeNode* Node, gint Column, GdkPixmap** Pixmap, GdkBitmap** Mask)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), -1);

	return gtk_ctree_node_get_pixmap(*this, Node, Column, Pixmap, Mask);
}

gint sdpGtkCTree::GetPixmapText(GtkCTreeNode* Node, gint Column, gchar** Text, guint8* Spacing, GdkPixmap** Pixmap, GdkBitmap** Mask)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), -1);

	return gtk_ctree_node_get_pixtext(*this, Node, Column, Text, Spacing, Pixmap, Mask);
}

gint sdpGtkCTree::GetInfo(GtkCTreeNode* Node, gchar** Text, guint8* Spacing, GdkPixmap** PixmapClosed, GdkBitmap** MaskClosed, GdkPixmap** PixmapOpened, GdkBitmap** MaskOpened, gboolean* IsLeaf, gboolean* Expanded)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), -1);

	return gtk_ctree_get_node_info(*this, Node, Text, Spacing, PixmapClosed, MaskClosed, PixmapOpened, MaskOpened, IsLeaf, Expanded);
}

void sdpGtkCTree::SetRowStyle(GtkCTreeNode* Node, GtkStyle* Style)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_node_set_row_style(*this, Node, Style);
}

GtkStyle* sdpGtkCTree::GetRowStyle(GtkCTreeNode* Node)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return gtk_ctree_node_get_row_style(*this, Node);
}

void sdpGtkCTree::SetCellStyle(GtkCTreeNode* Node, gint Column, GtkStyle* Style)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_node_set_cell_style(*this, Node, Column, Style);
}

GtkStyle* sdpGtkCTree::GetCellStyle(GtkCTreeNode* Node, gint Column)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return gtk_ctree_node_get_cell_style(*this, Node, Column);
}

void sdpGtkCTree::SetForegroundColor(GtkCTreeNode* Node, GdkColor* Color)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_node_set_foreground(*this, Node, Color);
}

void sdpGtkCTree::SetBackgroundColor(GtkCTreeNode* Node, GdkColor* Color)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_node_set_background(*this, Node, Color);
}

void sdpGtkCTree::SetRowData(GtkCTreeNode* Node, gpointer Data)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_node_set_row_data(*this, Node, Data);
}

void sdpGtkCTree::SetRowData(GtkCTreeNode* Node, gpointer Data, GtkDestroyNotify Destroy)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_node_set_row_data_full(*this, Node, Data, Destroy);
}

gpointer sdpGtkCTree::GetRowData(GtkCTreeNode* Node)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return gtk_ctree_node_get_row_data(*this, Node);
}

void sdpGtkCTree::MoveTo(GtkCTreeNode* Node, gint Column, gfloat RowAlign, gfloat ColumnAlign)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_node_moveto(*this, Node, Column, RowAlign, ColumnAlign);
}

GtkVisibility sdpGtkCTree::IsVisible(GtkCTreeNode* Node)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), GtkVisibility(-1));

	return gtk_ctree_node_is_visible(*this, Node);
}

void sdpGtkCTree::SetIndent(gint Indent)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_set_indent(*this, Indent);
}

void sdpGtkCTree::SetSpacing(gint Spacing)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_set_spacing(*this, Spacing);
}

void sdpGtkCTree::SetShowStub(gboolean ShowStub)
{
	// Not implemented ...
	g_return_if_fail(0);

/*
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_set_show_stub(*this, ShowStub);
*/
}

void sdpGtkCTree::SetLineStyle(GtkCTreeLineStyle LineStyle)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_set_line_style(*this, LineStyle);
}

void sdpGtkCTree::SetExpanderStyle(GtkCTreeExpanderStyle ExpanderStyle)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_set_expander_style(*this, ExpanderStyle);
}

void sdpGtkCTree::SetDragCompareFunction(GtkCTreeCompareDragFunc Function)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_set_drag_compare_func(*this, Function);
}

void sdpGtkCTree::SortNode(GtkCTreeNode* Node)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_sort_node(*this, Node);
}

void sdpGtkCTree::SortRecursive(GtkCTreeNode* Node)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ctree_sort_recursive(*this, Node);
}


