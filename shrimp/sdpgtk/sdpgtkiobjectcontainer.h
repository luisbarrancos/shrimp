#ifndef SDPGTKIOBJECTCONTAINER_H
#define SDPGTKIOBJECTCONTAINER_H

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
		\brief Declares the sdpGtkIObjectContainer sdpCOM interface
		\author Tim Shead (tshead@k-3d.com)
*/

#include <gtk/gtk.h>

#ifndef SDPTYPES_H
#include <sdptypes/sdptypes.h>
#endif // !SDPTYPES_H

#ifndef SDPXML_H
#include <sdpxml/sdpxml.h>
#endif // !SDPXML_H

// Forward class references ...
class sdpGtkObject;
class sdpGtkEvent;

// We have a small collision with <windows.h>
#ifdef SDPWIN32
#ifdef GetObject
#undef GetObject
#endif // GetObject
#endif // SDPWIN32

/////////////////////////////////////////////////////////////////////////////////////
// sdpGtkIObjectContainer

/// Interface for a GTK+ widget/event container class
class sdpGtkIObjectContainer
{
public:
	/// Notify the underlying container that an object has been created
	virtual void NotifyObject(GtkObject* Object) = 0;
	/// Ask the underlying container to map a name to an object
	virtual void MapObject(SDPCSTRING ObjectName, GtkObject* Object) = 0;
	/// Ask the underlying container to map a name to a custom object
	virtual void MapCustomObject(SDPCSTRING CustomObjectName, sdpGtkObject* CustomObject) = 0;
	/// Ask the underlying container to map a name to an event
	virtual void MapEvent(sdpxml::Document& Document, sdpxml::Element& Element, GtkObject* Object, bool Connect) = 0;
	/// Ask the underlying container to map a radio-button/radio-menu-item group by name
	virtual void MapGroup(SDPCSTRING GroupName, GSList* Group) = 0;
	/// Ask the underlying container to map a name to a string resource
	virtual void MapResource(SDPCSTRING ResourceName, SDPCSTRING ResourceValue) = 0;
	/// Ask the underlying container to create a custom object, if possible
	virtual sdpGtkObject* CreateCustomObject(sdpxml::Element& Element) = 0;
	/// Return an accelerator group
	virtual GtkAccelGroup* GetAcceleratorGroup() = 0;
	/// Return an object by name
	virtual GtkObject* GetObject(SDPCSTRING ObjectName) = 0;
	/// Return a radio-button/radio-menu-item group by name
	virtual GSList* GetGroup(SDPCSTRING GroupName) = 0;
};

#endif // SDPGTKIOBJECTCONTAINER_H

