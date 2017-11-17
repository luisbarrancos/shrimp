#ifndef SDPGTKVIEWPORT_H
#define SDPGTKVIEWPORT_H

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
		\brief Declares the sdpGtkViewport class which encapsualates a GtkViewport widget
		\author Tim Shead (tshead@k-3d.com)
*/

#include "sdpgtkbin.h"
#include "sdpgtkadjustment.h"

/// Encapsulates a GtkViewport widget
class sdpGtkViewport : public sdpGtkBin
{
public:

	/// Standard constructor
	sdpGtkViewport();
	/// Attaches this instance to an existing GtkViewport
	sdpGtkViewport(GtkViewport* Viewport);

	/// Creates a new GtkViewport widget
	bool Create();
	/// Creates a new GtkViewport widget
	bool Create(GtkAdjustment* HAdjustment, GtkAdjustment* VAdjustment);
	/// Creates a new GtkViewport widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	bool CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);
	bool AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child);

	/// Sets the horizontal adjustment
	void SetHorizontalAdjustment(GtkAdjustment* Adjustment);
	/// Sets the vertical adjustment
	void SetVerticalAdjustment(GtkAdjustment* Adjustment);
	/// Returns the horizontal adjustment
	sdpGtkAdjustment HorizontalAdjustment();
	/// Returns the vertical adjustment
	sdpGtkAdjustment VerticalAdjustment();

	/// Sets the embossing style of the viewport
	void SetShadowType(GtkShadowType ShadowType);

	/// Casts this instance to a GtkViewport pointer
	operator GtkViewport*() { return GTK_VIEWPORT(m_Object); }
};

#endif // SDPGTKVIEWPORT_H
