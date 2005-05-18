// SDPGTK
// Copyright © 1995-2003, Timothy M. Shead
//
// Contact: tshead@k-3d.com
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public
// License along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

/** \file
		\brief Implements sdpGtkScreenOverlay
		\author Tim Shead (tshead@k-3d.com)
*/

#include "sdpgtkscreenoverlay.h"

#include "sdpgtkutility.h"
#include "sdpgtkevent.h"


#if defined SDPWIN32
#include <gdk/gdkwin32.h>
#else // SDPWIN32
#include <gdk/gdkx.h>
#include <X11/X.h>
#endif // !SDPWIN32

//////////////////////////////////////////////////////////////////////////
// sdpGtkScreenOverlay

const GdkColor sdpGtkScreenOverlay::White = { 1, 0xffff, 0xffff, 0xffff };
const GdkColor sdpGtkScreenOverlay::Black = { 0, 0x0000, 0x0000, 0x0000 };

sdpGtkScreenOverlay::sdpGtkScreenOverlay()
{
	m_X = 0;
	m_Y = 0;
	m_Width = 0;
	m_Height = 0;
	m_ScreenWidth = 0;
	m_ScreenHeight = 0;

	m_OverlayColor = sdpVector3(1, 0, 0);
	m_OverlayGC = 0;

	m_Mask = 0;
	m_MaskGC = 0;
}

sdpGtkScreenOverlay::sdpGtkScreenOverlay(const sdpVector3 OverlayColor)
{
	m_X = 0;
	m_Y = 0;
	m_Width = 0;
	m_Height = 0;
	m_ScreenWidth = 0;
	m_ScreenHeight = 0;

	m_OverlayColor = OverlayColor;
	m_OverlayGC = 0;

	m_Mask = 0;
	m_MaskGC = 0;
}

sdpGtkScreenOverlay::sdpGtkScreenOverlay(const gulong X, const gulong Y, const gulong Width, const gulong Height, const sdpVector3 OverlayColor)
{
	m_X = X;
	m_Y = Y;
	m_Width = Width;
	m_Height = Height;
	m_ScreenWidth = 0;
	m_ScreenHeight = 0;

	m_OverlayColor = OverlayColor;
	m_OverlayGC = 0;

	m_Mask = 0;
	m_MaskGC = 0;
}

sdpGtkScreenOverlay::~sdpGtkScreenOverlay()
{
	DisconnectAllEvents();
	RootWidget().Destroy();
	Clear();

	if(m_OverlayGC)
		{
			gdk_gc_unref(m_OverlayGC);
			m_OverlayGC = 0;
		}

	if(m_Mask)
		{
			gdk_bitmap_unref(m_Mask);
			m_Mask = 0;
		}

	if(m_MaskGC)
		{
			gdk_gc_unref(m_MaskGC);
			m_MaskGC = 0;
		}
}

bool sdpGtkScreenOverlay::Create()
{
	std::istringstream gtkml(
		"<gtkml>"
			"<window type=\"popup\" show=\"false\">"
				"<drawingarea name=\"drawingarea\">"
				"</drawingarea>"
			"</window>"
		"</gtkml>");

	// Load the GTKML document ...
	g_return_val_if_fail(Load(gtkml, "sdpGtkScreenOverlay"), false);

	// Setup the events we want to receive (must happen before we're realized) ...
	gtk_widget_set_events(static_cast<GtkWidget*>(Widget("drawingarea")), GDK_EXPOSURE_MASK);
	MapEvent("expose-event", "onexpose", false, DrawingArea("drawingarea"), true);

	// Resize the window as needed ...
	m_ScreenWidth = gdk_screen_width();
	m_ScreenHeight = gdk_screen_height();

	if(0 == m_Width)
		{
			m_X = 0;
			m_Width = m_ScreenWidth;
		}

	if(0 == m_Height)
		{
			m_Y = 0;
			m_Height = m_ScreenHeight;
		}

	RootWidget().Realize();
	RootWidget().SetPosition(m_X, m_Y);
	RootWidget().SetSize(m_Width, m_Height);

	// Setup a GC for the visible overlay ...
	GdkWindow* window = static_cast<GtkWidget*>(RootWidget())->window;

	m_OverlayGC = gdk_gc_new(window);
	SetColor(m_OverlayColor);

	// Create a blank bitmap to use as a mask for the window ...
	const gulong buffersize = m_Width * m_Height;
	char* buffer = new char[buffersize];
	g_return_val_if_fail(buffer, false);
	memset(buffer, 0x00, buffersize);
	m_Mask = gdk_bitmap_create_from_data(window, buffer, m_Width, m_Height);
	delete[] buffer;

	// Setup a GC for the mask ...
	m_MaskGC = gdk_gc_new(m_Mask);
	gdk_gc_set_foreground(m_MaskGC, const_cast<GdkColor*>(&White));
	gdk_gc_set_background(m_MaskGC, const_cast<GdkColor*>(&Black));

	// Combine the mask with our window ...
	gdk_window_shape_combine_mask(window, m_Mask, 0, 0);

	// Make everything visible ...
	RootWidget().Show();

	return true;
}

void sdpGtkScreenOverlay::Update()
{
	// Combine the mask with our window ...
	GdkWindow* window = static_cast<GtkWidget*>(RootWidget())->window;
	gdk_window_shape_combine_mask(window, m_Mask, 0, 0);

	// Force a redraw ...
	RootWidget().QueueDraw();
	sdpGtkHandlePendingEvents();
}

void sdpGtkScreenOverlay::SetColor(const sdpVector3 Color)
{
	m_OverlayColor = Color;
	m_AllocatedColor.reset(new GdkColor);

	GdkVisual& visual = *RootWidget().GetVisual();

	m_AllocatedColor->pixel = 0;
	m_AllocatedColor->pixel |= static_cast<gushort>((pow(2, visual.red_prec) - 1) * Color[0]) << visual.red_shift;
	m_AllocatedColor->pixel |= static_cast<gushort>((pow(2, visual.green_prec) - 1) * Color[1]) << visual.green_shift;
	m_AllocatedColor->pixel |= static_cast<gushort>((pow(2, visual.blue_prec) - 1) * Color[2]) << visual.blue_shift;

	m_AllocatedColor->red = static_cast<gushort>(0xffff * Color[0]);
	m_AllocatedColor->green = static_cast<gushort>(0xffff * Color[1]);
	m_AllocatedColor->blue = static_cast<gushort>(0xffff * Color[2]);

	gdk_gc_set_foreground(m_OverlayGC, m_AllocatedColor.get());

	RootWidget().QueueDraw();
}

void sdpGtkScreenOverlay::OnEvent(sdpGtkEvent* Event)
{
	if(Event->Name() == "onexpose")
		OnExpose();
	else
		sdpGtkObjectContainer::OnEvent(Event);
}

void sdpGtkScreenOverlay::OnExpose()
{
	GtkWidget* widget = static_cast<GtkWidget*>(Widget("drawingarea"));
	GdkWindow* window = widget->window;
	gdk_draw_rectangle(window, m_OverlayGC, TRUE, 0, 0, m_ScreenWidth, m_ScreenHeight);
}


