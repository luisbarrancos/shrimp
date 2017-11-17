#ifndef SDPGTKSCALE_H
#define SDPGTKSCALE_H

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
		\brief Declares the sdpGtkScale class, which encapsulates a GtkScale widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkrange.h"

/// Encapsulates a GtkScale widget
class sdpGtkScale : public sdpGtkRange
{
public:
	/// Standard constructor
	sdpGtkScale();
	/// Attaches this instance to an existing GtkScale widget
	sdpGtkScale(GtkScale* Scale);

	bool CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Sets the number of digits to the right of the decimal point to display
	void SetDigits(gulong Digits);
	/// Controls whether the current scale value should be shown
	void SetDrawValue(bool Visible);
	/// Controls where the value will be shown
	void SetValuePosition(GtkPositionType Position);
	/// Returns the width of the value if drawn
	gint GetValueWidth();

	/// Casts this instance into a GtkScale pointer
	operator GtkScale*() { return GTK_SCALE(m_Object); }
};

#endif // SDPGTKSCALE_H
