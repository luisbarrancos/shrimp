
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

#include "sdpgtkfileselection.h"
#include "sdpgtkutility.h"

//////////////////////////////////////////////////////////////////////////////////////////
// sdpGtkFileSelection

sdpGtkFileSelection::sdpGtkFileSelection() : sdpGtkWindow()
{
}

sdpGtkFileSelection::sdpGtkFileSelection(GtkFileSelection* FileSelection) : sdpGtkWindow(GTK_WINDOW(FileSelection))
{
}


bool sdpGtkFileSelection::Create(SDPCSTRING Title)
{
	m_Object = GTK_OBJECT(gtk_file_selection_new(Title));
	return Attached();
}

bool sdpGtkFileSelection::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	return Create(sdpGtkInternationalText(Document, Element));
}

void sdpGtkFileSelection::SetFilePath(SDPCSTRING FilePath)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_file_selection_set_filename(*this, FilePath);
}

sdpString sdpGtkFileSelection::GetFilePath()
{
	// Sanity checks ...
#ifdef FAIL_ON_RET
	sdpString tmpResult;
	g_return_val_if_fail(Attached(), tmpResult);
#else
	g_return_val_if_fail(Attached(), sdpString());
#endif

	return sdpString(gtk_file_selection_get_filename(*this));
}

void sdpGtkFileSelection::CompletePath(SDPCSTRING Pattern)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_file_selection_complete(*this, Pattern);
}

void sdpGtkFileSelection::ShowFileOpButtons()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_file_selection_show_fileop_buttons(*this);
}

void sdpGtkFileSelection::HideFileOpButtons()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_file_selection_hide_fileop_buttons(*this);
}

sdpGtkButton sdpGtkFileSelection::OKButton()
{
	return sdpGtkButton(GTK_BUTTON(GTK_FILE_SELECTION(m_Object)->ok_button));
}

sdpGtkButton sdpGtkFileSelection::CancelButton()
{
	return sdpGtkButton(GTK_BUTTON(GTK_FILE_SELECTION(m_Object)->cancel_button));
}

sdpGtkButton sdpGtkFileSelection::HelpButton()
{
	return sdpGtkButton(GTK_BUTTON(GTK_FILE_SELECTION(m_Object)->help_button));
}
