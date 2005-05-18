#ifndef SDPGTKCALENDAR_H
#define SDPGTKCALENDAR_H

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
		\brief Declares the sdpGtkCalendar class, which encapsulates a GtkCalendar widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkwidget.h"

/// Encapsulates a GtkCalendar widget
class sdpGtkCalendar : public sdpGtkWidget
{
public:
	/// Standard constructor
	sdpGtkCalendar();
	/// Attaches the instance to an existing GtkCalendar widget
	sdpGtkCalendar(GtkCalendar* Calendar);

	/// Creates a new GtkCalendar
	bool Create();
	/// Creates a new GtkCalendar from a GTKML (XML) container
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	bool CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Moves the calendar to the given month/year
	gint SelectMonth(guint Month, guint Year);
	/// Selects the given day
	void SelectDay(guint Day);
	/// Marks the given day
	gint MarkDay(guint Day);
	/// Unmarks the given day
	gint UnmarkDay(guint Day);
	/// Removes all marks
	void ClearMarks();
	/// Sets display options
	void SetDisplayOptions(GtkCalendarDisplayOptions Options);
	/// Returns the currently selected date
	void GetDate(guint& Year, guint& Month, guint& Day);
	/// Freezes calendar updates
	void Freeze();
	/// Thaws calendar updates
	void Thaw();

	/// Casts this instance to a GtkCalendar pointer
	operator GtkCalendar*() { return GTK_CALENDAR(m_Object); }
};

#endif // SDPGTKCALENDAR_H
