#ifndef SDPGTKHRULER_H
#define SDPGTKHRULER_H

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
		\brief Declares the sdpGtkHRuler class, which encapsulates a GtkHRuler widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkruler.h"

/// Encapsulates a GtkHRuler widget
class sdpGtkHRuler : public sdpGtkRuler
{
public:
	/// Standard constructor
	sdpGtkHRuler();
	/// Attaches this instance to an existing GtkHRuler widget
	sdpGtkHRuler(GtkHRuler* Ruler);

	/// Creates a new GtkHRuler widget
	bool Create();
	/// Creates a new GtkHRuler widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Casts this instance into a GtkHRuler pointer
	operator GtkHRuler*() { return GTK_HRULER(m_Object); }
};

#endif // SDPGTKHRULER_H

