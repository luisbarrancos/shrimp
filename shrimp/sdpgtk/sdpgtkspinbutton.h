#ifndef SDPGTKSPINBUTTON_H
#define SDPGTKSPINBUTTON_H

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
		\brief Declares the sdpGtkSpinButton class, which encapsulates a GtkSpinButton widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkentry.h"
#include "sdpgtkadjustment.h"

/// Encapsulates a GtkSpinButton widget
class sdpGtkSpinButton : public sdpGtkEntry
{
public:
	/// Standard constructor
	sdpGtkSpinButton();
	/// Attaches this instance to an existing GtkSpinButton widget
	sdpGtkSpinButton(GtkSpinButton* Text);

	/// Creates a new GtkSpinButton widget
	bool Create(gdouble ClimbRate, guint Digits);
	/// Creates a new GtkSpinButton widget
	bool Create(GtkAdjustment* Adjustment, gdouble ClimbRate, guint Digits);
	/// Creates a new GtkSpinButton widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	bool CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);
	bool AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child);

	/// Configures the spin button
	void Configure(GtkAdjustment* Adjustment, gfloat ClimbRate, guint Digits);
	/// Sets the spin button adjustment
	void SetAdjustment(GtkAdjustment* Adjustment);
	/// Returns the spin button adjustment
	sdpGtkAdjustment Adjustment();
	/// Sets the number of digits to display in the widget
	void SetDigits(guint Digits);
	/// Returns the current spin button value as a gfloat
	void GetValue(gdouble& Value);
	/// Returns the current spin button value as a gint
	void GetValue(gint& Value);
	/// Sets the current spin button value
	void SetValue(gdouble Value);
	/// Sets the button update policy
	void SetUpdatePolicy(GtkSpinButtonUpdatePolicy Policy);

	void SetNumeric(bool Numeric);
	void SetWrap(bool Wrap);
	void SetSnapToTicks(bool SnapToTicks);

	/// Sets the button shadow type
	void SetShadowType(GtkShadowType ShadowType);
	/// Updates the button
	void Update();
	/// Spins the button the given direction and increment
	void Spin(GtkSpinType Direction, gfloat Increment);

	/// Casts this instance into a GtkSpinButton pointer
	operator GtkSpinButton*() { return GTK_SPIN_BUTTON(m_Object); }
};

#endif // SDPGTKSPINBUTTON_H

