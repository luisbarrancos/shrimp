#ifndef SDPGTKBUTTONBOX_H
#define SDPGTKBUTTONBOX_H

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
		\brief Declares the sdpGtkButtonBox class which encapsulates a GtkButtonBox widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkbox.h"

////////////////////////////////////////////////////////////////////////////////////////
// sdpGtkButtonBox

/// Encapsulates a GtkButtonBox widget
class sdpGtkButtonBox : public sdpGtkBox
{
public:
	/// Standard constructor
	sdpGtkButtonBox();
	/// Attaches this instance to an existing GtkButtonBox widget
	sdpGtkButtonBox(GtkButtonBox* ButtonBox);

	virtual bool CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Returns the minimum width and height of child widgets
	void GetChildSize(gint* MinWidth, gint* MinHeight);
	/// Sets the minimum width and height of child widgets
	void SetChildSize(gint MinWidget, gint MinHeight);
	/// Returns the horizontal and vertical padding of child widgets
	void GetChildPadding(gint* PadX, gint* PadY);
	/// Sets the horizontal and vertical padding of child widgets
	void SetChildPadding(gint PadX, gint PadY);
	/// Returns the spacing between child widgets
	gint GetSpacing();
	/// Sets the spacing between child widgets
	void SetSpacing(gint Spacing);
	/// Returns the layout style
	GtkButtonBoxStyle GetLayout();
	/// Sets the layout style
	void SetLayout(GtkButtonBoxStyle Style);

	/// Casts this instance to a GtkButtonBox pointer
	operator GtkButtonBox*() { return GTK_BUTTON_BOX(m_Object); }
};



#endif // SDPGTKBUTTONBOX_H
