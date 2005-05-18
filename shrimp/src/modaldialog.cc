//============================================================================
//
// Shrimp Shader Generator
// Copyright (C) 2000-2004 Andy Gill
//
// ModalDialog class taken from sample.cpp by T.Shead
// as distributed with SdpGtk.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
//============================================================================

#include "modaldialog.h"

bool ModalDialog::Load()
{
	sdpGtkObjectContainer::Load(guifile);

	gtk_window_set_position(RootWindow(), GTK_WIN_POS_CENTER);

	RootWidget().Show();

	return true;
}

void ModalDialog::DoModal(GtkWindow* window)
{
	g_return_if_fail(Load());

	if(window)
		sdpGtkObjectContainer::DoModal(window);
	else
		sdpGtkObjectContainer::DoModal();
}

void ModalDialog::OnEvent(sdpGtkEvent* event)
{
	if(event->Name() == "ondestroy")
		OnDestroy();
	else if(event->Name() == "onok")
		OnOK();
	else if(event->Name() == "oncancel")
		OnCancel();
	else
		sdpGtkObjectContainer::OnEvent(event);
}

void ModalDialog::OnDestroy()
{
	CancelModal();
}

void ModalDialog::OnOK()
{
	m_Result = true;
	RootWidget().Destroy();
}

void ModalDialog::OnCancel()
{
	m_Result = false;
	RootWidget().Destroy();
}


