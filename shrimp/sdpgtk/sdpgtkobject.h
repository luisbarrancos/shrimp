#ifndef SDPGTKOBJECT_H
#define SDPGTKOBJECT_H

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
		\brief Declares the sdpGtkObject class, which encapsulates a GtkObject
		\author Timothy M. Shead (tshead@k-3d.com)
		\author Dan Erikson <derikson@montana.com>
*/

extern "C"
{
#include <gtk/gtk.h>
}

#ifndef SDPXML_H
#include <sdpxml/sdpxml.h>
#endif // !SDPXML_H

// Forward class declarations
class sdpGtkIObjectContainer;

/////////////////////////////////////////////////////////////////////////////////////
// sdpGtkObject

/// Encapsulates a GtkObject
class sdpGtkObject
{
public:
	/// Standard constructor
	sdpGtkObject();
	/// Attaches this instance to an existing GtkObject
	sdpGtkObject(GtkObject* Object);

	virtual ~sdpGtkObject();

	/// Returns true if we're attached to an existing Gtk+ object
	bool Attached() const;
	/// Returns the custom type of this object as a string
	virtual const sdpString CustomType() const;

	/// Casts this instance to a GtkObject
	operator GtkObject*() const { return m_Object; }
	/// Returns the GtkObject this instance is attached to
	GtkObject* Object() const { return m_Object; }

	/// Called to create a Gtk+ widget when creating a UI from a GTKML (XML) document
	virtual bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);
	/// Called after the Gtk+ widget has been created to handle setting widget options from a GTKML (XML) document
	virtual bool CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);
	/// Called after the Gtk+ widget has been created to create child widgets from a GTKML (XML) document
	virtual bool CreateChildren(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);
	/// Called by CreateChildren for each child element to create child widgets from a GTKML (XML) document
	virtual void CreateChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement);
	/// Called after a child Gtk+ widget has been created to attach it to this instance
	virtual bool AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child);

	/// Sets a user-defined name-value pair
	void SetData(SDPCSTRING Name, gpointer Value);
	/// Returns a user-defined name-value pair
	gpointer GetData(SDPCSTRING Name);
	/// Deletes a user-defined name-value pair
	void RemoveData(SDPCSTRING Name);

protected:
	/// Stores the GtkObject this instance is attached to
	GtkObject* m_Object;
};

#endif // SDPGTKOBJECT_H

