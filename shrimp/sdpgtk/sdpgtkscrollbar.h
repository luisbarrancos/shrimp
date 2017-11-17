#ifndef SDPGTKSCROLLBAR_H
#define SDPGTKSCROLLBAR_H

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
		\brief Declares the sdpGtkScrollbar class, which encapsulates a GtkScrollbar widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkrange.h"

/// Encapsulates a GtkScrollbar widget
class sdpGtkScrollbar : public sdpGtkRange
{
public:
	/// Standard constructor
	sdpGtkScrollbar();
	/// Attaches this instance to an existing GtkScrollbar widget
	sdpGtkScrollbar(GtkScrollbar* Scrollbar);

	/// Casts this instance into a GtkScrollbar pointer
	operator GtkScrollbar*() { return GTK_SCROLLBAR(m_Object); }
};

#endif // SDPGTKSCROLLBAR_H
