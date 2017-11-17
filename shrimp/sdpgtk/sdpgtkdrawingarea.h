#ifndef SDPGTKDRAWINGAREA_H
#define SDPGTKDRAWINGAREA_H

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
		\brief Declares the sdpGtkDrawingArea class, which encapsulates a GtkDrawingArea widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkwidget.h"

/// Encapsulates a GtkDrawingArea widget
class sdpGtkDrawingArea : public sdpGtkWidget
{
public:
	/// Standard constructor
	sdpGtkDrawingArea();
	/// Attaches this instance to an existing GtkDrawingArea widget
	sdpGtkDrawingArea(GtkDrawingArea* DrawingArea);

	/// Creates a new GtkDrawingArea widget
	bool Create();
	/// Creates a new GtkDrawingArea widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	bool CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Sets the size of the drawing area
	void SetSize(gint Width, gint Height);

	/// Casts this instance to a GtkDrawingArea pointer
	operator GtkDrawingArea*() { return GTK_DRAWING_AREA(m_Object); }
};

#endif // SDPGTKDRAWINGAREA_H
