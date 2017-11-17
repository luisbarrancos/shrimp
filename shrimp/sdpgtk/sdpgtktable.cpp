
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

#include "sdpgtktable.h"
#include "sdpgtkutility.h"

/////////////////////////////////////////////////////////////////////////////
// sdpGtkTable

sdpGtkTable::sdpGtkTable() : sdpGtkContainer()
{
}

sdpGtkTable::sdpGtkTable(GtkTable* Table) : sdpGtkContainer(GTK_CONTAINER(Table))
{
}

bool sdpGtkTable::Create(gint Rows, gint Columns, bool Homogenous)
{
	// Sanity checks ...
	g_assert(Rows > 0);
	g_assert(Columns > 0);

	m_Object = GTK_OBJECT(gtk_table_new(Rows, Columns, Homogenous));
	return Attached();
}

bool sdpGtkTable::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	const gint rows = sdpxml::GetAttribute(Element, "rows", 1);
	sdpGtkMarkAttribute(Document, Element, "rows");

	const gint columns = sdpxml::GetAttribute(Element, "columns", 1);
	sdpGtkMarkAttribute(Document, Element, "columns");

	const bool homogeneous = sdpxml::GetAttribute(Element, "homogeneous", true);
	sdpGtkMarkAttribute(Document, Element, "homogeneous");

	return Create(rows, columns, homogeneous);
}

bool sdpGtkTable::CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	// Set spacings
	const guint row_spacings = sdpxml::GetAttribute(Element, "row-spacings", 0);
	sdpGtkMarkAttribute(Document, Element, "row-spacings");
	SetRowSpacings(row_spacings);

	const guint column_spacings = sdpxml::GetAttribute(Element, "column-spacings", 0);
	sdpGtkMarkAttribute(Document, Element, "column-spacings");
	SetColumnSpacings(column_spacings);

	return sdpGtkContainer::CreateOptions(ObjectContainer, Document, Element);
}

class vector4
{
public:
	gdouble n[4];

	vector4(const gdouble x, const gdouble y, const gdouble z, const gdouble w)
	{ n[0] = x; n[1] = y; n[2] = z; n[3] = w; }

	vector4& operator = (const vector4& v);

	friend std::ostream& operator<<(std::ostream& Stream, const vector4& RHS)
	{
		Stream << RHS.n[0] << " " << RHS.n[1] << " " << RHS.n[2] << " " << RHS.n[3];
		return Stream;
	}

	friend std::istream& operator>>(std::istream& Stream, vector4& RHS)
	{
		Stream >> RHS.n[0];
		RHS.n[1] = RHS.n[2] = RHS.n[3] = RHS.n[0];
		Stream >> RHS.n[1] >> RHS.n[2] >> RHS.n[3];

		return Stream;
	}
};

inline vector4& vector4::operator = (const vector4& v)
{ n[0] = v.n[0]; n[1] = v.n[1]; n[2] = v.n[2]; n[3] = v.n[3];
return *this; }

bool sdpGtkTable::AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child)
{
	// Sanity checks ...
	g_assert(Child);

	// Table cells ...
	const vector4 position = sdpxml::GetAttribute<vector4>(ChildElement, "tableposition", vector4(0, 1, 0, 1));
	sdpGtkMarkAttribute(Document, ChildElement, "tableposition");

	// Horizontal options ...
	const bool hexpand = sdpxml::GetAttribute(ChildElement, "hexpand", true);
	sdpGtkMarkAttribute(Document, ChildElement, "hexpand");

	const bool hshrink = sdpxml::GetAttribute(ChildElement, "hshrink", true);
	sdpGtkMarkAttribute(Document, ChildElement, "hshrink");

	const bool hfill = sdpxml::GetAttribute(ChildElement, "hfill", true);
	sdpGtkMarkAttribute(Document, ChildElement, "hfill");

	const gint hoptions = (hexpand ? GTK_EXPAND : 0) | (hshrink ? GTK_SHRINK : 0) | (hfill ? GTK_FILL : 0);

	// Vertical options ...
	const bool vexpand = sdpxml::GetAttribute(ChildElement, "vexpand", true);
	sdpGtkMarkAttribute(Document, ChildElement, "vexpand");

	const bool vshrink = sdpxml::GetAttribute(ChildElement, "vshrink", true);
	sdpGtkMarkAttribute(Document, ChildElement, "vshrink");

	const bool vfill = sdpxml::GetAttribute(ChildElement, "vfill", true);
	sdpGtkMarkAttribute(Document, ChildElement, "vfill");

	const gint voptions = (vexpand ? GTK_EXPAND : 0) | (vshrink ? GTK_SHRINK : 0) | (vfill ? GTK_FILL : 0);

	// Padding ...
	const gint xpadding = sdpxml::GetAttribute(ChildElement, "xpadding", 0);
	sdpGtkMarkAttribute(Document, ChildElement, "xpadding");

	const gint ypadding = sdpxml::GetAttribute(ChildElement, "ypadding", 0);
	sdpGtkMarkAttribute(Document, ChildElement, "ypadding");

	// Attach that baby!
	Attach(GTK_WIDGET(Child->Object()), gint(position.n[0]), gint(position.n[1]), gint(position.n[2]), gint(position.n[3]), GtkAttachOptions(hoptions), GtkAttachOptions(voptions), xpadding, ypadding);

	return true;
}

void sdpGtkTable::Attach(GtkWidget* Widget, gint Left, gint Right, gint Top, gint Bottom)
{
	// Sanity checks ...
	g_assert(Widget);
	g_return_if_fail(Attached());
	g_assert(Left >= 0);
	g_assert(Top >= 0);
	g_assert(Right >= 0);
	g_assert(Bottom >= 0);

	gtk_table_attach_defaults(*this, Widget, Left, Right, Top, Bottom);
}

void sdpGtkTable::Attach(GtkWidget* Widget, gint Left, gint Right, gint Top, gint Bottom, GtkAttachOptions XOptions, GtkAttachOptions YOptions, gint XPadding, gint YPadding)
{
	// Sanity checks ...
	g_assert(Widget);
	g_return_if_fail(Attached());
	g_assert(Left >= 0);
	g_assert(Top >= 0);
	g_assert(Right >= 0);
	g_assert(Bottom >= 0);

	gtk_table_attach(*this, Widget, Left, Right, Top, Bottom, XOptions, YOptions, XPadding, YPadding);
}

void sdpGtkTable::Resize(gint Rows, gint Columns)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_table_resize(*this, Rows, Columns);
}

void sdpGtkTable::SetRowSpacing(guint Row, guint Spacing)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_table_set_row_spacing(*this, Row, Spacing);
}

void sdpGtkTable::SetColumnSpacing(guint Column, guint Spacing)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_table_set_col_spacing(*this, Column, Spacing);
}

void sdpGtkTable::SetRowSpacings(guint Spacing)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_table_set_row_spacings(*this, Spacing);
}

void sdpGtkTable::SetColumnSpacings(guint Spacing)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_table_set_col_spacings(*this, Spacing);
}

void sdpGtkTable::SetHomogeneous(bool Homogeneous)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_table_set_homogeneous(*this, Homogeneous);
}


