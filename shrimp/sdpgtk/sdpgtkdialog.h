#ifndef SDPGTKDIALOG_H
#define SDPGTKDIALOG_H

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
		\brief Declares the sdpGtkDialog class, which encapsulates a GtkDialog widget
		\author Timothy M. Shead (tshead@k-3d.com)
		\author Dan Erikson <derikson@montana.com>
*/

#include "sdpgtkwindow.h"
#include "sdpgtkbutton.h"
#include "sdpgtklabel.h"
#include "sdpgtkvbox.h"
#include "sdpgtkhbox.h"

#include <vector>

////////////////////////////////////////////////////////////////////////////////////////////////
// sdpGtkDialog

/// Encapsulates a GtkDialog widget
class sdpGtkDialog : public sdpGtkWindow
{
public:
	/// Standard constructor
	sdpGtkDialog();
	/// Attaches this instance to an existing GtkDialog widget
	sdpGtkDialog(GtkDialog* Dialog);

	/// Creates a new GtkDialog widget
	bool Create();
	/// Creates a new GtkDialog widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Returns the top half of the dialog as an sdpGtkVBox
	sdpGtkVBox Top() { return sdpGtkVBox(GTK_VBOX(GTK_DIALOG(m_Object)->vbox)); }
	/// Returns the bottom half of the dialog as an sdpGtkHBox
	sdpGtkHBox Bottom() { return sdpGtkHBox(GTK_HBOX(GTK_DIALOG(m_Object)->action_area)); }

	void CreateChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement);

	/// Casts this instance to a GtkDialog pointer
	operator GtkDialog*() { return GTK_DIALOG(m_Object); }
};

#endif // SDPGTKDIALOG_H
