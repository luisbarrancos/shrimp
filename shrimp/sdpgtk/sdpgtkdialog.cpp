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

#include "sdpgtkdialog.h"
#include "sdpgtkutility.h"

//////////////////////////////////////////////////////////////////////////////////////////
// sdpGtkDialog

sdpGtkDialog::sdpGtkDialog() : sdpGtkWindow()
{
}

sdpGtkDialog::sdpGtkDialog(GtkDialog* Dialog) : sdpGtkWindow(GTK_WINDOW(Dialog))
{
}


bool sdpGtkDialog::Create()
{
	m_Object = GTK_OBJECT(gtk_dialog_new());
	return Attached();
}

bool sdpGtkDialog::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	return Create();
}

void sdpGtkDialog::CreateChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement)
{
	// Get the element name ...
	const sdpString name = ChildElement.Name();

	if(name == "dialog-top")
		{
			Top().CreateOptions(ObjectContainer, Document, ChildElement);
			Top().CreateChildren(ObjectContainer, Document, ChildElement);
		}

	else if(name == "dialog-bottom")
		{
			Bottom().CreateOptions(ObjectContainer, Document, ChildElement);
			Bottom().CreateChildren(ObjectContainer, Document, ChildElement);
		}
	else
		{
			sdpGtkWindow::CreateChild(ObjectContainer, Document, ChildElement);
		}
}
