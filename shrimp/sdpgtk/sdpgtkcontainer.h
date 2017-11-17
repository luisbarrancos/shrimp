#ifndef SDPGTKCONTAINER_H
#define SDPGTKCONTAINER_H

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
		\brief Declares the sdpGtkContainer class, which encapsulates a GtkContainer widget
		\author Timothy M. Shead (tshead@k-3d.com)
		\author Dan Erikson <derikson@montana.com>
*/

#include "sdpgtkwidget.h"

/// Encapsulates a GtkContainer widget
class sdpGtkContainer : public sdpGtkWidget
{
public:
	/// Standard constructor
	sdpGtkContainer();
	/// Attaches the constructor to a GtkContainer widget
	sdpGtkContainer(GtkContainer* Container);

	bool CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Attaches a child widget
	void Attach(GtkWidget* Widget);
	/// Attaches a child widget
	void Attach(sdpGtkWidget& Widget);
	/// Removes a child widget
	void Remove(GtkWidget* Widget);
	/// Removes a child widget
	void Remove(sdpGtkWidget& Widget);
	/// Sets the container border width
	void SetBorderWidth(guint BorderWidth);

	bool AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child);

	/// Casts this instance to a GtkContainer pointer
	operator GtkContainer*() { return GTK_CONTAINER(m_Object); }
};

#endif // SDPGTKCONTAINER_H
