
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



#include "sdpgtkbutton.h"
#include "sdpgtkutility.h"

///////////////////////////////////////////////////////////////////////////
// sdpGtkButton

sdpGtkButton::sdpGtkButton() : sdpGtkBin()
{
}

sdpGtkButton::sdpGtkButton(GtkButton* Button) : sdpGtkBin(GTK_BIN(Button))
{
}

bool sdpGtkButton::Create()
{
	m_Object = GTK_OBJECT(gtk_button_new());
	return Attached();
}

bool sdpGtkButton::Create(SDPCSTRING Label)
{
	// Sanity checks ...
	g_assert(Label);

	m_Object = GTK_OBJECT(gtk_button_new_with_label(Label));
	return Attached();
}

bool sdpGtkButton::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	const sdpString text(sdpGtkInternationalText(Document, Element));
	return text.size() ? Create(text) : Create();
}


bool sdpGtkButton::CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	// Relief ...
	const sdpString relieftext = sdpxml::GetAttribute<sdpString>(Element, "relief", "normal");
	sdpGtkMarkAttribute(Document, Element, "relief");

	GtkReliefStyle relief = GTK_RELIEF_NORMAL;
	if(relieftext == "normal")
		relief = GTK_RELIEF_NORMAL;
	else if(relieftext == "half")
		relief = GTK_RELIEF_HALF;
	else if(relieftext == "none")
		relief = GTK_RELIEF_NONE;

	SetRelief(relief);

	return sdpGtkBin::CreateOptions(ObjectContainer, Document, Element);
}

void sdpGtkButton::SetRelief(GtkReliefStyle Style)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_button_set_relief(*this, Style);
}

GtkReliefStyle sdpGtkButton::GetRelief()
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), GtkReliefStyle(-1));

	return gtk_button_get_relief(*this);
}

static const gulong delay = 500;

void sdpGtkButton::InteractiveActivate()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	GtkButton* button = GTK_BUTTON(m_Object);

	if(!GTK_WIDGET_IS_SENSITIVE(GTK_WIDGET(button)))
		return;

	gtk_button_pressed(button);
	sdpGtkHandlePendingEvents();
	
	sdpGtkSleep(delay);

	gtk_button_released(button);
	sdpGtkHandlePendingEvents();
	
	sdpGtkSleep(delay);
}


