
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
		\brief Implements the sdpGtkScale class, which wraps GtkScale
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkscale.h"
#include "sdpgtkutility.h"

sdpGtkScale::sdpGtkScale() : sdpGtkRange()
{
}

sdpGtkScale::sdpGtkScale(GtkScale* Scale) : sdpGtkRange(GTK_RANGE(Scale))
{
}

bool sdpGtkScale::CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	// Number of digits to display ...
	const gulong digits = sdpxml::GetAttribute(Element, "digits", 0);
	sdpGtkMarkAttribute(Document, Element, "digits");
	SetDigits(digits);

	// Show the value?
	const bool drawvalue = sdpxml::GetAttribute(Element, "drawvalue", true);
	sdpGtkMarkAttribute(Document, Element, "drawvalue");
	SetDrawValue(drawvalue);

	// Value position ...
	const sdpString valuepositiontext = sdpxml::GetAttribute<sdpString>(Element, "valueposition", "right");
	sdpGtkMarkAttribute(Document, Element, "valueposition");

	GtkPositionType valueposition;
	if(valuepositiontext == "left")
		valueposition = GTK_POS_LEFT;
	else if(valuepositiontext == "right")
		valueposition = GTK_POS_RIGHT;
	else if(valuepositiontext == "top")
		valueposition = GTK_POS_TOP;
	else if(valuepositiontext == "bottom")
		valueposition = GTK_POS_BOTTOM;
	else
		g_return_val_if_fail(0, false);

	SetValuePosition(valueposition);

	return sdpGtkRange::CreateOptions(ObjectContainer, Document, Element);
}

void sdpGtkScale::SetDigits(gulong Digits)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_scale_set_digits(*this, Digits);
}

void sdpGtkScale::SetDrawValue(bool Visible)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_scale_set_draw_value(*this, Visible);
}

void sdpGtkScale::SetValuePosition(GtkPositionType Position)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_scale_set_value_pos(*this, Position);
}

gint sdpGtkScale::GetValueWidth()
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return gtk_scale_get_value_width(*this);
}

