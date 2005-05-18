
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

#include "sdpgtkimage.h"

///////////////////////////////////////////////////////////////////////
// sdpGtkImage

sdpGtkImage::sdpGtkImage() : sdpGtkMisc()
{
}

sdpGtkImage::sdpGtkImage(GtkImage* Image) : sdpGtkMisc(GTK_MISC(Image))
{
}

bool sdpGtkImage::Create(GdkImage* Image, GdkBitmap* Mask)
{
	// Sanity checks ...
	g_return_val_if_fail(Image, false);
//	g_return_val_if_fail(Mask, false);

	m_Object = GTK_OBJECT(gtk_image_new(Image, Mask));
	return Attached();
}

/*
bool sdpGtkImage::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	// Create our image ...
//	sdpString path = sdpAppendPath(sdpExtractPath(Element->Document()->FilePath()), Element->Text());
	return Create(static_cast<GdkImage*>(0), static_cast<GdkBitmap*>(0));
}
*/

void sdpGtkImage::SetImage(GdkImage* Image, GdkBitmap* Mask)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_image_set(*this, Image, Mask);
}

void sdpGtkImage::GetImage(GdkImage** Image, GdkBitmap** Mask)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_image_get(*this, Image, Mask);
}

