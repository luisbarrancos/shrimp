#ifndef SDPGTKRANGE_H
#define SDPGTKRANGE_H

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
		\brief Declares the sdpGtkRange class, which encapsulates a GtkRange widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkwidget.h"
#include "sdpgtkadjustment.h"

/// Encapsulates a GtkRange widget
class sdpGtkRange : public sdpGtkWidget
{
public:
	/// Standard constructor
	sdpGtkRange();
	/// Attaches this instance to an existing GtkRange widget
	sdpGtkRange(GtkRange* Range);

	bool CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);
	bool AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child);

	/// Sets the range adjustment
	void SetAdjustment(GtkAdjustment* Adjustment);
	/// Returns the adjustment for this widget
	sdpGtkAdjustment Adjustment();
	/// Sets the update policy for this range widget
	void SetUpdatePolicy(GtkUpdateType Policy);

	/// Casts this instance into a GtkRange pointer
	operator GtkRange*() { return GTK_RANGE(m_Object); }
};

#endif // SDPGTKRANGE_H
