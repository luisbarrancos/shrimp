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
		\brief Implements the sdpGtkAdjustment class, which encapsulates a GtkAdjustment object
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkadjustment.h"
#include "sdpgtkutility.h"

////////////////////////////////////////////////////////////////////////////////////////
// sdpGtkAdjustment

sdpGtkAdjustment::sdpGtkAdjustment() : sdpGtkData()
{
}

sdpGtkAdjustment::sdpGtkAdjustment(GtkAdjustment* Adjustment) : sdpGtkData(GTK_DATA(Adjustment))
{
}

bool sdpGtkAdjustment::Create(gfloat Value, gfloat Lower, gfloat Upper, gfloat StepIncrement, gfloat PageIncrement, gfloat PageSize)
{
	m_Object = GTK_OBJECT(gtk_adjustment_new(Value, Lower, Upper, StepIncrement, PageIncrement, PageSize));
	return Attached();
}

bool sdpGtkAdjustment::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	// Get attributes ...
	const sdpVector2 range = sdpxml::GetAttribute(Element, "range", sdpVector2(0.0, 1.0));
	sdpGtkMarkAttribute(Document, Element, "range");

	const gfloat value = sdpxml::GetAttribute(Element, "value", range[0]);
	sdpGtkMarkAttribute(Document, Element, "value");

	const gfloat stepincrement = sdpxml::GetAttribute(Element, "stepincrement", (0.1 * (range[1] - range[0])));
	sdpGtkMarkAttribute(Document, Element, "stepincrement");

	const gfloat pageincrement = sdpxml::GetAttribute(Element, "pageincrement", stepincrement);
	sdpGtkMarkAttribute(Document, Element, "pageincrement");

	const gfloat pagesize = sdpxml::GetAttribute(Element, "pagesize", range[1] - range[0]);
	sdpGtkMarkAttribute(Document, Element, "pagesize");

	// Create the control ...
	return Create(value, range[0], range[1], stepincrement, pageincrement, pagesize);
}

gfloat sdpGtkAdjustment::Value()
{
	g_return_val_if_fail(Attached(), 0.0f);
	return GTK_ADJUSTMENT(m_Object)->value;
}

gfloat sdpGtkAdjustment::Lower()
{
	g_return_val_if_fail(Attached(), 0.0f);
	return GTK_ADJUSTMENT(m_Object)->lower;
}

gfloat sdpGtkAdjustment::Upper()
{
	g_return_val_if_fail(Attached(), 0.0f);
	return GTK_ADJUSTMENT(m_Object)->upper;
}

gfloat sdpGtkAdjustment::StepIncrement()
{
	g_return_val_if_fail(Attached(), 0.0f);
	return GTK_ADJUSTMENT(m_Object)->step_increment;
}

gfloat sdpGtkAdjustment::PageIncrement()
{
	g_return_val_if_fail(Attached(), 0.0f);
	return GTK_ADJUSTMENT(m_Object)->page_increment;
}

gfloat sdpGtkAdjustment::PageSize()
{
	g_return_val_if_fail(Attached(), 0.0f);
	return GTK_ADJUSTMENT(m_Object)->page_size;
}

void sdpGtkAdjustment::SetValue(gfloat Value)
{
	g_return_if_fail(Attached());
	gtk_adjustment_set_value(*this, Value);
}

void sdpGtkAdjustment::SetLower(gfloat Lower)
{
	g_return_if_fail(Attached());
	GTK_ADJUSTMENT(m_Object)->lower = Lower;
}

void sdpGtkAdjustment::SetUpper(gfloat Upper)
{
	g_return_if_fail(Attached());
	GTK_ADJUSTMENT(m_Object)->upper = Upper;
}

void sdpGtkAdjustment::SetStepIncrement(gfloat StepIncrement)
{
	g_return_if_fail(Attached());
	GTK_ADJUSTMENT(m_Object)->step_increment = StepIncrement;
}

void sdpGtkAdjustment::SetPageIncrement(gfloat PageIncrement)
{
	g_return_if_fail(Attached());
	GTK_ADJUSTMENT(m_Object)->page_increment = PageIncrement;
}

void sdpGtkAdjustment::SetPageSize(gfloat PageSize)
{
	g_return_if_fail(Attached());
	GTK_ADJUSTMENT(m_Object)->page_size = PageSize;
}

void sdpGtkAdjustment::ClampPage(gfloat Lower, gfloat Upper)
{
	g_return_if_fail(Attached());
	gtk_adjustment_clamp_page(*this, Lower, Upper);
}

void sdpGtkAdjustment::ValueChanged()
{
	g_return_if_fail(Attached());
	gtk_adjustment_value_changed(*this);
}

void sdpGtkAdjustment::Changed()
{
	g_return_if_fail(Attached());
	gtk_adjustment_changed(*this);
}


