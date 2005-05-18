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

#include "mainwindow.h"
#include "modaldialog.h"

#include <sdpxml/sdpxml.h>

#include <fstream>

MainWindow::MainWindow()
{
	gc = 0;
	pixmap = 0;

	state = Ready;
	currentElement = 0;
	circuitBoard = 0;
	setBasePath();

	std::string shaderPath = sdpAppendPath(basePath.c_str(), "shaders");
	renderOptions.setShaderPath(shaderPath);

	std::string prefsdir = sdpAppendPath(sdpGetHomeDirectory(), ".shrimp");
	std::string prefsfile = sdpAppendPath(prefsdir.c_str(), "prefs");

	if(!sdpFileExists(prefsfile.c_str()) ||
			!loadPrefs(prefsfile))
	{
		std::string mkDir = "mkdir -p " + prefsdir;
		system(mkDir.c_str());
	}
}

MainWindow::~MainWindow()
{
	std::string prefsdir = sdpAppendPath(sdpGetHomeDirectory(), ".shrimp");
	std::string prefsfile = sdpAppendPath(prefsdir.c_str(), "prefs");

	savePrefs(prefsfile);

	delete circuitBoard;
}

void MainWindow::Load()
{
	// Load the GTKML document ...
	gtkmlPath = sdpAppendPath(basePath.c_str(), "dialogtemplates");

	std::string mainwin = sdpAppendPath(gtkmlPath.c_str(), "mainwindow.gtkml");
	sdpGtkObjectContainer::Load(mainwin);

	canvas = (GtkWidget*)Widget("canvas");
	circuitBoard = new Circuit(canvas);
	circuitBoard->setZoom(Adjustment("zoom").Value());

	gtk_widget_set_events (canvas, GDK_EXPOSURE_MASK
			| GDK_LEAVE_NOTIFY_MASK
			| GDK_BUTTON_PRESS_MASK
			| GDK_POINTER_MOTION_MASK
			| GDK_POINTER_MOTION_HINT_MASK
			);

	// Make everything visible ...
	RootWidget().Show();

	//add default blocks.
	OnNewCircuit("onnewsurface");
}

void MainWindow::OnEvent(sdpGtkEvent* event)
{
	// Handle events ...
	if(event->Name() == "ondestroy")
		Exit();
	else if(event->Name() == "onexit")
		Exit();
	else if(event->Name() == "onabout")
		OnAbout();
	else if(event->Name() == "ontestconfigureevent")
		OnCanvasConfigureEvent();
	else if(event->Name() == "ontestexposeevent")
		OnCanvasExposeEvent(event);
	else if(event->Name() == "onbuttonpressevent")
		OnButtonPressEvent(event);
	else if(event->Name() == "onmousemoveevent")
		OnMouseMoveEvent(event);
	else if(event->Name() == "onzoom")
		OnZoom(event);
	else if(event->Name() == "onblockmove")
		OnBlockMove();
	else if(event->Name() == "onblockdelete")
		OnBlockDelete();
	else if(event->Name() == "onblockcopy")
		OnBlockCopy();
	else if(event->Name() == "onblockhelp")
		OnBlockHelp();
	else if(event->Name() == "onpaddisconnect")
		OnPadDisconnect();
	else if(event->Name() == "onpadproperties")
		OnPadProperties();
	else if(event->Name() == "onpadnewmulti")
	{
		addMultiPad((InputPad*)currentElement);
		forceRedraw();
	}
	else if(event->Name() == "onpadremovemulti")
	{
		removeMultiPad((InputPad*)currentElement);
		forceRedraw();
	}
	else if(event->Name() == "onnewsurface"
			|| event->Name() == "onnewdisplacement"
			|| event->Name() == "onnewlight"
			|| event->Name() == "onnewvolume")
		OnNewCircuit(event->Name());
	else if(event->Name() == "oncircuitopen")
		OnCircuitOpen();
	else if(event->Name() == "oncircuitsave")
		OnCircuitSave();
	else if(event->Name() == "oncircuitsaveas")
		OnCircuitSaveAs();
	else if(event->Name() == "oncircuitclose")
		OnCircuitClose();
	else if(event->Name() == "oncircuitresize")
		OnCircuitResize();
	else if(event->Name() == "onpreview")
		OnPreview();
	else if(event->Name() == "onsavecode")
		OnSaveCode();
	else if(event->Name() == "onshaderproperties")
		OnShaderProperties();
	else if(event->Name() == "onrenderoptions")
		OnRenderOptions();
	else if(event->Name() == "oncodepreview")
		OnCodePreview();
	else if(event->Name().left(8) == "openmenu")
		OpenMenu(event);
	else if(event->Name().left(10) == "onblockadd")
		OnBlockAdd(event->Name());
	else
		sdpGtkObjectContainer::OnEvent(event);
}

void MainWindow::Exit()
{
	DisconnectAllEvents();
	gtk_main_quit();
}

void MainWindow::OnAbout()
{
	ModalDialog about;
	std::string guifile = sdpAppendPath(sdpString(gtkmlPath), "about.gtkml");
	about.setGuiFile(guifile);
	about.DoModal();
}

void MainWindow::OnCanvasConfigureEvent()
{
	if(gc == 0)
	{
		GdkWindow* win = gtk_widget_get_parent_window(canvas);
		gc = gdk_gc_new(win);
		GdkFont* font = gdk_font_load(
			"-*-helvetica-medium-r-normal--*-140-*-*-*-*-iso8859-1");
		gdk_gc_set_font(gc, font);

	}

	if (pixmap)
		gdk_pixmap_unref(pixmap);

	pixmap = gdk_pixmap_new(canvas->window,
				canvas->allocation.width,
				canvas->allocation.height,
				-1);

	circuitBoard->draw(pixmap, gc);
}

void MainWindow::OnCanvasExposeEvent(sdpGtkEvent* event)
{
	sdpGtkEventWidgetExposeEvent* gtkEvent =
		static_cast<sdpGtkEventWidgetExposeEvent*>(event);

	GdkEventExpose* e = (GdkEventExpose*)gtkEvent->Event();

	gdk_draw_pixmap(canvas->window,
			gc,
			pixmap,
			e->area.x, e->area.y,
			e->area.x, e->area.y,
			e->area.width, e->area.height);
}

void MainWindow::OnZoom(sdpGtkEvent* event)
{
	sdpGtkEventAdjustmentValueChanged* gtkEvent =
		static_cast<sdpGtkEventAdjustmentValueChanged*>(event);

	circuitBoard->setZoom((int) gtkEvent->Adjustment()->value);
	forceRedraw();
}

void MainWindow::OnButtonPressEvent(sdpGtkEvent *event)
{
	sdpGtkEventWidgetButtonPressEvent* gtkEvent =
		static_cast<sdpGtkEventWidgetButtonPressEvent*>(event);

	GdkEventButton* bevent = (GdkEventButton*)gtkEvent->Event();

	int x = circuitBoard->toGrid(static_cast<int>(bevent->x));
	int y = circuitBoard->toGrid(static_cast<int>(bevent->y));
	GridEntity* underMouse = circuitBoard->entityAt(x, y);
	GtkWidget* popupmenu;

	if(bevent->button == 3)
	{
		if(state == Ready)
		{
			if(underMouse == 0)
				popupmenu = (GtkWidget*)Widget("normalmenu");
			else if(underMouse->isIOPad())
			{
				popupmenu = (GtkWidget*)Widget("iomenu");
				IOPad* underPad = (IOPad*)underMouse;
				if(underPad->isInput())
				{
					Widget("paddisconnect").SetSensitive(true);
					InputPad* inpad = (InputPad*)underPad;
					if(inpad->isMultiPad())
					{
						Widget("newmultipad").SetSensitive(true);
						Widget("removemultipad").SetSensitive(true);
					}
					else
					{
						Widget("newmultipad").SetSensitive(false);
						Widget("removemultipad").SetSensitive(false);
					}
				}
				else
				{
					Widget("paddisconnect").SetSensitive(false);
					Widget("newmultipad").SetSensitive(false);
					Widget("removemultipad").SetSensitive(false);
				}
			}
			else
				popupmenu = (GtkWidget*)Widget("blockmenu");

			currentElement = underMouse;
			gtk_menu_popup(GTK_MENU(popupmenu),
				0, 0, 0, 0,
				bevent->button, bevent->time);
		}
		else
		{
			cancelAction();
		}
	}
	else if(bevent->button == 1)
	{
		if(state == Ready || state == Connecting)
		{
			if(underMouse!=0)
			{
				if(underMouse->isIOPad())
				{
					if(state == Ready)
					{
						Statusbar("statusbar").Push(Statusbar("statusbar").GetContextID("click"), sdpString("Click another pad to connect"));
						state = Connecting;
						currentElement = underMouse;
					}
					else
					{
						IOPad* currentPad = (IOPad*)currentElement;
						IOPad* underPad = (IOPad*)underMouse;
						connectPads(currentPad, underPad);
						state = Ready;
					}
				}
				else if(state == Ready)
				{
					currentElement = underMouse;
					OnBlockMove();
				}
			}
		}
		else if(circuitBoard->freeSpaceAt(x, y,
			currentElement->getXSize(), currentElement->getYSize()))
		{
			currentElement->setPos(x, y);
			if(state == Adding)
				circuitBoard->addBlock((Block*)currentElement);
			else
				circuitBoard->replaceBlock((Block*)currentElement);
			state = Ready;
			forceRedraw();
		}
	}
}

void MainWindow::OnMouseMoveEvent(sdpGtkEvent* event)
{
	sdpGtkEventWidgetMotionNotifyEvent* gtkEvent =
		static_cast<sdpGtkEventWidgetMotionNotifyEvent*>(event);

	GdkEventMotion* mevent = (GdkEventMotion*)gtkEvent->Event();
	int sx, sy, gx, gy;
	GdkModifierType mstate;

	if(mevent->is_hint)
		gdk_window_get_pointer(mevent->window, &sx, &sy, &mstate);
	else
	{
		sx = (int) mevent->x;
		sy = (int) mevent->y;
		mstate = (GdkModifierType) mevent->state;
	}

	gx = circuitBoard->toGrid(sx);
	gy = circuitBoard->toGrid(sy);

	if(state == Moving || state == Adding)
	{
		int w = currentElement->getXSize();
		int h = currentElement->getYSize();

		drawCurrentElement(old_x, old_y);
		drawCurrentElement(gx, gy);
		old_x = gx; old_y = gy;
		if(circuitBoard->freeSpaceAt(gx, gy, w, h))
			Statusbar("statusbar").Push(Statusbar("statusbar").GetContextID("move"), sdpString("Press left to place"));
		else
			Statusbar("statusbar").Push(Statusbar("statusbar").GetContextID("move"), sdpString("Not enough space for block"));
	}
	else
	{
		GridEntity* underMouse = circuitBoard->entityAt(gx, gy);
		if(underMouse != 0)
		{
			if(underMouse->isIOPad() || state == Ready)
			{
				std::string message = underMouse->getName() + ": " + underMouse->getDesc();
				Statusbar("statusbar").Push(Statusbar("statusbar").GetContextID("connect"), message.c_str());
				if(underMouse->isIOPad())
				{
					IOPad* underPad = (IOPad*)underMouse;
					if(underPad->isInput() && underPad->isConnectable())
					{
						InputPad* underIn = (InputPad*)underPad;
						std::string value = "value: " + underIn->getStringValue();
						Statusbar("statusbar2").Push(Statusbar("statusbar2").GetContextID("value"), value.c_str());
					}
					else
						Statusbar("statusbar2").Push(Statusbar("statusbar2").GetContextID("value"), sdpString(""));
				}
				else
					Statusbar("statusbar2").Push(Statusbar("statusbar2").GetContextID("value"), sdpString(""));
			}
			else if(state == Connecting)
			{
				Statusbar("statusbar").Push(Statusbar("statusbar").GetContextID("connect"), sdpString(""));
				Statusbar("statusbar2").Push(Statusbar("statusbar2").GetContextID("value"), sdpString(""));
			}
		}
		else
		{
			Statusbar("statusbar").Push(Statusbar("statusbar").GetContextID("connect"), sdpString(""));
			Statusbar("statusbar2").Push(Statusbar("statusbar2").GetContextID("value"), sdpString(""));
		}

		if(state == Ready)
			currentElement = underMouse;
	}
}

void MainWindow::OpenMenu(sdpGtkEvent* event)
{
	sdpGtkEventWidgetButtonPressEvent* gtkEvent =
		static_cast<sdpGtkEventWidgetButtonPressEvent*>(event);

	GdkEventButton* bevent = (GdkEventButton*)gtkEvent->Event();

	//remove openmenu from start of string
	sdpString name = event->Name();
	name = name.right(name.length() - 8);

	GtkWidget* popupmenu = (GtkWidget*)Widget(name.c_str());

	gtk_menu_popup (GTK_MENU (popupmenu),
			0, 0, 0, 0,
			bevent->button, bevent->time);
}

void MainWindow::forceRedraw()
{
	GdkRectangle area;

	area.x = 0;
	area.y = 0;
	area.width = canvas->allocation.width;
	area.height = canvas->allocation.height;

	circuitBoard->draw(pixmap, gc);
	gtk_widget_draw(canvas, &area);
}

void MainWindow::cancelAction()
{
	if(state == Ready)
		return;
	if(state != Connecting)
		drawCurrentElement(old_x, old_y);
	if(state == Adding)
		delete currentElement;
	if(state == Moving)
		circuitBoard->replaceBlock((Block*)currentElement);

	Statusbar("statusbar").Push(Statusbar("statusbar").GetContextID("click"), sdpString("Action Cancelled"));
	state = Ready;
}

void MainWindow::setBasePath()
{
	basePath = sdpGetEnv("SHRIMP_BASE_PATH");
	if(basePath.size() == 0)
	{
		//look for a file to see if we can run anyway
		std::string afile = "dialogtemplates/blockhelp.gtkml";
		if(!sdpFileExists(afile.c_str()))
		{
			std::cout << "***SHRIMP_BASE_PATH variable not set." << std::endl;
			std::cout << "***This should point to the directory that you unpacked Shrimp into" << std::endl;
			std::cout << "***Quiting..." << std::endl;
			exit(1);
		}
	}
}

bool MainWindow::loadPrefs(std::string filename)
{
	std::ifstream file(filename.c_str());
	sdpxml::Document doc(filename);
	Parse(file, filename, &doc);

	if(doc.Name() != std::string("shrimp_prefs"))
	{
		std::cerr << "Couldn't load preference file : " << filename << std::endl;
		return false;
	}

	sdpxml::Element* renderprefs = sdpxml::FindElement(doc, sdpxml::SameName("renderprefs"));
	if(renderprefs)
		renderOptions.readPrefs(renderprefs);

	return true;
}

void MainWindow::savePrefs(std::string filename)
{
	sdpxml::Document doc("shrimp_prefs", "");
	doc.Children().push_back(sdpxml::Element("renderprefs"));
	renderOptions.writePrefs(doc.Children().back());

	// Save XML document
	std::ofstream out_file;
	out_file.open(filename.c_str(), std::ios::out | std::ios::trunc);
	out_file << doc << std::endl;
	out_file.close();
}


