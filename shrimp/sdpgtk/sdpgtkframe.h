#ifndef SDPGTKFRAME_H
#define SDPGTKFRAME_H

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
		\brief Declares the sdpGtkFrame class, which encapsulates a GtkFrame widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkbin.h"

/// Encapsulates a GtkFrame widget
class sdpGtkFrame : public sdpGtkBin
{
public:
	/// Standard constructor
	sdpGtkFrame();
	/// Attaches this instance to an existing GtkFrame widget
	sdpGtkFrame(GtkFrame* Frame);

	/// Creates a new GtkFrame widget
	bool Create();
	/// Creates a new GtkFrame widget with a label
	bool Create(SDPCSTRING Label);
	/// Creates a new GtkFrame widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	bool CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Sets the label text
	void SetLabel(SDPCSTRING Label);
	/// Sets the label alignment
	void SetLabelAlignment(gdouble Horizontal = 0.0, gdouble Vertical = 0.0);
	/// Sets the shadow type for the frame
	void SetShadowType(GtkShadowType ShadowType);

	/// Casts this instance into a GtkFrame pointer
	operator GtkFrame*() { return GTK_FRAME(m_Object); }
};

#endif // SDPGTKFRAME_H
