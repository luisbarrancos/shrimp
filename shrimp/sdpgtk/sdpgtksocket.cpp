
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

#include "sdpgtksocket.h"

#if defined SDPWIN32
#include <gdk/gdkwin32.h>
#else // SDPWIN32
#include <gdk/gdkx.h>
#include <X11/X.h>
#endif // !SDPWIN32

sdpGtkSocket::sdpGtkSocket() : sdpGtkContainer()
{
}

sdpGtkSocket::sdpGtkSocket(GtkSocket* Socket) : sdpGtkContainer(GTK_CONTAINER(Socket))
{
}

bool sdpGtkSocket::Create()
{
	m_Object = GTK_OBJECT(gtk_socket_new());
	return Attached();
}

bool sdpGtkSocket::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);
	
	return Create();
}

guint32 sdpGtkSocket::SocketID()
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	// Make sure we've been realized, first ...
	Realize();	
	
	// Return our X window ID ...
#if defined SDPWIN32
	return guint32(HWND(GDK_WINDOW_XWINDOW(GTK_WIDGET(m_Object)->window)));
#else // SDPWIN32	
	return GDK_WINDOW_XWINDOW(GTK_WIDGET(m_Object)->window);
#endif // !SDPWIN32
}

bool sdpGtkSocket::Plugged()
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), false);

	return GTK_SOCKET(m_Object)->plug_window ? true : false;
}

void sdpGtkSocket::Steal(guint32 WindowID)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	
	gtk_socket_steal(*this, WindowID);
}


