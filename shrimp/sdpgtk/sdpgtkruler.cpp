
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
		\brief Implements the sdpGtkRuler class, which wraps GtkRuler
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkruler.h"
#include "sdpgtkutility.h"

sdpGtkRuler::sdpGtkRuler() : sdpGtkWidget()
{
}

sdpGtkRuler::sdpGtkRuler(GtkRuler* Ruler) : sdpGtkWidget(GTK_WIDGET(Ruler))
{
}

bool sdpGtkRuler::CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	// Metric ...
	const sdpString metrictext = sdpxml::GetAttribute<sdpString>(Element, "metric", "pixels");
	sdpGtkMarkAttribute(Document, Element, "metric");

	GtkMetricType metric;
	if(metrictext == "pixels")
		metric = GTK_PIXELS;
	else if(metrictext == "inches")
		metric = GTK_INCHES;
	else if(metrictext == "cm")
		metric = GTK_CENTIMETERS;
	else
		g_return_val_if_fail(0, false);

	SetMetric(metric);

	// Ruler range ...
	const sdpVector2 range = sdpxml::GetAttribute(Element, "range", sdpVector2(0.0, 0.0));
	sdpGtkMarkAttribute(Document, Element, "range");

	// Current position ...
	const gdouble position = sdpxml::GetAttribute(Element, "position", 0.0);
	sdpGtkMarkAttribute(Document, Element, "position");

	// Maximum size ...
	const gdouble maxsize = sdpxml::GetAttribute(Element, "maxsize", 0.0);
	sdpGtkMarkAttribute(Document, Element, "maxsize");

	SetRange(range[0], range[1], position, maxsize);

	return sdpGtkWidget::CreateOptions(ObjectContainer, Document, Element);
}

void sdpGtkRuler::SetMetric(GtkMetricType Metric)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ruler_set_metric(*this, Metric);
}

void sdpGtkRuler::SetRange(gdouble Lower, gdouble Upper, gdouble Position, gdouble MaxSize)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_ruler_set_range(*this, Lower, Upper, Position, MaxSize);
}

