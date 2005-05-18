#ifndef SDPGTKTEXT_H
#define SDPGTKTEXT_H

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
		\brief Declares the sdpGtkText class, which encapsulates a GtkText widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkeditable.h"

/// Encapsulates a GtkText widget
class sdpGtkText : public sdpGtkEditable
{
public:
	/// Standard constructor
	sdpGtkText();
	/// Attaches this instance to an existing GtkText widget
	sdpGtkText(GtkText* Text);

	/// Creates a new GtkText widget
	bool Create();
	/// Creates a new GtkText widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	bool CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Controls whether the text is editable or read-only
	void SetEditable(bool Editable);
	/// Controls whether words are wrapped at the end of a row on a word boundary
	void SetWordWrap(bool WordWrap);
	/// Controls whether lines are wrapped at the end of a row, regardless of word boundary
	void SetLineWrap(bool LineWrap);
	

	void SetPoint(guint Index);
	guint GetPoint();
	guint GetLength();

	/// Freezes display updates for the widget
	void Freeze();
	/// Resumes display updates for the widget
	void Thaw();

	/// Inserts text into the widget
	void Insert(GdkFont* Font, GdkColor* ForegroundColor, GdkColor* BackgroundColor, const char* Text, gint Length);
	/// Deletes characters backwards from the cursor
	gint BackwardDelete(guint Count);
	/// Deletes characters forwards from the cursor
	gint ForwardDelete(guint Count);

	/// Casts this instance into a GtkText pointer
	operator GtkText*() { return GTK_TEXT(m_Object); }
};

#endif // SDPGTKTEXT_H

