#ifndef SDPGTKCOLORSELECTION_H
#define SDPGTKCOLORSELECTION_H

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
		\brief Declares the sdpGtkColorSelection class, which encapsulates a GtkColorSelection widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkvbox.h"

////////////////////////////////////////////////////////////////////////////////////////
// sdpGtkColorSelection

/// Encapsulates a GtkColorSelection widget
class sdpGtkColorSelection : public sdpGtkVBox
{
public:
	/// Standard constructor
	sdpGtkColorSelection();
	/// Attaches this instance to an existing GtkColorSelection widget
	sdpGtkColorSelection(GtkColorSelection* ColorSelection);

	/// Creates a new GtkColorSelection widget
	bool Create();
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Sets the update policy for this widget
	void SetUpdatePolicy(GtkUpdateType Policy);
	/// Enables opacity selection for this widget
	void SetOpacity(bool UseOpacity);
	/// Sets the currently selected color
	void SetColor(gdouble* Color);
	/// Returns the selected color
	void GetColor(gdouble* Color);

	void InteractiveSetColor(const sdpVector3 Color, const gdouble Speed, const bool Pause);

	/// Casts this instance to a GtkColorSelection pointer
	operator GtkColorSelection*() { return GTK_COLOR_SELECTION(m_Object); }
};



#endif // SDPGTKCOLORSELECTION_H
