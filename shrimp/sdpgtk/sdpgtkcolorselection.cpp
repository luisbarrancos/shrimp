
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

#include "sdpgtkcolorselection.h"

////////////////////////////////////////////////////////////////////////////////////////
// sdpGtkColorSelection

sdpGtkColorSelection::sdpGtkColorSelection() : sdpGtkVBox()
{
}

sdpGtkColorSelection::sdpGtkColorSelection(GtkColorSelection* ColorSelection) : sdpGtkVBox(GTK_VBOX(ColorSelection))
{
}

bool sdpGtkColorSelection::Create()
{
	m_Object = GTK_OBJECT(gtk_color_selection_new());
	return Attached();
}

bool sdpGtkColorSelection::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	return Create();
}

void sdpGtkColorSelection::SetUpdatePolicy(GtkUpdateType Policy)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_color_selection_set_update_policy(*this, Policy);
}

void sdpGtkColorSelection::SetOpacity(bool UseOpacity)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_color_selection_set_opacity(*this, UseOpacity);
}

void sdpGtkColorSelection::SetColor(gdouble* Color)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	g_assert(Color);

	gtk_color_selection_set_color(*this, Color);
}

void sdpGtkColorSelection::GetColor(gdouble* Color)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	g_assert(Color);

	gtk_color_selection_get_color(*this, Color);
}

void sdpGtkColorSelection::InteractiveSetColor(const sdpVector3 Color, const gdouble Speed, const bool Pause)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	GtkColorSelection* colorselection = GTK_COLOR_SELECTION(m_Object);
	sdpGtkWidget wheelarea(colorselection->wheel_area);
	sdpGtkWidget valuearea(colorselection->value_area);

	// Get the current color
	sdpVector3 curcolor;
	GetColor(curcolor);
	
	// Convert current and new colors to HSV ...
	sdpVector3 curhsv(curcolor.HSV());
	sdpVector3 hsv(sdpVector3(Color).HSV());

	if(curhsv != hsv)
		InteractiveShow(Speed, Pause);

	// If hue or saturation have changed, update the color wheel ...
	if(curhsv[0] != hsv[0] || curhsv[1] != hsv[1])
		{
			sdpVector3 newhsv(hsv[0], hsv[1], curhsv[2]);
			sdpVector3 newcolor(newhsv.RGB());
		
			gdouble theta(sdpRadians(newhsv[0]));
			sdpVector2 offset(-sin(theta) * newhsv[1], -cos(theta) * newhsv[1]);
			offset *= 0.5;
			offset += 0.5;
		
			wheelarea.InteractiveWarpPointer(offset[0], offset[1], Speed, Pause, false);
			SetColor(newcolor);
		}
		
	// If value has changed, update the value area ...
	if(curhsv[2] != hsv[2])
		{
			sdpVector3 newhsv(hsv[0], hsv[1], hsv[2]);
			sdpVector3 newcolor(newhsv.RGB());

			valuearea.InteractiveWarpPointer(0.5, 1.0 - newhsv[2], Speed, Pause, false);
			SetColor(newcolor);
		}	
}



