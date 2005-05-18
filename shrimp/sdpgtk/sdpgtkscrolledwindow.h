#ifndef SDPGTKSCROLLEDWINDOW_H
#define SDPGTKSCROLLEDWINDOW_H

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
		\brief Declares the sdpGtkScrolledWindow class, which encapsulates a GtkScrolledWindow widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkbin.h"
#include "sdpgtkadjustment.h"

/// Encapsulates a GtkScrolledWindow widget
class sdpGtkScrolledWindow : public sdpGtkBin
{
public:
	/// Standard constructor
	sdpGtkScrolledWindow();
	/// Attaches this instance to an existing GtkScrolledWindow widget
	sdpGtkScrolledWindow(GtkScrolledWindow* ScrolledWindow);

	/// Creates a new GtkScrolledWindow widget
	bool Create();
	/// Creates a new GtkScrolledWindow widget
	bool Create(GtkAdjustment* HorizontalAdjustment, GtkAdjustment* VerticalAdjustment);
	/// Creates a new GtkScrolledWindow widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	bool CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);
	bool AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child);

	/// Attaches a child widget
	void AttachWithViewport(GtkWidget* Widget);
	/// Sets the scrollbar policies for the window
	void SetScrollbarPolicy(GtkPolicyType HorizontalScrollbarPolicy, GtkPolicyType VerticalScrollbarPolicy);
	/// Sets the child widget placement within the window
	void SetPlacement(GtkCornerType Placement);
	/// Sets the horizontal adjustment
	void SetHorizontalAdjustment(GtkAdjustment* Adjustment);
	/// Sets the vertical adjustment
	void SetVerticalAdjustment(GtkAdjustment* Adjustment);
	/// Returns the horizontal adjustment
	sdpGtkAdjustment HorizontalAdjustment();
	/// Returns the vertical adjustment
	sdpGtkAdjustment VerticalAdjustment();

	/// Casts this instance into a GtkScrolledWindow pointer
	operator GtkScrolledWindow*() { return GTK_SCROLLED_WINDOW(m_Object); }
};

#endif // SDPGTKSCROLLEDWINDOW_H

