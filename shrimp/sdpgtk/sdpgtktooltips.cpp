
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



#include "sdpgtktooltips.h"



////////////////////////////////////////////////////////////////////////////////////////
// sdpGtkTooltips

sdpGtkTooltips::sdpGtkTooltips() : sdpGtkData()
{
}

sdpGtkTooltips::sdpGtkTooltips(GtkTooltips* Tooltips) : sdpGtkData(GTK_DATA(Tooltips))
{
}

bool sdpGtkTooltips::Create()
{
	m_Object = GTK_OBJECT(gtk_tooltips_new());
	return Attached();
}

bool sdpGtkTooltips::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	return Create();
}

void sdpGtkTooltips::Enable()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_tooltips_enable(*this);
}

void sdpGtkTooltips::Disable()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_tooltips_disable(*this);
}

void sdpGtkTooltips::SetDelay(gulong Delay)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_tooltips_set_delay(*this, Delay);
}

void sdpGtkTooltips::Set(sdpGtkObject& Object, SDPCSTRING Tip)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	Set(GTK_WIDGET(Object.Object()), Tip);
}

void sdpGtkTooltips::Set(GtkWidget* Widget, SDPCSTRING Tip)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	g_assert(Widget);

	gtk_tooltips_set_tip(*this, Widget, Tip, 0);
}
