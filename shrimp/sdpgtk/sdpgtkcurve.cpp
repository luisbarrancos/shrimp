
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



#include "sdpgtkcurve.h"


////////////////////////////////////////////////////////////////////////////////////////
// sdpGtkCurve

sdpGtkCurve::sdpGtkCurve() : sdpGtkDrawingArea()
{
}

sdpGtkCurve::sdpGtkCurve(GtkCurve* Curve) : sdpGtkDrawingArea(GTK_DRAWING_AREA(Curve))
{
}

bool sdpGtkCurve::Create()
{
	m_Object = GTK_OBJECT(gtk_curve_new());
	return Attached();
}

bool sdpGtkCurve::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	return Create();
}

void sdpGtkCurve::Reset()
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	
}

void sdpGtkCurve::SetGamma(gdouble Gamma)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_curve_set_gamma(*this, Gamma);	
}

void sdpGtkCurve::SetRange(gdouble MinX, gdouble MaxX, gdouble MinY, gdouble MaxY)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	
	gtk_curve_set_range(*this, MinX, MaxX, MinY, MaxY);
}

void sdpGtkCurve::GetVector(int Length, gfloat Vector[])
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	
	gtk_curve_get_vector(*this, Length, Vector);
}

void sdpGtkCurve::SetVector(int Length, gfloat Vector[])
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	
	gtk_curve_set_vector(*this, Length, Vector);
}

void sdpGtkCurve::SetCurveType(GtkCurveType Type)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	
	gtk_curve_set_curve_type(*this, Type);
}

