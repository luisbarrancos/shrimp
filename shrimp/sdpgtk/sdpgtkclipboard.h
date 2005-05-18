#ifndef SDPGTKCLIPBOARD_H
#define SDPGTKCLIPBOARD_H

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
		\brief Declares the sdpGtkClipboard family of classes, which make it easy to synchronously retrieve data from the clipboard (primary X selection)
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkobjectcontainer.h"


/////////////////////////////////////////////////////////////////////
// sdpGtkClipboard

typedef sdpGtkObjectContainer sdpGtkClipboardBase;

/// Provides an abstract base class for retrieving data from the clipboard (primary X selection)
class sdpGtkClipboard : public sdpGtkClipboardBase
{
public:
	sdpGtkClipboard();
	virtual ~sdpGtkClipboard();

protected:
	/// Call this from derived classes to start the retrieval process
	bool StartSelection();
	/// Override this to request the desired data type
	virtual bool RequestSelection() = 0;
	/// Override this to extract the desired data type
	virtual bool ReceiveSelection(sdpGtkEvent* Event) = 0;
	/// Set to "true" while waiting for data to be retrieved
	bool m_Waiting;
	/// Set to "true" iff data was successfully retrieved
	bool m_ContainsData;

private:	
	void OnEvent(sdpGtkEvent* Event);
};

///////////////////////////////////////////////////////////////////////
// sdpGtkClipboardText

typedef sdpGtkClipboard sdpGtkClipboardTextBase;

/// Extracts text data from the clipboard (primary X selection)
class sdpGtkClipboardText : public sdpGtkClipboardTextBase
{
public:
	/// Returns current clipboard data as text
	const sdpString& GetText();

private:
	// Implements required sdpGtkClipboard functionality
	bool RequestSelection();
	bool ReceiveSelection(sdpGtkEvent* Event);
			
	/// Caches clipboard data as text for retrieval
	sdpString m_Text;
};

#endif // SDPGTKCLIPBOARD_H

