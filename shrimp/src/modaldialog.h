//============================================================================
//
// Shrimp Shader Generator
// Copyright (C) 2000-2004 Andy Gill
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
//============================================================================

#ifndef MODALDIALOG_H
#define MODALDIALOG_H

#include <sdpgtk/sdpgtkevent.h>
#include <sdpgtk/sdpgtkobjectcontainer.h>

class ModalDialog : public sdpGtkObjectContainer
{
public:
	ModalDialog() :
		sdpGtkObjectContainer()
	{
		m_Result = false;
	}

	void setGuiFile(const std::string& filename)
	{
		guifile = filename;
	}

	void DoModal(GtkWindow* window = 0);

	bool OK() { return m_Result; }
	bool Cancelled() { return !m_Result; }

protected:
	virtual bool Load();

	void OnEvent(sdpGtkEvent* event);

	virtual void OnDestroy();
	virtual void OnOK();
	virtual void OnCancel();

	std::string guifile;

	bool m_Result;
};

#endif // MODALDIALOG_H

