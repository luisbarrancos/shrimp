
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
	\author Timothy M. Shead <tshead@k-3d.com>
	\author Dan Erikson <derikson@montana.com>
*/

#include "sdpgtkiobjectcontainer.h"
#include "sdpgtkwidgets.h"
#include "sdpgtkutility.h"

#include <iostream>

/////////////////////////////////////////////////////////////////////////////
// sdpGtkObject

sdpGtkObject::sdpGtkObject()
{
	m_Object = 0;
}

sdpGtkObject::sdpGtkObject(GtkObject* Object)
{
	m_Object = Object;
}

sdpGtkObject::~sdpGtkObject()
{
}

bool sdpGtkObject::Attached() const
{
	return m_Object ? true : false;
}

const sdpString sdpGtkObject::CustomType() const
{
	return sdpString("sdpGtkObject");
}

bool sdpGtkObject::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// This base-class implementation should never be called ...
	std::cerr << __PRETTY_FUNCTION__ << " should never be called at " << sdpxml::FileReference(Document, Element) << std::endl;
	return true;
}

bool sdpGtkObject::CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	return true;
}

static void sdpGtkLoadObject(sdpGtkObject& ParentObject, sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element, sdpGtkObject& NewObject)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	// Handle control options ...
	NewObject.CreateOptions(ObjectContainer, Document, Element);

	// Notify the object container about the new control ...
	ObjectContainer->NotifyObject(NewObject.Object());

	// If the control has a name, tell the object container to create a mapping ...
	const sdpString name = sdpxml::GetAttribute<sdpString>(Element, "name", "");
	sdpGtkMarkAttribute(Document, Element, "name");
	if(name.size())
		ObjectContainer->MapObject(name, NewObject.Object());

	// Recursively create children ...
	NewObject.CreateChildren(ObjectContainer, Document, Element);

	// Attach the object to its parent ...
	ParentObject.AttachChild(ObjectContainer, Document, Element, &NewObject);
}

static void sdpGtkLoadCustomObject(sdpGtkObject& ParentObject, sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element, sdpGtkObject& NewObject)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	// Handle control options ...
	NewObject.CreateOptions(ObjectContainer, Document, Element);

	// Notify the object container about the new control ...
	ObjectContainer->NotifyObject(NewObject.Object());

	// If the control has a name, tell the object container to create a mapping ...
	const sdpString name = sdpxml::GetAttribute<sdpString>(Element, "name", "");
	sdpGtkMarkAttribute(Document, Element, "name");
	if(name.size())
		ObjectContainer->MapCustomObject(name, &NewObject);

/*
	// Recursively create children ...
	NewObject.CreateChildren(ObjectContainer, Document, Element);
*/

	// Attach the object to its parent ...
	ParentObject.AttachChild(ObjectContainer, Document, Element, &NewObject);
}

// Once again, the prototype for this template function was *supposed* to be
// "static void", but the !@#$!$ MSVC++ 6 compiler can't seem to properly instantiate
// a template function unless the prototype contains the template arguments somewhere,
// even when you explicitly specify the template arguments in the function call (see below) ...
template<class Type>
static Type sdpGtkCreateObject(sdpGtkObject& ParentObject, sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Create the object ...
	Type object;
	if(!object.Create(ObjectContainer, Document, Element))
		{
			std::cout << "sdpGtk: Unable to create <" << Element.Name() << ">" << std::endl;
			g_return_val_if_fail(0, object);
		}

	// Give it a chance to load itself and its children ...
	sdpGtkLoadObject(ParentObject, ObjectContainer, Document, Element, object);

	return object;
}

static void sdpGtkCreateAccelerator(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element, GtkObject* Object)
{
	// Sanity checks ...
	g_assert(ObjectContainer);
	g_assert(Object);

	// Get the accelerator signal ...
	const sdpString signal = sdpxml::GetAttribute<sdpString>(Element, "signal", "");
	sdpGtkMarkAttribute(Document, Element, "signal");

	// Get the accelerator key ...
	const sdpString key = sdpxml::GetAttribute<sdpString>(Element, "key", "");
	sdpGtkMarkAttribute(Document, Element, "key");

	// Get the accelerator modifiers ...
	const sdpString modifiertext = sdpxml::GetAttribute<sdpString>(Element, "modifiers", "");
	sdpGtkMarkAttribute(Document, Element, "modifiers");

	guint modifiers = 0;
	if(modifiertext.find("shift") != sdpString::npos)
		modifiers |= GDK_SHIFT_MASK;
	if(modifiertext.find("lock") != sdpString::npos)
		modifiers |= GDK_LOCK_MASK;
	if(modifiertext.find("control") != sdpString::npos)
		modifiers |= GDK_CONTROL_MASK;
	if(modifiertext.find("mod1") != sdpString::npos)
		modifiers |= GDK_MOD1_MASK;
	if(modifiertext.find("mod2") != sdpString::npos)
		modifiers |= GDK_MOD2_MASK;
	if(modifiertext.find("mod3") != sdpString::npos)
		modifiers |= GDK_MOD3_MASK;
	if(modifiertext.find("mod4") != sdpString::npos)
		modifiers |= GDK_MOD4_MASK;
	if(modifiertext.find("mod5") != sdpString::npos)
		modifiers |= GDK_MOD5_MASK;
	if(modifiertext.find("button1") != sdpString::npos)
		modifiers |= GDK_BUTTON1_MASK;
	if(modifiertext.find("button2") != sdpString::npos)
		modifiers |= GDK_BUTTON2_MASK;
	if(modifiertext.find("button3") != sdpString::npos)
		modifiers |= GDK_BUTTON3_MASK;
	if(modifiertext.find("button4") != sdpString::npos)
		modifiers |= GDK_BUTTON4_MASK;
	if(modifiertext.find("button5") != sdpString::npos)
		modifiers |= GDK_BUTTON5_MASK;
	if(modifiertext.find("release") != sdpString::npos)
		modifiers |= GDK_RELEASE_MASK;

	// Get the accelerator flags ...
	const bool visible = sdpxml::GetAttribute(Element, "visible", true);
	sdpGtkMarkAttribute(Document, Element, "visible");

	const GtkAccelFlags flags = GtkAccelFlags(visible ? GTK_ACCEL_VISIBLE : 0);

	// Get the current accelerator group ...
	GtkAccelGroup* const group = ObjectContainer->GetAcceleratorGroup();
	g_assert(group);

	// Sanity checks ...
	if(1 != key.size())
		{
			std::cerr << "Couldn't create accelerator for signal [" << signal << "] key [" << key << "] modifiers [" << modifiertext << "]" << std::endl;
			g_return_if_fail(0);
		}

	gtk_widget_add_accelerator(GTK_WIDGET(Object), signal, group, *key.begin(), modifiers, flags);
}

static void sdpGtkCreateResource(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	const sdpString resourcename = sdpxml::GetAttribute<sdpString>(Element, "name", "");
	sdpGtkMarkAttribute(Document, Element, "name");
	if(0 == resourcename.size())
		{
			std::cerr << "Anonymous resource not allowed at " << sdpxml::FileReference(Document, Element) << std::endl;
			return;
		}

	const sdpString resourcevalue = sdpxml::GetAttribute<sdpString>(Element, "value", "");
	sdpGtkMarkAttribute(Document, Element, "value");

	ObjectContainer->MapResource(resourcename, resourcevalue);
}

bool sdpGtkObject::CreateChildren(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	// For each child element ...
	for(sdpxml::ElementCollection::iterator childelement = Element.Children().begin(); childelement != Element.Children().end(); childelement++)
		{
			CreateChild(ObjectContainer, Document, *childelement);
		}

	return true;
}

void sdpGtkObject::CreateChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement)
{
	// Get the element name ...
	const sdpString name = ChildElement.Name();

	// If it's a control, create it ...
	if(name == "accellabel") { sdpGtkCreateObject<sdpGtkAccelLabel>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "adjustment") { sdpGtkCreateObject<sdpGtkAdjustment>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "alignment") { sdpGtkCreateObject<sdpGtkAlignment>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "arrow") { sdpGtkCreateObject<sdpGtkArrow>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "aspectframe") { sdpGtkCreateObject<sdpGtkAspectFrame>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "button") { sdpGtkCreateObject<sdpGtkButton>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "calendar") { sdpGtkCreateObject<sdpGtkCalendar>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "checkbutton") { sdpGtkCreateObject<sdpGtkCheckButton>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "checkmenuitem") { sdpGtkCreateObject<sdpGtkCheckMenuItem>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "clist") { sdpGtkCreateObject<sdpGtkCList>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "colorselection") { sdpGtkCreateObject<sdpGtkColorSelection>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "colorselectiondialog") { sdpGtkCreateObject<sdpGtkColorSelectionDialog>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "combo") { sdpGtkCreateObject<sdpGtkCombo>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "ctree") { sdpGtkCreateObject<sdpGtkCTree>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "curve") { sdpGtkCreateObject<sdpGtkCurve>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "dialog") { sdpGtkCreateObject<sdpGtkDialog>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "drawingarea") { sdpGtkCreateObject<sdpGtkDrawingArea>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "entry") { sdpGtkCreateObject<sdpGtkEntry>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "eventbox") { sdpGtkCreateObject<sdpGtkEventBox>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "fileselection") { sdpGtkCreateObject<sdpGtkFileSelection>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "fixed") { sdpGtkCreateObject<sdpGtkFixed>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "fontselection") { sdpGtkCreateObject<sdpGtkFontSelection>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "fontselectiondialog") { sdpGtkCreateObject<sdpGtkFontSelectionDialog>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "frame") { sdpGtkCreateObject<sdpGtkFrame>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "gammacurve") { sdpGtkCreateObject<sdpGtkGammaCurve>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "handlebox") { sdpGtkCreateObject<sdpGtkHandleBox>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "hbox") { sdpGtkCreateObject<sdpGtkHBox>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "hbuttonbox") { sdpGtkCreateObject<sdpGtkHButtonBox>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "hpaned") { sdpGtkCreateObject<sdpGtkHPaned>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "hruler") { sdpGtkCreateObject<sdpGtkHRuler>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "hscale") { sdpGtkCreateObject<sdpGtkHScale>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "hscrollbar") { sdpGtkCreateObject<sdpGtkHScrollbar>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "hseparator") { sdpGtkCreateObject<sdpGtkHSeparator>(*this, ObjectContainer, Document, ChildElement); return; }
//			if(name == "image") { sdpGtkCreateObject<sdpGtkImage>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "inputdialog") { sdpGtkCreateObject<sdpGtkInputDialog>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "label") { sdpGtkCreateObject<sdpGtkLabel>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "list") { sdpGtkCreateObject<sdpGtkList>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "listitem") { sdpGtkCreateObject<sdpGtkListItem>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "menu") { sdpGtkCreateObject<sdpGtkMenu>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "menubar") { sdpGtkCreateObject<sdpGtkMenuBar>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "menuitem") { sdpGtkCreateObject<sdpGtkMenuItem>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "notebook") { sdpGtkCreateObject<sdpGtkNotebook>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "optionmenu") { sdpGtkCreateObject<sdpGtkOptionMenu>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "pixmap") { sdpGtkCreateObject<sdpGtkPixmap>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "radiobutton") { sdpGtkCreateObject<sdpGtkRadioButton>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "radiomenuitem") { sdpGtkCreateObject<sdpGtkRadioMenuItem>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "scrolledwindow") { sdpGtkCreateObject<sdpGtkScrolledWindow>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "socket") { sdpGtkCreateObject<sdpGtkSocket>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "spinbutton") { sdpGtkCreateObject<sdpGtkSpinButton>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "statusbar") { sdpGtkCreateObject<sdpGtkStatusbar>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "table") { sdpGtkCreateObject<sdpGtkTable>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "tearoffmenuitem") { sdpGtkCreateObject<sdpGtkTearoffMenuItem>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "text") { sdpGtkCreateObject<sdpGtkText>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "tipsquery") { sdpGtkCreateObject<sdpGtkTipsQuery>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "togglebutton") { sdpGtkCreateObject<sdpGtkToggleButton>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "toolbar") { sdpGtkCreateObject<sdpGtkToolbar>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "tooltips") { sdpGtkCreateObject<sdpGtkTooltips>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "tree") { sdpGtkCreateObject<sdpGtkTree>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "treeitem") { sdpGtkCreateObject<sdpGtkTreeItem>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "vbox") { sdpGtkCreateObject<sdpGtkVBox>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "vbuttonbox") { sdpGtkCreateObject<sdpGtkVButtonBox>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "vpaned") { sdpGtkCreateObject<sdpGtkVPaned>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "vruler") { sdpGtkCreateObject<sdpGtkVRuler>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "vscale") { sdpGtkCreateObject<sdpGtkVScale>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "vscrollbar") { sdpGtkCreateObject<sdpGtkVScrollbar>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "vseparator") { sdpGtkCreateObject<sdpGtkVSeparator>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "viewport") { sdpGtkCreateObject<sdpGtkViewport>(*this, ObjectContainer, Document, ChildElement); return; }
	if(name == "window") { sdpGtkCreateObject<sdpGtkWindow>(*this, ObjectContainer, Document, ChildElement); return; }

	// Handle events ...
	if(name == "event") { ObjectContainer->MapEvent(Document, ChildElement, Object(), false); return; }

	// Handle accelerators ...
	if(name == "accelerator") { sdpGtkCreateAccelerator(ObjectContainer, Document, ChildElement, Object()); return; }

	// Handle resources ...
	if(name == "resource") { sdpGtkCreateResource(ObjectContainer, Document, ChildElement); return; }

	// Handle custom objects ...
	sdpGtkObject* const customobject = ObjectContainer->CreateCustomObject(ChildElement);
	if(customobject)
		{
			customobject->Create(ObjectContainer, Document, ChildElement);
			sdpGtkLoadCustomObject(*this, ObjectContainer, Document, ChildElement, *customobject);
			return;
		}

	// If it's an internationalization tag, ignore it ...
	if(name == "i18n") { return; }

	// If we made it this far, it's an unknown widget type!
	std::cout << "Unknown widget type <" << name << "> and children will not be loaded at " << sdpxml::FileReference(Document, ChildElement) << std::endl;
	return;
}

bool sdpGtkObject::AttachChild(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& ChildElement, sdpGtkObject* Child)
{
	return true;
}

void sdpGtkObject::SetData(SDPCSTRING Name, gpointer Value)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	g_return_if_string_fail(Name);

	gtk_object_set_data(*this, Name, Value);
}

gpointer sdpGtkObject::GetData(SDPCSTRING Name)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);
	g_return_val_if_string_fail(Name, 0);

	return gtk_object_get_data(*this, Name);
}

void sdpGtkObject::RemoveData(SDPCSTRING Name)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	g_return_if_string_fail(Name);

	gtk_object_remove_data(*this, Name);
}


