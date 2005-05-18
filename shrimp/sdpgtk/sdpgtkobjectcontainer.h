#ifndef SDPGTKOBJECTCONTAINER_H
#define SDPGTKOBJECTCONTAINER_H

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
		\brief Declares the sdpGtkObjectContainer class, which can load GTKML (XML) documents
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkiobjectcontainer.h"
#include "sdpgtkwidgets.h"

#include <iostream>
#include <map>
#include <list>
#include <stack>

// We have a small collision with Xlib.h ...
#ifdef SDPUNIX
#ifdef RootWindow
#undef RootWindow
#endif // RootWindow

#endif // SPDUNIX


// Forward class declarations ...
class sdpGtkEvent;
class sdpxml::Document;

///////////////////////////////////////////////////////////////////
// sdpGtkObjectContainer

/// Loads GTKML (XML) documents
class sdpGtkObjectContainer :
	public sdpGtkIObjectContainer,
	public sdpGtkObject
{
public:
	sdpGtkObjectContainer();
	virtual ~sdpGtkObjectContainer();

	/// Loads a GTKML file from an XML document
	bool Load(sdpxml::Document& Document);
	/// Loads a GTKML file from a stream
	bool Load(std::istream& Stream, const sdpString FilePath);
	/// Loads a GTKML file from a filesystem
	bool Load(const sdpString FilePath);
	/// Loads a GTKML file from a filesystem, using a user's preferred language
	bool Load(const sdpString FilePath, const sdpString PreferredLanguage);

	/// The main event handler function
	virtual void OnEvent(sdpGtkEvent* Event);

	/// Returns the container's root object (the top-level object within a GTKML document)
	GtkObject* Root() { return m_Object; }

	/// Maps an event by name
	sdpGtkEvent* MapEvent(SDPCSTRING EventSignal, SDPCSTRING EventName, const bool After, GtkObject* const Object, const bool Connect);
	/// Maps an event by name
	sdpGtkEvent* MapEvent(SDPCSTRING EventSignal, SDPCSTRING EventName, const bool After, sdpGtkObject* const Object, const bool Connect);
	/// Maps an event by name
	sdpGtkEvent* MapEvent(SDPCSTRING EventSignal, SDPCSTRING EventName, const bool After, sdpGtkObject& Object, const bool Connect);

	/// Connects all events to GTK+
	void ConnectAllEvents();
	/// Blocks all object events
	void BlockAllEvents();
	/// Unblocks all object events
	void UnblockAllEvents();
	/// Disconnects all events from GTK+
	void DisconnectAllEvents();

	/// Deletes an event (the event must be explicitly disconnected by hand)
	void DeleteEvent(sdpGtkEvent* Event);

	/// Grabs the application focus and begins a modal loop
	void DoModal();
	/// Grabs the application focus and begins a modal loop
	void DoModal(GtkWindow* TransientOwner);
	/// Grabs the application focus and begins a modal loop
	void DoModal(sdpGtkWindow& TransientOwner);
	/// Finishes the modal loop and releases the focus
	void CancelModal();
	/// Tests to see if the modal loop is active
	bool IsModal();
	
	/// Returns a resource by name
	sdpString Resource(SDPCSTRING ResourceName);
	/// Returns a resource by name
	sdpString Resource(SDPCSTRING ResourceName, SDPCSTRING DefaultValue);
	
	/// Returns a custom object by name
	sdpGtkObject* CustomObject(SDPCSTRING CustomObjectName);

	/// Interactively show a widget
	bool InteractiveShow(SDPCSTRING Name, const gdouble Speed, const bool Pause);
	/// Interactively highlight a widget
	bool InteractiveHighlight(SDPCSTRING Name, const gdouble Speed, const bool Pause);
	/// Interactively activate a button
	bool InteractiveActivateButton(SDPCSTRING Name, const gdouble Speed, const bool Pause);
	/// Interactively activate a toggle-button
	bool InteractiveToggleButton(SDPCSTRING Name, const gdouble Speed, const bool Pause);
	/// Interactively activate a menu item
	bool InteractiveActivateMenuItem(SDPCSTRING Name, const gdouble Speed, const bool Pause);
	/// Interactively put text into a text control
	bool InteractiveSetText(SDPCSTRING Name, SDPCSTRING Text, const gdouble Speed, const bool Pause);
	/// Interactively move the mouse pointer to a control (and make sure it's visible)
	bool InteractiveMoveTo(SDPCSTRING Name, const gdouble Speed, const bool Pause);

	// Object access with typecasting
	sdpGtkAccelLabel AccelLabel(SDPCSTRING ControlName);
	sdpGtkAdjustment Adjustment(SDPCSTRING ControlName);
	sdpGtkArrow Arrow(SDPCSTRING ControlName);
	sdpGtkAspectFrame AspectFrame(SDPCSTRING ControlName);
	sdpGtkAlignment Alignment(SDPCSTRING ControlName);
	sdpGtkBin Bin(SDPCSTRING ControlName);
	sdpGtkBox Box(SDPCSTRING ControlName);
	sdpGtkButton Button(SDPCSTRING ControlName);
	sdpGtkButtonBox ButtonBox(SDPCSTRING ControlName);
	sdpGtkCalendar Calendar(SDPCSTRING ControlName);
	sdpGtkCheckButton CheckButton(SDPCSTRING ControlName);
	sdpGtkCheckMenuItem CheckMenuItem(SDPCSTRING ControlName);
	sdpGtkCList CList(SDPCSTRING ControlName);
	sdpGtkColorSelection ColorSelection(SDPCSTRING ControlName);
	sdpGtkColorSelectionDialog ColorSelectionDialog(SDPCSTRING ControlName);
	sdpGtkCombo Combo(SDPCSTRING ControlName);
	sdpGtkContainer Container(SDPCSTRING ControlName);
	sdpGtkCTree CTree(SDPCSTRING ControlName);
	sdpGtkCurve Curve(SDPCSTRING ControlName);
	sdpGtkData Data(SDPCSTRING ControlName);
	sdpGtkDialog Dialog(SDPCSTRING ControlName);
	sdpGtkDrawingArea DrawingArea(SDPCSTRING ControlName);
	sdpGtkEditable Editable(SDPCSTRING ControlName);
	sdpGtkEntry Entry(SDPCSTRING ControlName);
	sdpGtkEventBox EventBox(SDPCSTRING ControlName);
	sdpGtkFileSelection FileSelection(SDPCSTRING ControlName);
	sdpGtkFixed Fixed(SDPCSTRING ControlName);
	sdpGtkFontSelection FontSelection(SDPCSTRING ControlName);
	sdpGtkFontSelectionDialog FontSelectionDialog(SDPCSTRING ControlName);
	sdpGtkFrame Frame(SDPCSTRING ControlName);
	sdpGtkGammaCurve GammaCurve(SDPCSTRING ControlName);
	sdpGtkHandleBox HandleBox(SDPCSTRING ControlName);
	sdpGtkHBox HBox(SDPCSTRING ControlName);
	sdpGtkHButtonBox HButtonBox(SDPCSTRING ControlName);
	sdpGtkHPaned HPaned(SDPCSTRING ControlName);
	sdpGtkHRuler HRuler(SDPCSTRING ControlName);
	sdpGtkHScale HScale(SDPCSTRING ControlName);
	sdpGtkHScrollbar HScrollbar(SDPCSTRING ControlName);
	sdpGtkHSeparator HSeparator(SDPCSTRING ControlName);
	sdpGtkImage Image(SDPCSTRING ControlName);
	sdpGtkInputDialog InputDialog(SDPCSTRING ControlName);
	sdpGtkItem Item(SDPCSTRING ControlName);
	sdpGtkLabel Label(SDPCSTRING ControlName);
	sdpGtkList List(SDPCSTRING ControlName);
	sdpGtkListItem ListItem(SDPCSTRING ControlName);
	sdpGtkMenu Menu(SDPCSTRING ControlName);
	sdpGtkMenuBar MenuBar(SDPCSTRING ControlName);
	sdpGtkMenuItem MenuItem(SDPCSTRING ControlName);
	sdpGtkMenuShell MenuShell(SDPCSTRING ControlName);
	sdpGtkMisc Misc(SDPCSTRING ControlName);
	sdpGtkNotebook Notebook(SDPCSTRING ControlName);
	sdpGtkObject Object(SDPCSTRING ControlName);
	sdpGtkOptionMenu OptionMenu(SDPCSTRING ControlName);
	sdpGtkPaned Paned(SDPCSTRING ControlName);
	sdpGtkPixmap Pixmap(SDPCSTRING ControlName);
	sdpGtkRange Range(SDPCSTRING ControlName);
	sdpGtkScrollbar Scrollbar(SDPCSTRING ControlName);
	sdpGtkScrolledWindow ScrolledWindow(SDPCSTRING ControlName);
	sdpGtkSeparator Separator(SDPCSTRING ControlName);
	sdpGtkSocket Socket(SDPCSTRING ControlName);
	sdpGtkSpinButton SpinButton(SDPCSTRING ControlName);
	sdpGtkStatusbar Statusbar(SDPCSTRING ControlName);
	sdpGtkTable Table(SDPCSTRING ControlName);
	sdpGtkTearoffMenuItem TearoffMenuItem(SDPCSTRING ControlName);
	sdpGtkText Text(SDPCSTRING ControlName);
	sdpGtkTipsQuery TipsQuery(SDPCSTRING ControlName);
	sdpGtkToggleButton ToggleButton(SDPCSTRING ControlName);
	sdpGtkToolbar Toolbar(SDPCSTRING ControlName);
	sdpGtkTooltips Tooltips(SDPCSTRING ControlName);
	sdpGtkTree Tree(SDPCSTRING ControlName);
	sdpGtkTreeItem TreeItem(SDPCSTRING ControlName);
	sdpGtkVBox VBox(SDPCSTRING ControlName);
	sdpGtkVButtonBox VButtonBox(SDPCSTRING ControlName);
	sdpGtkViewport Viewport(SDPCSTRING ControlName);
	sdpGtkVPaned VPaned(SDPCSTRING ControlName);
	sdpGtkVRuler VRuler(SDPCSTRING ControlName);
	sdpGtkVScale VScale(SDPCSTRING ControlName);
	sdpGtkVScrollbar VScrollbar(SDPCSTRING ControlName);
	sdpGtkVSeparator VSeparator(SDPCSTRING ControlName);
 	sdpGtkWidget Widget(SDPCSTRING ControlName);
	sdpGtkWindow Window(SDPCSTRING ControlName);

	// Root object access with typecasting ...
	sdpGtkAccelLabel RootAccelLabel();
	sdpGtkAdjustment RootAdjustment();
	sdpGtkAlignment RootAlignment();
	sdpGtkArrow RootArrow();
	sdpGtkAspectFrame RootAspectFrame();
	sdpGtkBin RootBin();
	sdpGtkBox RootBox();
	sdpGtkButton RootButton();
	sdpGtkButtonBox RootButtonBox();
	sdpGtkCalendar RootCalendar();
	sdpGtkCheckButton RootCheckButton();
	sdpGtkCheckMenuItem RootCheckMenuItem();
	sdpGtkCList RootCList();
	sdpGtkColorSelection RootColorSelection();
	sdpGtkColorSelectionDialog RootColorSelectionDialog();
	sdpGtkCombo RootCombo();
	sdpGtkContainer RootContainer();
	sdpGtkCTree RootCTree();
	sdpGtkCurve RootCurve();
	sdpGtkData RootData();
	sdpGtkDialog RootDialog();
	sdpGtkDrawingArea RootDrawingArea();
	sdpGtkEditable RootEditable();
	sdpGtkEntry RootEntry();
	sdpGtkEventBox RootEventBox();
	sdpGtkFileSelection RootFileSelection();
	sdpGtkFixed RootFixed();
	sdpGtkFontSelection RootFontSelection();
	sdpGtkFontSelectionDialog RootFontSelectionDialog();
	sdpGtkFrame RootFrame();
	sdpGtkGammaCurve RootGammaCurve();
	sdpGtkHandleBox RootHandleBox();
	sdpGtkHBox RootHBox();
	sdpGtkHButtonBox RootHButtonBox();
	sdpGtkHPaned RootHPaned();
	sdpGtkHRuler RootHRuler();
	sdpGtkHScale RootHScale();
	sdpGtkHScrollbar RootHScrollbar();
	sdpGtkHSeparator RootHSeparator();
	sdpGtkImage RootImage();
	sdpGtkInputDialog RootInputDialog();
	sdpGtkItem RootItem();
	sdpGtkLabel RootLabel();
	sdpGtkList RootList();
	sdpGtkListItem RootListItem();
	sdpGtkMenu RootMenu();
	sdpGtkMenuBar RootMenuBar();
	sdpGtkMenuItem RootMenuItem();
	sdpGtkMenuShell RootMenuShell();
	sdpGtkMisc RootMisc();
	sdpGtkNotebook RootNotebook();
	sdpGtkObject RootObject();
	sdpGtkOptionMenu RootOptionMenu();
	sdpGtkPaned RootPaned();
	sdpGtkPixmap RootPixmap();
	sdpGtkRange RootRange();
	sdpGtkScrollbar RootScrollbar();
	sdpGtkScrolledWindow RootScrolledWindow();
	sdpGtkSeparator RootSeparator();
	sdpGtkSocket RootSocket();
	sdpGtkSpinButton RootSpinButton();
	sdpGtkStatusbar RootStatusbar();
	sdpGtkTable RootTable();
	sdpGtkTearoffMenuItem RootTearoffMenuItem();
	sdpGtkText RootText();
	sdpGtkTipsQuery RootTipsQuery();
	sdpGtkToggleButton RootToggleButton();
	sdpGtkToolbar RootToolbar();
	sdpGtkTooltips RootTooltips();
	sdpGtkTree RootTree();
	sdpGtkTreeItem RootTreeItem();
	sdpGtkVBox RootVBox();
	sdpGtkVButtonBox RootVButtonBox();
	sdpGtkViewport RootViewport();
	sdpGtkVPaned RootVPaned();
	sdpGtkVRuler RootVRuler();
	sdpGtkVScale RootVScale();
	sdpGtkVScrollbar RootVScrollbar();
	sdpGtkVSeparator RootVSeparator();
	sdpGtkWidget RootWidget();
	sdpGtkWindow RootWindow();

protected:
	/// Frees up all storage
	void Clear();
	/// Frees "normal" GTK+ objects
	void ClearObjects();
	/// Frees "custom" objects
	void ClearCustomObjects();
	/// Frees radio-button/radio menu item groups
	void ClearGroups();
	/// Frees event objects
	void ClearEvents();

	// sdpGtkIObjectContainer overrides ...
	void NotifyObject(GtkObject* Object);
	void MapObject(SDPCSTRING ObjectName, GtkObject* Object);
	void MapCustomObject(SDPCSTRING CustomObjectName, sdpGtkObject* CustomObject);
	void MapGroup(SDPCSTRING GroupName, GSList* Group);
	void MapResource(SDPCSTRING ResourceName, SDPCSTRING ResourceValue);
	void MapEvent(sdpxml::Document& Document, sdpxml::Element& Element, GtkObject* Object, bool Connect);
	sdpGtkObject* CreateCustomObject(sdpxml::Element& Element);
	GtkAccelGroup* GetAcceleratorGroup();
	GtkObject* GetObject(SDPCSTRING ObjectName);
	GSList* GetGroup(SDPCSTRING GroupName);

private:
	/// Tests to see that there are no unused elements or attributes in a GTKML document
	bool TestCoverage(const sdpxml::Document& XML);
	/// Recursively tests to see that an element and its children were "used" by a GTKML document
	bool TestElementCoverage(const sdpxml::Document& Document, const sdpxml::Element& Element);

	/// Stores the state of the modal loop
	bool m_RunModal;

	typedef std::map<sdpString, GtkObject*> ObjectMap;
	typedef ObjectMap::iterator ObjectIterator;
	/// Stores the mapping of names to objects
	ObjectMap m_Objects;
	
	typedef std::map<sdpString, sdpGtkObject*> CustomObjectMap;
	typedef CustomObjectMap::iterator CustomObjectIterator;
	/// Stores the mapping of names to custom objects
	CustomObjectMap m_CustomObjects;
	
	typedef std::map<sdpString, GSList*> GroupMap;
	typedef GroupMap::iterator GroupIterator;
	/// Stores the mapping of names to groups
	GroupMap m_Groups;

	typedef std::multimap<sdpString, sdpGtkEvent*> EventMap;
	typedef EventMap::iterator EventIterator;
	/// Stores the mapping of names to events
	EventMap m_Events;

	/// Singleton accelerator group for handling accelerator keys
	GtkAccelGroup* m_AcceleratorGroup;
	
	typedef std::map<sdpString, sdpString> ResourceMap;
	typedef ResourceMap::iterator ResourceIterator;
	/// Stores the mapping of names to resources
	ResourceMap m_Resources;
};

#endif // SDPGTKOBJECTCONTAINER_H

