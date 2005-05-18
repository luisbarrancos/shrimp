#ifndef SDPGTKALIGNMENT_H
#define SDPGTKALIGNMENT_H

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
		\brief Declares the sdpGtkAlignment class which encapsualates a GtkAlignment widget
		\author Tim Shead (tshead@k-3d.com)
*/

#include "sdpgtkbin.h"

/// Encapsulates a GtkAlignment widget
class sdpGtkAlignment : public sdpGtkBin
{
public:
	/// Standard constructor
	sdpGtkAlignment();
	/// Attaches this instance to an existing GtkAlignment
	sdpGtkAlignment(GtkAlignment* Alignment);

	/// Creates a new GtkAlignment widget
	bool Create(gfloat XAlign, gfloat YAlign, gfloat XScale, gfloat YScale);
	/// Creates a new GtkAlignment widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Sets the alignment properties
	void SetAlignment(gfloat XAlign, gfloat YAlign, gfloat XScale, gfloat YScale);

	/// Casts this instance to a GtkAlignment pointer
	operator GtkAlignment*() { return GTK_ALIGNMENT(m_Object); }
};

#endif // SDPGTKALIGNMENT_H
