#ifndef SDPGTKRULER_H
#define SDPGTKRULER_H

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
		\brief Declares the sdpGtkRuler class, which encapsulates a GtkRuler widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkwidget.h"

/// Encapsulates a GtkRuler widget
class sdpGtkRuler : public sdpGtkWidget
{
public:
	/// Standard constructor
	sdpGtkRuler();
	/// Attaches this instance to an existing GtkRuler widget
	sdpGtkRuler(GtkRuler* Ruler);

	bool CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Sets the units-of-measure for the ruler
	void SetMetric(GtkMetricType Metric);
	/// Sets the range of units displayed by the ruler
	void SetRange(gdouble Lower, gdouble Upper, gdouble Position, gdouble MaxSize);

	/// Casts this instance into a GtkRuler pointer
	operator GtkRuler*() { return GTK_RULER(m_Object); }
};

#endif // SDPGTKRULER_H
