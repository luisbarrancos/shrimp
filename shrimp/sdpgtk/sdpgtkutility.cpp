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

extern "C"
{
#include <gtk/gtk.h>
}

#include "sdpgtkutility.h"

#if defined SDPWIN32
#include <gdk/gdkwin32.h>
#else // SDPWIN32
#include <gdk/gdkx.h>
#include <X11/X.h>
#endif // !SDPWIN32

#include <iostream>

sdpString sdpGtkInternationalText(sdpxml::Document& Document, sdpxml::Element& Element)
{
	for(sdpxml::ElementCollection::iterator international = Element.Children().begin(); international != Element.Children().end(); international++)
		{
			if(international->Name() == "i18n")
				{
					sdpGtkMarkAttribute(Document, *international, "language");
					return international->Text();
				}
		}

	return Element.Text();
}

void sdpGtkMarkAttribute(sdpxml::Document& Document, sdpxml::Element& Element, const sdpString Attribute)
{
	// Sanity checks ...
	g_assert(Attribute.size());

	// Get the named attribute ...
	sdpxml::AttributePointer const attribute = sdpxml::FindAttribute(Element, sdpxml::SameName(Attribute));
	if(!attribute)
		return;

	// Make sure someone else hasn't already used this attribute ...
	const sdpString usedby = attribute->Meta("usedby");
	if(usedby.size())
		{
			std::cout << "Attribute [" << Attribute << "] already in use at " << sdpxml::FileReference(Document, *attribute) << std::endl;
			return;
		}

	// Record the fact that we're using it ...
	attribute->SetMeta("usedby", Element.Name());
}

GtkShadowType sdpGtkGetShadowType(sdpxml::Document& Document, sdpxml::Element& Element, const GtkShadowType Default)
{
	GtkShadowType result = Default;

	sdpxml::AttributePointer const shadowtype = sdpxml::FindAttribute(Element, sdpxml::SameName("shadowtype"));
	if(shadowtype)
		{
			const sdpString resulttext = shadowtype->Value();
			sdpGtkMarkAttribute(Document, Element, "shadowtype");

			if(resulttext == "none")
				result = GTK_SHADOW_NONE;
			else if(resulttext == "in")
				result = GTK_SHADOW_IN;
			else if(resulttext == "out")
				result = GTK_SHADOW_OUT;
			else if(resulttext == "etched-in")
				result = GTK_SHADOW_ETCHED_IN;
			else if(resulttext == "etched-out")
				result = GTK_SHADOW_ETCHED_OUT;
			else
				std::cout << "Attribute [shadowtype] contains unknown value [" << resulttext << "] at " << sdpxml::FileReference(Document, *shadowtype) << std::endl;
		}

	return result;
}

void sdpGtkHandlePendingEvents()
{
	while(gtk_events_pending())
		gtk_main_iteration();
}

static gint sdpGtkSleepCallback(gpointer Data)
{
	bool* const complete = reinterpret_cast<bool*>(Data);
	g_return_val_if_fail(complete, FALSE);

	*complete = true;

	return FALSE;
}

void sdpGtkSleep(const gulong Milliseconds)
{
	bool complete = false;

	gtk_timeout_add(Milliseconds, sdpGtkSleepCallback, &complete);

	while(!complete)
		sdpGtkHandlePendingEvents();
}

void sdpGtkWarpPointer(GdkWindow* const TargetWindow, const gint XOffset, const gint YOffset)
{
	// Sanity checks ...
	g_assert(TargetWindow);

#ifdef SDPWIN32

	// Convert window coordinates to screen coordinates ...
	HWND window = HWND(GDK_WINDOW_XWINDOW(TargetWindow));
	g_return_if_fail(window);

	RECT windowrect;
	::GetWindowRect(window, &windowrect);

	gint XCursorPos=XOffset + windowrect.left;
	gint YCursorPos=YOffset + windowrect.top;

	// Make that pointer jump!
	SetCursorPos(XCursorPos, YCursorPos);

#else // SDPWIN32

	// Get the X display ...
	Display* display = (Display*)GDK_DISPLAY();
	g_return_if_fail(display);

	// Get our X window ...
	Window xwindow = GDK_WINDOW_XWINDOW(TargetWindow);
	g_return_if_fail(xwindow);

	// Move that pointer!
	XWarpPointer(display, None, xwindow, 0, 0, 0, 0, XOffset, YOffset);
	XFlush(display);

#endif // !SDPWIN32
}

void sdpGtkWarpPointer(GtkWidget* const Widget, const gint XOffset, const gint YOffset)
{
	// Sanity checks ...
	g_assert(Widget);

	sdpGtkWarpPointer(Widget->window, XOffset, YOffset);
}

/// Computes N!
gdouble sdpFactorial(const gulong N)
{
	gulong result = 1;

	for(gulong i = 2; i <= N; ++i)
		result *= i;

	return gdouble(result);
}

/// Returns a Bezier / Bernstein basis for the given order, control point number, and parameter value
gdouble sdpBernsteinBasis(const gulong Order, const gulong ControlPoint, const gdouble Parameter)
{
	// Sanity checks ...
	g_assert(Order > 1);
	g_assert(ControlPoint <= Order);

	const gulong n = Order - 1;
	const gulong i = ControlPoint;
	const gdouble t = Parameter;

	const gdouble ni = sdpFactorial(n) / (sdpFactorial(i) * sdpFactorial(n - i));

	return ni * pow(t, i) * pow((1 - t), (n - i));
}

/// Computes a Bezier curve value with given order,  control points, and parameter value
template<class Type>
Type sdpBezier(const std::vector<Type>& ControlPoints, const gdouble Parameter)
{
	// Sanity checks ...
	g_assert(ControlPoints.size() > 1);

	Type result = 0.0;

	for(gulong i = 0; i < ControlPoints.size(); i++)
		result += sdpBernsteinBasis(ControlPoints.size(), i, Parameter) * ControlPoints[i];

	return result;
}

void sdpGtkInteractiveWarpPointer(GtkWidget* const Widget, const gint XOffset, const gint YOffset, sdpGtkInteractiveWarpPointerCallback& Callback, const gdouble Speed, const bool Pause, const bool ManhattanStyle)
{
	// Sanity checks ...
	g_assert(Widget);
	g_return_if_fail(Speed);

	// Get the current mouse pointer position, relative to our window ...
	gint pointerx = 0;
	gint pointery = 0;
	GdkModifierType modifiers;
	gdk_window_get_pointer(Widget->window, &pointerx, &pointery, &modifiers);

	// Make it our starting point ...
	sdpVector2 from = sdpVector2(gdouble(pointerx), gdouble(pointery));

	// Setup our end point ...
	sdpVector2 to = sdpVector2(gdouble(XOffset), gdouble(YOffset));

	// Calculate the number of steps, based on the distance to travel (then adjust, based on our speed) ...
	const gulong steps = static_cast<gulong>((((from-to).Length() / 20) + 30) / Speed);
	const gdouble delta = 1.0 / gdouble(steps);
	const gulong delay = static_cast<gulong>(10.0);

	// Setup some sloppiness ...
	const gdouble sloppiness = 75;
	const gdouble randomscale = RAND_MAX * 0.5;
	sdpVector2 slop = sdpVector2((rand()-randomscale) / randomscale, (rand()-randomscale) / randomscale) * sloppiness;

	// Setup a Bezier curve for our path ...
	std::vector<sdpVector2> pathpoints;
	pathpoints.push_back(from);
	if(ManhattanStyle)
		{
			pathpoints.push_back(sdpVector2(to[0], from[1]));
			pathpoints.push_back(sdpVector2(to[0], from[1]));
		}
	pathpoints.push_back(to);

	// Setup a Bezier curve for some nice non-linear motion ...
	std::vector<gdouble> ratepoints;
	ratepoints.push_back(0);
	ratepoints.push_back(0.1);
	ratepoints.push_back(0.9);
	ratepoints.push_back(1);

	for(gulong i = 1; i <= steps; i++)
		{
			const gdouble percent = sdpBezier(ratepoints, delta * i);
			sdpVector2 actualposition;

			if(ManhattanStyle)
				{
					actualposition = sdpBezier(pathpoints, percent);
				}
			else
				{
					const sdpVector2 sloppyto = sdpLerp(to+slop, to, percent);
					actualposition = sdpLerp(from, sloppyto, percent);
				}

			// Call the callback, giving it a chance to cancel further execution ...
			if(!Callback.HandleInteractivePointerWarp(Widget, gint(actualposition[0]), gint(actualposition[1])))
				return;

			sdpGtkSleep(delay);
//			sdpGtkHandlePendingEvents();
		}

	if(Pause)
		{
			sdpGtkSleep(static_cast<gulong>(500.0 / Speed));
//			sdpGtkHandlePendingEvents();
		}
}

class WarpPointer : public sdpGtkInteractiveWarpPointerCallback
{
public:
	bool HandleInteractivePointerWarp(GtkWidget* const Widget, const gint XOffset, const gint YOffset)
	{
		sdpGtkWarpPointer(Widget, XOffset, YOffset);
		return true;
	}
};

void sdpGtkInteractiveWarpPointer(GtkWidget* const Widget, const gint XOffset, const gint YOffset, const gdouble Speed, const bool Pause, const bool ManhattanStyle)
{
	WarpPointer callback;
	sdpGtkInteractiveWarpPointer(Widget, XOffset, YOffset, callback, Speed, Pause, ManhattanStyle);
}


