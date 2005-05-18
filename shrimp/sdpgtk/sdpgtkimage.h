#ifndef SDPGTKIMAGE_H
#define SDPGTKIMAGE_H

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
		\brief Declares the sdpGtkImage class, which encapsulates a GtkImage widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkmisc.h"

//////////////////////////////////////////////////////////////////////
// sdpGtkImage

/// Encapsulates a GtkImage widget
class sdpGtkImage : public sdpGtkMisc
{
public:
	/// Standard constructor
	sdpGtkImage();
	/// Attaches this instance to an existing GtkImage widget
	sdpGtkImage(GtkImage* Image);

	/// Creates a new GtkImage widget
	bool Create(GdkImage* Image, GdkBitmap* Mask);
	/// Creates a new GtkImage widget from a GTKML (XML) document
//	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Sets a new image and mask for the widget
	void SetImage(GdkImage* Image, GdkBitmap* Mask);
	/// Returns the image and mask of the widget
	void GetImage(GdkImage** Image, GdkBitmap** Mask);

	/// Casts this instance into a GtkImage pointer
	operator GtkImage*() { return GTK_IMAGE(m_Object); }
};

#endif // SDPGTKIMAGE_H

