#ifndef SDPGTKACCELLABEL_H
#define SDPGTKACCELLABEL_H

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
		\brief Declares the sdpGtkAccelLabel class, which encapsulates a GtkAccelLabel widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtklabel.h"

//////////////////////////////////////////////////////////////////////
// sdpGtkAccelLabel

/// Encapsulates a GtkAccelLabel widget
class sdpGtkAccelLabel : public sdpGtkLabel
{
public:
	/// Standard constructor
	sdpGtkAccelLabel();
	/// Attaches this instance to an existing GtkAccelLabel widget
	sdpGtkAccelLabel(GtkAccelLabel* AccelLabel);

	/// Creates a new GtkAccelLabel widget
	bool Create(SDPCSTRING Text);
	/// Creates a new GtkAccelLabel widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Sets the widget whose accelerator should be displayed
	void SetAcceleratorWidget(GtkWidget* Widget);
	/// Returns the width required to display the current accelerator keys
	guint GetAcceleratorWidth();
	/// Updates the label
	void RefetchAccelerator();

	/// Casts this instance into a GtkAccelLabel pointer
	operator GtkAccelLabel*() { return GTK_ACCEL_LABEL(m_Object); }
};

#endif // SDPGTKACCELLABEL_H
