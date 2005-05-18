// SDPTypes Library
// Copyright © 1995-2003, Timothy M. Shead
//
// Contact: tshead@k-3d.com
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

/** \file
		\brief Implements an extended string class, sdpString, derived from std::string
		\author Tim Shead (tshead@k-3d.com)
*/

#include "sdptypes.h"

#include <stdio.h>
#include <stdarg.h>
#include <malloc.h>

#include <iomanip>
#include <algorithm>
#include <functional>

#if defined SDPWIN32
#define vsnprintf _vsnprintf
#endif	// SDPWIN32

void sdpString::formattedreplace(const char Delimiter, SDPCSTRING Specifier, SDPCSTRING Replacement)
{
	// Sanity checks ...
	g_assert(Delimiter);
	g_assert_string(Specifier);

	const sdpString specifier = Delimiter + sdpString(Specifier);
	const sdpString replacement(Replacement);

	// For each copy of the specifier we find ...
	size_type index = find(specifier);
	while(index != npos)
	{
		// Make sure the user didn't want a literal ...
		if(index) {
			if(at(index-1) == Delimiter)
			{
				index = find(specifier, index + 1);
				continue;
			}
		}

		// Make the replacement!
		replace(index, specifier.size(), replacement);
		index = find(specifier, index + replacement.size() + 1);
	}
}

sdpString& sdpString::trim()
{
	trimleft();
	trimright();
	return *this;
}

sdpString& sdpString::trimleft()
{
	// Easiest case ...
	if(!size())
		return *this;

	size_type i;
	for(i = 0; i < size(); ++i)
		if(!isspace(operator[](i)))
			break;

	// No whitespace, so we're done ...
	if(i == 0)
		return *this;

	// All whitespace, so clear the string ...
	if(i == size())
	{
		clear();
		return *this;
	}

	const sdpString temp = right(size()-i);
	assign(temp);

	return *this;
}

sdpString& sdpString::trimright()
{
	// Easiest case ...
	if(!size())
		return *this;

	size_type i;
	for(i = size()-1; i >= 0; --i) {
		if(!isspace(operator[](i)))
			break;
	}

	// No whitespace, so we're done ...
	if(i == (size()-1))
		return *this;

	// All whitespace, so clear the string ...
	if(i == size_type(-1))
	{
		clear();
		return *this;
	}

	const sdpString temp = left(i+1);
	assign(temp);

	return *this;
}

sdpString& sdpString::clear()
{
	erase();
	return *this;
}

sdpString sdpString::left(size_type Count) const
{
	g_assert(Count <= size());
	return sdpString(begin(), begin() + Count);
}

sdpString sdpString::mid(size_type Start, size_type Count) const
{
	g_assert(Start + Count <= size());
	return sdpString(begin() + Start, begin() + Start + Count);
}

sdpString sdpString::right(size_type Count) const
{
	g_assert(Count <= size());
	return sdpString(end() - Count, end());
}

const bool sdpString::isalphanumeric() const
{
	for(const_iterator i = begin(); i != end(); ++i)
		if(!isalnum((gint)*i)) return false;

	return true;
}

const bool sdpString::isalphabetic() const
{
	for(const_iterator i = begin(); i != end(); ++i)
		if(!isalpha((gint)*i)) return false;

	return true;
}

const bool sdpString::isnumeric() const
{
	for(const_iterator i = begin(); i != end(); ++i)
		if(!isdigit((gint)*i)) return false;

	return true;
}

const bool sdpString::islowercase() const
{
	for(const_iterator i = begin(); i != end(); ++i)
		if(!islower((gint)*i)) return false;

	return true;
}

const bool sdpString::isprintable() const
{
	for(const_iterator i = begin(); i != end(); ++i)
		if(!isprint((gint)*i)) return false;

	return true;
}

const bool sdpString::ispunctuation() const
{
	for(const_iterator i = begin(); i != end(); ++i)
		if(!ispunct((gint)*i)) return false;

	return true;
}

const bool sdpString::iswhitespace() const
{
	for(const_iterator i = begin(); i != end(); ++i)
		if(!isspace((gint)*i)) return false;

	return true;
}

const bool sdpString::isuppercase() const
{
	for(const_iterator i = begin(); i != end(); ++i)
		if(!isupper((gint)*i)) return false;

	return true;
}

void sdpString::replaceall(SDPCSTRING Target, SDPCSTRING Replacement)
{
	// Sanity checks ...
	g_assert_string(Target);
//	g_assert(Replacement);	// Notice - the replacement can be empty, but not NULL ...

	size_type length = strlen(Target);

	for(size_type index = find(Target); index != npos; index = find(Target, index+1))
		replace(index, length, Replacement);
}

void sdpString::replaceall(const char Target, const char Replacement)
{
	for(size_type index = find(Target); index != npos; index = find(Target))
		(*this)[index] = Replacement;
}


