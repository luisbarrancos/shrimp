
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

#include "sdpgtkradiobutton.h"
#include "sdpgtkutility.h"

#include "sdpgtkiobjectcontainer.h"

///////////////////////////////////////////////////////////////////////////
// sdpGtkRadioButton

sdpGtkRadioButton::sdpGtkRadioButton()
{
}

sdpGtkRadioButton::sdpGtkRadioButton(GtkRadioButton* RadioButton) : sdpGtkCheckButton(GTK_CHECK_BUTTON(RadioButton))
{
}

bool sdpGtkRadioButton::Create(GSList* Group)
{
	m_Object = GTK_OBJECT(gtk_radio_button_new(Group));
	return Attached();
}

bool sdpGtkRadioButton::Create(GSList* Group, SDPCSTRING Label)
{
	// Sanity checks ...
	g_assert(Label);

	m_Object = GTK_OBJECT(gtk_radio_button_new_with_label(Group, Label));
	return Attached();
}

bool sdpGtkRadioButton::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	// Get a group name (required) ...
	const sdpString group = sdpxml::GetAttribute<sdpString>(Element, "group", "");
	sdpGtkMarkAttribute(Document, Element, "group");
	g_return_val_if_fail(group.size(), false);
	
	// Create the widget ...
	const sdpString text(sdpGtkInternationalText(Document, Element));
	if(text.size())
		g_return_val_if_fail(Create(ObjectContainer->GetGroup(group), text), false);
	else
		g_return_val_if_fail(Create(ObjectContainer->GetGroup(group)), false);
		
	ObjectContainer->MapGroup(group, gtk_radio_button_group(*this));

	return true;
}

