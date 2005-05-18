#ifndef SDPGTKBOX_H
#define SDPGTKBOX_H

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

#include "sdpgtkcontainer.h"

////////////////////////////////////////////////////////////////////////////////////////
// sdpGtkBox

class sdpGtkBox : public sdpGtkContainer
{
public:
	sdpGtkBox();
	sdpGtkBox(GtkBox* Box);

	// Operations ...
	void PackStart(GtkWidget* Widget, bool Expand = true, bool Fill = true, guint Padding = 0);
	void PackEnd(GtkWidget* Widget, bool Expand = true, bool Fill = true, guint Padding = 0);
	void SetHomogeneous(bool Homogeneous);
	virtual void SetSpacing(gint Spacing);

	// XML overrides ...
	bool AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child);
	bool CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	// Casting ...
	operator GtkBox*() { return GTK_BOX(m_Object); }
};



#endif // SDPGTKBOX_H
