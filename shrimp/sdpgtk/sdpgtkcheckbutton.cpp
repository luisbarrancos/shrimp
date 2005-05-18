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

#include <string.h>
#include "sdpgtkcheckbutton.h"
#include "sdpgtkutility.h"

///////////////////////////////////////////////////////////////////////////
// sdpGtkCheckButton

sdpGtkCheckButton::sdpGtkCheckButton()
{
}

sdpGtkCheckButton::sdpGtkCheckButton(GtkCheckButton* CheckButton) : sdpGtkToggleButton(GTK_TOGGLE_BUTTON(CheckButton))
{
}

bool sdpGtkCheckButton::Create()
{
	m_Object = GTK_OBJECT(gtk_check_button_new());
	return Attached();
}

bool sdpGtkCheckButton::Create(SDPCSTRING Label)
{
	// Sanity checks ...
	g_assert(Label);

	m_Object = GTK_OBJECT(gtk_check_button_new_with_label(Label));
	return Attached();
}

bool sdpGtkCheckButton::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	const sdpString text(sdpGtkInternationalText(Document, Element));
	return text.size() ? Create(text) : Create();
}

