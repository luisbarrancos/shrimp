#ifndef SDPGTKTABLE_H
#define SDPGTKTABLE_H

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
		\brief Declares the sdpGtkTable class, which encapsulates a GtkTable widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkcontainer.h"

////////////////////////////////////////////////////////////////////////////////////////
// sdpGtkTable

/// Encapsulates a GtkTable widget
class sdpGtkTable : public sdpGtkContainer
{
public:
	/// Standard constructor
	sdpGtkTable();
	/// Attaches this instance to an existing GtkTable widget
	sdpGtkTable(GtkTable* Table);

	/// Creates a new GtkTable widget
	bool Create(gint Rows, gint Columns, bool Homogenous);
	/// Creates a new GtkTable widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	bool CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	bool AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child);

	/// Attaches a child widget
	void Attach(GtkWidget* Widget, gint Left, gint Right, gint Top, gint Bottom);
	/// Attaches a child widget
	void Attach(GtkWidget* Widget, gint Left, gint Right, gint Top, gint Bottom, GtkAttachOptions XOptions, GtkAttachOptions YOptions, gint XPadding, gint YPadding);
	/// Changes the number of rows and columns in the table
	void Resize(gint Rows, gint Columns);
	/// Sets spacing for the given row
	void SetRowSpacing(guint Row, guint Spacing);
	/// Sets spacing for the given column
	void SetColumnSpacing(guint Column, guint Spacing);
	/// Sets spacing for all rows
	void SetRowSpacings(guint Spacing);
	/// Sets spacing for all columns
	void SetColumnSpacings(guint Spacing);
	/// Changes whether the table is homogeneous or non-homogeneous
	void SetHomogeneous(bool Homogeneous);

	/// Casts this instance into a GtkTable pointer
	operator GtkTable*() { return GTK_TABLE(m_Object); }
};

#endif // SDPGTKTABLE_H

