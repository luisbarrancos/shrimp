#ifndef SDPGTKCLIST_H
#define SDPGTKCLIST_H

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
		\brief Declares the sdpGtkCList class, which encapsulates a GtkCList widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkcontainer.h"
#include <vector>

/// Encapsulates a GtkCList widget
class sdpGtkCList : public sdpGtkContainer
{
public:
	/// Standard constructor
	sdpGtkCList();
	/// Attaches this instance to an existing GtkCList
	sdpGtkCList(GtkCList* CList);

	/// Creates a new GtkCList
	bool Create(gint Columns);
	/// Creates a new GtkCList with column titles
	bool Create(gint Columns, SDPCSTRING Titles[]);
	/// Creates a new GtkCList from a GTKML (XML) container
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	bool CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	GtkAdjustment* GetHAdjustment();
	GtkAdjustment* GetVAdjustment();
	void SetHAdjustment(GtkAdjustment* Adjustment);
	void SetVAdjustment(GtkAdjustment* Adjustment);
	/// Sets the shadow type for the clist
	void SetShadowType(GtkShadowType ShadowType);
	/// Sets the selection mode for the clist
	void SetSelectionMode(GtkSelectionMode SelectionMode);
	/// Freezes display updates for the clist
	void Freeze();
	/// Thaws display updates for the clist
	void Thaw();
	/// Selects every row of the clist
	void SelectAll();
	/// Deselects every row of the clist
	void DeselectAll();

	void UndoSelection();
	void Clear();

	void MoveTo(gint Row, gint Column, gfloat RowAlign, gfloat ColumnAlign);
	gint GetHitInfo(gint X, gint Y, gint* Row, gint* Column);

	/// Returns the number of columns in the clist
	gint ColumnCount();
	/// Makes column titles visible
	void ShowColumnTitles();
	/// Hides column titles
	void HideColumnTitles();

	void ColumnTitlesActive();
	void ColumnTitlesPassive();

	void ColumnTitleActive(gint Column);
	void ColumnTitlePassive(gint Column);

	/// Sets an individual column's title
	void SetColumnTitle(gint Column, SDPCSTRING Title);
	/// Sets an individual column's title widget
	void SetColumnWidget(gint Column, GtkWidget* Widget);
	/// Returns a column's title
	SDPSTRING GetColumnTitle(gint Column);
	/// Returns a column's title widget
	GtkWidget* GetColumnWidget(gint Column);

	void SetColumnJustification(gint Column, GtkJustification Justification);
	void SetColumnVisibility(gint Column, gboolean Visible);
	void SetColumnResizeable(gint Column, gboolean Resizeable);
	void SetColumnAutoResize(gint Column, gboolean AutoResize);

	gint GetOptimalColumnWidth(gint Column);
	void SetColumnWidth(gint Column, gint Width);
	void SetColumnMinWidth(gint Column, gint MinWidth);
	void SetColumnMaxWidth(gint Column, gint MaxWidth);

	// Rows ...
	gint RowCount();

	void SetRowHeight(guint Height);

	GtkVisibility GetRowVisible(gint Row);

	void SetRowStyle(gint Row, GtkStyle* Style);
	GtkStyle* GetRowStyle(gint Row);

	void SetSelectable(gint Row, gboolean Selectable);
	gboolean GetSelectable(gint Row);

	void SetForegroundColor(gint Row, GdkColor* Color);
	void SetBackgroundColor(gint Row, GdkColor* Color);

	gint Prepend(SDPCSTRING Text);
	gint Prepend(SDPCSTRING Text[]);
	
	gint Append(SDPCSTRING Text);
	gint Append(SDPCSTRING Text[]);
	
	gint Insert(const gint Row, SDPCSTRING Text);
	gint Insert(const gint Row, SDPCSTRING Text[]);

	void Remove(gint Row);

	void SetRowData(gint Row, gpointer Data);
	gpointer GetRowData(gint Row);
	gint FindRowFromData(gpointer Data);

	void SelectRow(gint Row, gint Column);
	void DeselectRow(gint Row, gint Column);

	void SwapRows(gint Row1, gint Row2);
	void MoveRow(gint Source, gint Destination);

	// Cells ...
	GtkCellType GetCellType(gint Row, gint Column);
	
	void SetCellStyle(gint Row, gint Column, GtkStyle* Style);
	GtkStyle* GetCellStyle(gint Row, gint Column);

	void SetShift(gint Row, gint Column, gint Vertical, gint Horizontal);

	void SetText(gint Row, gint Column, SDPCSTRING Text);
	void SetPixmap(gint Row, gint Column, GdkPixmap* Pixmap, GdkBitmap* Mask);
	void SetPixmapText(gint Row, gint Column, SDPCSTRING Text, guint8 Spacing, GdkPixmap* Pixmap, GdkBitmap* Mask);

	sdpString GetText(gint Row, gint Column);
	gint GetPixmap(gint Row, gint Column, GdkPixmap** Pixmap, GdkBitmap** Mask);
	gint GetPixmapText(gint Row, gint Column, SDPSTRING* Text, guint8* Spacing, GdkPixmap** Pixmap, GdkBitmap** Mask);

	// Sorting ...
	void SetCompareFunction(GtkCListCompareFunc Function);
	void SetSortColumn(gint Column);
	void SetSortType(GtkSortType Type);
	void Sort();
	void SetAutoSort(gboolean AutoSort);

	/// Moves the pointer from its current location to the center of the row
	bool InteractiveWarpPointer(const gint Row, const gdouble Speed, const bool Pause);
	/// Moves the pointer from its current location to a position relative to the row (expressed as percentages)
	bool InteractiveWarpPointer(const gint Row, const gdouble XPercent, const gdouble YPercent, const gdouble Speed, const bool Pause);
	/// Moves the pointer from its current location to a position relative to the row (expressed in pixels)
	bool InteractiveWarpPointer(const gint Row, const gint XOffset, const gint YOffset, const gdouble Speed, const bool Pause);

	/// Defines a set of list rows
	typedef std::vector<gint> Rows;
	typedef Rows::iterator RowIterator;
	/// Returns the set of currently-selected rows
	Rows GetSelectedRows();	

	// Casting ...
	operator GtkCList*() { return GTK_CLIST(m_Object); }
};

#endif // SDPGTKCLIST_H

