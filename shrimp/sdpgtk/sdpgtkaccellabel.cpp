
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

#include "sdpgtkaccellabel.h"
#include "sdpgtkutility.h"

///////////////////////////////////////////////////////////////////////
// sdpGtkAccelLabel

sdpGtkAccelLabel::sdpGtkAccelLabel() : sdpGtkLabel()
{
}

sdpGtkAccelLabel::sdpGtkAccelLabel(GtkAccelLabel* AccelLabel) : sdpGtkLabel(GTK_LABEL(AccelLabel))
{
}

bool sdpGtkAccelLabel::Create(SDPCSTRING Text)
{
	// Sanity checks ...
	g_assert(Text);

	m_Object = GTK_OBJECT(gtk_accel_label_new(Text));
	return Attached();
}

bool sdpGtkAccelLabel::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	return Create(sdpGtkInternationalText(Document, Element));
}

void sdpGtkAccelLabel::SetAcceleratorWidget(GtkWidget* Widget)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	g_assert(Widget);

	gtk_accel_label_set_accel_widget(*this, Widget);
}

guint sdpGtkAccelLabel::GetAcceleratorWidth()
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return gtk_accel_label_get_accel_width(*this);
}

void sdpGtkAccelLabel::RefetchAccelerator()
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	
	gtk_accel_label_refetch(*this);
}

