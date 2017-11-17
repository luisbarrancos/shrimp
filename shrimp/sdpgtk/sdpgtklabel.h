#ifndef SDPGTKLABEL_H
#define SDPGTKLABEL_H

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
		\brief Declares the sdpGtkLabel class, which encapsulates a GtkLabel widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkmisc.h"

/////////////////////////////////////////////////////////////////////////////
// sdpGtkLabel

/// Encapsulates a GtkLabel widget
class sdpGtkLabel : public sdpGtkMisc
{
public:
	/// Standard constructor
	sdpGtkLabel();
	/// Attaches this instance to an existing GtkLabel widget
	sdpGtkLabel(GtkLabel* Label);

	/// Creates a new GtkLabel widget
	bool Create(SDPCSTRING Text);
	/// Creates a new GtkLabel widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Sets the label text
	void SetText(sdpString Text);
	/// Controls whether the label wraps text to multiple lines
	void SetLineWrap(bool Wrap);

	/// Casts this instance into a GtkLabel pointer
	operator GtkLabel*() { return GTK_LABEL(m_Object); }
};

#endif // SDPGTKLABEL_H

