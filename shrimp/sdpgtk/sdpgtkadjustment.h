#ifndef SDPGTKADJUSTMENT_H
#define SDPGTKADJUSTMENT_H

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
		\brief Declares the sdpGtkAdjustment class which encapsulate a GtkAdjustment

		\author Tim Shead (tshead@k-3d.com)
*/

#include "sdpgtkdata.h"

////////////////////////////////////////////////////////////////////////////////////////
// sdpGtkAdjustment


/// Encapsulates a GtkAdjustment
class sdpGtkAdjustment : public sdpGtkData
{
public:

	/// Standard constructor
	sdpGtkAdjustment();
	/// Attaches this instance to an existing GtkAdjustment widget
	sdpGtkAdjustment(GtkAdjustment* Adjustment);

	/// Creates a new GtkAdjustment widget
	bool Create(gfloat Value, gfloat Lower, gfloat Upper, gfloat StepIncrement, gfloat PageIncrement, gfloat PageSize);
	/// Creates a new GtkAdjustment widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Returns the current adjustment value
	gfloat Value();
	/// Returns the current lower limit
	gfloat Lower();
	/// Returns the current upper limit
	gfloat Upper();
	/// Returns the current step increment
	gfloat StepIncrement();
	/// Returns the current page increment
	gfloat PageIncrement();
	/// Returns the current page size
	gfloat PageSize();

	/// Sets the current adjustment value
	void SetValue(gfloat Value);
	/// Sets the lower limit
	void SetLower(gfloat Lower);
	/// Sets the upper limit
	void SetUpper(gfloat Upper);
	/// Sets the step increment
	void SetStepIncrement(gfloat StepIncrement);
	/// Sets the page increment
	void SetPageIncrement(gfloat PageIncrement);
	/// Sets the page size
	void SetPageSize(gfloat PageSize);
	/// Sets the lower and upper limits simultaneously
	void ClampPage(gfloat Lower, gfloat Upper);
	/// Notify the underlying object that the value has changed
	void ValueChanged();
	/// Notify the underlying object that the other limits have changed
	void Changed();

	/// Casts this instance to a GtkAdjustment pointer
	operator GtkAdjustment*() { return GTK_ADJUSTMENT(m_Object); }
};


#endif // SDPGTKADJUSTMENT_H
