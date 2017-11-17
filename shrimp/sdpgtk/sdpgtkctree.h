#ifndef SDPGTKCTREE_H
#define SDPGTKCTREE_H

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

#include "sdpgtkclist.h"

class sdpGtkCTree : public sdpGtkCList
{
public:
	sdpGtkCTree();
	sdpGtkCTree(GtkCTree* CTree);

	// Creation, insertion, deletion ...
	bool Create(gint Columns, gint TreeColumn);
	bool Create(gint Columns, gint TreeColumn, SDPCSTRING Titles[]);
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	GtkCTreeNode* InsertNode(GtkCTreeNode* Parent,
													 GtkCTreeNode* Sibling,
													 SDPCSTRING Text[],
													 guint8 Spacing = 0,
													 GdkPixmap* PixmapClosed = 0,
													 GdkBitmap* MaskClosed = 0,
													 GdkPixmap* PixmapOpened = 0,
													 GdkBitmap* MaskOpened = 0,
													 gboolean IsLeaf = false,
													 gboolean Expanded = true);

	void RemoveNode(GtkCTreeNode* Node);

//	GtkCTreeNode* insert_gNode(GtkCTreeNode* parent, GtkCTreeNode* sibling, GNode* gNode, GtkCTreeGNodeFunc func, gpointer Data);
//	GNode* export_to_gNode(GNode* parent, GNode* sibling, GtkCTreeNode* Node, GtkCTreeGNodeFunc func, gpointer Data);

	// Generic recursive functions, querying / finding tree information
//	void post_recursive(GtkCTreeNode* Node, GtkCTreeFunc func, gpointer Data);
//	void post_recursive_to_depth(GtkCTreeNode* Node, gint depth, GtkCTreeFunc func, gpointer Data);
//	void pre_recursive(GtkCTreeNode* Node, GtkCTreeFunc func, gpointer Data);
//	void pre_recursive_to_depth(GtkCTreeNode* Node, gint depth, GtkCTreeFunc func, gpointer Data);
	
	gboolean IsViewable(GtkCTreeNode* Node);
	GtkCTreeNode* Last(GtkCTreeNode* Node);
	GtkCTreeNode* Node(GtkCTreeRow* Row);
	GtkCTreeNode* Node(guint Row);
//	gboolean find(GtkCTreeNode* Node, GtkCTreeNode* child);
	gboolean IsAncestor(GtkCTreeNode* Node, GtkCTreeNode* Child);
//	GtkCTreeNode* find_by_row_Data(GtkCTreeNode* Node, gpointer Data);

	// returns a GList of all GtkCTreeNodes with row->Data == Data
//	GList* find_all_by_row_Data(GtkCTreeNode* Node, gpointer Data);
//	GtkCTreeNode* find_by_row_Data_custom(GtkCTreeNode* Node, gpointer Data, GCompareFunc func);

	// returns a GList of all GtkCTreeNodes with row->Data == Data
//	GList* find_all_by_row_Data_custom(GtkCTreeNode* Node, gpointer Data, GCompareFunc func);
//	gboolean is_hot_spot(gint x, gint y);

	// Tree signals : move, expand, collapse, (un)select
	void Move(GtkCTreeNode* Node, GtkCTreeNode* NewParent, GtkCTreeNode* NewSibling);
	void Expand(GtkCTreeNode* Node);
	void ExpandRecursive(GtkCTreeNode* Node);
	void ExpandToDepth(GtkCTreeNode* Node, gint Depth);
	void Collapse(GtkCTreeNode* Node);
	void CollapseRecursive(GtkCTreeNode* Node);
	void CollapseToDepth(GtkCTreeNode* Node, gint Depth);
	void ToggleExpansion(GtkCTreeNode* Node);
	void ToggleExpansionRecursive(GtkCTreeNode* Node);
	void Select(GtkCTreeNode* Node);
	void SelectRecursive(GtkCTreeNode* Node);
	void Unselect(GtkCTreeNode* Node);
	void UnselectRecursive(GtkCTreeNode* Node);
//	void real_select_recursive(GtkCTreeNode* Node, gint state);

	// "GtkCList"-like functions
	void SetText(GtkCTreeNode* Node, gint Column, SDPCSTRING Text);
	void SetPixmap(GtkCTreeNode* Node, gint Column, GdkPixmap* Pixmap, GdkBitmap* Mask);
	void SetPixmapText(GtkCTreeNode* Node, gint Column, SDPCSTRING Text, guint8 Spacing, GdkPixmap* Pixmap, GdkBitmap* Mask);
	void SetInfo(GtkCTreeNode* Node, SDPCSTRING Text, guint8 Spacing, GdkPixmap* PixmapClosed, GdkBitmap* MaskClosed, GdkPixmap* PixmapOpened, GdkBitmap* MaskOpened, gboolean IsLeaf, gboolean Expanded);
	void SetShift(GtkCTreeNode* Node, gint Column, gint Vertical, gint Horizontal);
	void SetSelectable(GtkCTreeNode* Node, gboolean Selectable);
	gboolean GetSelectable(GtkCTreeNode* Node);
	GtkCellType GetCellType(GtkCTreeNode* Node, gint Column);
	sdpString GetText(GtkCTreeNode* Node, gint Column);
	gint GetPixmap(GtkCTreeNode* Node, gint Column, GdkPixmap** Pixmap, GdkBitmap** Mask);
	gint GetPixmapText(GtkCTreeNode* Node, gint Column, gchar** Text, guint8* Spacing, GdkPixmap** Pixmap, GdkBitmap** Mask);
	gint GetInfo(GtkCTreeNode* Node, gchar** Text, guint8* Spacing, GdkPixmap** PixmapClosed, GdkBitmap** MaskClosed, GdkPixmap** PixmapOpened, GdkBitmap** MaskOpened, gboolean* IsLeaf, gboolean* Expanded);
	void SetRowStyle(GtkCTreeNode* Node, GtkStyle* Style);
	GtkStyle* GetRowStyle(GtkCTreeNode* Node);
	void SetCellStyle(GtkCTreeNode* Node, gint Column, GtkStyle* Style);
	GtkStyle* GetCellStyle(GtkCTreeNode* Node, gint Column);
	void SetForegroundColor(GtkCTreeNode* Node, GdkColor* Color);
	void SetBackgroundColor(GtkCTreeNode* Node, GdkColor* Color);
	void SetRowData(GtkCTreeNode* Node, gpointer Data);
	void SetRowData(GtkCTreeNode* Node, gpointer Data, GtkDestroyNotify Destroy);
	gpointer GetRowData(GtkCTreeNode* Node);
	void MoveTo(GtkCTreeNode* Node, gint Column, gfloat RowAlign, gfloat ColumnAlign);
	GtkVisibility IsVisible(GtkCTreeNode* Node);

	// GtkCTree specific functions
	void SetIndent(gint Indent);
	void SetSpacing(gint Spacing);
	void SetShowStub(gboolean ShowStub);
	void SetLineStyle(GtkCTreeLineStyle LineStyle);
	void SetExpanderStyle(GtkCTreeExpanderStyle ExpanderStyle);
	void SetDragCompareFunction(GtkCTreeCompareDragFunc Function);

	// Tree sorting functions
	void SortNode(GtkCTreeNode* Node);
	void SortRecursive(GtkCTreeNode* Node);

	// Casting ...
	operator GtkCTree*() { return GTK_CTREE(m_Object); }
};

#endif // SDPGTKCTREE_H

