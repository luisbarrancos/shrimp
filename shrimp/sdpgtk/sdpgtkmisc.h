#ifndef SDPGTKMISC_H
#define SDPGTKMISC_H

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
		\brief Declares the sdpGtkMisc class, which encapsulates a GtkMisc widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkwidget.h"

///////////////////////////////////////////////////////////////////////
// sdpGtkMisc

/// Encapsulates a GtkMisc widget
class sdpGtkMisc : public sdpGtkWidget
{
public:
	/// Standard constructor
	sdpGtkMisc();
	/// Attaches this instance to an existing GtkMisc widget
	sdpGtkMisc(GtkMisc* Misc);

	bool CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Sets the horizontal and vertical alignment
	void SetAlignment(gfloat XAlignment, gfloat YAlignment);
	/// Sets the horizontal and vertical padding
	void SetPadding(gint XPad, gint YPad);

	/// Casts this instance into a GtkMisc pointer
	operator GtkMisc*() { return GTK_MISC(m_Object); }
};


#endif // SDPGTKMISC_H
