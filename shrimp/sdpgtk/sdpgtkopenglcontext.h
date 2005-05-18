#ifndef SDPGTKOPENGLCONTEXT_H
#define SDPGTKOPENGLCONTEXT_H

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
		\brief Declares the sdpGtkOpenGLContext class, which an OpenGL render context in a cross-platform way
		\author Tim Shead (tshead@k-3d.com)
*/

#ifdef SDPWIN32
#include <gdk/gdkwin32.h>
#else // SDPWIN32
#include <gdk/gdkx.h>
#include <X11/X.h>
#endif // !SDPWIN32

#include <GL/gl.h>
#include <GL/glu.h>

#if defined SDPUNIX
#include <GL/glx.h>
#endif // SDPUNIX

#include <vector>
#include <algorithm>

// Generic NULL ressource
#ifndef None
#define None 0
#endif

// Provide GLX_ constants for a consistent interface under Win32 ...
#ifdef SDPWIN32

enum
{
	GLX_USE_GL = 1,
	GLX_BUFFER_SIZE = 2,
	GLX_LEVEL = 3,
	GLX_RGBA = 4,
	GLX_DOUBLEBUFFER = 5,
	GLX_STEREO = 6,
	GLX_AUX_BUFFERS = 7,
	GLX_RED_SIZE = 8,
	GLX_GREEN_SIZE = 9,
	GLX_BLUE_SIZE = 10,
	GLX_ALPHA_SIZE = 11,
	GLX_DEPTH_SIZE = 12,
	GLX_STENCIL_SIZE = 13,
	GLX_ACCUM_RED_SIZE = 14,
	GLX_ACCUM_GREEN_SIZE = 15,
	GLX_ACCUM_BLUE_SIZE = 16,
	GLX_ACCUM_ALPHA_SIZE = 17,
};

#endif // SDPWIN32


/// An OpenGL attribute list
typedef std::vector<int> sdpGtkOpenGLAttributeList;

///////////////////////////////////////////////////////////////////////////
// sdpGtkOpenGLContext

/// Encapsulates an OpenGL context in a cross-platform manner
class sdpGtkOpenGLContext
{
friend class sdpGtkOpenGLWidget;
public:
	inline sdpGtkOpenGLContext();
	inline ~sdpGtkOpenGLContext();

	/// Creates the OpenGL context
	inline bool Create(const bool DirectRender, const bool DoubleBuffer, const gulong Red, const gulong Green, const gulong Blue, const gulong Depth);
	/// Creates the OpenGL context from an array of GLX_ constants
	inline bool Create(const bool DirectRender, const sdpGtkOpenGLAttributeList& AttributeList);

	// Since Win32 requires a device context to create an OpenGL context, creation becomes a two-step process ...
	inline bool PostCreate(GtkWidget* Widget);

	/// Returns "true" if the context is initialized and ready for use
	inline bool Initialized() const;
	/// Destroys the OpenGL context (the C++ object can be re-used)
	inline void Destroy();

	/// Called to make the OpenGL context active, prior to making OpenGL calls
	inline bool Begin();
	/// Called to swap the OpenGL context buffers, if double-buffering is being used
	inline bool SwapBuffers();
	/// Called to deactive the OpenGL context, once OpenGL drawing has ended
	inline bool End();

	/// Returns whether direct rendering was requested
	inline bool DirectRender() const { return m_DirectRender; }
	/// Returns the requested attributes for this context
	inline const sdpGtkOpenGLAttributeList& AttributeList() const { return m_AttributeList; }

	/// Returns the OpenGL context
#ifdef SDPWIN32
	inline HGLRC& Context() { return m_Context; }
#else // SDPWIN32
	inline GLXContext& Context() { return m_Context; }
#endif // !SDPWIN32


	/// Returns the visual associated with this context
	inline GdkVisual* Visual() const { return m_Visual; }
	/// Returns the colormap associated with this context
	inline GdkColormap* Colormap() const { return m_Colormap; }
	/// Returns the widget associated with this context
	inline GtkWidget* Widget() const { return m_Widget; }

protected:
	// Stores whether direct rendering was requested
	bool m_DirectRender;
	// Stores the requested OpenGL attributes
	sdpGtkOpenGLAttributeList m_AttributeList;

#ifdef SDPWIN32
	HWND m_Window;
	HGLRC m_Context;
	HDC m_DeviceContext;
#else // SDPWIN32
	GLXContext m_Context;
#endif // !SDPWIN32

	/// Stores the OpenGL / GDK visual
	GdkVisual* m_Visual;
	/// Stores the OpenGL / GDK colormap
	GdkColormap* m_Colormap;
	/// Stores the GTK+ widget
	GtkWidget* m_Widget;
};

///////////////////////////////////////////////////////////////////////////
// sdpGtkOpenGLContext

sdpGtkOpenGLContext::sdpGtkOpenGLContext()
{
#ifdef SDPWIN32
	m_Window = 0;
	m_DeviceContext = 0;
#endif

	m_Context = 0;
	m_Visual = 0;
	m_Colormap = 0;
	m_Widget = 0;
}

sdpGtkOpenGLContext::~sdpGtkOpenGLContext()
{
	Destroy();
}

bool sdpGtkOpenGLContext::Create(const bool DirectRender, const bool DoubleBuffer, const gulong Red, const gulong Green, const gulong Blue, const gulong Depth)
{
	// Setup our desired visual attributes ...
	sdpGtkOpenGLAttributeList attributes;
	attributes.push_back(GLX_USE_GL);
	attributes.push_back(GLX_RGBA);

	if(DoubleBuffer)
		attributes.push_back(GLX_DOUBLEBUFFER);

	attributes.push_back(GLX_RED_SIZE); attributes.push_back(Red);
	attributes.push_back(GLX_GREEN_SIZE); attributes.push_back(Green);
	attributes.push_back(GLX_BLUE_SIZE); attributes.push_back(Blue);
	attributes.push_back(GLX_DEPTH_SIZE); attributes.push_back(Depth);
	attributes.push_back(None);

	return Create(DirectRender, attributes);
}

bool sdpGtkOpenGLContext::Create(const bool DirectRender, const sdpGtkOpenGLAttributeList& AttributeList)
{
	// Sanity checks ...
	g_return_val_if_fail(AttributeList.size(), false);

	// If this fails, the attribute list doesn't contain a request for OpenGL!
	g_return_val_if_fail(std::find(AttributeList.begin(), AttributeList.end(), GLX_USE_GL) != AttributeList.end(), false);

	// If this fails, the attribute list wasn't properly terminated ...
	g_return_val_if_fail(AttributeList.back() == None, false);

	// Make sure we aren't initialized twice in a row ...
	g_return_val_if_fail(!Initialized(), false);

	// Store requested configuration ...
	m_DirectRender = DirectRender;
	m_AttributeList = AttributeList;

#ifdef SDPWIN32

	// Because Win32 requires a device context (and thus a widget) in order to create
	// the GDI OpenGL context, we have to defer until PostCreate(), below

#else // SDPWIN32

	// Get the X display ...
	Display* display = GDK_DISPLAY();
	g_return_val_if_fail(display, false);

	int screen = DefaultScreen(display);

	// Make sure the X server supports GLX ...
	if(!glXQueryExtension(display, NULL, NULL))
		{
			std::cerr << "sdpGtkOpenGLContext::Create() - GLX extensions not supported by X server" << std::endl;
			return false;
		}

	// Find a matching OpenGL (we fail quietly if we can't, since client code may want to try again with lower requirements) ...
	XVisualInfo* visualinfo = glXChooseVisual(display, screen, const_cast<int*>(&AttributeList[0]));
	if(0 == visualinfo)
		return false;

	// Get the GDK visual ...
	m_Visual = gdkx_visual_get(visualinfo->visualid);
	g_return_val_if_fail(m_Visual, false);

	// Create the GDK colormap ...
	m_Colormap = gdk_colormap_new(m_Visual, true);
	g_return_val_if_fail(m_Colormap, false);

	// Create the OpenGL context ...
	m_Context = glXCreateContext(display, visualinfo, None, DirectRender ? True : False);
	g_return_val_if_fail(m_Context, false);

	XFree(visualinfo);

#endif // !SDPWIN32

	return true;
}

bool sdpGtkOpenGLContext::PostCreate(GtkWidget* Widget)
{
	// Sanity checks ...
	g_return_val_if_fail(Widget, false);

#ifdef SDPWIN32
	// For Win32, the widget must be realized first ...
	g_return_val_if_fail(GTK_WIDGET_REALIZED(Widget), false);

	// Get the widget's underlying HWND ...
	HWND window = HWND(GDK_WINDOW_XWINDOW(Widget->window));
	g_return_val_if_fail(window, false);

	// Get the HWND's GDI device context ...
	HDC devicecontext = GetDC(window);
	g_return_val_if_fail(devicecontext, false);

	// Create a pixel format descriptor with the desired attributes ...
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	pfd.iPixelType = PFD_TYPE_COLORINDEX;
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;

	for(gulong i = 0; i < m_AttributeList.size(); )
		{
			switch(m_AttributeList[i])
				{
					case GLX_RGBA:
						pfd.iPixelType = PFD_TYPE_RGBA;
						i += 1;
						break;
					case GLX_DOUBLEBUFFER:
						pfd.dwFlags |= PFD_DOUBLEBUFFER;
						i += 1;
						break;
					case GLX_AUX_BUFFERS:
						pfd.cAuxBuffers = m_AttributeList[i+1];
						i += 2;
						break;
					case GLX_RED_SIZE:
						pfd.cRedBits = m_AttributeList[i+1];
						i += 2;
						break;
					case GLX_GREEN_SIZE:
						pfd.cGreenBits = m_AttributeList[i+1];
						i += 2;
						break;
					case GLX_BLUE_SIZE:
						pfd.cBlueBits = m_AttributeList[i+1];
						i += 2;
						break;
					case GLX_ALPHA_SIZE:
						pfd.cAlphaBits = m_AttributeList[i+1];
						i += 2;
						break;
					case GLX_DEPTH_SIZE:
						pfd.cDepthBits = m_AttributeList[i+1];
						i += 2;
						break;
					case GLX_STENCIL_SIZE:
						pfd.cStencilBits = m_AttributeList[i+1];
						i += 2;
						break;
					case GLX_ACCUM_RED_SIZE:
						pfd.cAccumRedBits = m_AttributeList[i+1];
						i += 2;
						break;
					case GLX_ACCUM_GREEN_SIZE:
						pfd.cAccumGreenBits = m_AttributeList[i+1];
						i += 2;
						break;
					case GLX_ACCUM_BLUE_SIZE:
						pfd.cAccumBlueBits = m_AttributeList[i+1];
						i += 2;
						break;
					case GLX_ACCUM_ALPHA_SIZE:
						pfd.cAccumAlphaBits = m_AttributeList[i+1];
						i += 2;
						break;
					default:
						i += 1;
						break;
				}
		}

	pfd.cColorBits = pfd.cRedBits + pfd.cGreenBits + pfd.cBlueBits;
	pfd.cAccumBits = pfd.cAccumRedBits + pfd.cAccumGreenBits + pfd.cAccumBlueBits;

	int pixelformat = ChoosePixelFormat(devicecontext, &pfd);
	SetPixelFormat(devicecontext, pixelformat, &pfd);
	DescribePixelFormat(devicecontext, pixelformat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	// Create the OpenGL context ...
	m_Context = wglCreateContext(devicecontext);

	// Release the GDI device context ...
	ReleaseDC(window, devicecontext);

	g_return_val_if_fail(m_Context, false);

#else // SDPWIN32

	// Nothing to do here, because in X the visual has already been created

#endif // !SDPWIN32

	m_Widget = Widget;

	return true;
}

bool sdpGtkOpenGLContext::Initialized() const
{
#ifdef SDPWIN32
	return m_Context && m_Widget ? true : false;
#else // SDPWIN32
	return m_Visual && m_Colormap && m_Context && m_Widget ? true : false;
#endif // !SDPWIN32

}

void sdpGtkOpenGLContext::Destroy()
{
	// Destroy the OpenGL context ...
#ifdef SDPWIN32

	wglMakeCurrent(0, 0);
	if(m_Context)
		wglDeleteContext(m_Context);

	if(m_DeviceContext)
		ReleaseDC(m_Window, m_DeviceContext);

	m_Window = 0;
	m_DeviceContext = 0;

#else // SDPWIN32

	// Get the X display ...
	Display* display = GDK_DISPLAY();
	g_return_if_fail(display);

	// Select out our context ...
	glXMakeCurrent(display, None, NULL);

	// Zap it ...
	if(m_Context)
		glXDestroyContext(display, m_Context);

#endif // !SDPWIN32


	// General clean-up ...
	if(m_Visual)
		gdk_visual_unref(m_Visual);

	if(m_Colormap)
		gdk_colormap_unref(m_Colormap);

	// Zero out our state ...
	m_Visual = 0;
	m_Colormap = 0;
	m_Context = 0;
	m_Widget = 0;
}

bool sdpGtkOpenGLContext::Begin()
{
	// Sanity checks ...
	g_return_val_if_fail(Initialized(), false);

#ifdef SDPWIN32

	if(!m_DeviceContext)
		{
			// Get the widget's underlying HWND ...
			m_Window = HWND(GDK_WINDOW_XWINDOW(m_Widget->window));
			g_return_val_if_fail(m_Window, false);

			// Get the HWND's GDI device context ...
			m_DeviceContext = GetDC(m_Window);
			g_return_val_if_fail(m_DeviceContext, false);
		}

	// Make the OpenGL context current ...
	wglMakeCurrent(m_DeviceContext, m_Context);

#else // SDPWIN32

	// Get the X window ...
	Window window = GDK_WINDOW_XWINDOW(m_Widget->window);
	g_return_val_if_fail(window, false);

	// Get the X display ...
	Display* display = GDK_DISPLAY();
	g_return_val_if_fail(display, false);

	// Make the OpenGL context current ...
	glXMakeCurrent(display, window, m_Context);

#endif // !SDPWIN32

	return true;
}

bool sdpGtkOpenGLContext::SwapBuffers()
{
	// Sanity checks ...
	g_return_val_if_fail(Initialized(), false);

#ifdef SDPWIN32

	if(!m_DeviceContext)
		{
			// Get the widget's underlying HWND ...
			HWND window = HWND(GDK_WINDOW_XWINDOW(m_Widget->window));
			g_return_val_if_fail(window, false);

			// Get the HWND's GDI device context ...
			HDC devicecontext = GetDC(window);
			g_return_val_if_fail(devicecontext, false);

			// Swap the context buffer to the display ...
			::SwapBuffers(devicecontext);

			// Release the GDI device context ...
			ReleaseDC(window, devicecontext);
		}
	else
		{
			// Swap the context buffer to the display using current DC...
			::SwapBuffers(m_DeviceContext);
		}

#else // SDPWIN32

	// Get the X window ...
	Window window = GDK_WINDOW_XWINDOW(m_Widget->window);
	g_return_val_if_fail(window, false);

	// Get the X display ...
	Display* display = GDK_DISPLAY();
	g_return_val_if_fail(display, false);

	// Swap display buffers
	glXSwapBuffers(display, window);

#endif // !SDPWIN32

	return true;
}

bool sdpGtkOpenGLContext::End()
{
	// Sanity checks ...
	g_return_val_if_fail(Initialized(), false);

#ifdef SDPWIN32

	// Select out our context ...
	wglMakeCurrent(0, 0);

	// Release our GDI DC context ...
	if(m_DeviceContext)
	{
		ReleaseDC(m_Window, m_DeviceContext);
		m_DeviceContext = 0;
	}

#else // SDPWIN32

	// Get the X display ...
	Display* display = GDK_DISPLAY();
	g_return_val_if_fail(display, false);

	// Select out our context ...
	glXMakeCurrent(display, None, NULL);

#endif // !SDPWIN32

	return true;
}

#endif // SDPGTKOPENGLCONTEXT_H
