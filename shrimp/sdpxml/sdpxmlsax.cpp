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
		\brief Implements the SDPXML SAX parser
		\author Tim Shead (tshead@k-3d.com)
*/

#include <sdpxml/sdpxml.h>
using namespace sdpxml;

namespace
{

static char getchar(std::istream& Stream, gulong& Line, gulong& Column)
{
	// Sanity checks ...
	g_assert(Stream.good());

	char result = 0;

	Stream.get(result);

	if(result == '\n')
		{
			Line++;
			Column = 0;
		}
	else
		{
			Column++;
		}

	return result;
}

static void skipwhitespace(std::istream& Stream, gulong& Line, gulong& Column)
{
	// Sanity checks ...
	g_assert(Stream.good());

	for(char c = Stream.peek(); isspace(c); c = Stream.peek())
		c = getchar(Stream, Line, Column);
}

} // namespace

namespace sdpxml
{

bool Parse(std::istream& Stream, const sdpString FilePath, SAXHandler* const Handler)
{
	// Sanity checks ...
	g_assert(Handler);
	g_return_val_if_fail(Stream.good(), false);

	// Setup our parser state vector ...
	typedef enum
	{
		STARTDOCUMENT,
		PROCESSINGINSTRUCTION,
		COMMENT,
		STARTELEMENT,
		ATTRIBUTENAME,
		ATTRIBUTEVALUE,
		ELEMENT,
		ENDELEMENT,
	} ParserState;

	ParserState state = STARTDOCUMENT;
	gulong line = 1;
	gulong column = 0;
	gulong depth = 0;

	char c;
	sdpString pitarget;
	sdpString elementname;
	sdpString attributename;
	sdpString attributevalue;
	sdpString characterdata;
	sdpStringArray attributes;

	// Start the document ...
	Handler->StartDocument(line, column);

	// Skip any initial whitespace ...
	skipwhitespace(Stream, line, column);

	while(!Stream.eof())
		{
			switch(state)
				{
					case STARTDOCUMENT:
						c = getchar(Stream, line, column);
						if(c == '<')
							{
								c = getchar(Stream, line, column);
								if(c == '?')
									{
										state = PROCESSINGINSTRUCTION;
									}
								else if(c == '!')
									{
										state = COMMENT;
									}
								else
									{
										state = STARTELEMENT;
										elementname += c;
									}
							}
						else
							{
								Handler->Error("Unexpected character [" + sdpToString(c) + "] near start-of-document", line, column);
							}
						break;

					case PROCESSINGINSTRUCTION:
						c = getchar(Stream, line, column);
						if(c == '?')
							{
								c = getchar(Stream, line, column);
								if(c != '>')
									{
										Handler->Error("Unexpected character [" + sdpToString(c) + "] near end-of processing instruction", line, column);
									}

								Handler->ProcessingInstruction(pitarget, 0, line, column);
								pitarget.clear();
								state = ELEMENT;
							}
						else
							{
								pitarget += c;
							}
						break;

					case COMMENT:
						c = getchar(Stream, line, column);
						if(c == '-')
							{
								c = getchar(Stream, line, column);
								if(c == '-')
									{
										c = getchar(Stream, line, column);
										if(c == '>')
											{
												state = ELEMENT;
												break;
											}
									}
							}

						break;

					case STARTELEMENT:
						c = getchar(Stream, line, column);
						if(c == '/')
							{
								c = getchar(Stream, line, column);
								if(c != '>')
									{
										Handler->Error("Unexpected character [" + sdpToString(c) + "] near end-of element", line, column);
									}

								state = ELEMENT;
								Handler->StartElement(elementname, attributes, line, column);
								depth++;

								Handler->EndElement(line, column);
								depth--;
								if(0 == depth)
									{
										Handler->EndDocument(line, column);
										return true;
									}

								elementname.clear();
								attributes.clear();
							}
						else if(c == '>')
							{
								state = ELEMENT;
								Handler->StartElement(elementname, attributes, line, column);
								depth++;
								elementname.clear();
								attributes.clear();
							}
						else if(isspace(c))
							{
								skipwhitespace(Stream, line, column);

								c = getchar(Stream, line, column);
								if(c == '/')
									{
										c = getchar(Stream, line, column);
										if(c != '>')
											{
												Handler->Error("Unexpected character [" + sdpToString(c) + "] near end-of element", line, column);
											}

										state = ELEMENT;
										Handler->StartElement(elementname, attributes, line, column);
										depth++;

										Handler->EndElement(line, column);
										depth--;

										if(0 == depth)
											{
												Handler->EndDocument(line, column);
												return true;
											}

										elementname.clear();
										attributes.clear();
									}
								else if(c == '>')
									{
										state = ELEMENT;
										Handler->StartElement(elementname, attributes, line, column);
										depth++;
										elementname.clear();
										attributes.clear();
									}
								else
									{
										state = ATTRIBUTENAME;
										attributename += c;
									}
							}
						else
							{
								elementname += c;
							}
						break;

					case ATTRIBUTENAME:
						c = getchar(Stream, line, column);
						if(c == '=')
							{
								skipwhitespace(Stream, line, column);

								c = getchar(Stream, line, column);
								if(c != '\'' && c != '"')
									{
										Handler->Error("Unexpected character [" + sdpToString(c) + "] near begining-of attribute value", line, column);
									}

								state = ATTRIBUTEVALUE;
								break;
							}
						else if(isspace(c))
							{
								skipwhitespace(Stream, line, column);
							}
						else
							{
								attributename += c;
							}
						break;

					case ATTRIBUTEVALUE:
						c = getchar(Stream, line, column);
						if(c == '\'' || c == '"')
							{
								attributes.push_back(attributename);
								attributes.push_back(attributevalue);
								attributename.clear();
								attributevalue.clear();

								state = STARTELEMENT;
							}
						else
							{
								attributevalue += c;
							}
						break;

					case ELEMENT:
						c = getchar(Stream, line, column);
						if(c == '<')
							{
								characterdata.trim();
								if(characterdata.size())
									{
										Handler->Characters(characterdata, line, column);
										characterdata.clear();
									}

								c = Stream.peek();
								if(c == '/')
									{
										state = ENDELEMENT;
									}
								else if(c == '!')
									{
										state = COMMENT;
									}
								else
									{
										state = STARTELEMENT;
									}
							}
						else
							{
								characterdata += c;
							}
						break;

					case ENDELEMENT:
						c = getchar(Stream, line, column);
						if(c == '>')
							{
								state = ELEMENT;
								Handler->EndElement(line, column);
								depth--;

								if(0 == depth)
									{
										Handler->EndDocument(line, column);
										return true;
									}
							}
						break;
				}
		}

	// If we got this far, we're missing a close-element somewhere ...
	Handler->Error("Premature end-of-document at depth " + sdpToString(depth), line, column);

	// Finish the document ...
	Handler->EndDocument(line, column);

	return true;
}

} // namespace sdpxml


