
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

#include "sdpgtkfontselectiondialog.h"
#include "sdpgtkutility.h"

//////////////////////////////////////////////////////////////////////////////////////////
// sdpGtkFontSelectionDialog

sdpGtkFontSelectionDialog::sdpGtkFontSelectionDialog() : sdpGtkWindow()
{
}

sdpGtkFontSelectionDialog::sdpGtkFontSelectionDialog(GtkFontSelectionDialog* FontSelectionDialog) : sdpGtkWindow(GTK_WINDOW(FontSelectionDialog))
{
}

bool sdpGtkFontSelectionDialog::Create(SDPCSTRING Title)
{
	m_Object = GTK_OBJECT(gtk_font_selection_dialog_new(Title));
	return Attached();
}

bool sdpGtkFontSelectionDialog::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	return Create(sdpGtkInternationalText(Document, Element));
}

sdpGtkButton sdpGtkFontSelectionDialog::OKButton()
{
	return sdpGtkButton(GTK_BUTTON(GTK_FONT_SELECTION_DIALOG(m_Object)->ok_button));
}

sdpGtkButton sdpGtkFontSelectionDialog::CancelButton()
{
	return sdpGtkButton(GTK_BUTTON(GTK_FONT_SELECTION_DIALOG(m_Object)->cancel_button));
}

sdpGtkButton sdpGtkFontSelectionDialog::ApplyButton()
{
	return sdpGtkButton(GTK_BUTTON(GTK_FONT_SELECTION_DIALOG(m_Object)->apply_button));
}


