
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

#include "sdpgtkhandlebox.h"
#include "sdpgtkutility.h"

sdpGtkHandleBox::sdpGtkHandleBox() : sdpGtkBin()
{
}

sdpGtkHandleBox::sdpGtkHandleBox(GtkHandleBox* HandleBox) : sdpGtkBin(GTK_BIN(HandleBox))
{
}

bool sdpGtkHandleBox::Create()
{
	m_Object = GTK_OBJECT(gtk_handle_box_new());
	return Attached();
}

bool sdpGtkHandleBox::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	// Create the control ...
	return Create();
}

bool sdpGtkHandleBox::CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	// Shadow type ...
	SetShadowType(sdpGtkGetShadowType(Document, Element, GTK_SHADOW_ETCHED_IN));

	// Handle position ...
	sdpString handlepositiontext = sdpxml::GetAttribute<sdpString>(Element, "handleposition", "top");
	sdpGtkMarkAttribute(Document, Element, "handleposition");

	GtkPositionType handleposition;
	if(handlepositiontext == "left")
		handleposition = GTK_POS_LEFT;
	else if(handlepositiontext == "right")
		handleposition = GTK_POS_RIGHT;
	else if(handlepositiontext == "top")
		handleposition = GTK_POS_TOP;
	else if(handlepositiontext == "bottom")
		handleposition = GTK_POS_BOTTOM;
	else
		g_return_val_if_fail(0, false);

	SetHandlePosition(handleposition);

	// Snap Edge ...
	sdpString snapedgetext = sdpxml::GetAttribute<sdpString>(Element, "snapedge", "top");
	sdpGtkMarkAttribute(Document, Element, "snapedge");

	GtkPositionType snapedge;
	if(snapedgetext == "left")
		snapedge = GTK_POS_LEFT;
	else if(snapedgetext == "right")
		snapedge = GTK_POS_RIGHT;
	else if(snapedgetext == "top")
		snapedge = GTK_POS_TOP;
	else if(snapedgetext == "bottom")
		snapedge = GTK_POS_BOTTOM;
	else
		g_return_val_if_fail(0, false);

	SetSnapEdge(snapedge);

	return sdpGtkBin::CreateOptions(ObjectContainer, Document, Element);
}

void sdpGtkHandleBox::SetShadowType(GtkShadowType ShadowType)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_handle_box_set_shadow_type(*this, ShadowType);
}

void sdpGtkHandleBox::SetHandlePosition(GtkPositionType PositionType)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_handle_box_set_handle_position(*this, PositionType);
}

void sdpGtkHandleBox::SetSnapEdge(GtkPositionType SnapEdge)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_handle_box_set_snap_edge(*this, SnapEdge);
}

