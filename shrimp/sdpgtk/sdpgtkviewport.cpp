
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

#include "sdpgtkviewport.h"
#include "sdpgtkutility.h"

#include <iostream>

sdpGtkViewport::sdpGtkViewport() : sdpGtkBin()
{
}

sdpGtkViewport::sdpGtkViewport(GtkViewport* Viewport) : sdpGtkBin(GTK_BIN(Viewport))
{
}

bool sdpGtkViewport::Create()
{
	return Create((GtkAdjustment*)0, (GtkAdjustment*)0);
}

bool sdpGtkViewport::Create(GtkAdjustment* HAdjustment, GtkAdjustment* VAdjustment)
{
	m_Object = GTK_OBJECT(gtk_viewport_new(HAdjustment, VAdjustment));
	return Attached();
}

bool sdpGtkViewport::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	// Create the control ...
	return Create((GtkAdjustment*)0, (GtkAdjustment*)0);
}

bool sdpGtkViewport::CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	// Shadow type ...
	SetShadowType(sdpGtkGetShadowType(Document, Element, GTK_SHADOW_ETCHED_IN));

	return sdpGtkBin::CreateOptions(ObjectContainer, Document, Element);
}

bool sdpGtkViewport::AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child)
{
	// Sanity checks ...
	g_assert(ObjectContainer);
	g_assert(Child);

	// Is the child an adjustment?
	if(ChildElement.Name() == "adjustment")
		{
			// Figure out which one ...
			const sdpString target = sdpxml::GetAttribute<sdpString>(ChildElement, "target", "");
			sdpGtkMarkAttribute(Document, ChildElement, "target");

			if(target == "horizontal")
				SetHorizontalAdjustment(GTK_ADJUSTMENT(Child->Object()));
			else if(target == "vertical")
				SetVerticalAdjustment(GTK_ADJUSTMENT(Child->Object()));
			else
				std::cout << "<viewport> child <adjustment> needs to specify a target: horizontal or vertical" << std::endl;

			return true;
		}

	// Default behavior ...
	Attach(GTK_WIDGET(Child->Object()));
	return true;
}

sdpGtkAdjustment sdpGtkViewport::HorizontalAdjustment()
{
	// Sanity checks ...
#ifdef	FAIL_ON_RET
	sdpGtkAdjustment tmpResult;
	g_return_val_if_fail(Attached(), tmpResult);
#else
	g_return_val_if_fail(Attached(), sdpGtkAdjustment());
#endif

	return sdpGtkAdjustment(gtk_viewport_get_hadjustment(*this));
}

sdpGtkAdjustment sdpGtkViewport::VerticalAdjustment()
{
	// Sanity checks ...
#ifdef	FAIL_ON_RET
	sdpGtkAdjustment tmpResult;
	g_return_val_if_fail(Attached(), tmpResult);
#else	
	g_return_val_if_fail(Attached(), sdpGtkAdjustment());
#endif

	return sdpGtkAdjustment(gtk_viewport_get_vadjustment(*this));
}

void sdpGtkViewport::SetHorizontalAdjustment(GtkAdjustment* Adjustment)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_viewport_set_hadjustment(*this, Adjustment);
}

void sdpGtkViewport::SetVerticalAdjustment(GtkAdjustment* Adjustment)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_viewport_set_vadjustment(*this, Adjustment);
}

void sdpGtkViewport::SetShadowType(GtkShadowType ShadowType)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_viewport_set_shadow_type(*this, ShadowType);
}

