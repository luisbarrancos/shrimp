
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

#include "sdpgtkscrolledwindow.h"
#include "sdpgtkutility.h"

#include <iostream>

sdpGtkScrolledWindow::sdpGtkScrolledWindow() : sdpGtkBin()
{
}

sdpGtkScrolledWindow::sdpGtkScrolledWindow(GtkScrolledWindow* ScrolledWindow) : sdpGtkBin(GTK_BIN(ScrolledWindow))
{
}

void sdpGtkScrolledWindow::AttachWithViewport(GtkWidget* Widget)
{
	gtk_scrolled_window_add_with_viewport(*this, Widget);
}

bool sdpGtkScrolledWindow::Create()
{
	m_Object = GTK_OBJECT(gtk_scrolled_window_new(0, 0));
	return Attached();
}

bool sdpGtkScrolledWindow::Create(GtkAdjustment* HorizontalAdjustment, GtkAdjustment* VerticalAdjustment)
{
	m_Object = GTK_OBJECT(gtk_scrolled_window_new(HorizontalAdjustment, VerticalAdjustment));
	return Attached();
}

bool sdpGtkScrolledWindow::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	return Create();
}


bool sdpGtkScrolledWindow::CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	const sdpString hscrollbar = sdpxml::GetAttribute<sdpString>(Element, "hscrollbar", "automatic");
	sdpGtkMarkAttribute(Document, Element, "hscrollbar");

	const sdpString vscrollbar = sdpxml::GetAttribute<sdpString>(Element, "vscrollbar", "automatic");
	sdpGtkMarkAttribute(Document, Element, "vscrollbar");


	GtkPolicyType hscrollbarpolicy = GTK_POLICY_AUTOMATIC;
	if(hscrollbar == "automatic")
		hscrollbarpolicy = GTK_POLICY_AUTOMATIC;
	else if(hscrollbar == "always")
		hscrollbarpolicy = GTK_POLICY_ALWAYS;
	else if(hscrollbar == "never")
		hscrollbarpolicy = GTK_POLICY_NEVER;
	else
		g_return_val_if_fail(0, false);

	GtkPolicyType vscrollbarpolicy = GTK_POLICY_AUTOMATIC;
	if(vscrollbar == "automatic")
		vscrollbarpolicy = GTK_POLICY_AUTOMATIC;
	else if(vscrollbar == "always")
		vscrollbarpolicy = GTK_POLICY_ALWAYS;
	else if(vscrollbar == "never")
		vscrollbarpolicy = GTK_POLICY_NEVER;
	else
		g_return_val_if_fail(0, false);

	SetScrollbarPolicy(hscrollbarpolicy, vscrollbarpolicy);

	return sdpGtkBin::CreateOptions(ObjectContainer, Document, Element);
}

bool sdpGtkScrolledWindow::AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child)
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
				std::cout << "<scrolledwindow> child <adjustment> needs to specify a target: horizontal or vertical" << std::endl;

			return true;
		}
	// Is the child an object that handles its own scrollbars?
	else if(ChildElement.Name() == "clist" ||
		ChildElement.Name() == "ctree" ||
		ChildElement.Name() == "layout")
		{
			Attach(GTK_WIDGET(Child->Object()));
			return true;
		}

	// Default behavior ...
	AttachWithViewport(GTK_WIDGET(Child->Object()));
	return true;
}

void sdpGtkScrolledWindow::SetScrollbarPolicy(GtkPolicyType HorizontalScrollbarPolicy, GtkPolicyType VerticalScrollbarPolicy)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_scrolled_window_set_policy(*this, HorizontalScrollbarPolicy, VerticalScrollbarPolicy);
}

void sdpGtkScrolledWindow::SetPlacement(GtkCornerType Placement)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_scrolled_window_set_placement(*this, Placement);
}

/// Sets the horizontal adjustment
void sdpGtkScrolledWindow::SetHorizontalAdjustment(GtkAdjustment* Adjustment)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_scrolled_window_set_hadjustment(*this, Adjustment);
}

/// Sets the vertical adjustment
void sdpGtkScrolledWindow::SetVerticalAdjustment(GtkAdjustment* Adjustment)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_scrolled_window_set_vadjustment(*this, Adjustment);
}

/// Returns the horizontal adjustment
sdpGtkAdjustment sdpGtkScrolledWindow::HorizontalAdjustment()
{
	// Sanity checks ...
#ifdef	FAIL_ON_RET
	sdpGtkAdjustment tmpResult;
	g_return_val_if_fail(Attached(), tmpResult);
#else
	g_return_val_if_fail(Attached(), sdpGtkAdjustment());
#endif

	return sdpGtkAdjustment(gtk_scrolled_window_get_hadjustment(*this));
}

/// Returns the vertical adjustment
sdpGtkAdjustment sdpGtkScrolledWindow::VerticalAdjustment()
{
	// Sanity checks ...
#ifdef	FAIL_ON_RET
	sdpGtkAdjustment tmpResult;
	g_return_val_if_fail(Attached(), tmpResult);
#else
	g_return_val_if_fail(Attached(), sdpGtkAdjustment());
#endif

	return sdpGtkAdjustment(gtk_scrolled_window_get_vadjustment(*this));
}

