#ifndef SDPGTKSCREENOVERLAY_H
#define SDPGTKSCREENOVERLAY_H

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
		\brief Declares the sdpGtkScreenOverlay class, which provides an interface for drawing transparent displays over the top of the user's screen
		\author Tim Shead (tshead@k-3d.com)
*/

#include "sdpgtkobjectcontainer.h"
#include <memory>

//////////////////////////////////////////////////////////////////////////
// sdpGtkScreenOverlay

/// Provides an interface for drawing transparent displays over the top of the user's screen
class sdpGtkScreenOverlay : public sdpGtkObjectContainer
{
public:
	sdpGtkScreenOverlay();
	sdpGtkScreenOverlay(const sdpVector3 OverlayColor);
	sdpGtkScreenOverlay(const gulong X, const gulong Y, const gulong Width, const gulong Height, const sdpVector3 OverlayColor);
	
	~sdpGtkScreenOverlay();

	/// Creates the display
	bool Create();

	// Data access
	GdkDrawable* Mask() { return m_Mask; }
	GdkGC* MaskGC() { return m_MaskGC; }

	/// Changes the display color
	void SetColor(const sdpVector3 OverlayColor);

	/// Called to refresh the overlay after changes have been made
	void Update();

	// Predefined colors for convenience
	static const GdkColor White;
	static const GdkColor Black;

protected:
	void OnEvent(sdpGtkEvent* Event);
	void OnExpose();
	
private:
	gulong m_X;
	gulong m_Y;
	gulong m_Width;
	gulong m_Height;
	gulong m_ScreenWidth;
	gulong m_ScreenHeight;

	sdpVector3 m_OverlayColor;
	std::auto_ptr<GdkColor> m_AllocatedColor;
	GdkGC* m_OverlayGC;

	GdkBitmap* m_Mask;
	GdkGC* m_MaskGC;
};

#endif // !SDPGTKSCREENOVERLAY_H


