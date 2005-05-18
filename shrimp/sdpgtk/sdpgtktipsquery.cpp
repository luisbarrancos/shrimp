
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

#include "sdpgtktipsquery.h"
#include "sdpgtkutility.h"

///////////////////////////////////////////////////////////////////////
// sdpGtkTipsQuery

sdpGtkTipsQuery::sdpGtkTipsQuery() : sdpGtkLabel()
{
}

sdpGtkTipsQuery::sdpGtkTipsQuery(GtkTipsQuery* TipsQuery) : sdpGtkLabel(GTK_LABEL(TipsQuery))
{
}

bool sdpGtkTipsQuery::Create()
{
	// Sanity checks ...

	m_Object = GTK_OBJECT(gtk_tips_query_new());
	return Attached();
}

bool sdpGtkTipsQuery::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	return Create();
}

bool sdpGtkTipsQuery::CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	const sdpString inactive = sdpxml::GetAttribute<sdpString>(Element, "inactive", "");
	sdpGtkMarkAttribute(Document, Element, "inactive");

	const sdpString notip = sdpxml::GetAttribute<sdpString>(Element, "notip", "");
	sdpGtkMarkAttribute(Document, Element, "notip");
	
	SetLabels(inactive, notip);

	return sdpGtkLabel::CreateOptions(ObjectContainer, Document, Element);
}

void sdpGtkTipsQuery::StartQuery()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_tips_query_start_query(*this);
}

void sdpGtkTipsQuery::StopQuery()
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_tips_query_stop_query(*this);
}

void sdpGtkTipsQuery::SetCaller(GtkWidget* Widget)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	g_assert(Widget);
	
	gtk_tips_query_set_caller(*this, Widget);
}

void sdpGtkTipsQuery::SetLabels(SDPCSTRING Inactive, SDPCSTRING NoTip)
{
	// Sanity checks ...
	g_return_if_fail(Attached());
	
	gtk_tips_query_set_labels(*this, Inactive, NoTip);
}

