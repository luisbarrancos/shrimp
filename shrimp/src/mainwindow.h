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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "circuit.h"
#include "renderoptions.h"

#include <sdpgtk/sdpgtkobjectcontainer.h>
#include <sdpgtk/sdpgtkevent.h>
#include <sdpgtk/sdpgtkevents.h>
#include <sdpgtk/sdpgtkfileselector.h>

class MainWindow :
	public sdpGtkObjectContainer
{
public:
	MainWindow();
	~MainWindow();

	// Loads the GTKML template
	void Load();

private:
	void OnEvent(sdpGtkEvent* event);

	void Exit();
	void OnCanvasConfigureEvent();
	void OnCanvasExposeEvent(sdpGtkEvent* event);
	void OnAbout();
	void OnButtonPressEvent(sdpGtkEvent* event);
	void OnMouseMoveEvent(sdpGtkEvent* event);
	void OnZoom(sdpGtkEvent* event);
	void OnBlockMove();
	void OnBlockAdd(std::string name);
	void OnBlockDelete();
	void OnBlockCopy();
	void OnBlockHelp();
	void OpenMenu(sdpGtkEvent* event);
	void OnPadDisconnect();
	void OnPadProperties();
	void OnCircuitOpen();
	void OnCircuitSave();
	void OnCircuitSaveAs();
	void OnCircuitClose();
	void OnCircuitResize();
	void OnPreview();
	void OnSaveCode();
	void OnShaderProperties();
	void OnRenderOptions();
	void OnCodePreview();

	void forceRedraw();
	void drawCurrentElement(int x, int y);
	void cancelAction();
	void connectPads(IOPad* aPad, IOPad* bPad);
	InputPad* addMultiPad(InputPad* inPad);
	void removeMultiPad(InputPad* inPad);
	void setBasePath();
	bool loadPrefs(std::string filename);
	void savePrefs(std::string filename);

	void OnNewCircuit(std::string eventName);
	Circuit* loadCircuit(std::string filename);
	void saveCircuit(const std::string& filename);

	enum { Ready, Moving, Connecting, Adding } state;

	GtkWidget* canvas;
	GdkGC* gc;
	GdkPixmap* pixmap;

	Circuit* circuitBoard;
	GridEntity* currentElement;

	int old_x, old_y;

	std::string basePath;
	std::string gtkmlPath;

	RenderOptions renderOptions;
};

#endif // MAINWINDOW_H

