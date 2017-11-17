
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



#include "sdpgtkfontselection.h"


//////////////////////////////////////////////////////////////////////////////////////////
// sdpGtkFontSelection

sdpGtkFontSelection::sdpGtkFontSelection() : sdpGtkNotebook()
{
}

sdpGtkFontSelection::sdpGtkFontSelection(GtkFontSelection* FontSelection) : sdpGtkNotebook(GTK_NOTEBOOK(FontSelection))
{
}

bool sdpGtkFontSelection::Create()
{
	m_Object = GTK_OBJECT(gtk_font_selection_new());
	return Attached();
}

bool sdpGtkFontSelection::Create(sdpGtkIObjectContainer* const ObjectContainer, sdpxml::Document& Document, sdpxml::Element& Element)
{
	// Sanity checks ...
	g_assert(ObjectContainer);

	return Create();
}

sdpString sdpGtkFontSelection::GetFontName()
{
	// Sanity checks ...
#ifdef	FAIL_ON_RET
	sdpString tmpResult;
	g_return_val_if_fail(Attached(), tmpResult);
#else
	g_return_val_if_fail(Attached(), sdpString());
#endif

	return sdpString(gtk_font_selection_get_font_name(*this));
}

GdkFont* sdpGtkFontSelection::GetFont()
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), 0);

	return gtk_font_selection_get_font(*this);
}

bool sdpGtkFontSelection::SetFontName(SDPCSTRING FontName)
{
	// Sanity checks ...
	g_return_val_if_fail(Attached(), false);
	g_assert_string(FontName);

	return gtk_font_selection_set_font_name(*this, FontName) ? true : false;
}

/* This sets one of the font filters, to limit the fonts shown. The filter_type
   is GTK_FONT_FILTER_BASE or GTK_FONT_FILTER_USER. The font type is a
   combination of the bit flags GTK_FONT_BITMAP, GTK_FONT_SCALABLE and
   GTK_FONT_SCALABLE_BITMAP (or GTK_FONT_ALL for all font types).
   The foundries, weights etc. are arrays of strings containing property
   values, e.g. 'bold', 'demibold', and *MUST* finish with a NULL.
   Standard long names are also accepted, e.g. 'italic' instead of 'i'.

   e.g. to allow only fixed-width fonts ('char cell' or 'monospaced') to be
   selected use:

  gchar *spacings[] = { "c", "m", NULL };
  gtk_font_selection_set_filter (GTK_FONT_SELECTION (fontsel),
				       GTK_FONT_FILTER_BASE, GTK_FONT_ALL,
				       NULL, NULL, NULL, NULL, spacings, NULL);

  to allow only true scalable fonts to be selected use:

  gtk_font_selection_set_filter (GTK_FONT_SELECTION (fontsel),
				       GTK_FONT_FILTER_BASE, GTK_FONT_SCALABLE,
				       NULL, NULL, NULL, NULL, NULL, NULL);
void	   gtk_font_selection_set_filter	(GtkFontSelectionFontSelection *fsd,
						 GtkFontFilterType filter_type,
						 GtkFontType	   font_type,
						 gchar		 **foundries,
						 gchar		 **weights,
						 gchar		 **slants,
						 gchar		 **setwidths,
						 gchar		 **spacings,
						 gchar		 **charsets);
*/

sdpString sdpGtkFontSelection::GetPreviewText()
{
	// Sanity checks ...
#ifdef	FAIL_ON_RET
	sdpString tmpResult;
	g_return_val_if_fail(Attached(), tmpResult);
#else
	g_return_val_if_fail(Attached(), sdpString());
#endif

	return sdpString(gtk_font_selection_get_preview_text(*this));
}

void sdpGtkFontSelection::SetPreviewText(SDPCSTRING Text)
{
	// Sanity checks ...
	g_return_if_fail(Attached());

	gtk_font_selection_set_preview_text(*this, Text);
}


