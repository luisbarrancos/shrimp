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
		\brief Implements the sdpGtkObjectContainer class, which can load GTKML (XML) documents
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtkobjectcontainer.h"
#include "sdpgtkutility.h"

#include "sdpgtkevents.h"
#include "sdpgtkloopevents.h"

#include <fstream>

#ifdef	SDPWIN32
#undef	GetObject
#endif	//SDP_WIN32

////////////////////////////////////////////////////////////////////////////////
// sdpGtkObjectContainer

sdpGtkObjectContainer::sdpGtkObjectContainer()
{
	m_AcceleratorGroup = 0;
	m_RunModal = false;
}

sdpGtkObjectContainer::~sdpGtkObjectContainer()
{
	Clear();
}

// Cleanup all storage ...
void sdpGtkObjectContainer::Clear()
{
	m_Object = 0;
	m_RunModal = false;

	ClearObjects();
	ClearCustomObjects();
	ClearGroups();
	ClearEvents();
}

// Remove all objects ...
void sdpGtkObjectContainer::ClearObjects()
{
	m_Objects.clear();
}

// Remove all custom objects ...
void sdpGtkObjectContainer::ClearCustomObjects()
{
	// Zap each custom object ...
	for(CustomObjectIterator object = m_CustomObjects.begin(); object != m_CustomObjects.end(); object++)
		delete object->second;

	m_CustomObjects.clear();
}

// Remove all groups ...
void sdpGtkObjectContainer::ClearGroups()
{
	m_Groups.clear();
}

// Remove all events ...
void sdpGtkObjectContainer::ClearEvents()
{
	// Zap each event ...
	for(EventIterator event = m_Events.begin(); event != m_Events.end(); event++)
		delete event->second;

	m_Events.clear();
}

// Connect all unconnected events ...
void sdpGtkObjectContainer::ConnectAllEvents()
{
	// For each event ...
	for(EventIterator event = m_Events.begin(); event != m_Events.end(); event++)
		{
			// Skip events that are already connected ...
			if(event->second->Handler())
				continue;

			// Connect the event ...
			event->second->Connect();
		}
}

// Block all object events ...
void sdpGtkObjectContainer::BlockAllEvents()
{
	// For each event ...
	for(EventIterator event = m_Events.begin(); event != m_Events.end(); event++)
		{
			// Skip events that aren't connected ...
			if(0 == event->second->Handler())
				continue;

			((sdpGtkObjectEvent*)event->second)->Block();
		}
}

// Unblock all object events ...
void sdpGtkObjectContainer::UnblockAllEvents()
{
	// For each event ...
	for(EventIterator event = m_Events.begin(); event != m_Events.end(); event++)
		{
			// Skip events that aren't connected ...
			if(0 == event->second->Handler())
				continue;

			((sdpGtkObjectEvent*)event->second)->Unblock();
		}
}

// Disconnects all events ...
void sdpGtkObjectContainer::DisconnectAllEvents()
{
	for(EventIterator event = m_Events.begin(); event != m_Events.end(); event++)
		{
			// Skip events that aren't connected ...
			if(0 == event->second->Handler())
				continue;

			// Disconnect the event ...
			event->second->Disconnect();
		}
}

void sdpGtkObjectContainer::DeleteEvent(sdpGtkEvent* Event)
{
	// Sanity checks ...
	g_assert(Event);

	// For each event ...
	for(EventIterator event = m_Events.begin(); event != m_Events.end(); event++)
		{
			// Skip events that don't match ...
			if(event->second != Event)
				continue;

			// Get rid of the event ...
			delete event->second;
			m_Events.erase(event);
			return;
		}

	g_return_if_fail(0);	// Unknown event!
}

// Lets us know that an object has been created ...
void sdpGtkObjectContainer::NotifyObject(GtkObject* Object)
{
	// Sanity checks ...
	g_assert(Object);

	if(!m_Object)
		m_Object = Object;
}

// Maps a name to an object ...
void sdpGtkObjectContainer::MapObject(SDPCSTRING ObjectName, GtkObject* Object)
{
	// Sanity checks ...
	g_assert_string(ObjectName);
	g_assert(Object);

	// Make sure we don't have any duplicate names!
	ObjectIterator object = m_Objects.find(ObjectName);
	if(object != m_Objects.end())
		{
			std::cerr << "Cannot map object with duplicate name [" << ObjectName << "]" << std::endl;
			g_return_if_fail(0);
		}

	m_Objects[ObjectName] = Object;
}

// Maps a custom object by name ...
void sdpGtkObjectContainer::MapCustomObject(SDPCSTRING CustomObjectName, sdpGtkObject* CustomObject)
{
	// Sanity checks ...
	g_assert_string(CustomObjectName);
	g_assert(CustomObject);

	// Make sure we don't have any duplicate names!
	CustomObjectIterator customobject = m_CustomObjects.find(CustomObjectName);
	if(customobject != m_CustomObjects.end())
		{
			std::cerr << "Cannot map custom object with duplicate name [" << CustomObjectName << "]" << std::endl;
			g_return_if_fail(0);
		}


	m_CustomObjects[CustomObjectName] = CustomObject;
}

// Maps a group by name ...
void sdpGtkObjectContainer::MapGroup(SDPCSTRING GroupName, GSList* Group)
{
	// Sanity checks ...
	g_assert_string(GroupName);

	m_Groups[GroupName] = Group;
}

// Maps a resource by name ...
void sdpGtkObjectContainer::MapResource(SDPCSTRING ResourceName, SDPCSTRING ResourceValue)
{
	// Sanity checks ...
	g_assert_string(ResourceName);

	m_Resources[ResourceName] = ResourceValue;
}

// Maps an event from an XML document ...
void sdpGtkObjectContainer::MapEvent(sdpxml::Document& Document, sdpxml::Element& Element, GtkObject* Object, bool Connect)
{
	// Sanity checks ...
	g_assert(Object);

	// Get the event signal ...
	const sdpString signal = sdpxml::GetAttribute<sdpString>(Element, "signal", "");
	sdpGtkMarkAttribute(Document, Element, "signal");

	// Get the event name ...
	const sdpString name = sdpxml::GetAttribute<sdpString>(Element, "name", "");
	sdpGtkMarkAttribute(Document, Element, "name");

	// Do we want to handle the signal before or after the default handler?
	const bool after = sdpxml::GetAttribute(Element, "after", false);
	sdpGtkMarkAttribute(Document, Element, "after");

	// Create and map the event (but don't connect it, yet) ...
	sdpGtkEvent* event = MapEvent(signal, name, after, Object, false);
	g_assert(event);

	// Special case: if the event is a timeout event, set its delay ...
	if(signal == "timeout")
		{
			const gulong duration = sdpxml::GetAttribute(Element, "duration", 1000);
			sdpGtkMarkAttribute(Document, Element, "duration");

			((sdpGtkEventTimeout*)event)->SetDuration(duration);
		}

	// Connect the event ...
	if(Connect)
		event->Connect();
}

// Maps an event by name ...
sdpGtkEvent* sdpGtkObjectContainer::MapEvent(SDPCSTRING EventSignal, SDPCSTRING EventName, const bool After, sdpGtkObject& Object, const bool Connect)
{
	// Create the event based on its' underlying GTK widget ...
	return MapEvent(EventSignal, EventName, After, &Object, Connect);
}

// Maps an event by name ...
sdpGtkEvent* sdpGtkObjectContainer::MapEvent(SDPCSTRING EventSignal, SDPCSTRING EventName, const bool After, sdpGtkObject* const Object, const bool Connect)
{
	// Create the event based on its' underlying GTK widget ...
	return MapEvent(EventSignal, EventName, After, Object->Object(), Connect);
}

// Maps an event by name ...
sdpGtkEvent* sdpGtkObjectContainer::MapEvent(SDPCSTRING EventSignal, SDPCSTRING EventName, const bool After, GtkObject* const Object, const bool Connect)
{
	// Sanity checks ...
	g_assert_string(EventSignal);
	g_assert_string(EventName);
	g_assert(Object);

	// Create an event based on its' type ...
	sdpGtkEvent* event = sdpGtkEvent::CreateEvent(EventSignal, EventName, After, this, Object);
	g_return_val_if_fail(event, 0);

	// Make the GTK event connection ...
	if(Connect)
		event->Connect();

	// Stash the event ...
	m_Events.insert(EventMap::value_type(EventName, event));

	return event;
}

// This can be overridden in derived classes to create custom objects ...
sdpGtkObject* sdpGtkObjectContainer::CreateCustomObject(sdpxml::Element& Element)
{
	return 0;
}

// Get the accelerator group off the top of the stack
GtkAccelGroup* sdpGtkObjectContainer::GetAcceleratorGroup()
{
	// Sanity checks ...
	g_assert(Root());

	if(!m_AcceleratorGroup)
		{
			// Create a new accelerator group ...
			m_AcceleratorGroup = gtk_accel_group_new();
			g_assert(m_AcceleratorGroup);

			// Attach it to the given object ...
			gtk_accel_group_attach(m_AcceleratorGroup, RootObject());
		}

	// Return the top-level group ...
	return m_AcceleratorGroup;
}

// Returns an object by name ...
GtkObject* sdpGtkObjectContainer::GetObject(SDPCSTRING ObjectName)
{
	// Sanity checks ...
	g_assert_string(ObjectName);

	// See if the object exists ...
	ObjectIterator i = m_Objects.find(ObjectName);
	return i != m_Objects.end() ? i->second : 0;
}

// Returns a group by name ...
GSList* sdpGtkObjectContainer::GetGroup(SDPCSTRING GroupName)
{
	// Sanity checks ...
	g_assert_string(GroupName);

	// Make sure we have a valid group ...
	GroupIterator group = m_Groups.find(GroupName);
	if(group == m_Groups.end())
		m_Groups[GroupName] = 0;

	return m_Groups[GroupName];
}

static void ErrorUnknownResource(SDPCSTRING ResourceName)
{
	std::cout << "sdpGtkObjectContainer:: unknown resource \"" << ResourceName << "\"" << std::endl;
}

// Returns a resource by name ...
sdpString sdpGtkObjectContainer::Resource(SDPCSTRING ResourceName)
{
	// Sanity checks ...
	g_assert_string(ResourceName);

	sdpString result;
	ResourceIterator resource = m_Resources.find(ResourceName);
	if(resource == m_Resources.end())
		{
			ErrorUnknownResource(ResourceName);
			return sdpString();
		}

	return resource->second;
}

// Returns a resource by name ...
sdpString sdpGtkObjectContainer::Resource(SDPCSTRING ResourceName, SDPCSTRING DefaultValue)
{
	// Sanity checks ...
	g_assert_string(ResourceName);

	sdpString result;
	ResourceIterator resource = m_Resources.find(ResourceName);
	if(resource == m_Resources.end())
		return sdpString(DefaultValue);

	return resource->second;
}

// Returns a custom object by name ...
sdpGtkObject* sdpGtkObjectContainer::CustomObject(SDPCSTRING CustomObjectName)
{
	// Sanity checks ...
	g_assert_string(CustomObjectName);

	CustomObjectIterator customobject = m_CustomObjects.find(CustomObjectName);
	g_return_val_if_fail(customobject != m_CustomObjects.end(), 0);

	return customobject->second;
}

bool sdpGtkObjectContainer::Load(sdpxml::Document& XML)
{
	// Make sure we get rid of existing data ...
	Clear();

	// Make sure it's a GTKML document ...
	g_return_val_if_fail(XML.Name() == "gtkml", false);

	// Recursively create children ...
	g_return_val_if_fail(CreateChildren(this, XML, XML), false);

	// Test to be sure all the attributes were used ...
	bool result = TestCoverage(XML);

	// Connect our events ...
	ConnectAllEvents();

	return result;
}

// Loads a GTKML file from a stream ...
bool sdpGtkObjectContainer::Load(std::istream& Stream, const sdpString FilePath)
{
	// Sanity checks ...
	g_return_val_if_fail(Stream.good(), false);

	// Load the stream as an XML document ...
	sdpxml::Document document("empty", FilePath);
	g_return_val_if_fail(sdpxml::Parse(Stream, FilePath, &document), false);

	// Parse the XML document tree ...
	return Load(document);
}

bool sdpGtkObjectContainer::Load(const sdpString FilePath)
{
	// Sanity checks ...
	g_return_val_if_fail(FilePath.size(), false);

	// Open the file as a stream ...
	std::ifstream file(FilePath);
	if(!file.good())
		{
			std::cerr << "sdpGtkObjectContainer::Load(): File [" << FilePath << "] cannot be opened" << std::endl;
			g_return_val_if_fail(0, false);
		}

	// Load it ...
	return Load(file, FilePath);
}

bool sdpGtkObjectContainer::Load(const sdpString FilePath, const sdpString PreferredLanguage)
{
	// Sanity checks ...
	g_return_val_if_fail(FilePath.size(), false);

	if(PreferredLanguage.size())
		{
			const sdpString preferredfilepath = FilePath + "." + PreferredLanguage;

			if(sdpFileExists(preferredfilepath))
				return Load(preferredfilepath);
		}

	return Load(FilePath);
}

bool sdpGtkObjectContainer::TestCoverage(const sdpxml::Document& XML)
{
	if(!TestElementCoverage(XML, XML))
		return false;

	return true;
}

bool sdpGtkObjectContainer::TestElementCoverage(const sdpxml::Document& Document, const sdpxml::Element& Element)
{
	for(sdpxml::AttributeCollection::const_iterator attribute = Element.Attributes().begin(); attribute != Element.Attributes().end(); attribute++)
		{
			const sdpString usedby = attribute->Meta("usedby");
			if(!usedby.size())
				std::cout << "Unused attribute [" << attribute->Name() << "] will be ignored at " << sdpxml::FileReference(Document, Element) << std::endl;
		}

	for(sdpxml::ElementCollection::const_iterator element = Element.Children().begin(); element != Element.Children().end(); element++)
		TestElementCoverage(Document, *element);

	return true;
}

void sdpGtkObjectContainer::OnEvent(sdpGtkEvent* Event)
{
	// Sanity checks ...
	g_assert(Event);

	std::cout << "Un-handled GTKML Event: '" << Event->Name() << "'" << std::endl;
}

void sdpGtkObjectContainer::DoModal()
{
	// Sanity checks ...
	g_return_if_fail(!IsModal());
	g_return_if_fail(m_Object);

	// Make sure we grab events ...
	gtk_window_set_modal(RootWindow(), true);

	// Event loop ...
	m_RunModal = true;
	while(m_RunModal)
		gtk_main_iteration();
}

void sdpGtkObjectContainer::DoModal(GtkWindow* TransientOwner)
{
	// Sanity checks ...
	g_return_if_fail(TransientOwner);

	RootWindow().SetTransientFor(TransientOwner);

	DoModal();
}

void sdpGtkObjectContainer::DoModal(sdpGtkWindow& TransientOwner)
{
	// Sanity checks ...
	g_return_if_fail(TransientOwner.Attached());

	DoModal((GtkWindow*)TransientOwner);
}

void sdpGtkObjectContainer::CancelModal()
{
	// Sanity checks ...
	g_return_if_fail(IsModal());
	g_return_if_fail(m_Object);

	// Release events ...
	gtk_window_set_modal(RootWindow(), false);

	// Cancel modal operation ...
	m_RunModal = false;
}

bool sdpGtkObjectContainer::IsModal()
{
	return m_RunModal;
}

bool sdpGtkObjectContainer::InteractiveShow(SDPCSTRING Name, const gdouble Speed, const bool Pause)
{
	// Sanity checks ...
	g_assert_string(Name);

	sdpGtkWidget widget = Widget(Name);
	g_return_val_if_fail(widget.Attached(), false);

	widget.InteractiveShow(Speed, Pause);

	return true;
}

bool sdpGtkObjectContainer::InteractiveHighlight(SDPCSTRING Name, const gdouble Speed, const bool Pause)
{
	// Sanity checks ...
	g_assert_string(Name);

	sdpGtkWidget widget = Widget(Name);
	g_return_val_if_fail(widget.Attached(), false);

	widget.InteractiveShow(Speed, Pause);
	widget.InteractiveHighlight(Speed, Pause);

	return true;
}

bool sdpGtkObjectContainer::InteractiveActivateButton(SDPCSTRING Name, const gdouble Speed, const bool Pause)
{
	// Sanity checks ...
	g_assert_string(Name);

	sdpGtkButton button = Button(Name);
	g_return_val_if_fail(button.Attached(), false);

	button.InteractiveShow(Speed, Pause);
	button.InteractiveWarpPointer(Speed, Pause, false);
	button.InteractiveActivate();

	return true;
}

bool sdpGtkObjectContainer::InteractiveToggleButton(SDPCSTRING Name, const gdouble Speed, const bool Pause)
{
	// Sanity checks ...
	g_assert_string(Name);

	sdpGtkToggleButton button = ToggleButton(Name);
	g_return_val_if_fail(button.Attached(), false);

	button.InteractiveShow(Speed, Pause);
	button.InteractiveWarpPointer(Speed, Pause, false);
	button.InteractiveToggle();

	return true;
}

bool sdpGtkObjectContainer::InteractiveActivateMenuItem(SDPCSTRING Name, const gdouble Speed, const bool Pause)
{
	// Sanity checks ...
	g_assert_string(Name);

	sdpGtkMenuItem targetitem = MenuItem(Name);
	g_return_val_if_fail(targetitem.Attached(), false);

	// Build a list of menu items above this one, so we can get at 'em ...
	typedef std::vector<GtkWidget*> MenuItems;
	MenuItems items;

	for(GtkWidget* ancestor = GTK_WIDGET(targetitem.Object()); ancestor; )
		{
			if(GTK_IS_MENU_ITEM(ancestor))
				items.push_back(ancestor);

			if(GTK_IS_MENU(ancestor))
				ancestor = gtk_menu_get_attach_widget (GTK_MENU(ancestor));
			else
				ancestor = ancestor->parent;
		}

	// Make our item visible ...
	targetitem.InteractiveShow(Speed, Pause);

	// Close everything down ...
	for(MenuItems::iterator item = items.begin(); item != items.end(); item++)
		sdpGtkMenuItem(GTK_MENU_ITEM(*item)).Deselect();

	// Make sure we let go of the pointer and keyboard ...
	gdk_pointer_ungrab (GDK_CURRENT_TIME);
	gdk_keyboard_ungrab (GDK_CURRENT_TIME);

	// Activate it ...
	targetitem.InteractiveActivate();

	return true;
}

bool sdpGtkObjectContainer::InteractiveSetText(SDPCSTRING Name, SDPCSTRING Value, const gdouble Speed, const bool Pause)
{
	// Sanity checks ...
	g_assert_string(Name);

	sdpGtkEditable editable = Editable(Name);
	g_return_val_if_fail(editable.Attached(), false);

	editable.InteractiveShow(Speed, Pause);
	editable.InteractiveWarpPointer(Speed, Pause, false);
	editable.InteractiveSetText(Value, Speed);

	return true;
}

bool sdpGtkObjectContainer::InteractiveMoveTo(SDPCSTRING Name, const gdouble Speed, const bool Pause)
{
	// Sanity checks ...
	g_assert_string(Name);

	sdpGtkWidget widget = Widget(Name);
	g_return_val_if_fail(widget.Attached(), false);

	widget.InteractiveShow(Speed, Pause);
	widget.InteractiveWarpPointer(Speed, Pause, false);

	return true;
}

//////////////////////////////////////////////////////////////////////////
// Control-access functions

static void ErrorUnknownWidget(SDPCSTRING ControlName)
{
	std::cout << "sdpGtkObjectContainer: unknown widget \"" << ControlName << "\"" << std::endl;
}

static void ErrorTypecast(SDPCSTRING ControlName, SDPCSTRING Type)
{
	std::cout << "sdpGtkObjectContainer: widget \"" << ControlName << "\" is not a " << Type << std::endl;
}

#define SDPGTKCONTROLACCESS(MethodName, Class, Typecast, Test)															\
	Class sdpGtkObjectContainer::MethodName(SDPCSTRING ControlName)														\
	{																																													\
		GtkObject* object = m_Objects[ControlName];																						\
																																														\
		if(!object)																																							\
			ErrorUnknownWidget(ControlName);																											\
																																														\
		if(!Test(object))																																				\
			ErrorTypecast(ControlName, #Typecast);																								\
																																														\
		return Class(Typecast(object));																													\
	}

SDPGTKCONTROLACCESS(AccelLabel, sdpGtkAccelLabel, GTK_ACCEL_LABEL, GTK_IS_ACCEL_LABEL);
SDPGTKCONTROLACCESS(Adjustment, sdpGtkAdjustment, GTK_ADJUSTMENT, GTK_IS_ADJUSTMENT);
SDPGTKCONTROLACCESS(Alignment, sdpGtkAlignment, GTK_ALIGNMENT, GTK_IS_ALIGNMENT);
SDPGTKCONTROLACCESS(Arrow, sdpGtkArrow, GTK_ARROW, GTK_IS_ARROW);
SDPGTKCONTROLACCESS(AspectFrame, sdpGtkAspectFrame, GTK_ASPECT_FRAME, GTK_IS_ASPECT_FRAME);
SDPGTKCONTROLACCESS(Bin, sdpGtkBin, GTK_BIN, GTK_IS_BIN);
SDPGTKCONTROLACCESS(Box, sdpGtkBox, GTK_BOX, GTK_IS_BOX);
SDPGTKCONTROLACCESS(Button, sdpGtkButton, GTK_BUTTON, GTK_IS_BUTTON);
SDPGTKCONTROLACCESS(ButtonBox, sdpGtkButtonBox, GTK_BUTTON_BOX, GTK_IS_BUTTON_BOX);
SDPGTKCONTROLACCESS(Calendar, sdpGtkCalendar, GTK_CALENDAR, GTK_IS_CALENDAR);
SDPGTKCONTROLACCESS(CheckButton, sdpGtkCheckButton, GTK_CHECK_BUTTON, GTK_IS_CHECK_BUTTON);
SDPGTKCONTROLACCESS(CheckMenuItem, sdpGtkCheckMenuItem, GTK_CHECK_MENU_ITEM, GTK_IS_CHECK_MENU_ITEM);
SDPGTKCONTROLACCESS(CList, sdpGtkCList, GTK_CLIST, GTK_IS_CLIST);
SDPGTKCONTROLACCESS(ColorSelection, sdpGtkColorSelection, GTK_COLOR_SELECTION, GTK_IS_COLOR_SELECTION);
SDPGTKCONTROLACCESS(ColorSelectionDialog, sdpGtkColorSelectionDialog, GTK_COLOR_SELECTION_DIALOG, GTK_IS_COLOR_SELECTION_DIALOG);
SDPGTKCONTROLACCESS(Combo, sdpGtkCombo, GTK_COMBO, GTK_IS_COMBO);
SDPGTKCONTROLACCESS(Container, sdpGtkContainer, GTK_CONTAINER, GTK_IS_CONTAINER);
SDPGTKCONTROLACCESS(CTree, sdpGtkCTree, GTK_CTREE, GTK_IS_CTREE);
SDPGTKCONTROLACCESS(Curve, sdpGtkCurve, GTK_CURVE, GTK_IS_CURVE);
SDPGTKCONTROLACCESS(Data, sdpGtkData, GTK_DATA, GTK_IS_DATA);
SDPGTKCONTROLACCESS(Dialog, sdpGtkDialog, GTK_DIALOG, GTK_IS_DIALOG);
SDPGTKCONTROLACCESS(DrawingArea, sdpGtkDrawingArea, GTK_DRAWING_AREA, GTK_IS_DRAWING_AREA);
SDPGTKCONTROLACCESS(Editable, sdpGtkEditable, GTK_EDITABLE, GTK_IS_EDITABLE);
SDPGTKCONTROLACCESS(Entry, sdpGtkEntry, GTK_ENTRY, GTK_IS_ENTRY);
SDPGTKCONTROLACCESS(EventBox, sdpGtkEventBox, GTK_EVENT_BOX, GTK_IS_EVENT_BOX);
SDPGTKCONTROLACCESS(FileSelection, sdpGtkFileSelection, GTK_FILE_SELECTION, GTK_IS_FILE_SELECTION);
SDPGTKCONTROLACCESS(Fixed, sdpGtkFixed, GTK_FIXED, GTK_IS_FIXED);
SDPGTKCONTROLACCESS(FontSelection, sdpGtkFontSelection, GTK_FONT_SELECTION, GTK_IS_FONT_SELECTION);
SDPGTKCONTROLACCESS(FontSelectionDialog, sdpGtkFontSelectionDialog, GTK_FONT_SELECTION_DIALOG, GTK_IS_FONT_SELECTION_DIALOG);
SDPGTKCONTROLACCESS(Frame, sdpGtkFrame, GTK_FRAME, GTK_IS_FRAME);
SDPGTKCONTROLACCESS(GammaCurve, sdpGtkGammaCurve, GTK_GAMMA_CURVE, GTK_IS_GAMMA_CURVE);
SDPGTKCONTROLACCESS(HandleBox, sdpGtkHandleBox, GTK_HANDLE_BOX, GTK_IS_HANDLE_BOX);
SDPGTKCONTROLACCESS(HBox, sdpGtkHBox, GTK_HBOX, GTK_IS_HBOX);
SDPGTKCONTROLACCESS(HButtonBox, sdpGtkHButtonBox, GTK_HBUTTON_BOX, GTK_IS_HBUTTON_BOX);
SDPGTKCONTROLACCESS(HPaned, sdpGtkHPaned, GTK_HPANED, GTK_IS_HPANED);
SDPGTKCONTROLACCESS(HRuler, sdpGtkHRuler, GTK_HRULER, GTK_IS_HRULER);
SDPGTKCONTROLACCESS(HScale, sdpGtkHScale, GTK_HSCALE, GTK_IS_HSCALE);
SDPGTKCONTROLACCESS(HScrollbar, sdpGtkHScrollbar, GTK_HSCROLLBAR, GTK_IS_HSCROLLBAR);
SDPGTKCONTROLACCESS(HSeparator, sdpGtkHSeparator, GTK_HSEPARATOR, GTK_IS_HSEPARATOR);
SDPGTKCONTROLACCESS(Image, sdpGtkImage, GTK_IMAGE, GTK_IS_IMAGE);
SDPGTKCONTROLACCESS(InputDialog, sdpGtkInputDialog, GTK_INPUT_DIALOG, GTK_IS_INPUT_DIALOG);
SDPGTKCONTROLACCESS(Item, sdpGtkItem, GTK_ITEM, GTK_IS_ITEM);
SDPGTKCONTROLACCESS(Label, sdpGtkLabel, GTK_LABEL, GTK_IS_LABEL);
SDPGTKCONTROLACCESS(List, sdpGtkList, GTK_LIST, GTK_IS_LIST);
SDPGTKCONTROLACCESS(ListItem, sdpGtkListItem, GTK_LIST_ITEM, GTK_IS_LIST_ITEM);
SDPGTKCONTROLACCESS(Menu, sdpGtkMenu, GTK_MENU, GTK_IS_MENU);
SDPGTKCONTROLACCESS(MenuBar, sdpGtkMenuBar, GTK_MENU_BAR, GTK_IS_MENU_BAR);
SDPGTKCONTROLACCESS(MenuItem, sdpGtkMenuItem, GTK_MENU_ITEM, GTK_IS_MENU_ITEM);
SDPGTKCONTROLACCESS(MenuShell, sdpGtkMenuShell, GTK_MENU_SHELL, GTK_IS_MENU_SHELL);
SDPGTKCONTROLACCESS(Misc, sdpGtkMisc, GTK_MISC, GTK_IS_MISC);
SDPGTKCONTROLACCESS(Notebook, sdpGtkNotebook, GTK_NOTEBOOK, GTK_IS_NOTEBOOK);
SDPGTKCONTROLACCESS(Object, sdpGtkObject, GTK_OBJECT, GTK_IS_OBJECT);
SDPGTKCONTROLACCESS(OptionMenu, sdpGtkOptionMenu, GTK_OPTION_MENU, GTK_IS_OPTION_MENU);
SDPGTKCONTROLACCESS(Paned, sdpGtkPaned, GTK_PANED, GTK_IS_PANED);
SDPGTKCONTROLACCESS(Pixmap, sdpGtkPixmap, GTK_PIXMAP, GTK_IS_PIXMAP);
SDPGTKCONTROLACCESS(Range, sdpGtkRange, GTK_RANGE, GTK_IS_RANGE);
SDPGTKCONTROLACCESS(Scrollbar, sdpGtkScrollbar, GTK_SCROLLBAR, GTK_IS_SCROLLBAR);
SDPGTKCONTROLACCESS(ScrolledWindow, sdpGtkScrolledWindow, GTK_SCROLLED_WINDOW, GTK_IS_SCROLLED_WINDOW);
SDPGTKCONTROLACCESS(Separator, sdpGtkSeparator, GTK_SEPARATOR, GTK_IS_SEPARATOR);
SDPGTKCONTROLACCESS(Socket, sdpGtkSocket, GTK_SOCKET, GTK_IS_SOCKET);
SDPGTKCONTROLACCESS(SpinButton, sdpGtkSpinButton, GTK_SPIN_BUTTON, GTK_IS_SPIN_BUTTON);
SDPGTKCONTROLACCESS(Statusbar, sdpGtkStatusbar, GTK_STATUSBAR, GTK_IS_STATUSBAR);
SDPGTKCONTROLACCESS(Table, sdpGtkTable, GTK_TABLE, GTK_IS_TABLE);
SDPGTKCONTROLACCESS(TearoffMenuItem, sdpGtkTearoffMenuItem, GTK_TEAROFF_MENU_ITEM, GTK_IS_TEAROFF_MENU_ITEM);
SDPGTKCONTROLACCESS(Text, sdpGtkText, GTK_TEXT, GTK_IS_TEXT);
SDPGTKCONTROLACCESS(TipsQuery, sdpGtkTipsQuery, GTK_TIPS_QUERY, GTK_IS_TIPS_QUERY);
SDPGTKCONTROLACCESS(ToggleButton, sdpGtkToggleButton, GTK_TOGGLE_BUTTON, GTK_IS_TOGGLE_BUTTON);
SDPGTKCONTROLACCESS(Toolbar, sdpGtkToolbar, GTK_TOOLBAR, GTK_IS_TOOLBAR);
SDPGTKCONTROLACCESS(Tooltips, sdpGtkTooltips, GTK_TOOLTIPS, GTK_IS_TOOLTIPS);
SDPGTKCONTROLACCESS(Tree, sdpGtkTree, GTK_TREE, GTK_IS_TREE);
SDPGTKCONTROLACCESS(TreeItem, sdpGtkTreeItem, GTK_TREE_ITEM, GTK_IS_TREE_ITEM);
SDPGTKCONTROLACCESS(VBox, sdpGtkVBox, GTK_VBOX, GTK_IS_VBOX);
SDPGTKCONTROLACCESS(VButtonBox, sdpGtkVButtonBox, GTK_VBUTTON_BOX, GTK_IS_VBUTTON_BOX);
SDPGTKCONTROLACCESS(Viewport, sdpGtkViewport, GTK_VIEWPORT, GTK_IS_VIEWPORT);
SDPGTKCONTROLACCESS(VPaned, sdpGtkVPaned, GTK_VPANED, GTK_IS_VPANED);
SDPGTKCONTROLACCESS(VRuler, sdpGtkVRuler, GTK_VRULER, GTK_IS_VRULER);
SDPGTKCONTROLACCESS(VScale, sdpGtkVScale, GTK_VSCALE, GTK_IS_VSCALE);
SDPGTKCONTROLACCESS(VScrollbar, sdpGtkVScrollbar, GTK_VSCROLLBAR, GTK_IS_VSCROLLBAR);
SDPGTKCONTROLACCESS(VSeparator, sdpGtkVSeparator, GTK_VSEPARATOR, GTK_IS_VSEPARATOR);
SDPGTKCONTROLACCESS(Widget, sdpGtkWidget, GTK_WIDGET, GTK_IS_WIDGET);
SDPGTKCONTROLACCESS(Window, sdpGtkWindow, GTK_WINDOW, GTK_IS_WINDOW);

static void ErrorRootTypecast(SDPCSTRING Type)
{
	std::cout << "sdpGtkObjectContainer: root object is not a " << Type << std::endl;
}

#define SDPGTKROOTCONTROLACCESS(MethodName, Class, Typecast, Test)													\
	Class sdpGtkObjectContainer::MethodName()																									\
	{																																													\
		GtkObject* object = Root();																												\
																																														\
		if(!Test(object))																																				\
			ErrorRootTypecast(#Typecast);																								\
																																														\
		return Class(Typecast(object));																													\
	}

SDPGTKROOTCONTROLACCESS(RootAccelLabel, sdpGtkAccelLabel, GTK_ACCEL_LABEL, GTK_IS_ACCEL_LABEL);
SDPGTKROOTCONTROLACCESS(RootAdjustment, sdpGtkAdjustment, GTK_ADJUSTMENT, GTK_IS_ADJUSTMENT);
SDPGTKROOTCONTROLACCESS(RootAlignment, sdpGtkAlignment, GTK_ALIGNMENT, GTK_IS_ALIGNMENT);
SDPGTKROOTCONTROLACCESS(RootArrow, sdpGtkArrow, GTK_ARROW, GTK_IS_ARROW);
SDPGTKROOTCONTROLACCESS(RootAspectFrame, sdpGtkAspectFrame, GTK_ASPECT_FRAME, GTK_IS_ASPECT_FRAME);
SDPGTKROOTCONTROLACCESS(RootBin, sdpGtkBin, GTK_BIN, GTK_IS_BIN);
SDPGTKROOTCONTROLACCESS(RootBox, sdpGtkBox, GTK_BOX, GTK_IS_BOX);
SDPGTKROOTCONTROLACCESS(RootButton, sdpGtkButton, GTK_BUTTON, GTK_IS_BUTTON);
SDPGTKROOTCONTROLACCESS(RootButtonBox, sdpGtkButtonBox, GTK_BUTTON_BOX, GTK_IS_BUTTON_BOX);
SDPGTKROOTCONTROLACCESS(RootCheckButton, sdpGtkCheckButton, GTK_CHECK_BUTTON, GTK_IS_CHECK_BUTTON);
SDPGTKROOTCONTROLACCESS(RootCheckMenuItem, sdpGtkCheckMenuItem, GTK_CHECK_MENU_ITEM, GTK_IS_CHECK_MENU_ITEM);
SDPGTKROOTCONTROLACCESS(RootCalendar, sdpGtkCalendar, GTK_CALENDAR, GTK_IS_CALENDAR);
SDPGTKROOTCONTROLACCESS(RootCList, sdpGtkCList, GTK_CLIST, GTK_IS_CLIST);
SDPGTKROOTCONTROLACCESS(RootColorSelection, sdpGtkColorSelection, GTK_COLOR_SELECTION, GTK_IS_COLOR_SELECTION);
SDPGTKROOTCONTROLACCESS(RootColorSelectionDialog, sdpGtkColorSelectionDialog, GTK_COLOR_SELECTION_DIALOG, GTK_IS_COLOR_SELECTION_DIALOG);
SDPGTKROOTCONTROLACCESS(RootCombo, sdpGtkCombo, GTK_COMBO, GTK_IS_COMBO);
SDPGTKROOTCONTROLACCESS(RootContainer, sdpGtkContainer, GTK_CONTAINER, GTK_IS_CONTAINER);
SDPGTKROOTCONTROLACCESS(RootCTree, sdpGtkCTree, GTK_CTREE, GTK_IS_CTREE);
SDPGTKROOTCONTROLACCESS(RootCurve, sdpGtkCurve, GTK_CURVE, GTK_IS_CURVE);
SDPGTKROOTCONTROLACCESS(RootData, sdpGtkData, GTK_DATA, GTK_IS_DATA);
SDPGTKROOTCONTROLACCESS(RootDialog, sdpGtkDialog, GTK_DIALOG, GTK_IS_DIALOG);
SDPGTKROOTCONTROLACCESS(RootDrawingArea, sdpGtkDrawingArea, GTK_DRAWING_AREA, GTK_IS_DRAWING_AREA);
SDPGTKROOTCONTROLACCESS(RootEditable, sdpGtkEditable, GTK_EDITABLE, GTK_IS_EDITABLE);
SDPGTKROOTCONTROLACCESS(RootEntry, sdpGtkEntry, GTK_ENTRY, GTK_IS_ENTRY);
SDPGTKROOTCONTROLACCESS(RootEventBox, sdpGtkEventBox, GTK_EVENT_BOX, GTK_IS_EVENT_BOX);
SDPGTKROOTCONTROLACCESS(RootFileSelection, sdpGtkFileSelection, GTK_FILE_SELECTION, GTK_IS_FILE_SELECTION);
SDPGTKROOTCONTROLACCESS(RootFixed, sdpGtkFixed, GTK_FIXED, GTK_IS_FIXED);
SDPGTKROOTCONTROLACCESS(RootFontSelection, sdpGtkFontSelection, GTK_FONT_SELECTION, GTK_IS_FONT_SELECTION);
SDPGTKROOTCONTROLACCESS(RootFontSelectionDialog, sdpGtkFontSelectionDialog, GTK_FONT_SELECTION_DIALOG, GTK_IS_FONT_SELECTION_DIALOG);
SDPGTKROOTCONTROLACCESS(RootFrame, sdpGtkFrame, GTK_FRAME, GTK_IS_FRAME);
SDPGTKROOTCONTROLACCESS(RootGammaCurve, sdpGtkGammaCurve, GTK_GAMMA_CURVE, GTK_IS_GAMMA_CURVE);
SDPGTKROOTCONTROLACCESS(RootHandleBox, sdpGtkHandleBox, GTK_HANDLE_BOX, GTK_IS_HANDLE_BOX);
SDPGTKROOTCONTROLACCESS(RootHBox, sdpGtkHBox, GTK_HBOX, GTK_IS_HBOX);
SDPGTKROOTCONTROLACCESS(RootHButtonBox, sdpGtkHButtonBox, GTK_HBUTTON_BOX, GTK_IS_HBUTTON_BOX);
SDPGTKROOTCONTROLACCESS(RootHPaned, sdpGtkHPaned, GTK_HPANED, GTK_IS_HPANED);
SDPGTKROOTCONTROLACCESS(RootHRuler, sdpGtkHRuler, GTK_HRULER, GTK_IS_HRULER);
SDPGTKROOTCONTROLACCESS(RootHScale, sdpGtkHScale, GTK_HSCALE, GTK_IS_HSCALE);
SDPGTKROOTCONTROLACCESS(RootHScrollbar, sdpGtkHScrollbar, GTK_HSCROLLBAR, GTK_IS_HSCROLLBAR);
SDPGTKROOTCONTROLACCESS(RootHSeparator, sdpGtkHSeparator, GTK_HSEPARATOR, GTK_IS_HSEPARATOR);
SDPGTKROOTCONTROLACCESS(RootImage, sdpGtkImage, GTK_IMAGE, GTK_IS_IMAGE);
SDPGTKROOTCONTROLACCESS(RootInputDialog, sdpGtkInputDialog, GTK_INPUT_DIALOG, GTK_IS_INPUT_DIALOG);
SDPGTKROOTCONTROLACCESS(RootItem, sdpGtkItem, GTK_ITEM, GTK_IS_ITEM);
SDPGTKROOTCONTROLACCESS(RootLabel, sdpGtkLabel, GTK_LABEL, GTK_IS_LABEL);
SDPGTKROOTCONTROLACCESS(RootList, sdpGtkList, GTK_LIST, GTK_IS_LIST);
SDPGTKROOTCONTROLACCESS(RootListItem, sdpGtkListItem, GTK_LIST_ITEM, GTK_IS_LIST_ITEM);
SDPGTKROOTCONTROLACCESS(RootMenu, sdpGtkMenu, GTK_MENU, GTK_IS_MENU);
SDPGTKROOTCONTROLACCESS(RootMenuBar, sdpGtkMenuBar, GTK_MENU_BAR, GTK_IS_MENU_BAR);
SDPGTKROOTCONTROLACCESS(RootMenuItem, sdpGtkMenuItem, GTK_MENU_ITEM, GTK_IS_MENU_ITEM);
SDPGTKROOTCONTROLACCESS(RootMenuShell, sdpGtkMenuShell, GTK_MENU_SHELL, GTK_IS_MENU_SHELL);
SDPGTKROOTCONTROLACCESS(RootMisc, sdpGtkMisc, GTK_MISC, GTK_IS_MISC);
SDPGTKROOTCONTROLACCESS(RootNotebook, sdpGtkNotebook, GTK_NOTEBOOK, GTK_IS_NOTEBOOK);
SDPGTKROOTCONTROLACCESS(RootObject, sdpGtkObject, GTK_OBJECT, GTK_IS_OBJECT);
SDPGTKROOTCONTROLACCESS(RootOptionMenu, sdpGtkOptionMenu, GTK_OPTION_MENU, GTK_IS_OPTION_MENU);
SDPGTKROOTCONTROLACCESS(RootPaned, sdpGtkPaned, GTK_PANED, GTK_IS_PANED);
SDPGTKROOTCONTROLACCESS(RootPixmap, sdpGtkPixmap, GTK_PIXMAP, GTK_IS_PIXMAP);
SDPGTKROOTCONTROLACCESS(RootRange, sdpGtkRange, GTK_RANGE, GTK_IS_RANGE);
SDPGTKROOTCONTROLACCESS(RootScrollbar, sdpGtkScrollbar, GTK_SCROLLBAR, GTK_IS_SCROLLBAR);
SDPGTKROOTCONTROLACCESS(RootScrolledWindow, sdpGtkScrolledWindow, GTK_SCROLLED_WINDOW, GTK_IS_SCROLLED_WINDOW);
SDPGTKROOTCONTROLACCESS(RootSeparator, sdpGtkSeparator, GTK_SEPARATOR, GTK_IS_SEPARATOR);
SDPGTKROOTCONTROLACCESS(RootSocket, sdpGtkSocket, GTK_SOCKET, GTK_IS_SOCKET);
SDPGTKROOTCONTROLACCESS(RootSpinButton, sdpGtkSpinButton, GTK_SPIN_BUTTON, GTK_IS_SPIN_BUTTON);
SDPGTKROOTCONTROLACCESS(RootStatusbar, sdpGtkStatusbar, GTK_STATUSBAR, GTK_IS_STATUSBAR);
SDPGTKROOTCONTROLACCESS(RootTable, sdpGtkTable, GTK_TABLE, GTK_IS_TABLE);
SDPGTKROOTCONTROLACCESS(RootTearoffMenuItem, sdpGtkTearoffMenuItem, GTK_TEAROFF_MENU_ITEM, GTK_IS_TEAROFF_MENU_ITEM);
SDPGTKROOTCONTROLACCESS(RootText, sdpGtkText, GTK_TEXT, GTK_IS_TEXT);
SDPGTKROOTCONTROLACCESS(RootTipsQuery, sdpGtkTipsQuery, GTK_TIPS_QUERY, GTK_IS_TIPS_QUERY);
SDPGTKROOTCONTROLACCESS(RootToggleButton, sdpGtkToggleButton, GTK_TOGGLE_BUTTON, GTK_IS_TOGGLE_BUTTON);
SDPGTKROOTCONTROLACCESS(RootToolbar, sdpGtkToolbar, GTK_TOOLBAR, GTK_IS_TOOLBAR);
SDPGTKROOTCONTROLACCESS(RootTooltips, sdpGtkTooltips, GTK_TOOLTIPS, GTK_IS_TOOLTIPS);
SDPGTKROOTCONTROLACCESS(RootTree, sdpGtkTree, GTK_TREE, GTK_IS_TREE);
SDPGTKROOTCONTROLACCESS(RootTreeItem, sdpGtkTreeItem, GTK_TREE_ITEM, GTK_IS_TREE_ITEM);
SDPGTKROOTCONTROLACCESS(RootVBox, sdpGtkVBox, GTK_VBOX, GTK_IS_VBOX);
SDPGTKROOTCONTROLACCESS(RootVButtonBox, sdpGtkVButtonBox, GTK_VBUTTON_BOX, GTK_IS_VBUTTON_BOX);
SDPGTKROOTCONTROLACCESS(RootViewport, sdpGtkViewport, GTK_VIEWPORT, GTK_IS_VIEWPORT);
SDPGTKROOTCONTROLACCESS(RootVPaned, sdpGtkVPaned, GTK_VPANED, GTK_IS_VPANED);
SDPGTKROOTCONTROLACCESS(RootVRuler, sdpGtkVRuler, GTK_VRULER, GTK_IS_VRULER);
SDPGTKROOTCONTROLACCESS(RootVScale, sdpGtkVScale, GTK_VSCALE, GTK_IS_VSCALE);
SDPGTKROOTCONTROLACCESS(RootVScrollbar, sdpGtkVScrollbar, GTK_VSCROLLBAR, GTK_IS_VSCROLLBAR);
SDPGTKROOTCONTROLACCESS(RootVSeparator, sdpGtkVSeparator, GTK_VSEPARATOR, GTK_IS_VSEPARATOR);
SDPGTKROOTCONTROLACCESS(RootWidget, sdpGtkWidget, GTK_WIDGET, GTK_IS_WIDGET);
SDPGTKROOTCONTROLACCESS(RootWindow, sdpGtkWindow, GTK_WINDOW, GTK_IS_WINDOW);


