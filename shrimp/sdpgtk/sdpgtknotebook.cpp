
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

#include "sdpgtknotebook.h"
#include "sdpgtklabel.h"
#include "sdpgtkutility.h"

sdpGtkNotebook::sdpGtkNotebook() : sdpGtkContainer()
{
}

sdpGtkNotebook::sdpGtkNotebook(GtkNotebook* Notebook) : sdpGtkContainer(GTK_CONTAINER(Notebook))
{
}

bool sdpGtkNotebook::Create()
{
	m_Object = GTK_OBJECT(gtk_notebook_new());
	return Attached();
}

bool sdpGtkNotebook::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	// Create our notebook ...
	return Create();
}

bool sdpGtkNotebook::AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child)
{
	// Sanity checks ...
	g_assert(Child);

	const sdpString tablabel = sdpxml::GetAttribute<sdpString>(ChildElement, "tablabel", "");
	sdpGtkMarkAttribute(Document, ChildElement, "tablabel");

	sdpGtkLabel label;
	label.Create(tablabel);

	AppendPage(GTK_WIDGET(Child->Object()), GTK_WIDGET(label.Object()));
	return true;
}

void sdpGtkNotebook::LeftTabs()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_notebook_set_tab_pos(*this, GTK_POS_LEFT);
}

void sdpGtkNotebook::RightTabs()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_notebook_set_tab_pos(*this, GTK_POS_RIGHT);
}

void sdpGtkNotebook::TopTabs()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_notebook_set_tab_pos(*this, GTK_POS_TOP);
}

void sdpGtkNotebook::BottomTabs()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_notebook_set_tab_pos(*this, GTK_POS_BOTTOM);
}

void sdpGtkNotebook::ShowTabs()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_notebook_set_show_tabs(*this, true);
}

void sdpGtkNotebook::HideTabs()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_notebook_set_show_tabs(*this, false);
}

void sdpGtkNotebook::ShowBorder()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_notebook_set_show_border(*this, true);
}

void sdpGtkNotebook::HideBorder()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_notebook_set_show_border(*this, false);
}

void sdpGtkNotebook::AppendPage(GtkWidget* Page, GtkWidget* Label)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	g_assert(Page);

	gtk_notebook_append_page(*this, Page, Label);
}

void sdpGtkNotebook::PrependPage(GtkWidget* Page, GtkWidget* Label)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	g_assert(Page);

	gtk_notebook_prepend_page(*this, Page, Label);
}

void sdpGtkNotebook::InsertPage(GtkWidget* Page, GtkWidget* Label, gint Position)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	g_assert(Page);

	gtk_notebook_insert_page(*this, Page, Label, Position);
}

void sdpGtkNotebook::RemovePage(gint Position)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_notebook_remove_page(*this, Position);
}

gint sdpGtkNotebook::CurrentPage()
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), -1);

	return gint(gtk_notebook_get_current_page(*this));
}

void sdpGtkNotebook::SetPage(gint Page)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_notebook_set_page(*this, Page);
}

void sdpGtkNotebook::NextPage()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_notebook_next_page(*this);
}

void sdpGtkNotebook::PreviousPage()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_notebook_prev_page(*this);
}

bool sdpGtkNotebook::InteractiveShowPage(const gint Page, const gdouble Speed, const bool Pause)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), false);
	g_return_val_if_fail(Page >= 0, false);

	if(Page == CurrentPage())
		return true;

	gint pagenumber = 0;
	GtkNotebookPage* page = 0;
	for(GList* list = GTK_NOTEBOOK(m_Object)->children; list; list = list->next)
		{
			page = GTK_NOTEBOOK_PAGE(list);

			if(pagenumber == Page)
				break;
				
			pagenumber++;
		}
	g_return_val_if_fail(page, false);
	
	InteractiveWarpPointer(page->allocation.x + (page->allocation.width / 2), page->allocation.y + (page->allocation.height / 2), Speed, Pause, false);
	SetPage(Page);

	return true;
}


