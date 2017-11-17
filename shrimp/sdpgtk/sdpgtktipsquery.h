#ifndef SDPGTKTIPSQUERY_H
#define SDPGTKTIPSQUERY_H

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
		\brief Declares the sdpGtkTipsQuery class, which encapsulates a GtkTipsQuery widget
		\author Timothy M. Shead (tshead@k-3d.com)
*/

#include "sdpgtklabel.h"

//////////////////////////////////////////////////////////////////////
// sdpGtkTipsQuery

/// Encapsulates a GtkTipsQuery widget
class sdpGtkTipsQuery : public sdpGtkLabel
{
public:
	/// Standard constructor
	sdpGtkTipsQuery();
	/// Attaches this instance to an existing GtkTipsQuery widget
	sdpGtkTipsQuery(GtkTipsQuery* TipsQuery);

	/// Creates a new GtkTipsQuery widget
	bool Create();
	/// Creates a new GtkTipsQuery widget from a GTKML (XML) document
	bool Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	bool CreateOptions(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element);

	/// Starts a query
	void StartQuery();
	/// Stops a query
	void StopQuery();
	/// Sets the widget that began a query
	void SetCaller(GtkWidget* Caller);
	/// Sets the text to display when the query is not in effect, and the text to display when the query is in effect but the widget beneath the pointer has no tooltip
	void SetLabels(SDPCSTRING Inactive, SDPCSTRING NoTip);

	/// Casts this instance into a GtkTipsQuery pointer
	operator GtkTipsQuery*() { return GTK_TIPS_QUERY(m_Object); }
};

#endif // SDPGTKTIPSQUERY_H

