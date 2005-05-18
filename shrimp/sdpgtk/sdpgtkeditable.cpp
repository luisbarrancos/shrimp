
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

#include "sdpgtkeditable.h"
#include "sdpgtkutility.h"

#include <gdk/gdkkeysyms.h>

sdpGtkEditable::sdpGtkEditable() : sdpGtkWidget()
{
}

sdpGtkEditable::sdpGtkEditable(GtkEditable* Editable) : sdpGtkWidget(GTK_WIDGET(Editable))
{
}

void sdpGtkEditable::SetPosition(gint Position)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_editable_set_position(*this, Position);
}

gint sdpGtkEditable::GetPosition()
{
	// Sanity checks ...
	g_return_val_if_fail(m_Object, -1);

	return gtk_editable_get_position(*this);
}

void sdpGtkEditable::SelectRegion(gint Start, gint End)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_editable_select_region(*this, Start, End);
}

void sdpGtkEditable::DeleteSelection()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_editable_delete_selection(*this);
}

void sdpGtkEditable::DeleteText(gint Start, gint End)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_editable_delete_text(*this, Start, End);
}

void sdpGtkEditable::InsertText(SDPCSTRING Text, gint TextLength, gint* Position)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_editable_insert_text(*this, Text, TextLength, Position);
}

void sdpGtkEditable::SetText(SDPCSTRING Text)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	
	DeleteText(0, -1);

	gint position = 0;
	sdpString text(Text);
	InsertText(text, text.size(), &position);
}

sdpString sdpGtkEditable::GetText(gint Start, gint End)
{
	// Sanity checks ...
#ifdef	FAIL_ON_RET
	sdpString tmpResult;
	g_return_val_if_fail(m_Object, tmpResult);
#else
	g_return_val_if_fail(m_Object, sdpString());
#endif

	gchar* buffer = gtk_editable_get_chars(*this, Start, End);
	sdpString result(buffer);
	g_free(buffer);

	return result;
}

sdpString sdpGtkEditable::GetText()
{
	// Sanity checks ...
#ifdef	FAIL_ON_RET
	sdpString tmpResult;
	g_return_val_if_fail(m_Object, tmpResult);
#else
	g_return_val_if_fail(m_Object, sdpString());
#endif

	return GetText(0, -1);
}

void sdpGtkEditable::Cut()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_editable_cut_clipboard(*this);
}

void sdpGtkEditable::Copy()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_editable_copy_clipboard(*this);
}

void sdpGtkEditable::Paste()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_editable_paste_clipboard(*this);
}

void sdpGtkEditable::SetEditable(gboolean Editable)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_editable_set_editable(*this, Editable);
}

bool sdpGtkEditable::InteractiveSetText(SDPCSTRING Text, const gdouble Speed)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), false);
	g_return_val_if_fail(Speed, false);

	sdpString text(Text);

	GrabFocus();
	SetPosition(-1);
	SelectRegion(0, -1);
	sdpGtkHandlePendingEvents();
	sdpGtkSleep(static_cast<gulong>(500 / Speed));

	DeleteText(0, -1);
	sdpGtkHandlePendingEvents();
	sdpGtkSleep(static_cast<gulong>(500 / Speed));

	for(guint i = 0; i < text.size(); i++)
		{
			gint position = i;
			InsertText(&text[i], 1, &position);
			sdpGtkHandlePendingEvents();
			sdpGtkSleep(static_cast<gulong>((25 + (rand() % 150)) / Speed));
		}

	sdpGtkHandlePendingEvents();
	sdpGtkSleep(static_cast<gulong>(500 / Speed));

	GdkEventKey event;
	event.type = GDK_KEY_PRESS;
	event.window = GTK_WIDGET(Object())->window;
	event.send_event = TRUE;
	event.time= GDK_CURRENT_TIME;
	event.state = 0;
	event.keyval = GDK_Tab;
	event.length = 1;
	event.string = "\t";
	
	gtk_main_do_event(reinterpret_cast<GdkEvent*>(&event));
	
	return true;
}

