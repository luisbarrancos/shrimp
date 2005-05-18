#ifndef SDPGTKUTILITY_H
#define SDPGTKUTILITY_H

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

#include <gtk/gtk.h>

#ifndef SDPTYPES_H
#include <sdptypes/sdptypes.h>
#endif // !SDPTYPES_H

#ifndef SDPXML_H
#include <sdpxml/sdpxml.h>
#endif // !SDPXML_H

/// Retrieves text from a GTKML (XML) element, transparently checking for internationalized (<i18n></i18n>) text ...
sdpString sdpGtkInternationalText(sdpxml::Document& Document, sdpxml::Element& Element);

/// Marks a GTKML (XML) attribute as "used", so we can warn about unused & unknown attributes when loading documents
void sdpGtkMarkAttribute(sdpxml::Document& Document, sdpxml::Element& Element, const sdpString Attribute);
/// Looks for a "shadowtype" attribute in a GTKML (XML) document and returns its value
GtkShadowType sdpGtkGetShadowType(sdpxml::Document& Document, sdpxml::Element& Element, const GtkShadowType Default);

/// Dispatches any pending GTK+ events (good to do after any long operations)
void sdpGtkHandlePendingEvents();

/// Provides a portable Sleep() that doesn't block processing of GTK+ events
void sdpGtkSleep(const gulong Milliseconds);

/// Provides a cross-platform way to move the mouse pointer, relative to the given window
void sdpGtkWarpPointer(GdkWindow* const Window, const gint XOffset, const gint YOffset);
/// Provides a cross-platform way to move the mouse pointer, relative to the given widget
void sdpGtkWarpPointer(GtkWidget* const Widget, const gint XOffset, const gint YOffset);

/// Abstract interface for a callback called when simulating mouse movement
class sdpGtkInteractiveWarpPointerCallback
{
public:
	virtual bool HandleInteractivePointerWarp(GtkWidget* const Widget, const gint XOffset, const gint YOffset) = 0;
};

/// Calls a callback repeatedly with simulated mouse motion coordinates, relative to the given widget
void sdpGtkInteractiveWarpPointer(GtkWidget* const Widget, const gint XOffset, const gint YOffset, sdpGtkInteractiveWarpPointerCallback& Callback, const gdouble Speed, const bool Pause, const bool ManhattanStyle);
/// Simulates user interaction by moving the mouse pointer, relative to the given widget
void sdpGtkInteractiveWarpPointer(GtkWidget* const Widget, const gint XOffset, const gint YOffset, const gdouble Speed, const bool Pause, const bool ManhattanStyle);

#endif // SDPGTKUTILITY_H

