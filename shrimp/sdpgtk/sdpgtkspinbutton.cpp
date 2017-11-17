
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

#include "sdpgtkspinbutton.h"
#include "sdpgtkutility.h"

sdpGtkSpinButton::sdpGtkSpinButton() : sdpGtkEntry()
{
}

sdpGtkSpinButton::sdpGtkSpinButton(GtkSpinButton* Button) : sdpGtkEntry(GTK_ENTRY(Button))
{
}

bool sdpGtkSpinButton::Create(gdouble ClimbRate, guint Digits)
{
	return Create(0, ClimbRate, Digits);
}

bool sdpGtkSpinButton::Create(GtkAdjustment* Adjustment, gdouble ClimbRate, guint Digits)
{
	m_Object = GTK_OBJECT(gtk_spin_button_new(Adjustment, ClimbRate, Digits));
	return Attached();
}

bool sdpGtkSpinButton::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	const gdouble climbrate = sdpxml::GetAttribute(Element, "climbrate", 1.0);
	sdpGtkMarkAttribute(Document, Element, "climbrate");

	const guint digits = sdpxml::GetAttribute(Element, "digits", 0);
	sdpGtkMarkAttribute(Document, Element, "digits");

	g_return_val_if_fail(Create(climbrate, digits), false);
	
	// Initialize our contents with the element text ...
	SetText(sdpGtkInternationalText(Document, Element));
	
	return true;
}

bool sdpGtkSpinButton::CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	// Shadow type ...
	SetShadowType(sdpGtkGetShadowType(Document, Element, GTK_SHADOW_ETCHED_IN));

	return sdpGtkEntry::CreateOptions(ObjectContainer, Document, Element);
}

bool sdpGtkSpinButton::AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child)
{
	// Sanity checks ...
	g_assert(ObjectContainer);
	g_assert(Child);

	// Is the child an adjustment?
	if(ChildElement.Name() == "adjustment")
		{
			SetAdjustment(GTK_ADJUSTMENT(Child->Object()));
			return true;
		}

	// Default behavior ...
	return sdpGtkEntry::AttachChild(ObjectContainer, Document, ChildElement, Child);
}

void sdpGtkSpinButton::Configure(GtkAdjustment* Adjustment, gfloat ClimbRate, guint Digits)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_spin_button_configure(*this, Adjustment, ClimbRate, Digits);
}

void sdpGtkSpinButton::SetAdjustment(GtkAdjustment* Adjustment)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_spin_button_set_adjustment(*this, Adjustment);
}

sdpGtkAdjustment sdpGtkSpinButton::Adjustment()
{
	// Sanity checks ...
#ifdef	FAIL_ON_RET
	sdpGtkAdjustment tmpResult;
	g_return_val_if_fail(Attached(), tmpResult);
#else
	g_return_val_if_fail(Attached(), sdpGtkAdjustment());
#endif

	return sdpGtkAdjustment(gtk_spin_button_get_adjustment(*this));
}

void sdpGtkSpinButton::SetDigits(guint Digits)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_spin_button_set_digits(*this, Digits);
}

void sdpGtkSpinButton::GetValue(gdouble& Value)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	Value = gtk_spin_button_get_value_as_float(*this);
}

void sdpGtkSpinButton::GetValue(gint& Value)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	Value = gtk_spin_button_get_value_as_int(*this);
}

void sdpGtkSpinButton::SetValue(gdouble Value)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_spin_button_set_value(*this, Value);
}

void sdpGtkSpinButton::SetUpdatePolicy(GtkSpinButtonUpdatePolicy Policy)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_spin_button_set_update_policy(*this, Policy);
}

void sdpGtkSpinButton::SetNumeric(bool Numeric)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_spin_button_set_numeric(*this, Numeric);
}

void sdpGtkSpinButton::Spin(GtkSpinType Direction, gfloat Increment)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_spin_button_spin(*this, Direction, Increment);
}

void sdpGtkSpinButton::SetWrap(bool Wrap)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_spin_button_set_wrap(*this, Wrap);
}

void sdpGtkSpinButton::SetShadowType(GtkShadowType ShadowType)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_spin_button_set_shadow_type(*this, ShadowType);
}

void sdpGtkSpinButton::SetSnapToTicks(bool SnapToTicks)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_spin_button_set_snap_to_ticks(*this, SnapToTicks);
}

void sdpGtkSpinButton::Update()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_spin_button_update(*this);
}
