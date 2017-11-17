#ifndef SDPGTKMENUSHELL_H
#define SDPGTKMENUSHELL_H

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
		\brief Declares the sdpGtkMenuShell class, which encapsulates a GtkMenuShell widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkcontainer.h"

//////////////////////////////////////////////////////////////
// sdpGtkMenuShell

/// Encapsulates a GtkMenuShell widget
class sdpGtkMenuShell : public sdpGtkContainer
{
public:
	/// Standard constructor
	sdpGtkMenuShell();
	/// Attaches this instance to an existing GtkMenuShell widget
	sdpGtkMenuShell(GtkMenuShell* MenuShell);

	/// Casts this instance into a GtkMenuShell pointer
	operator GtkMenuShell*() { return GTK_MENU_SHELL(m_Object); }
};



#endif // SDPGTKMENUSHELL_H
