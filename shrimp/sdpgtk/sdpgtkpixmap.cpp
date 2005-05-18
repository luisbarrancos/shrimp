
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

#include "sdpgtkpixmap.h"
#include "sdpgtkutility.h"

///////////////////////////////////////////////////////////////////////
// sdpGtkPixmap

sdpGtkPixmap::sdpGtkPixmap() : sdpGtkMisc()
{
}

sdpGtkPixmap::sdpGtkPixmap(GtkPixmap* Pixmap) : sdpGtkMisc(GTK_MISC(Pixmap))
{
}

bool sdpGtkPixmap::Create(SDPCSTRING ImagePath)
{
	// Sanity checks ...
	g_assert_string(ImagePath);

	GdkPixmap* image = 0;
	GdkBitmap* mask = 0;
	g_return_val_if_fail(CreatePixmap(ImagePath, image, mask), false);

	return Create(image, mask);
}

bool sdpGtkPixmap::Create(char* Data[])
{
	// Sanity checks ...
	g_assert(Data);

	GdkPixmap* image = 0;
	GdkBitmap* mask = 0;
	g_return_val_if_fail(CreatePixmap(Data, image, mask), false);

	return Create(image, mask);
}

bool sdpGtkPixmap::Create(GdkPixmap* Image, GdkBitmap* Mask)
{
	// Sanity checks ...
	g_return_val_if_fail(Image, false);
	g_return_val_if_fail(Mask, false);

	m_Object = GTK_OBJECT(gtk_pixmap_new(Image, Mask));
	return Attached();
}

bool sdpGtkPixmap::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	// Create our pixmap ...
	return Create(sdpAppendPath(sdpDirectory(Document.SourceURL()), sdpGtkInternationalText(Document, Element)));
}

bool sdpGtkPixmap::SetPixmap(SDPCSTRING ImagePath)
{
	// Sanity checks ...
	g_assert_string(ImagePath);

	GdkPixmap* image = 0;
	GdkBitmap* mask = 0;
	g_return_val_if_fail(CreatePixmap(ImagePath, image, mask), false);

	SetPixmap(image, mask);

	return true;
}

bool sdpGtkPixmap::SetPixmap(char* Data[])
{
	// Sanity checks ...
	g_assert(Data);

	GdkPixmap* image = 0;
	GdkBitmap* mask = 0;
	g_return_val_if_fail(CreatePixmap(Data, image, mask), false);

	SetPixmap(image, mask);

	return true;
}

void sdpGtkPixmap::SetPixmap(GdkPixmap* Pixmap, GdkBitmap* Mask)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_pixmap_set(*this, Pixmap, Mask);
}

void sdpGtkPixmap::GetPixmap(GdkPixmap** Pixmap, GdkBitmap** Mask)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_pixmap_get(*this, Pixmap, Mask);
}

bool sdpGtkPixmap::CreatePixmap(SDPCSTRING ImagePath, GdkPixmap*& Image, GdkBitmap*& Mask)
{
	// Sanity checks ...
	g_assert_string(ImagePath);

	// Create a temporary window ... why does gdk need this!?
	GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_realize(window);
	
	Image = gdk_pixmap_create_from_xpm(window->window, &Mask, 0, ImagePath);

	// Get rid of the temporary window ...
	gtk_widget_destroy(GTK_WIDGET(window));

	return true;
}

bool sdpGtkPixmap::CreatePixmap(char* Data[], GdkPixmap*& Image, GdkBitmap*& Mask)
{
	// Sanity checks ...
	g_assert(Data);

	// Create a temporary window ... why does gdk need this!?
	GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_realize(window);
	
	Image = gdk_pixmap_create_from_xpm_d(window->window, &Mask, 0, (gchar**)Data);

	// Get rid of the temporary window ...
	gtk_widget_destroy(GTK_WIDGET(window));

	return true;
}



