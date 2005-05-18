
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

#include "sdpgtkrange.h"

sdpGtkRange::sdpGtkRange() : sdpGtkWidget()
{
}

sdpGtkRange::sdpGtkRange(GtkRange* Range) : sdpGtkWidget(GTK_WIDGET(Range))
{
}

void sdpGtkRange::SetAdjustment(GtkAdjustment* Adjustment)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_range_set_adjustment(*this, Adjustment);
}

sdpGtkAdjustment sdpGtkRange::Adjustment()
{
	// Sanity checks ...
#ifdef	FAIL_ON_RET
	sdpGtkAdjustment tmpResult;
	g_return_val_if_fail(Attached(), tmpResult);
#else
	g_return_val_if_fail(Attached(), sdpGtkAdjustment());
#endif

	return sdpGtkAdjustment(gtk_range_get_adjustment(*this));
}

void sdpGtkRange::SetUpdatePolicy(GtkUpdateType Policy)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_range_set_update_policy(*this, Policy);
}

bool sdpGtkRange::CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	return sdpGtkWidget::CreateOptions(ObjectContainer, Document, Element);
}

bool sdpGtkRange::AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child)
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
	return sdpGtkWidget::AttachChild(ObjectContainer, Document, ChildElement, Child);
}

