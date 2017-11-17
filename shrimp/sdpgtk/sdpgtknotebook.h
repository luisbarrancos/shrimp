#ifndef SDPGTKNOTEBOOK_H
#define SDPGTKNOTEBOOK_H

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
		\brief Declares the sdpGtkNotebook class, which encapsulates a GtkNotebook widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkcontainer.h"

/// Encapsulates a GtkNotebook widget
class sdpGtkNotebook : public sdpGtkContainer
{
public:
	/// Standard constructor
	sdpGtkNotebook();
	/// Attaches this instance to an existing GtkNotebook widget
	sdpGtkNotebook(GtkNotebook* Notebook);

	/// Creates a new GtkNotebook widget
	bool Create();
	/// Creates a new GtkNotebook widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	bool AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child);

	/// Moves the notebook tabs to the left side of the widget
	void LeftTabs();
	/// Moves the notebook tabs to the right side of the widget
	void RightTabs();
	/// Moves the notebook tabs to the top of the widget
	void TopTabs();
	/// Moves the notebook tabs to the bottom of the widget
	void BottomTabs();
	/// Makes the notebook tabs visible
	void ShowTabs();
	/// Hides the notebook tabs
	void HideTabs();
	/// Makes the notebook border visible
	void ShowBorder();
	/// Hides the notebook border
	void HideBorder();

	/// Appends a page to the notebook
	void AppendPage(GtkWidget* Page, GtkWidget* Label);
	/// Prepends a page to the notebook
	void PrependPage(GtkWidget* Page, GtkWidget* Label);
	/// Inserts a page into the notebook
	void InsertPage(GtkWidget* Page, GtkWidget* Label, gint Position);
	/// Removes a page from the notebook
	void RemovePage(gint Position);

	/// Returns the currently selected page
	gint CurrentPage();
	/// Sets the current page
	void SetPage(gint Page);
	/// Moves to the next page
	void NextPage();
	/// Moves to the previous page
	void PreviousPage();
	
	/// Makes the given notebook page visible, with visible feedback
	bool InteractiveShowPage(const gint Page, const gdouble Speed, const bool Pause);
	
	/// Casts this instance into a GtkNotebook pointer
	operator GtkNotebook*() { return GTK_NOTEBOOK(m_Object); }
};

#endif // SDPGTKNOTEBOOK_H
