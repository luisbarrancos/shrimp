#ifndef SDPGTKARROW_H
#define SDPGTKARROW_H

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
		\brief Declares the sdpGtkArrow class, which encapsulates a GtkArrow widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkmisc.h"

//////////////////////////////////////////////////////////////////////
// sdpGtkArrow

/// Encapsulates a GtkArrow widget
class sdpGtkArrow : public sdpGtkMisc
{
public:
	/// Standard constructor
	sdpGtkArrow();
	/// Attaches this instance to an existing GtkArrow widget
	sdpGtkArrow(GtkArrow* Arrow);

	/// Creates a new GtkArrow widget
	bool Create(GtkArrowType ArrowType, GtkShadowType ShadowType);
	/// Creates a new GtkArrow widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Sets the arrow parameters
	void Set(GtkArrowType ArrowType, GtkShadowType ShadowType);

	/// Casts this instance into a GtkArrow pointer
	operator GtkArrow*() { return GTK_ARROW(m_Object); }
};

#endif // SDPGTKARROW_H
