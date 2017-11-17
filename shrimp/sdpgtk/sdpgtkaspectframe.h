#ifndef SDPGTKASPECTFRAME_H
#define SDPGTKASPECTFRAME_H

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
		\brief Declares the sdpGtkAspectFrame class, which encapsulates a GtkAspectFrame widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkframe.h"

/// Encapsulates a GtkAspectFrame widget
class sdpGtkAspectFrame : public sdpGtkFrame
{
public:
	/// Standard constructor
	sdpGtkAspectFrame();
	/// Attaches this instance to an existing GtkAspectFrame widget
	sdpGtkAspectFrame(GtkAspectFrame* Frame);

	/// Creates a new GtkAspectFrame widget
	bool Create(SDPCSTRING Label, gdouble XAlignment, gdouble YAlignment, gdouble Ratio, bool IgnoreRatio);
	/// Creates a new GtkAspectFrame widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Sets the frame properties
	void Set(gdouble XAlignment, gdouble YAlignment, gdouble Ratio, bool IgnoreRatio);
	
	/// Casts this instance into a GtkFrame pointer
	operator GtkAspectFrame*() { return GTK_ASPECT_FRAME(m_Object); }
};

#endif // SDPGTKASPECTFRAME_H

