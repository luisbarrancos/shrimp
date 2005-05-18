#ifndef SDPGTKHBOX_H
#define SDPGTKHBOX_H

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
		\brief Declares the sdpGtkHBox class, which encapsulates a GtkHBox widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkbox.h"

////////////////////////////////////////////////////////////////////////////////////////
// sdpGtkHBox

/// Encapsulates a GtkHBox widget
class sdpGtkHBox : public sdpGtkBox
{
public:
	/// Standard constructor
	sdpGtkHBox();
	/// Attaches this instance to an existing GtkHBox widget
	sdpGtkHBox(GtkHBox* HBox);

	/// Creates a new GtkHBox widget
	bool Create(bool Homogenous, gint Spacing);
	/// Creates a new GtkHBox widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Casts this instance into a GtkHBox pointer
	operator GtkHBox*() { return GTK_HBOX(m_Object); }
};



#endif // SDPGTKHBOX_H
