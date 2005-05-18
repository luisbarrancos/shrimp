#ifndef SDPGTKWIDGET_H
#define SDPGTKWIDGET_H

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
		\brief Declares the sdpGtkWidget class, which encapsulates a GtkWidget
		\author Timothy M. Shead (tshead@k-3d.com)
		\author Dan Erikson <derikson@montana.com>
*/

#include "sdpgtkobject.h"

/// Encapsulates a GtkWidget
class sdpGtkWidget : public sdpGtkObject
{
public:
	/// Standard constructor
	sdpGtkWidget();
	/// Attaches this instance to an existing GtkWidget
	sdpGtkWidget(GtkWidget* Widget);

	virtual ~sdpGtkWidget();

	bool CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);
	bool CreateTooltip(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Increments the reference count of the widget
	void Reference();
	/// Decrements the reference count of the widget
	void UnReference();
	/// Destroys the widget (note that this is NOT called by the destructor)
	void Destroy();
	/// Maps the widget
	void Map();
	/// Unmaps the widget
	void UnMap();
	/// Realizes (creates the X window) for the widget
	void Realize();
	/// Unrealizes the widget
	void UnRealize();

	/// Sets the widget state
	void SetState(GtkStateType State);

	/// Unparents the widget
	void UnParent();
	/// Sets the widget's parent widget
	void SetParent(GtkWidget* Parent);
	/// Sets the widget's parent window
	void SetParentWindow(GdkWindow* Parent);
	/// Returns the widget's parent window
	GdkWindow* GetParentWindow();
	/// Reparents the widget
	void Reparent(GtkWidget* NewParent);

	/// Returns the parent widget
	GtkWidget* GetParent();
	/// Returns the top-level ancestor of this widget
	GtkWidget* GetTopLevel();
	/// Returns the ancestor of this widget that has the given type
	GtkWidget* GetAncestor(GtkType WidgetType);
	/// Returns true if the given widget is an ancestor of this one
	gint IsAncestor(GtkWidget* Child);

	/// Sets the widget name
	void SetName(SDPCSTRING Name);
	/// Returns the widget name
	gchar* GetName();

	void SetCanFocus(bool CanFocus);
	bool GetCanFocus();

	void SetCanDefault(bool CanDefault);
	bool GetCanDefault();

	void GetPath(guint* PathLength, gchar** Path, gchar** PathReversed);
	void GetClassPath(guint* PathLength, gchar** Path, gchar** PathReversed);

	/// Sets the widget style
	void SetStyle(GtkStyle* Style);
	/// Returns the widget style
	GtkStyle* GetStyle();
	/// Returns the widget colormap
	GdkColormap* GetColormap();
	/// Returns the widget visual
	GdkVisual* GetVisual();

	void EnsureStyle();
	void RestoreDefaultStyle();
	void ModifyStyle(GtkRcStyle* Style);
	void SetSensitive(bool Sensitive);

	// Shapes ...
	void CombineShapeMask(GdkBitmap* Mask, gint OffsetX, gint OffsetY);
	void ResetShapeMask();

	/// Makes the widget visible
	void Show();
	/// Makes the widget visible right now
	void ShowNow();
	/// Makes the widget and all its children recursively visible
	void ShowAll();
	/// Hides the widget
	void Hide();
	/// Recursively hides the widget and all its children
	void HideAll();

	/// Queues an asynchronous redraw of the widget
	void QueueDraw();
	/// Queues an asynchronous redraw of the given area of the widget
	void QueueDrawArea(gint Left, gint Top, gint Width, gint Height);
	void QueueClear();
	void QueueClearArea(gint Left, gint Top, gint Width, gint Height);

	void Draw(GdkRectangle* Area);
	void DrawFocus();
	void DrawDefault();

	/// Queues a resize of the widget
	void QueueResize();

	void SizeRequest(GtkRequisition* Requisition);
	void SizeAllocate(GtkAllocation* Allocation);
	void GetChildRequisition(GtkRequisition* Requisition);

	/// Adds an accelerator key to the widget
	void AddAccelerator(SDPCSTRING Signal, GtkAccelGroup* Group, guint Key, guint Modifiers, GtkAccelFlags Flags);
	/// Removes an accelerator key from a widget
	void RemoveAccelerator(GtkAccelGroup* Group, guint Key, guint Modifiers);
	/// Removes multiple accelerator keys from a widget
	void RemoveAccelerators(SDPCSTRING Signal, bool VisibleOnly);

	void LockAccelerators();
	void UnlockAccelerators();
	bool AcceleratorsLocked();

	/// Sets the widget position relative to its parent
	void SetPosition(gint Left, gint Top);
	/// Sets the widget size in pixels
	void SetSize(gint Width, gint Height);
	/// Sets the widget size in characters
	void SetCharacterSize(gdouble Width, gdouble Height);

	gint Left() const;
	gint Top() const;
	gint Width() const;
	gint Height() const;

	// State ...
	void Activate();
	void GrabAdd();
	void GrabRemove();
	void GrabFocus();
	void GrabDefault();

	// Drag-and-drop ...
	void SetDragSource(GdkModifierType StartButton, GtkTargetEntry* TargetArray, gint TargetCount, GdkDragAction DragAction);
	void RemoveDragSource();

	void SetDragDestination(GtkDestDefaults Flags, GtkTargetEntry* TargetArray, gint TargetCount, GdkDragAction DragAction);
	void RemoveDragDestination();

	// Miscellaneous ...
	void GetPointer(gint* X, gint* Y);
	void Popup(gint X, gint Y);
	gint Intersect(GdkRectangle* Area, GdkRectangle* Intersection);

	/// Does whatever is required (raises the window, changes notebook pages, etc.) to make this widget visible
	bool InteractiveShow(const gdouble Speed, const bool Pause);
	/// Overlays graphics on the screen to draw attention to this widget
	bool InteractiveHighlight(const gdouble Speed, const bool Pause);
	/// Moves the pointer from its current location to the center of the widget
	bool InteractiveWarpPointer(const gdouble Speed, const bool Pause, const bool ManhattanStyle);
	/// Moves the pointer from its current location to a position relative to the widget (expressed as percentages)
	bool InteractiveWarpPointer(const gdouble XPercent, const gdouble YPercent, const gdouble Speed, const bool Pause, const bool ManhattanStyle);
	/// Moves the pointer from its current location to a position relative to the widget (expressed in pixels)
	bool InteractiveWarpPointer(const gint XOffset, const gint YOffset, const gdouble Speed, const bool Pause, const bool ManhattanStyle);

	/// Casts this instance into a GtkWidget pointer
	operator GtkWidget*() { return GTK_WIDGET(m_Object); }
};

#endif // SDPGTKWIDGET_H

