#ifndef SDPGTKPIXMAP_H
#define SDPGTKPIXMAP_H

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
		\brief Declares the sdpGtkPixmap class, which encapsulates a GtkPixmap widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkmisc.h"

//////////////////////////////////////////////////////////////////////
// sdpGtkPixmap

/// Encapsulates a GtkPixmap widget
class sdpGtkPixmap : public sdpGtkMisc
{
public:
	/// Standard constructor
	sdpGtkPixmap();
	/// Attaches this instance to an existing GtkPixmap widget
	sdpGtkPixmap(GtkPixmap* Pixmap);

	/// Creates a new GtkPixmap widget
	bool Create(SDPCSTRING ImagePath);
	/// Creates a new GtkPixmap widget
	bool Create(char* Data[]);
	/// Creates a new GtkPixmap widget
	bool Create(GdkPixmap* Image, GdkBitmap* Mask);
	/// Creates a new GtkPixmap widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	bool SetPixmap(SDPCSTRING ImagePath);
	bool SetPixmap(char* Data[]);
	void SetPixmap(GdkPixmap* Pixmap, GdkBitmap* Mask);
	
	void GetPixmap(GdkPixmap** Pixmap, GdkBitmap** Mask);

	/// Creates a GdkPixmap from a file
	static bool CreatePixmap(SDPCSTRING ImagePath, GdkPixmap*& Image, GdkBitmap*& Mask);
	/// Creates a GdkPixmap from a memory buffer
	static bool CreatePixmap(char* Data[], GdkPixmap*& Image, GdkBitmap*& Mask);

	/// Casts this instance into a GtkPixmap pointer
	operator GtkPixmap*() { return GTK_PIXMAP(m_Object); }
};

#endif // SDPGTKPIXMAP_H
