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

#ifndef IOPROPERTIES_H
#define IOPROPERTIES_H

#include "iopad.h"
#include "modaldialog.h"

class IOProperties :
	public ModalDialog
{
public:
	IOProperties(IOPad* p);

private:
	bool Load();
	void OnEvent(sdpGtkEvent* event);
	void OnOK();
	void OnTypeChange(std::string name);
	void OnUseStringToggle();
	void OnColourPressEvent();
	void OnColourConfigureEvent();
	void OnColourExposeEvent(sdpGtkEvent* e);

	void drawColour();
	void updateColour();
	void setSensitivity(std::string type);
	void setVectorValue(sdpVector3 v);
	void getVectorValue(sdpVector3& v);

	IOPad* pad;
	std::string new_type;
	sdpVector3 decoded_val;

	GdkGC* gc;
	GdkPixmap* pixmap;
};

#endif // IOPROPERTIES_H

