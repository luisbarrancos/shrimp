
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

#include "sdpgtkwidget.h"
#include "sdpgtkmenuitem.h"
#include "sdpgtkscreenoverlay.h"
#include "sdpgtktooltips.h"
#include "sdpgtkutility.h"



#include <iostream>
#include <stdlib.h>

sdpGtkWidget::sdpGtkWidget() : sdpGtkObject()
{
}

sdpGtkWidget::sdpGtkWidget(GtkWidget* Widget) : sdpGtkObject(GTK_OBJECT(Widget))
{
}

sdpGtkWidget::~sdpGtkWidget()
{
}

void sdpGtkWidget::Reference()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_widget_ref(*this);
}

void sdpGtkWidget::UnReference()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_widget_unref(*this);
}

void sdpGtkWidget::Destroy()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_widget_destroy(*this);
	m_Object = 0;
}

void sdpGtkWidget::Map()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_widget_map(*this);
}

void sdpGtkWidget::UnMap()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_widget_unmap(*this);
}

void sdpGtkWidget::Realize()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_widget_realize(*this);
}

void sdpGtkWidget::UnRealize()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_widget_unrealize(*this);
}

void sdpGtkWidget::SetState(GtkStateType State)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_widget_set_state(*this, State);
}

void sdpGtkWidget::UnParent()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_widget_unparent(*this);
}

void sdpGtkWidget::SetParent(GtkWidget* Parent)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	g_assert(Parent);

	gtk_widget_set_parent(*this, Parent);
}

void sdpGtkWidget::SetParentWindow(GdkWindow* Parent)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	g_assert(Parent);

	gtk_widget_set_parent_window(*this, Parent);
}

GdkWindow* sdpGtkWidget::GetParentWindow()
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return gtk_widget_get_parent_window(*this);
}

void sdpGtkWidget::Reparent(GtkWidget* NewParent)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	g_assert(NewParent);

	gtk_widget_reparent(*this, NewParent);
}

GtkWidget* sdpGtkWidget::GetParent()
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	if(GTK_IS_MENU(m_Object))
		return gtk_menu_get_attach_widget(GTK_MENU(m_Object));

	return GTK_WIDGET(m_Object)->parent;
}

GtkWidget* sdpGtkWidget::GetTopLevel()
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return gtk_widget_get_toplevel(*this);
}

GtkWidget* sdpGtkWidget::GetAncestor(GtkType WidgetType)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return gtk_widget_get_ancestor(*this, WidgetType);
}

gint sdpGtkWidget::IsAncestor(GtkWidget* Child)
{
	// Sanity checks ...
	g_assert(Child);
	g_return_val_if_fail(Attached(), -1);

	return gtk_widget_is_ancestor(Child, *this);
}

void sdpGtkWidget::SetName(SDPCSTRING Name)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	g_assert(Name);

	gtk_widget_set_name(*this, Name);
}

gchar* sdpGtkWidget::GetName()
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return gtk_widget_get_name(*this);
}

void sdpGtkWidget::SetCanFocus(bool CanFocus)
{
	if(CanFocus)
		GTK_OBJECT_SET_FLAGS(Object(), GTK_CAN_FOCUS);
	else
		GTK_OBJECT_UNSET_FLAGS(Object(), GTK_CAN_FOCUS);
}

bool sdpGtkWidget::GetCanFocus()
{
	return GTK_WIDGET_CAN_FOCUS(Object());
}

void sdpGtkWidget::SetCanDefault(bool CanDefault)
{
	if(CanDefault)
		GTK_OBJECT_SET_FLAGS(Object(), GTK_CAN_DEFAULT);
	else
		GTK_OBJECT_UNSET_FLAGS(Object(), GTK_CAN_DEFAULT);
}

bool sdpGtkWidget::GetCanDefault()
{
	return GTK_WIDGET_CAN_DEFAULT(Object());
}

void sdpGtkWidget::GetPath(guint* PathLength, gchar** Path, gchar** PathReversed)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	g_assert(PathLength);

	gtk_widget_path(*this, PathLength, Path, PathReversed);
}

void sdpGtkWidget::GetClassPath(guint* PathLength, gchar** Path, gchar** PathReversed)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	g_assert(PathLength);

	gtk_widget_class_path(*this, PathLength, Path, PathReversed);
}

void sdpGtkWidget::SetStyle(GtkStyle* Style)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	g_assert(Style);

	gtk_widget_set_style(*this, Style);
}

GtkStyle* sdpGtkWidget::GetStyle()
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return gtk_widget_get_style(*this);
}

GdkColormap* sdpGtkWidget::GetColormap()
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return gtk_widget_get_colormap(*this);
}

GdkVisual* sdpGtkWidget::GetVisual()
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return gtk_widget_get_visual(*this);
}

void sdpGtkWidget::EnsureStyle()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_widget_ensure_style(*this);
}

void sdpGtkWidget::RestoreDefaultStyle()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_widget_restore_default_style(*this);
}

void sdpGtkWidget::ModifyStyle(GtkRcStyle* Style)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	g_assert(Style);

	gtk_widget_modify_style(*this, Style);
}

void sdpGtkWidget::SetSensitive(bool Sensitive)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_widget_set_sensitive(*this, Sensitive);
}

void sdpGtkWidget::CombineShapeMask(GdkBitmap* Mask, gint OffsetX, gint OffsetY)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	g_assert(Mask);

	gtk_widget_shape_combine_mask(*this, Mask, OffsetX, OffsetY);
}

void sdpGtkWidget::ResetShapeMask()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_widget_reset_shapes(*this);
}

void sdpGtkWidget::Show()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_widget_show(*this);
}

void sdpGtkWidget::ShowNow()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_widget_show_now(*this);
}

void sdpGtkWidget::ShowAll()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_widget_show_all(*this);
}

void sdpGtkWidget::Hide()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_widget_hide(*this);
}

void sdpGtkWidget::HideAll()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_widget_hide_all(*this);
}

void sdpGtkWidget::QueueDraw()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_widget_queue_draw(*this);
}

void sdpGtkWidget::QueueDrawArea(gint Left, gint Top, gint Width, gint Height)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_widget_queue_draw_area(*this, Left, Top, Width, Height);
}

void sdpGtkWidget::QueueClear()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_widget_queue_clear(*this);
}

void sdpGtkWidget::QueueClearArea(gint Left, gint Top, gint Width, gint Height)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_widget_queue_clear_area(*this, Left, Top, Width, Height);
}

void sdpGtkWidget::Draw(GdkRectangle* Area)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
//	g_assert(Area);

	gtk_widget_draw(*this, Area);
}

void sdpGtkWidget::DrawFocus()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_widget_draw_focus(*this);
}

void sdpGtkWidget::DrawDefault()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_widget_draw_default(*this);
}

void sdpGtkWidget::QueueResize()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_widget_queue_resize(*this);
}

void sdpGtkWidget::SizeRequest(GtkRequisition* Requisition)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	g_assert(Requisition);

	gtk_widget_size_request(*this, Requisition);
}

void sdpGtkWidget::SizeAllocate(GtkAllocation* Allocation)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	g_assert(Allocation);

	gtk_widget_size_allocate(*this, Allocation);
}

void sdpGtkWidget::GetChildRequisition(GtkRequisition* Requisition)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	g_assert(Requisition);

	gtk_widget_get_child_requisition(*this, Requisition);
}

void sdpGtkWidget::AddAccelerator(SDPCSTRING Signal, GtkAccelGroup* Group, guint Key, guint Modifiers, GtkAccelFlags Flags)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	g_assert_string(Signal);
	g_assert(Group);

	gtk_widget_add_accelerator(*this, Signal, Group, Key, Modifiers, Flags);
}

void sdpGtkWidget::RemoveAccelerator(GtkAccelGroup* Group, guint Key, guint Modifiers)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	g_assert(Group);

	gtk_widget_remove_accelerator(*this, Group, Key, Modifiers);
}

void sdpGtkWidget::RemoveAccelerators(SDPCSTRING Signal, bool VisibleOnly)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	g_assert_string(Signal);

	gtk_widget_remove_accelerators(*this, Signal, VisibleOnly);
}

void sdpGtkWidget::LockAccelerators()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_widget_lock_accelerators(*this);
}

void sdpGtkWidget::UnlockAccelerators()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_widget_unlock_accelerators(*this);
}

bool sdpGtkWidget::AcceleratorsLocked()
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), false);

	return gtk_widget_accelerators_locked(*this) ? true : false;
}

void sdpGtkWidget::SetPosition(gint Left, gint Top)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_widget_set_uposition(*this, Left, Top);
}

gint sdpGtkWidget::Left() const
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), -1);

	return GTK_WIDGET(m_Object)->allocation.x;
}

gint sdpGtkWidget::Top() const
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), -1);

	return GTK_WIDGET(m_Object)->allocation.y;
}

gint sdpGtkWidget::Width() const
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), -1);

	return GTK_WIDGET(m_Object)->allocation.width;
}

gint sdpGtkWidget::Height() const
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), -1);

	return GTK_WIDGET(m_Object)->allocation.height;
}

void sdpGtkWidget::SetSize(gint Width, gint Height)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_widget_set_usize(*this, Width, Height);
}

void sdpGtkWidget::SetCharacterSize(gdouble Width, gdouble Height)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	const static sdpString metrictext("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_^");

	GtkWidget* widget = *this;

	gint lbearing = 0;
	gint rbearing = 0;
	gint width = 0;
	gint ascent = 0;
	gint descent = 0;

	gdk_string_extents(widget->style->font, metrictext, &lbearing, &rbearing, &width, &ascent, &descent);

	gdouble averagewidth = gdouble(lbearing + width + rbearing) / gdouble(metrictext.size());
	gdouble averageheight = gdouble(ascent + descent);

	gdouble targetwidth = Width * averagewidth;
	gdouble targetheight = Height * averageheight;

	gtk_widget_set_usize(widget, gint(targetwidth) + widget->style->klass->xthickness, gint(targetheight) + widget->style->klass->ythickness);
}

void sdpGtkWidget::Activate()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_widget_activate(*this);
}

void sdpGtkWidget::GrabAdd()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_grab_add(*this);
}

void sdpGtkWidget::GrabRemove()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_grab_remove(*this);
}

void sdpGtkWidget::GrabFocus()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_widget_grab_focus(*this);
}

void sdpGtkWidget::GrabDefault()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_widget_grab_default(*this);
}

void sdpGtkWidget::SetDragSource(GdkModifierType StartButton, GtkTargetEntry* TargetArray, gint TargetCount, GdkDragAction DragAction)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	g_assert(TargetArray);
	g_assert(TargetCount);

	gtk_drag_source_set(*this, StartButton, TargetArray, TargetCount, DragAction);
}

void sdpGtkWidget::RemoveDragSource()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	// Not implemented, yet!
	g_return_if_fail(0);

//	gtk_drag_source_unset(*this);
}

void sdpGtkWidget::SetDragDestination(GtkDestDefaults Flags, GtkTargetEntry* TargetArray, gint TargetCount, GdkDragAction DragAction)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	g_assert(TargetArray);
	g_assert(TargetCount);

	gtk_drag_dest_set(*this, Flags, TargetArray, TargetCount, DragAction);
}

void sdpGtkWidget::RemoveDragDestination()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_drag_dest_unset(*this);
}

void sdpGtkWidget::GetPointer(gint* X, gint* Y)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_widget_get_pointer(*this, X, Y);
}

void sdpGtkWidget::Popup(gint X, gint Y)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_widget_popup(*this, X, Y);
}

gint sdpGtkWidget::Intersect(GdkRectangle* Area, GdkRectangle* Intersection)
{
	// Sanity checks ...
	g_assert(Area);
	g_assert(Intersection);
	g_return_val_if_fail(Attached(), -1);

	return gtk_widget_intersect(*this, Area, Intersection);
}

bool sdpGtkWidget::CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	// Size (in pixels) ...
	const sdpVector2 size = sdpxml::GetAttribute(Element, "size", sdpVector2(0.0, 0.0));
	sdpGtkMarkAttribute(Document, Element, "size");
	if(size[0] && size[1])
		SetSize(gint(size[0]), gint(size[1]));

	// Size (in characters) ...
	const sdpVector2 charactersize = sdpxml::GetAttribute(Element, "charactersize", sdpVector2(0.0, 0.0));
	sdpGtkMarkAttribute(Document, Element, "charactersize");
	if(charactersize[0] && charactersize[1])
		SetCharacterSize(charactersize[0], charactersize[1]);

	const bool can_default = sdpxml::GetAttribute<bool>(Element, "can-default", GetCanDefault());
	sdpGtkMarkAttribute(Document, Element, "can-default");
	SetCanDefault(can_default);

	const bool can_focus = sdpxml::GetAttribute<bool>(Element, "can-focus", GetCanFocus());
	sdpGtkMarkAttribute(Document, Element, "can-focus");
	SetCanFocus(can_focus);

	const bool grab_default = sdpxml::GetAttribute<bool>(Element, "default", false);
	sdpGtkMarkAttribute(Document, Element, "default");
	if(grab_default)
		GrabDefault();

	// Drag-and-drop ...
	const sdpString dragsource = sdpxml::GetAttribute<sdpString>(Element, "dragsource", "");
	sdpGtkMarkAttribute(Document, Element, "dragsource");
	if(dragsource.size())
		{
			gchar* temp = const_cast<gchar*>(SDPCSTRING(dragsource));
			GtkTargetEntry targets[] = {{temp, 0, 1}};
			SetDragSource(GDK_MODIFIER_MASK, targets, 1, GDK_ACTION_DEFAULT);
		}

	const sdpString dragdestination = sdpxml::GetAttribute<sdpString>(Element, "dragdestination", "");
	sdpGtkMarkAttribute(Document, Element, "dragdestination");
	if(dragdestination.size())
		{
			gchar* temp = const_cast<gchar*>(SDPCSTRING(dragdestination));
			GtkTargetEntry targets[] = {{temp, 0, 1}};
			SetDragDestination(GTK_DEST_DEFAULT_ALL, targets, 1, GDK_ACTION_DEFAULT);
		}

	// Built-in tooltip support ...
	CreateTooltip(ObjectContainer, Document, Element);

	// Visibility ...
	const bool show = sdpxml::GetAttribute(Element, "show", true);
	sdpGtkMarkAttribute(Document, Element, "show");
	show ? Show() : Hide();

	return sdpGtkObject::CreateOptions(ObjectContainer, Document, Element);
}

// We have an unfortunate clash with windoze.h!
#ifdef SDPWIN32
#ifdef GetObject
#undef GetObject
#endif // GetObject
#endif // SDPWIN32

bool sdpGtkWidget::CreateTooltip(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// If a tooltip isn't specified, we're done ...
	sdpxml::AttributeCollection::iterator tooltip = std::find_if(Element.Attributes().begin(), Element.Attributes().end(), sdpxml::SameName("tooltip"));
	if(tooltip == Element.Attributes().end())
		return true;

	if(0 == tooltip->Value().size())
		return true;

	// Make sure the tooltip hasn't already been implemented (by a toolbar, for example) ...
	if(tooltip->Meta("usedby").size())
		return true;

	// Get the tooltip text ...
	sdpGtkMarkAttribute(Document, Element, "tooltip");

	// Get the built-in tooltips object ...
	GtkObject* tooltipsobject = ObjectContainer->GetObject("sdpgtk_tooltips");
	if(!tooltipsobject)
		{
			// built-in tooltips object doesn't exist, yet, so create it ...
			sdpGtkTooltips tooltips;
			g_assert(tooltips.Create());
			tooltips.Enable();

			ObjectContainer->MapObject("sdpgtk_tooltips", tooltips.Object());

			tooltipsobject = ObjectContainer->GetObject("sdpgtk_tooltips");
		}

	// Make sure we got the built-in tooltips object ...
	g_assert(tooltipsobject);

	// Add our tooltip ...
	sdpGtkTooltips(GTK_TOOLTIPS(tooltipsobject)).Set(*this, tooltip->Value());

	return true;
}

bool sdpGtkWidget::InteractiveShow(const gdouble Speed, const bool Pause)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), false);
	g_return_val_if_fail(Speed, false);

	// Build a list of parent widgets ...
	typedef std::vector<GtkWidget*> Widgets;
	Widgets widgets;

	for(GtkWidget* ancestor = *this; ancestor; )
		{
			widgets.push_back(ancestor);

			if(GTK_IS_MENU(ancestor))
				ancestor = gtk_menu_get_attach_widget (GTK_MENU(ancestor));
			else
				ancestor = ancestor->parent;
		}

	// The top-level item ought to be a window, so make sure it's visible
	if(GTK_IS_WINDOW(widgets.back()))
		{
			gdk_window_show(widgets.back()->window);
			gdk_window_raise(widgets.back()->window);
		}

	// Walk the list, switching notebook pages and opening menus as required
	bool topmenu = true;
	for(Widgets::reverse_iterator widget = widgets.rbegin(); widget != widgets.rend(); widget++)
		{
			if(GTK_IS_MENU_ITEM(*widget))
				{
					if(topmenu)
						{
							sdpGtkMenuItem(GTK_MENU_ITEM(*widget)).InteractiveWarpPointer(0.25, 0.5, Speed, Pause, false);
							topmenu = false;
						}
					else
						{
							sdpGtkMenuItem(GTK_MENU_ITEM(*widget)).InteractiveWarpPointer(0.25, 0.5, Speed, Pause, true); // Note: we move the pointer "Manhattan Style" so the child menu doesn't close
						}
					sdpGtkMenuItem(GTK_MENU_ITEM(*widget)).InteractiveSelect();
				}
			else if(GTK_IS_NOTEBOOK(*widget))
				{
					Widgets::reverse_iterator notebookchild = widget; notebookchild++;
					if(notebookchild == widgets.rbegin())
						continue;

					gint pagenumber = gtk_notebook_page_num(GTK_NOTEBOOK(*widget), *notebookchild);
					if(pagenumber == gtk_notebook_get_current_page(GTK_NOTEBOOK(*widget)))
						continue;

					GtkNotebookPage* page = 0;
					for(GList* list = GTK_NOTEBOOK(*widget)->children; list; list = list->next)
						{
							page = GTK_NOTEBOOK_PAGE(list);

							if(page->child == (*notebookchild))
								break;
						}
					g_return_val_if_fail(page, false);

					sdpGtkWidget(*widget).InteractiveWarpPointer(page->allocation.x + (page->allocation.width / 2), page->allocation.y + (page->allocation.height / 2), Speed, Pause, false);
					gtk_notebook_set_page(GTK_NOTEBOOK(*widget), pagenumber);
				}
		}

	return true;
}

static sdpVector2 sdpGtkHighlightCoords(const gdouble Radians, const gdouble Flatness, const gdouble XRadius, const gdouble YRadius, const sdpVector2 Center)
{
	gdouble arcx = cos(Radians);
	gdouble arcy = -sin(Radians);
	arcx = pow(fabs(arcx), Flatness) * sdpSign(arcx);
	arcy = pow(fabs(arcy), Flatness) * sdpSign(arcy);

	return sdpVector2(arcx * XRadius, arcy * YRadius) + Center;
}

bool sdpGtkWidget::InteractiveHighlight(const gdouble Speed, const bool Pause)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), false);
	g_return_val_if_fail(Speed, false);

	// Get widget position relative to the root window ...
	gint left = 0;
	gint top = 0;
	gdk_window_get_origin(GTK_WIDGET(m_Object)->window, &left, &top);

	gint width = Width();
	gint height = Height();

/* Simplified highlighting - draw a box over the widget
	// Create a screen overlay ...
	sdpGtkScreenOverlay overlay(left, top, width, height, sdpVector3(1, 0, 0));
	g_return_val_if_fail(overlay.Create(), false);

	gdk_draw_rectangle(overlay.Mask(), overlay.MaskGC(), TRUE, 0, 0, width, height);
	overlay.Update();

	sdpGtkSleep(1000);
*/

	// Expand the size of the box so we don't overlap the widget so much
	const gdouble size = std::max(width, height);
	const gdouble ratio = std::max(sdpLerp(0.15, 0.05, size / 500), 0.05);
	const gdouble padding = size * ratio;

	left -= gint(padding);
	top -= gint(padding);
	width += gint(padding) * 2;
	height += gint(padding) * 2;

	// Setup some parameters ...
	const gulong samples = 8;
	const gulong startangle = 70;
	const gdouble brushsize = 5;

	const gdouble flatness = std::max(sdpLerp(1.0, 0.7, size / 500), 0.7);

	gdouble xradius = (width * 0.5) - brushsize;
	gdouble yradius = (height * 0.5) - brushsize;

	sdpVector2 center(width * 0.5, height * 0.5);

	// Create a screen overlay ...
	sdpGtkScreenOverlay overlay(left, top, width, height, sdpVector3(1, 0, 0));
	g_return_val_if_fail(overlay.Create(), false);

	// Move to the beginning of the arc ...
	sdpVector2 point = sdpGtkHighlightCoords(sdpRadians(gdouble(startangle*samples) / samples), flatness, xradius, yradius, center);
	sdpGtkInteractiveWarpPointer(static_cast<GtkWidget*>(overlay.RootWidget()), gint(point[0]), gint(point[1]), Speed, false, false);

	// Draw the arc around the widget ...
	for(gulong i = startangle * samples; i <= (360 + startangle) * samples; i += 1)
		{
			point = sdpGtkHighlightCoords(sdpRadians(gdouble(i) / samples), flatness, xradius, yradius, center);
			gdk_draw_arc(overlay.Mask(), overlay.MaskGC(), TRUE, gint(point[0] - (brushsize * 0.5)), gint(point[1] - (brushsize * 0.5)), gint(brushsize), gint(brushsize), 0, 360 * 64);
			sdpGtkWarpPointer(static_cast<GtkWidget*>(overlay.RootWidget()), gint(point[0]), gint(point[1]));

			if(0 == i % (24 * samples))
				{
					overlay.Update();
#ifdef SDPUNIX
					sdpGtkSleep(static_cast<gulong>(30.0 / Speed));
#endif // SDPUNIX
				}
		}
	overlay.Update();
	sdpGtkSleep(static_cast<gulong>(750.0 / Speed));

	return true;
}

bool sdpGtkWidget::InteractiveWarpPointer(const gdouble Speed, const bool Pause, const bool ManhattanStyle)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), false);

	return InteractiveWarpPointer(0.5, 0.5, Speed, Pause, ManhattanStyle);
}

bool sdpGtkWidget::InteractiveWarpPointer(const gdouble XPercent, const gdouble YPercent, const gdouble Speed, const bool Pause, const bool ManhattanStyle)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), false);

	// Get our current window dimensions ...
	GtkWidget* widget = *this;

	return InteractiveWarpPointer(gint(XPercent * widget->allocation.width), gint(YPercent * widget->allocation.height), Speed, Pause, ManhattanStyle);
}

bool sdpGtkWidget::InteractiveWarpPointer(const gint XOffset, const gint YOffset, const gdouble Speed, const bool Pause, const bool ManhattanStyle)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), false);

	if(GTK_WIDGET_NO_WINDOW(m_Object))
		{
			GtkWidget* parent = 0;
			GtkWidget* widget = *this;
			if(GTK_IS_MENU(widget))
				parent = gtk_menu_get_attach_widget(GTK_MENU(widget));
			else
				parent = widget->parent;

			sdpGtkInteractiveWarpPointer(parent, XOffset + widget->allocation.x, YOffset + widget->allocation.y, Speed, Pause, ManhattanStyle);
		}
	else
		{
			sdpGtkInteractiveWarpPointer(*this, XOffset, YOffset, Speed, Pause, ManhattanStyle);
		}

	return true;
}


