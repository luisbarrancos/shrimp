#ifndef SDPGTKHANDLEBOX_H
#define SDPGTKHANDLEBOX_H

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
		\brief Declares the sdpGtkHandleBox class which encapsualates a GtkHandleBox widget
		\author Tim Shead (tshead@k-3d.com)
*/

#include "sdpgtkbin.h"

/// Encapsulates a GtkHandleBox widget
class sdpGtkHandleBox : public sdpGtkBin
{
public:

	/// Standard constructor
	sdpGtkHandleBox();
	/// Attaches this instance to an existing GtkHandleBox
	sdpGtkHandleBox(GtkHandleBox* HandleBox);

	/// Creates a new GtkHandleBox widget
	bool Create();
	/// Creates a new GtkHandleBox widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	bool CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Sets the embossing style of the handle
	void SetShadowType(GtkShadowType ShadowType);
	/// Sets the handle position
	void SetHandlePosition(GtkPositionType PositionType);
	/// Sets the snap edge
	void SetSnapEdge(GtkPositionType SnapEdge);

	/// Casts this instance to a GtkHandleBox pointer
	operator GtkHandleBox*() { return GTK_HANDLE_BOX(m_Object); }
};

#endif // SDPGTKHANDLEBOX_H
