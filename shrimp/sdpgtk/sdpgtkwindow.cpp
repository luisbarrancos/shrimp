
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
	\author Timothy M. Shead <tshead@k-3d.com>
	\author Dan Erikson <derikson@montana.com>
*/

#include "sdpgtkwindow.h"
#include "sdpgtkutility.h"

sdpGtkWindow::sdpGtkWindow() : sdpGtkBin()
{
}

sdpGtkWindow::sdpGtkWindow(GtkWindow* Window) : sdpGtkBin(GTK_BIN(Window))
{
}

bool sdpGtkWindow::Create(GtkWindowType Type)
{
	m_Object = GTK_OBJECT(gtk_window_new(Type));
	return Attached();
}

bool sdpGtkWindow::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	// Create the window ...
	g_return_val_if_fail(Create(GTK_WINDOW_TOPLEVEL), false);

	// Default size ...
	const sdpVector2 defaultsize = sdpxml::GetAttribute(Element, "defaultsize", sdpVector2(0.0, 0.0));
	sdpGtkMarkAttribute(Document, Element, "defaultsize");
	if(defaultsize[0] && defaultsize[1])
		SetDefaultSize(gint(defaultsize[0]), gint(defaultsize[1]));

	return true;
}


bool sdpGtkWindow::CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	// Set the window type ...
	const sdpString type = sdpxml::GetAttribute<sdpString>(Element, "type", "");
	sdpGtkMarkAttribute(Document, Element, "type");

	GtkWindowType windowtype = GetWindowType();
	if(type == "toplevel")
		windowtype = GTK_WINDOW_TOPLEVEL;
	else if(type == "dialog")
		windowtype = GTK_WINDOW_DIALOG;
	else if(type == "popup")
		windowtype = GTK_WINDOW_POPUP;
	else if(type != "")
		g_return_val_if_fail(0, false);	// Unknown window type!

	SetWindowType(windowtype);

	// Set the window title ...
	const sdpString title = sdpxml::GetAttribute<sdpString>(Element, "title", "");
	sdpGtkMarkAttribute(Document, Element, "title");
	SetTitle(title);

	// Set window modality ...
	const bool modal = sdpxml::GetAttribute(Element, "modal", false);
	sdpGtkMarkAttribute(Document, Element, "modal");
	SetModal(modal);

	// Handle window resizing policy ...
	const bool allowshrink = sdpxml::GetAttribute(Element, "allowshrink", false);
	sdpGtkMarkAttribute(Document, Element, "allowshrink");

	const bool allowgrow = sdpxml::GetAttribute(Element, "allowgrow", true);
	sdpGtkMarkAttribute(Document, Element, "allowgrow");

	const bool autoshrink = sdpxml::GetAttribute(Element, "autoshrink", true) ;
	sdpGtkMarkAttribute(Document, Element, "autoshrink");

	SetPolicy(allowshrink, allowgrow, autoshrink);

	return sdpGtkBin::CreateOptions(ObjectContainer, Document, Element);
}

void sdpGtkWindow::SetTitle(SDPCSTRING Title)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_window_set_title(*this, sdpString(Title));
}

void sdpGtkWindow::SetFocus(GtkWidget* Widget)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	gtk_window_set_focus(*this, Widget);
}

void sdpGtkWindow::SetDefault(GtkWidget* Widget)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	gtk_window_set_default(*this, Widget);
}

void sdpGtkWindow::SetPolicy(gint AllowShrink, gint AllowGrow, gint AutoShrink)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_window_set_policy(*this, AllowShrink, AllowGrow, AutoShrink);
}

void sdpGtkWindow::SetPosition(GtkWindowPosition Position)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_window_set_position(*this, Position);
}

void sdpGtkWindow::SetDefaultSize(gint Width, gint Height)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_window_set_default_size(*this, Width, Height);
}

void sdpGtkWindow::SetModal(bool Modal)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_window_set_modal(*this, Modal);
}

void sdpGtkWindow::SetTransientFor(GtkWindow* Window)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	
	gtk_window_set_transient_for(*this, Window);
}

void sdpGtkWindow::SetWindowType(GtkWindowType Type)
{
	gtk_object_set(*this, "type", Type, NULL);	
}

GtkWindowType sdpGtkWindow::GetWindowType()
{
	GtkWindowType type;
	gtk_object_get(*this, "type", &type, NULL);
	return type;
}
