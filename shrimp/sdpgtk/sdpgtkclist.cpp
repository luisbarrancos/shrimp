
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
#include "sdpgtkutility.h"

sdpGtkCList::sdpGtkCList() : sdpGtkContainer()
{
}

sdpGtkCList::sdpGtkCList(GtkCList* CList) : sdpGtkContainer(GTK_CONTAINER(CList))
{
}

bool sdpGtkCList::Create(gint Columns)
{
	// Sanity checks ...
	g_assert(Columns);

	m_Object = GTK_OBJECT(gtk_clist_new(Columns));
	return Attached();
}

bool sdpGtkCList::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	const gulong columns = sdpxml::GetAttribute(Element, "columns", 0);
	sdpGtkMarkAttribute(Document, Element, "columns");

	g_return_val_if_fail(columns, false);	// You MUST specify how many columns you want!

	return Create(columns);
}

bool sdpGtkCList::CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	// Selection mode ...
	const sdpString selectionmodetext = sdpxml::GetAttribute<sdpString>(Element, "selectionmode", "single");
	sdpGtkMarkAttribute(Document, Element, "selectionmode");

	GtkSelectionMode selectionmode = GTK_SELECTION_SINGLE;
	if(selectionmodetext == "single")
		selectionmode = GTK_SELECTION_SINGLE;
	else if(selectionmodetext == "browse")
		selectionmode = GTK_SELECTION_BROWSE;
	else if(selectionmodetext == "multiple")
		selectionmode = GTK_SELECTION_MULTIPLE;
	else if(selectionmodetext == "extended")
		selectionmode = GTK_SELECTION_EXTENDED;
	else
		g_return_val_if_fail(0, false);

	SetSelectionMode(selectionmode);

	// Shadow type ...
	SetShadowType(sdpGtkGetShadowType(Document, Element, GTK_SHADOW_ETCHED_IN));

	return sdpGtkContainer::CreateOptions(ObjectContainer, Document, Element);
}

GtkAdjustment* sdpGtkCList::GetHAdjustment()
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return gtk_clist_get_hadjustment(*this);
}

GtkAdjustment* sdpGtkCList::GetVAdjustment()
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return gtk_clist_get_vadjustment(*this);
}

void sdpGtkCList::SetHAdjustment(GtkAdjustment* Adjustment)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_set_hadjustment(*this, Adjustment);
}

void sdpGtkCList::SetVAdjustment(GtkAdjustment* Adjustment)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_set_vadjustment(*this, Adjustment);
}

void sdpGtkCList::SetShadowType(GtkShadowType ShadowType)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_set_shadow_type(*this, ShadowType);
}

void sdpGtkCList::SetSelectionMode(GtkSelectionMode SelectionMode)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_set_selection_mode(*this, SelectionMode);
}

void sdpGtkCList::Freeze()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_freeze(*this);
}

void sdpGtkCList::Thaw()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_thaw(*this);
}

void sdpGtkCList::SelectAll()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_select_all(*this);
}

void sdpGtkCList::DeselectAll()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_unselect_all(*this);
}

void sdpGtkCList::UndoSelection()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_undo_selection(*this);
}

void sdpGtkCList::Clear()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_clear(*this);
}

void sdpGtkCList::MoveTo(gint Row, gint Column, gfloat RowAlign, gfloat ColumnAlign)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_moveto(*this, Row, Column, RowAlign, ColumnAlign);
}

gint sdpGtkCList::GetHitInfo(gint X, gint Y, gint* Row, gint* Column)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), -1);

	return gtk_clist_get_selection_info(*this, X, Y, Row, Column);
}

gint sdpGtkCList::ColumnCount()
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), -1);

	return GTK_CLIST(m_Object)->columns;
}

void sdpGtkCList::ShowColumnTitles()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_column_titles_show(*this);
}

void sdpGtkCList::HideColumnTitles()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_column_titles_hide(*this);
}

void sdpGtkCList::ColumnTitlesActive()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_column_titles_active(*this);
}

void sdpGtkCList::ColumnTitlesPassive()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_column_titles_passive(*this);
}

void sdpGtkCList::ColumnTitleActive(gint Column)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_column_title_active(*this, Column);
}

void sdpGtkCList::ColumnTitlePassive(gint Column)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_column_title_passive(*this, Column);
}

void sdpGtkCList::SetColumnTitle(gint Column, SDPCSTRING Title)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_set_column_title(*this, Column, Title);
}

void sdpGtkCList::SetColumnWidget(gint Column, GtkWidget* Widget)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_set_column_widget(*this, Column, Widget);
}

SDPSTRING sdpGtkCList::GetColumnTitle(gint Column)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return gtk_clist_get_column_title(*this, Column);
}

GtkWidget* sdpGtkCList::GetColumnWidget(gint Column)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return gtk_clist_get_column_widget(*this, Column);
}

void sdpGtkCList::SetColumnJustification(gint Column, GtkJustification Justification)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_set_column_justification(*this, Column, Justification);
}

void sdpGtkCList::SetColumnVisibility(gint Column, gboolean Visible)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_set_column_visibility(*this, Column, Visible);
}

void sdpGtkCList::SetColumnResizeable(gint Column, gboolean Resizeable)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_set_column_resizeable(*this, Column, Resizeable);
}

void sdpGtkCList::SetColumnAutoResize(gint Column, gboolean AutoResize)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_set_column_auto_resize(*this, Column, AutoResize);
}

gint sdpGtkCList::GetOptimalColumnWidth(gint Column)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), -1);

	return gtk_clist_optimal_column_width(*this, Column);
}

void sdpGtkCList::SetColumnWidth(gint Column, gint Width)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_set_column_width(*this, Column, Width);
}

void sdpGtkCList::SetColumnMinWidth(gint Column, gint MinWidth)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_set_column_min_width(*this, Column, MinWidth);
}

void sdpGtkCList::SetColumnMaxWidth(gint Column, gint MaxWidth)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_set_column_max_width(*this, Column, MaxWidth);
}

gint sdpGtkCList::RowCount()
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), -1);

	return GTK_CLIST(m_Object)->rows;
}

void sdpGtkCList::SetRowHeight(guint Height)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_set_row_height(*this, Height);
}

GtkVisibility sdpGtkCList::GetRowVisible(gint Row)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), GtkVisibility(-1));

	return gtk_clist_row_is_visible(*this, Row);
}

void sdpGtkCList::SetRowStyle(gint Row, GtkStyle* Style)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_set_row_style(*this, Row, Style);
}

GtkStyle* sdpGtkCList::GetRowStyle(gint Row)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return gtk_clist_get_row_style(*this, Row);
}

void sdpGtkCList::SetSelectable(gint Row, gboolean Selectable)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_set_selectable(*this, Row, Selectable);
}

gboolean sdpGtkCList::GetSelectable(gint Row)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), false);

	return gtk_clist_get_selectable(*this, Row) ? true : false;
}

void sdpGtkCList::SetForegroundColor(gint Row, GdkColor* Color)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_set_foreground(*this, Row, Color);
}

void sdpGtkCList::SetBackgroundColor(gint Row, GdkColor* Color)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_set_background(*this, Row, Color);
}

gint sdpGtkCList::Prepend(SDPCSTRING Text)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), -1);

	return gtk_clist_prepend(*this, const_cast<gchar**>(&Text));
}

gint sdpGtkCList::Prepend(SDPCSTRING Text[])
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), -1);

	return gtk_clist_prepend(*this, const_cast<gchar**>(Text));
}

gint sdpGtkCList::Append(SDPCSTRING Text)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), -1);

	return gtk_clist_append(*this, const_cast<gchar**>(&Text));
}

gint sdpGtkCList::Append(SDPCSTRING Text[])
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), -1);

	return gtk_clist_append(*this, const_cast<gchar**>(Text));
}

gint sdpGtkCList::Insert(gint Row, SDPCSTRING Text)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), -1);

	return gtk_clist_insert(*this, Row, const_cast<gchar**>(&Text));
}

gint sdpGtkCList::Insert(gint Row, SDPCSTRING Text[])
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), -1);

	return gtk_clist_insert(*this, Row, const_cast<gchar**>(Text));
}

void sdpGtkCList::Remove(gint Row)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_remove(*this, Row);
}

void sdpGtkCList::SetRowData(gint Row, gpointer Data)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_set_row_data(*this, Row, Data);
}

gpointer sdpGtkCList::GetRowData(gint Row)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return gtk_clist_get_row_data(*this, Row);
}

gint sdpGtkCList::FindRowFromData(gpointer Data)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), -1);

	return gtk_clist_find_row_from_data(*this, Data);
}

void sdpGtkCList::SelectRow(gint Row, gint Column)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_select_row(*this, Row, Column);
}

void sdpGtkCList::DeselectRow(gint Row, gint Column)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_unselect_row(*this, Row, Column);
}

void sdpGtkCList::SwapRows(gint Row1, gint Row2)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_swap_rows(*this, Row1, Row2);
}

void sdpGtkCList::MoveRow(gint Source, gint Destination)
{
	// Not implemented ...
	g_return_if_fail(0);

/*
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_row_move(*this, Source, Destination);
*/
}

GtkCellType sdpGtkCList::GetCellType(gint Row, gint Column)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), GtkCellType(-1));

	return gtk_clist_get_cell_type(*this, Row, Column);
}

void sdpGtkCList::SetCellStyle(gint Row, gint Column, GtkStyle* Style)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_set_cell_style(*this, Row, Column, Style);
}

GtkStyle* sdpGtkCList::GetCellStyle(gint Row, gint Column)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return gtk_clist_get_cell_style(*this, Row, Column);
}

void sdpGtkCList::SetShift(gint Row, gint Column, gint Vertical, gint Horizontal)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_set_shift(*this, Row, Column, Vertical, Horizontal);
}

void sdpGtkCList::SetText(gint Row, gint Column, SDPCSTRING Text)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_set_text(*this, Row, Column, Text);
}

void sdpGtkCList::SetPixmap(gint Row, gint Column, GdkPixmap* Pixmap, GdkBitmap* Mask)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_set_pixmap(*this, Row, Column, Pixmap, Mask);
}

void sdpGtkCList::SetPixmapText(gint Row, gint Column, SDPCSTRING Text, guint8 Spacing, GdkPixmap* Pixmap, GdkBitmap* Mask)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_set_pixtext(*this, Row, Column, Text, Spacing, Pixmap, Mask);
}

sdpString sdpGtkCList::GetText(gint Row, gint Column)
{
	// Sanity checks ...
#ifdef FAIL_ON_RET
	sdpString tmpResult;
	g_return_val_if_fail(Attached(), tmpResult);
#else
	g_return_val_if_fail(Attached(), sdpString());
#endif
	gchar* text = 0;
	gtk_clist_get_text(*this, Row, Column, &text);

	return sdpString(text);
}

gint sdpGtkCList::GetPixmap(gint Row, gint Column, GdkPixmap** Pixmap, GdkBitmap** Mask)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), -1);

	return gtk_clist_get_pixmap(*this, Row, Column, Pixmap, Mask);
}

gint sdpGtkCList::GetPixmapText(gint Row, gint Column, SDPSTRING* Text, guint8* Spacing, GdkPixmap** Pixmap, GdkBitmap** Mask)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), -1);

	return gtk_clist_get_pixtext(*this, Row, Column, Text, Spacing, Pixmap, Mask);
}

void sdpGtkCList::SetCompareFunction(GtkCListCompareFunc Function)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_set_compare_func(*this, Function);
}

void sdpGtkCList::SetSortColumn(gint Column)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_set_sort_column(*this, Column);
}

void sdpGtkCList::SetSortType(GtkSortType Type)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_set_sort_type(*this, Type);
}

void sdpGtkCList::Sort()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_sort(*this);
}

void sdpGtkCList::SetAutoSort(gboolean AutoSort)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_clist_set_auto_sort(*this, AutoSort);
}

static bool RowCoordinates(sdpGtkCList& List, const gint Row, gint& Top, gint& Bottom)
{
	// Sanity checks ...
	g_assert(List.Attached());
	g_assert(Row >= 0);

	Top = INT_MAX;
	Bottom = -INT_MAX;

	bool result = false;

	gint testrow, testcolumn;
	for(gint i = 0; i < List.Height(); i++)
		{
			List.GetHitInfo(0, i, &testrow, &testcolumn);
			if(Row == testrow)
				{
					result = true;

					Top = std::min(Top, i);
					Bottom = std::max(Bottom, i);
				}
		}

	return result;
}

bool sdpGtkCList::InteractiveWarpPointer(const gint Row, const gdouble Speed, const bool Pause)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), false);

	return InteractiveWarpPointer(Row, 0.5, 0.5, Speed, Pause);
}

bool sdpGtkCList::InteractiveWarpPointer(const gint Row, const gdouble XPercent, const gdouble YPercent, const gdouble Speed, const bool Pause)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), false);

	// Make sure the row's visible ...
	MoveTo(Row, 0, 0.5, 0.0);

	// Get the row's dimensions ...
	gint top, bottom;
	g_return_val_if_fail(RowCoordinates(*this, Row, top, bottom), false);

	GtkWidget* widget = GTK_WIDGET(m_Object);
	return sdpGtkWidget::InteractiveWarpPointer(gint(XPercent * widget->allocation.width) + widget->style->klass->xthickness, gint(YPercent * (bottom - top)) + top + widget->style->klass->ythickness, Speed, Pause, false);
}

bool sdpGtkCList::InteractiveWarpPointer(const gint Row, const gint XOffset, const gint YOffset, const gdouble Speed, const bool Pause)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), false);

	// Make sure the row's visible ...
	MoveTo(Row, 0, 0.5, 0.0);

	// Get the row's dimensions ...
	gint top, bottom;
	g_return_val_if_fail(RowCoordinates(*this, Row, top, bottom), false);

	GtkWidget* widget = GTK_WIDGET(m_Object);
	return sdpGtkWidget::InteractiveWarpPointer(XOffset + widget->style->klass->xthickness, YOffset + top + widget->style->klass->ythickness, Speed, Pause, false);
}

sdpGtkCList::Rows sdpGtkCList::GetSelectedRows()
{
	// Sanity checks ...
#ifdef FAIL_ON_RET
	sdpGtkCList::Rows tmpResult;
	g_return_val_if_fail(Attached(), tmpResult);
	g_return_val_if_fail(!GTK_IS_CTREE(m_Object), tmpResult); // CTree stores a different type of data in GtkCList->selection, so you can't use this method!!!
#else
	g_return_val_if_fail(Attached(), Rows());
	g_return_val_if_fail(!GTK_IS_CTREE(m_Object), Rows()); // CTree stores a different type of data in GtkCList->selection, so you can't use this method!!!
#endif

	Rows result;

	GtkCList* list = *this;
	for(GList* selection = list->selection; selection; selection = selection->next)
		{
			guint rowindex = GPOINTER_TO_UINT(selection->data);
			result.push_back(rowindex);
		}

	return result;
}


