#ifndef SDPGTKTOOLTIPS_H
#define SDPGTKTOOLTIPS_H

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
		\brief Declares the sdpGtkTooltips class, which encapsulates a GtkTooltips widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkdata.h"

////////////////////////////////////////////////////////////////////////////////////////
// sdpGtkTooltip

/// Encapsulates a GtkTooltips widget
class sdpGtkTooltips : public sdpGtkData
{
public:
	/// Standard constructor
	sdpGtkTooltips();
	/// Attaches this instance to an existing GtkTooltips widget
	sdpGtkTooltips(GtkTooltips* Tooltips);

	/// Creates a new GtkTooltips widget
	bool Create();
	/// Creates a new GtkTooltips widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Enables tooltips
	void Enable();
	/// Disables tooltips
	void Disable();
	/// Sets the delay between the time the mouse starts hovering, and the time the tooltip appears
	void SetDelay(gulong Delay);

	/// Sets the tooltip for the given widget	
	void Set(sdpGtkObject& Object, SDPCSTRING Tip);
	/// Sets the tooltip for the given widget
	void Set(GtkWidget* Widget, SDPCSTRING Tip);

	/// Casts this instance into a GtkTooltips pointer
	operator GtkTooltips*() { return GTK_TOOLTIPS(m_Object); }
};

#endif // SDPGTKTOOLTIPS_H
