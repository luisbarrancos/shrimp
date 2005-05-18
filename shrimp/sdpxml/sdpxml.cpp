// SDPXML Library
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
		\brief Implements functionality of the SDPXML library
		\author Tim Shead (tshead@k-3d.com)
*/

#include "sdpxml.h"

#include <fstream>
#include <iterator>
#include <iostream>

namespace
{

/// Encodes a normal text string for use in an XML document
sdpString encodestring(const sdpString& PlainText)
{
	sdpString result(PlainText);

	result.replaceall("&", "&amp;");	// This one's gotta be first!!!
	result.replaceall("\"", "&quot;");
	result.replaceall("\'", "&apos;");
	result.replaceall("<", "&lt;");
	result.replaceall(">", "&gt;");

	return result;
}

/// Decodes a string extracted from an XML document into normal text
sdpString decodestring(const sdpString& EncodedText)
{
	sdpString result(EncodedText);

	result.replaceall("&lt;", "<");
	result.replaceall("&gt;", ">");
	result.replaceall("&apos;", "\'");
	result.replaceall("&quot;", "\"");
	result.replaceall("&amp;", "&");

	return result;
}

int indentindex()
{
	static const int index = std::ios::xalloc();
	return index;
}

long& currentindent(std::ios& Stream)
{
	return Stream.iword(indentindex());
}

std::ostream& resetindent(std::ostream& Stream)
{
	currentindent(Stream) = 0;
	return Stream;
}

std::ostream& pushindent(std::ostream& Stream)
{
	currentindent(Stream)++;
	return Stream;
}

std::ostream& popindent(std::ostream& Stream)
{
	long& indent = currentindent(Stream);
	indent -= (indent > 0);
	return Stream;
}

std::ostream& indentation(std::ostream& Stream)
{
	const long& indent = currentindent(Stream);
	for(long i = 0; i < indent; i++)
		Stream << "\t";

	return Stream;
}

} // namespace

namespace sdpxml
{

/////////////////////////////////////////////////////////////////////////////
// MetaData

void MetaData::SetMeta(const sdpString Name, const sdpString Value)
{
	// Sanity checks ...
	g_assert(Name.size());

	m_Data[Name] = Value;
}

const sdpString MetaData::Meta(const sdpString Name) const
{
	// Sanity checks ...
	g_assert(Name.size());

	DataMap::const_iterator data = m_Data.find(Name);
	return data != m_Data.end() ? data->second : sdpString();
}

/////////////////////////////////////////////////////////////////////////////
// Attribute

Attribute::Attribute(const sdpString Name, const sdpString Value) :
	m_Name(Name),
	m_Value(Value),
	m_Line(0),
	m_Column(0)
{
	// Sanity checks ...
	g_assert(m_Name.size());
}

Attribute::Attribute(const sdpString Name, const sdpString Value, const gulong Line, const gulong Column) :
	m_Name(Name),
	m_Value(Value),
	m_Line(Line),
	m_Column(Column)
{
	// Sanity checks ...
	g_assert(m_Name.size());
}

std::ostream& operator<<(std::ostream& Stream, const Attribute& Data)
{
	Stream << Data.m_Name << "=\"" << encodestring(Data.m_Value) << "\"";
	return Stream;
}

/////////////////////////////////////////////////////////////////////////////
// Element

Element::Element(const sdpString Name) :
	m_Name(Name),
	m_Line(0),
	m_Column(0)
{
	// Sanity checks ...
	g_assert(m_Name.size());
}

Element::Element(const sdpString Name, const sdpString Text) :
	m_Name(Name),
	m_Line(0),
	m_Column(0),
	m_Text(Text)
{
	// Sanity checks ...
	g_assert(m_Name.size());
}

Element::Element(const sdpString Name, const sdpString Text, const Attribute Att1) :
	m_Name(Name),
	m_Line(0),
	m_Column(0),
	m_Text(Text)
{
	// Sanity checks ...
	g_assert(m_Name.size());

	// Add Attributes ...
	m_Attributes.push_back(Att1);
}

Element::Element(const sdpString Name, const sdpString Text, const Attribute Att1, const Attribute Att2) :
	m_Name(Name),
	m_Line(0),
	m_Column(0),
	m_Text(Text)
{
	// Sanity checks ...
	g_assert(m_Name.size());

	// Add Attributes ...
	m_Attributes.push_back(Att1);
	m_Attributes.push_back(Att2);
}

Element::Element(const sdpString Name, const sdpString Text, const Attribute Att1, const Attribute Att2, const Attribute Att3) :
	m_Name(Name),
	m_Line(0),
	m_Column(0),
	m_Text(Text)
{
	// Sanity checks ...
	g_assert(m_Name.size());

	// Add Attributes ...
	m_Attributes.push_back(Att1);
	m_Attributes.push_back(Att2);
	m_Attributes.push_back(Att3);
}

Element::Element(const sdpString Name, const sdpString Text, const Attribute Att1, const Attribute Att2, const Attribute Att3, const Attribute Att4) :
	m_Name(Name),
	m_Line(0),
	m_Column(0),
	m_Text(Text)
{
	// Sanity checks ...
	g_assert(m_Name.size());

	// Add Attributes ...
	m_Attributes.push_back(Att1);
	m_Attributes.push_back(Att2);
	m_Attributes.push_back(Att3);
	m_Attributes.push_back(Att4);
}

Element::Element(const sdpString Name, const sdpString Text, const Attribute Att1, const Attribute Att2, const Attribute Att3, const Attribute Att4, const Attribute Att5) :
	m_Name(Name),
	m_Line(0),
	m_Column(0),
	m_Text(Text)
{
	// Sanity checks ...
	g_assert(m_Name.size());

	// Add Attributes ...
	m_Attributes.push_back(Att1);
	m_Attributes.push_back(Att2);
	m_Attributes.push_back(Att3);
	m_Attributes.push_back(Att4);
	m_Attributes.push_back(Att5);
}

Element::Element(const sdpString Name, const sdpString Text, const Attribute Att1, const Attribute Att2, const Attribute Att3, const Attribute Att4, const Attribute Att5, const Attribute Att6) :
	m_Name(Name),
	m_Line(0),
	m_Column(0),
	m_Text(Text)
{
	// Sanity checks ...
	g_assert(m_Name.size());

	// Add Attributes ...
	m_Attributes.push_back(Att1);
	m_Attributes.push_back(Att2);
	m_Attributes.push_back(Att3);
	m_Attributes.push_back(Att4);
	m_Attributes.push_back(Att5);
	m_Attributes.push_back(Att6);
}

Element::Element(const sdpString Name, const sdpString Text, const Attribute Att1, const Attribute Att2, const Attribute Att3, const Attribute Att4, const Attribute Att5, const Attribute Att6, const Attribute Att7) :
	m_Name(Name),
	m_Line(0),
	m_Column(0),
	m_Text(Text)
{
	// Sanity checks ...
	g_assert(m_Name.size());

	// Add Attributes ...
	m_Attributes.push_back(Att1);
	m_Attributes.push_back(Att2);
	m_Attributes.push_back(Att3);
	m_Attributes.push_back(Att4);
	m_Attributes.push_back(Att5);
	m_Attributes.push_back(Att6);
	m_Attributes.push_back(Att7);
}

Element::Element(const sdpString Name, const sdpString Text, const Attribute Att1, const Attribute Att2, const Attribute Att3, const Attribute Att4, const Attribute Att5, const Attribute Att6, const Attribute Att7, const Attribute Att8) :
	m_Name(Name),
	m_Line(0),
	m_Column(0),
	m_Text(Text)
{
	// Sanity checks ...
	g_assert(m_Name.size());

	// Add Attributes ...
	m_Attributes.push_back(Att1);
	m_Attributes.push_back(Att2);
	m_Attributes.push_back(Att3);
	m_Attributes.push_back(Att4);
	m_Attributes.push_back(Att5);
	m_Attributes.push_back(Att6);
	m_Attributes.push_back(Att7);
	m_Attributes.push_back(Att8);
}

Element::Element(const sdpString Name, const sdpStringArray& Attributes, const gulong Line, const gulong Column) :
	m_Name(Name),
	m_Line(Line),
	m_Column(Column)
{
	// Sanity checks ...
	g_assert(m_Name.size());

	// Add the Attributes ...
	for(gulong index = 0; index < Attributes.size(); index += 2)
		m_Attributes.push_back(Attribute(Attributes[index], decodestring(Attributes[index+1]), Line, Column));
}

std::ostream& operator<<(std::ostream& Stream, const Element& Data)
{
	Stream << indentation << "<" << Data.m_Name;

	if(Data.m_Attributes.size())
		{
			for(AttributeCollection::const_iterator attribute = Data.m_Attributes.begin(); attribute != Data.m_Attributes.end(); attribute++)
				Stream << " " << *attribute;
		}

	if(Data.m_Children.size())
		{
			Stream << ">" << Data.m_Text << std::endl;

			Stream << pushindent;
			std::copy(Data.m_Children.begin(), Data.m_Children.end(), std::ostream_iterator<Element>(Stream));
			Stream << popindent;

			Stream << indentation << "</" << Data.m_Name << ">" << std::endl;
		}
	else if(Data.m_Text.size())
		{
			Stream << ">" << Data.m_Text << "</" << Data.m_Name << ">" << std::endl;
		}
	else
		{
			Stream << "/>" << std::endl;
		}

	return Stream;
}

/////////////////////////////////////////////////////////////////////////////
// SameName

SameName::SameName(const sdpString Name) :
	m_Name(Name)
{
	 // Sanity checks ...
	 g_assert(m_Name.size());
}

bool SameName::operator()(const Attribute& Arg)
{
	return Arg.Name() == m_Name;
}

bool SameName::operator()(const Element& Arg)
{
	return Arg.Name() == m_Name;
}

/////////////////////////////////////////////////////////////////////////////
// Document

Document::Document(const sdpString Name) :
	Element(Name)
{
}

Document::Document(const sdpString Name, const sdpString SourceURL) :
	Element(Name),
	m_SourceURL(SourceURL)
{
}

Document::~Document()
{
}

void Document::operator=(const Element& Data)
{
	m_Name = Data.Name();
	m_Attributes = Data.Attributes();
	m_Children = Data.Children();
	m_Line = Data.Line();
	m_Column = Data.Column();
}

bool Document::Load(const sdpString FilePath)
{
	std::ifstream file(FilePath);
	return Load(file, FilePath);
}

bool Document::Load(std::istream& Stream, const sdpString FilePath)
{
	m_SourceURL = FilePath;
	return Parse(Stream, FilePath, this);
}

/////////////////////////////////////////////////////////////////////////////
// SAX event handlers ...

void Document::StartDocument(const gulong Line, const gulong Column)
{
	// Make sure we start with an empty stack ...
	while(m_ElementStack.size())
		m_ElementStack.pop();
}

void Document::EndDocument(const gulong Line, const gulong Column)
{
	// Make sure we end up with an empty stack ...
	g_return_if_fail(m_ElementStack.empty());
}

void Document::ProcessingInstruction(const sdpString Target, const sdpString Data, const gulong Line, const gulong Column)
{
}

void Document::StartElement(const sdpString Name, const sdpStringArray& Attributes, const gulong Line, const gulong Column)
{
	if(m_ElementStack.empty())
		{
			*this = Element(Name, Attributes, Line, Column);
			m_ElementStack.push(this);
		}
	else
		{
			m_ElementStack.top()->Children().push_back(Element(Name, Attributes, Line, Column));
			m_ElementStack.push(&m_ElementStack.top()->Children().back());
		}
}

void Document::EndElement(const gulong Line, const gulong Column)
{
	g_return_if_fail(m_ElementStack.size());
	m_ElementStack.pop();
}

void Document::Characters(const sdpString Text, const gulong Line, const gulong Column)
{
	// Get rid of whitespace before we do anything ...
	sdpString text(Text);
	text.trim();

	// If we've still got something, assign it to our Element ...
	if(text.size() && m_ElementStack.top())
		m_ElementStack.top()->Text() = text;
}

void Document::CDATABlock(const sdpString Value, const gulong Line, const gulong Column)
{
	Characters(Value, Line, Column);
}

void Document::Warning(const sdpString Message, const gulong Line, const gulong Column)
{
	std::cerr << FileReference(SourceURL(), Line, Column) << ": " << Message << std::endl;
}

void Document::Error(const sdpString Message, const gulong Line, const gulong Column)
{
	std::cerr << FileReference(SourceURL(), Line, Column) << ": " << Message << std::endl;
}

void Document::FatalError(const sdpString Message, const gulong Line, const gulong Column)
{
	std::cerr << FileReference(SourceURL(), Line, Column) << ": " << Message << std::endl;
}

/////////////////////////////////////////////////////////////////////////////
// FileReference

FileReference::FileReference(const Document& Doc, const Element& Element) :
	m_SourceURL(Doc.SourceURL()),
	m_Line(Element.Line()),
	m_Column(Element.Column())
{
}

FileReference::FileReference(const Document& Doc, const Attribute& Attribute) :
	m_SourceURL(Doc.SourceURL()),
	m_Line(Attribute.Line()),
	m_Column(Attribute.Column())
{
}

FileReference::FileReference(const sdpString SourceURL, const gulong Line, const gulong Column) :
	m_SourceURL(SourceURL),
	m_Line(Line),
	m_Column(Column)
{
}

std::ostream& operator<<(std::ostream& Stream, const FileReference& Arg)
{
	Stream << Arg.m_SourceURL << ": line " << Arg.m_Line << " column " << Arg.m_Column;
	return Stream;
}

} // namespace sdpxml


