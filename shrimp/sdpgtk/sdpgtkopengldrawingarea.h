#ifndef SDPGTKOPENGLDRAWINGAREA_H
#define SDPGTKOPENGLDRAWINGAREA_H

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
		\brief Declares the sdpGtkOpenGLDrawingArea class, a specialization of sdpGtkDrawingArea for displaying OpenGL graphics
		\author Tim Shead (tshead@k-3d.com)
*/

#include "sdpgtkdrawingarea.h"
#include "sdpgtkopenglcontext.h"

///////////////////////////////////////////////////////////////////////////
// sdpGtkOpenGLDrawingArea

/// A specialization of sdpGtkDrawingArea for displaying OpenGL graphics
class sdpGtkOpenGLDrawingArea : public sdpGtkDrawingArea
{
public:
	inline sdpGtkOpenGLDrawingArea();

	/// Creates the drawing area with given attributes and attaches it to a parent
	inline bool Create(sdpGtkContainer& Parent, const bool DirectRender, const bool DoubleBuffer, const gulong Red, const gulong Green, const gulong Blue, const gulong Depth);
	/// Creates the drawing area from an array of GLX_ constants and attaches it to a parent
	inline bool Create(sdpGtkContainer& Parent, const bool DirectRender, const sdpGtkOpenGLAttributeList& AttributeList);

	/// Optional initialization if you intend to draw text using X fonts
	inline bool InitializeFont();
	/// Returns the drawing list for the first character of the current X font
	inline gulong FontBase() const;
	/// Returns the height of the current font above its baseline
	inline gint FontAscent() const;
	/// Returns the depth of the current font below its baseline
	inline gint FontDescent() const;

	/// Returns "true" if the widget is initialized and ready for use
	inline bool Initialized() const;
	/// Called to make the OpenGL context active, prior to making OpenGL calls
	inline bool Begin();
	/// Called to swap the OpenGL context buffers, if double-buffering is being used
	inline bool SwapBuffers();
	/// Called to deactivate the OpenGL context, once OpenGL drawing has ended
	inline bool End();

protected:
	/// Private creation to handle differences between X and Win32
	inline bool Create(sdpGtkContainer& Parent);

	/// Stores the OpenGL context for this widget
	sdpGtkOpenGLContext m_Context;

	/// Stores the beginning of a set of drawing lists for drawing characters
	gulong m_FontBase;
	/// Stores the height of the current font above its baseline
	gint m_FontAscent;
	/// Stores the depth of the current font below its baseline
	gint m_FontDescent;
};

///////////////////////////////////////////////////////////////////////////
// sdpGtkOpenGLDrawingArea

sdpGtkOpenGLDrawingArea::sdpGtkOpenGLDrawingArea() :
	m_FontBase(0),
	m_FontAscent(0),
	m_FontDescent(0)
{
}

bool sdpGtkOpenGLDrawingArea::Create(sdpGtkContainer& Parent, const bool DirectRender, const bool DoubleBuffer, const gulong Red, const gulong Green, const gulong Blue, const gulong Depth)
{
	// Sanity checks ...
	g_assert(Parent.Attached());

	// OpenGL context creation - first step (we fail quietly here because the client may wish to try again with looser requirements) ...
	if(!m_Context.Create(DirectRender, DoubleBuffer, Red, Green, Blue, Depth))
		return false;

	// Create ourselves ...
	g_return_val_if_fail(Create(Parent), false);

	// OpenGL context creation - second step ...
	g_return_val_if_fail(m_Context.PostCreate(GTK_WIDGET(Object())), false);

	return true;
}

bool sdpGtkOpenGLDrawingArea::Create(sdpGtkContainer& Parent, const bool DirectRender, const sdpGtkOpenGLAttributeList& AttributeList)
{
	// Sanity checks ...
	g_assert(Parent.Attached());

	// OpenGL context creation - first step (we fail quietly here because the client may wish to try again with looser requirements) ...
	if(!m_Context.Create(DirectRender, AttributeList))
		return false;

	// Create ourselves ...
	g_return_val_if_fail(Create(Parent), false);

	// OpenGL context creation - second step ...
	g_return_val_if_fail(m_Context.PostCreate(GTK_WIDGET(Object())), false);

	return true;
}

bool sdpGtkOpenGLDrawingArea::Create(sdpGtkContainer& Parent)
{
	// Sanity checks ...
	g_assert(Parent.Attached());

#ifdef SDPWIN32

	// Create our own widget ...
	sdpGtkDrawingArea::Create();
	g_return_val_if_fail(Attached(), false);

#else // SDPWIN32

	// Create our own widget, using the context' colormap and visual ...
	gtk_widget_push_colormap(m_Context.Colormap());
	gtk_widget_push_visual(m_Context.Visual());

	sdpGtkDrawingArea::Create();

	gtk_widget_pop_visual();
	gtk_widget_pop_colormap();

	g_return_val_if_fail(Attached(), false);

#endif // !SDPWIN32


	// Setup the events we want to receive (must happen before we're realized) ...
	gtk_widget_set_events(GTK_WIDGET(Object()),
				GDK_POINTER_MOTION_MASK |
				GDK_POINTER_MOTION_HINT_MASK |
				GDK_BUTTON_MOTION_MASK |
				GDK_BUTTON_PRESS_MASK |
				GDK_BUTTON_RELEASE_MASK |
				GDK_KEY_PRESS_MASK |
				GDK_KEY_RELEASE_MASK |
				GDK_EXPOSURE_MASK);

	// Attach ourselves to our parent (this MUST happen before we're realized) ...
	Parent.Attach(*this);

	// We MUST be realized in order to create the Win32 opengl context ...
	Realize();

	// Make ourselves visible by default ...
	Show();

	return true;
}

bool sdpGtkOpenGLDrawingArea::InitializeFont()
{
	g_return_val_if_fail(Begin(), false);

	m_FontBase = glGenLists(256);

	GtkWidget* const widget = GTK_WIDGET(m_Object);
	g_return_val_if_fail(widget, false);

#ifdef SDPWIN32

	HWND window = HWND(GDK_WINDOW_XWINDOW(widget->window));
	g_return_val_if_fail(window, false);

	HDC devicecontext = GetDC(window);
	g_return_val_if_fail(devicecontext, false);

	wglUseFontBitmaps(devicecontext, 0, 256, m_FontBase);

	// Release the GDI device context ...
	ReleaseDC(window, devicecontext);

#else // SDPWIN32

	g_return_val_if_fail(widget->style, false);
	g_return_val_if_fail(widget->style->font, false);

	const gint fontid = gdk_font_id(widget->style->font);
	g_return_val_if_fail(fontid, false);

	glXUseXFont(fontid, 0, 256, m_FontBase);

#endif // !SDPWIN32

	// Get some font metrics ...
	sdpString metrictext("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_^");
	gdk_string_extents(widget->style->font, metrictext, 0, 0, 0, &m_FontAscent, &m_FontDescent);

	return End();
}

gulong sdpGtkOpenGLDrawingArea::FontBase() const
{
	return m_FontBase;
}

gint sdpGtkOpenGLDrawingArea::FontAscent() const
{
	return m_FontAscent;
}

gint sdpGtkOpenGLDrawingArea::FontDescent() const
{
	return m_FontDescent;
}

bool sdpGtkOpenGLDrawingArea::Initialized() const
{
	return Attached() && m_Context.Initialized() ? true : false;
}

bool sdpGtkOpenGLDrawingArea::Begin()
{
	return m_Context.Begin();
}

bool sdpGtkOpenGLDrawingArea::SwapBuffers()
{
	return m_Context.SwapBuffers();
}

bool sdpGtkOpenGLDrawingArea::End()
{
	return m_Context.End();
}

#endif // SDPGTKOPENGLDRAWINGAREA_H
