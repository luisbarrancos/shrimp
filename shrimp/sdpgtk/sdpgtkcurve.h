#ifndef SDPGTKCURVE_H
#define SDPGTKCURVE_H

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
		\brief Declares the sdpGtkCurve class, which encapsulates a GtkCurve widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkdrawingarea.h"

////////////////////////////////////////////////////////////////////////////////////////
// sdpGtkCurve

/// Encapsulates a GtkCurve widget
class sdpGtkCurve : public sdpGtkDrawingArea
{
public:
	/// Standard constructor
	sdpGtkCurve();
	/// Attaches this instance to an existing GtkCurve widget
	sdpGtkCurve(GtkCurve* Curve);

	/// Creates a new GtkCurve widget
	bool Create();
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);
	
	/// Reset the curve to its default
	void Reset();
	/// Creates a gamma curve
	void SetGamma(gdouble Gamma);
	/// Controls the curve range
	void SetRange(gdouble MinX, gdouble MaxX, gdouble MinY, gdouble MaxY);
	/// Returns the curve contents
	void GetVector(int Length, gfloat Vector[]);
	/// Sets the curve contents
	void SetVector(int Length, gfloat Vector[]);
	/// Sets the curve type: interpolated, linear, or freehand
	void SetCurveType(GtkCurveType Type);
	
	/// Casts this instance to a GtkCurve pointer
	operator GtkCurve*() { return GTK_CURVE(m_Object); }
};



#endif // SDPGTKCURVE_H

