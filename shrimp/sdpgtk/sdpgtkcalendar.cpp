
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
		\brief Implements the sdpGtkCalendar class, which encapsulates the GtkCalendar widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkcalendar.h"
#include "sdpgtkutility.h"

sdpGtkCalendar::sdpGtkCalendar() : sdpGtkWidget()
{
}

sdpGtkCalendar::sdpGtkCalendar(GtkCalendar* Calendar) : sdpGtkWidget(GTK_WIDGET(Calendar))
{
}

bool sdpGtkCalendar::Create()
{
	m_Object = GTK_OBJECT(gtk_calendar_new());
	return Attached();
}

bool sdpGtkCalendar::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	return Create();
}

bool sdpGtkCalendar::CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	const sdpString textdisplayoptions = sdpxml::GetAttribute<sdpString>(Element, "displayoptions", "");
	sdpGtkMarkAttribute(Document, Element, "displayoptions");

	if(textdisplayoptions.size())
		{
			int displayoptions = 0;

			if(textdisplayoptions.find("heading") != sdpString::npos)
				displayoptions |= GTK_CALENDAR_SHOW_HEADING;
			if(textdisplayoptions.find("daynames") != sdpString::npos)
				displayoptions |= GTK_CALENDAR_SHOW_DAY_NAMES;
			if(textdisplayoptions.find("nomonthchanges") != sdpString::npos)
				displayoptions |= GTK_CALENDAR_NO_MONTH_CHANGE;
			if(textdisplayoptions.find("weeknumbers") != sdpString::npos)
				displayoptions |= GTK_CALENDAR_SHOW_WEEK_NUMBERS;
			if(textdisplayoptions.find("startmonday") != sdpString::npos)
				displayoptions |= GTK_CALENDAR_WEEK_START_MONDAY;

			SetDisplayOptions(GtkCalendarDisplayOptions(displayoptions));
		}

	return sdpGtkWidget::CreateOptions(ObjectContainer, Document, Element);
}

gint sdpGtkCalendar::SelectMonth(guint Month, guint Year)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), -1);

	return gtk_calendar_select_month(*this, Month, Year);
}

void sdpGtkCalendar::SelectDay(guint Day)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_calendar_select_day(*this, Day);
}

gint sdpGtkCalendar::MarkDay(guint Day)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), -1);

	return gtk_calendar_mark_day(*this, Day);
}

gint sdpGtkCalendar::UnmarkDay(guint Day)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), -1);

	return gtk_calendar_unmark_day(*this, Day);
}

void sdpGtkCalendar::ClearMarks()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_calendar_clear_marks(*this);
}

void sdpGtkCalendar::SetDisplayOptions(GtkCalendarDisplayOptions Options)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_calendar_display_options(*this, Options);
}

void sdpGtkCalendar::GetDate(guint& Year, guint& Month, guint& Day)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_calendar_get_date(*this, &Year, &Month, &Day);
}

void sdpGtkCalendar::Freeze()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_calendar_freeze(*this);
}

void sdpGtkCalendar::Thaw()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_calendar_thaw(*this);
}

