#ifndef SDPXML_H
#define SDPXML_H

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
		\brief Declares the public API for the SDPXML library
		\author Tim Shead (tshead@k-3d.com)
*/

#include <sdptypes/sdptypes.h>

#include <list>
#include <map>
#include <stack>

namespace sdpxml
{
// Forward class declarations
class Attribute;
class Element;
class Document;
class MetaData;

typedef Attribute* AttributePointer;
typedef Element* ElementPointer;

/// Defines a collection of XML Attributes
typedef std::list<Attribute> AttributeCollection;
/// Defines a collection of pointers-to-XML Attributes
typedef std::list<AttributePointer> AttributePointerCollection;
/// Defines a collection of XML Elements
typedef std::list<Element> ElementCollection;
/// Defines a collection of pointers-to-XML Elements
typedef std::list<ElementPointer> ElementPointerCollection;

/// Encapsulates metadata that is not part of the underlying XML document
class MetaData
{
public:
	void SetMeta(const sdpString Name, const sdpString Value);
	const sdpString Meta(const sdpString Name) const;

private:
	typedef std::map<sdpString, sdpString> DataMap;
	DataMap m_Data;
};

/// Encapsulates an XML Attribute
class Attribute :
	public MetaData
{
public:
	Attribute(const sdpString Name, const sdpString Value);
	Attribute(const sdpString Name, const sdpString Value, const gulong Line, const gulong Column);

	const sdpString& Name() const { return m_Name; }
	const sdpString& Value() const { return m_Value; }
	const gulong Line() const { return m_Line; }
	const gulong Column() const { return m_Column; }

	friend std::ostream& operator<<(std::ostream& Stream, const Attribute& Data);

protected:
	/// Stores the Attribute Name
	sdpString m_Name;
	/// Stores the Attribute Value
	sdpString m_Value;
	/// Stores the Line number in the source XML Document (0 if none)
	gulong m_Line;
	/// Stores the Column number in the source XML Document (0 if none)
	gulong m_Column;
};

/// Stream inserter for serializing Attribute objects
std::ostream& operator<<(std::ostream& Stream, const Attribute& Data);

/// Encapsulates an XML Element
class Element :
	public MetaData
{
public:
	Element(const sdpString Name);
	Element(const sdpString Name, const sdpString Text);
	Element(const sdpString Name, const sdpString Text, const Attribute Att1);
	Element(const sdpString Name, const sdpString Text, const Attribute Att1, const Attribute Att2);
	Element(const sdpString Name, const sdpString Text, const Attribute Att1, const Attribute Att2, const Attribute Att3);
	Element(const sdpString Name, const sdpString Text, const Attribute Att1, const Attribute Att2, const Attribute Att3, const Attribute Att4);
	Element(const sdpString Name, const sdpString Text, const Attribute Att1, const Attribute Att2, const Attribute Att3, const Attribute Att4, const Attribute Att5);
	Element(const sdpString Name, const sdpString Text, const Attribute Att1, const Attribute Att2, const Attribute Att3, const Attribute Att4, const Attribute Att5, const Attribute Att6);
	Element(const sdpString Name, const sdpString Text, const Attribute Att1, const Attribute Att2, const Attribute Att3, const Attribute Att4, const Attribute Att5, const Attribute Att6, const Attribute Att7);
	Element(const sdpString Name, const sdpString Text, const Attribute Att1, const Attribute Att2, const Attribute Att3, const Attribute Att4, const Attribute Att5, const Attribute Att6, const Attribute Att7, const Attribute Att8);
	Element(const sdpString Name, const sdpStringArray& Attributes, const gulong Line, const gulong Column);

	const sdpString& Name() const { return m_Name; }
	const gulong Line() const { return m_Line; }
	const gulong Column() const { return m_Column; }

	AttributeCollection& Attributes() { return m_Attributes; }
	const AttributeCollection& Attributes() const { return m_Attributes; }

	ElementCollection& Children() { return m_Children; }
	const ElementCollection& Children() const { return m_Children; }

	sdpString& Text() { return m_Text; }
	const sdpString& Text() const { return m_Text; }

	Element& Append(const Element& Child)
	{
		m_Children.push_back(Child);
		return m_Children.back();
	}

	friend std::ostream& operator<<(std::ostream& Stream, const Element& Data);

protected:
	/// Stores the Element Name
	sdpString m_Name;
	/// Stores the Line number in the source XML Document (0 if none)
	gulong m_Line;
	/// Stores the Column number in the source XML Document (0 if none)
	gulong m_Column;

	/// Stores the Attribute objects associated with this Element
	AttributeCollection m_Attributes;
	/// Stores the child Element objects associated with this Element
	ElementCollection m_Children;
	/// Stores the Text contained by this Element
	sdpString m_Text;
};

/// Stream inserter for serializing Element objects
std::ostream& operator<<(std::ostream& Stream, const Element& Data);

/// Functor object for doing name comparisons in standard algorithms
class SameName
{
public:
	SameName(const sdpString Name);

	bool operator()(const Attribute& Arg);
	bool operator()(const Element& Arg);

private:
	const sdpString m_Name;
};

/// Callback interface for an object that wishes to receive parsing events
class SAXHandler
{
public:
	virtual void StartDocument(const gulong Line, const gulong Column) = 0;
	virtual void EndDocument(const gulong Line, const gulong Column) = 0;
	virtual void ProcessingInstruction(const sdpString Target, const sdpString Data, const gulong Line, const gulong Column) = 0;
	virtual void StartElement(const sdpString Name, const sdpStringArray& Attributes, const gulong Line, const gulong Column) = 0;
	virtual void EndElement(const gulong Line, const gulong Column) = 0;
	virtual void Characters(const sdpString Text, const gulong Line, const gulong Column) = 0;
	virtual void CDATABlock(const sdpString Value, const gulong Line, const gulong Column) = 0;
	virtual void Warning(const sdpString Message, const gulong Line, const gulong Column) = 0;
	virtual void Error(const sdpString Message, const gulong Line, const gulong Column) = 0;
	virtual void FatalError(const sdpString Message, const gulong Line, const gulong Column) = 0;
};

/// Parses an XML source Document, returning data to the caller through the ISAXHandler interface
bool Parse(std::istream& Stream, const sdpString FilePath, SAXHandler* const Handler);

/// Encapsulates a complete XML Document
class Document :
	public Element,
	public SAXHandler
{
public:
	Document(const sdpString Name);
	Document(const sdpString Name, const sdpString SourceURL);
	virtual ~Document();

	sdpString& SourceURL() { return m_SourceURL; }
	const sdpString& SourceURL() const { return m_SourceURL; }

	bool Load(const sdpString FilePath);
	bool Load(std::istream& Stream, const sdpString FilePath);

	void operator=(const Element& Element);

private:
	sdpString m_SourceURL;

	// SAXHandler implementation
	void StartDocument(const gulong Line, const gulong Column);
	void EndDocument(const gulong Line, const gulong Column);
	void ProcessingInstruction(const sdpString Target, const sdpString Data, const gulong Line, const gulong Column);
	void StartElement(const sdpString Name, const sdpStringArray& Attributes, const gulong Line, const gulong Column);
	void EndElement(const gulong Line, const gulong Column);
	void Characters(const sdpString Text, const gulong Line, const gulong Column);
	void CDATABlock(const sdpString Value, const gulong Line, const gulong Column);
	void Warning(const sdpString Message, const gulong Line, const gulong Column);
	void Error(const sdpString Message, const gulong Line, const gulong Column);
	void FatalError(const sdpString Message, const gulong Line, const gulong Column);

	typedef std::stack<Element*> Elementstack;
	Elementstack m_ElementStack;
};

/// Convenience object that formats line/column data from an XML document for error output, warnings, etc.
class FileReference
{
public:
	FileReference(const Document& Doc, const Element& Element);
	FileReference(const Document& Doc, const Attribute& Attribute);
	FileReference(const sdpString SourceURL, const gulong Line, const gulong Column);

	friend std::ostream& operator<<(std::ostream& Stream, const FileReference& Arg);

private:
	const sdpString m_SourceURL;
	const gulong m_Line;
	const gulong m_Column;
};

/// Inserter for serializing FileReference objects
std::ostream& operator<<(std::ostream& Stream, const FileReference& Arg);

/// Quietly tries to find an attribute, parse its value, and place it into Result, with error output
template<class TYPE>
bool ParseAttribute(const Element& Source, const sdpString Name, TYPE& Result)
{
	// Sanity checks ...
	g_assert(Name.size());

	for(AttributeCollection::const_iterator attribute = Source.Attributes().begin(); attribute != Source.Attributes().end(); attribute++)
		{
			if(Name == attribute->Name())
				{
					Result = sdpFromString(attribute->Value(), TYPE(Result));
					return true;
				}
		}

	return false;
}

/// Template specialization for strings, so that they retrieve the entire attribute value, including whitespace
template<>
inline bool ParseAttribute(const Element& Source, const sdpString Name, sdpString& Result)
{
	// Sanity checks ...
	g_assert(Name.size());

	for(AttributeCollection::const_iterator attribute = Source.Attributes().begin(); attribute != Source.Attributes().end(); attribute++)
		{
			if(Name == attribute->Name())
				{
					Result = attribute->Value();
					return true;
				}
		}

	return false;
}

/// Quietly tries to find an attribute, parse its value, and return it, with a provided default and no error output
template<class TYPE>
TYPE GetAttribute(const Element& Source, const sdpString Name, const TYPE Default)
{
	TYPE result(Default);
	ParseAttribute<TYPE>(Source, Name, result);

	return result;
}

/// Template specialization for strings, so that they retrieve the entire attribute value, including whitespace
template<>
inline sdpString GetAttribute(const Element& Source, const sdpString Name, const sdpString Default)
{
	sdpString result(Default);
	ParseAttribute(Source, Name, result);

	return result;
}

/// Quietly sets an attribute value, overwriting any existing values
void SetAttribute(Element& Target, Attribute Value);

/// Returns a child element by name, or NULL
template<class TEST>
ElementPointer FindElement(Element& Parent, TEST Test)
{
	// Sanity checks ...
	ElementCollection::iterator result = std::find_if(Parent.Children().begin(), Parent.Children().end(), Test);
	return (result != Parent.Children().end()) ? &(*result) : 0;
}

/// Returns an attribute by name, or NULL
template<class TEST>
AttributePointer FindAttribute(Element& Parent, TEST Test)
{
	// Sanity checks ...
	AttributeCollection::iterator result = std::find_if(Parent.Attributes().begin(), Parent.Attributes().end(), Test);
	return (result != Parent.Attributes().end()) ? &(*result) : 0;
}

} // namespace sdpxml

#endif // SDPXML_H

