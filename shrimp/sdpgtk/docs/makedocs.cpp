// K-3D
// Copyright © 1995-2003, Timothy M. Shead
//
// Contact: tshead@k-3d.com
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public
// License along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#include <sdpxml/sdpxml.h>

static const sdpString GTKMLVersion = "0.1.7";

typedef std::multimap<sdpString, sdpxml::Element&> GTKMLElementMap;

void StartHTMLPage(SDPCSTRING Title, std::ostream& Stream)
{
	// Sanity checks ...
	g_assert_string(Title);
	g_assert(Stream.good());
	
	Stream << "<html>" << std::endl;
	Stream << "<head>" << std::endl;
	Stream << "<title>" << Title << "</title>" << std::endl;
	Stream << "<link rel=\"stylesheet\" type=\"text/css\" href=\"gtkml.css\">" << std::endl;
	Stream << "</head>" << std::endl;
	Stream << "<body>" << std::endl << std::endl;
}

void FinishHTMLPage(std::ostream& Stream)
{
	// Sanity checks ...
	g_assert(Stream.good());
	
	Stream << "</body>" << std::endl;
	Stream << "</html>" << std::endl << std::endl;
}

void Header(std::ostream& Stream)
{
	// Sanity checks ...
	g_assert(Stream.good());
	
	Stream << "<h4 align=\"right\">GTKML " << GTKMLVersion << " Reference</h4>" << std::endl;
}

void Footer(std::ostream& Stream)
{
	// Sanity checks ...
	g_assert(Stream.good());
	
	Stream << "<h4 align=\"right\">GTKML " << GTKMLVersion << " Reference</h4>" << std::endl;
}

void GetGTKMLElements(sdpxml::Element& Parent, GTKMLElementMap& Results)
{
	// Sanity checks ...
	g_assert(Parent);

	if(Parent->Name() == sdpString("element"))
		{
			const sdpString elementname = sdpxml::GetAttribute(Parent, "name", "");

			if(elementname.size())			
				Results.insert(std::make_pair(elementname, Parent));
		}
			
	for(SDPXMLELEMENTHANDLE e = Parent->FirstElement(); e; e = Parent->NextElement(e))
		GetGTKMLElements(Parent->Element(e), Results);
}

void GetGTKMLAttributes(sdpxml::Element& Parent, GTKMLElementMap& Results)
{
	// Sanity checks ...
	g_assert(Parent);
	
	for(SDPXMLELEMENTHANDLE e = Parent->FirstElement(); e; e = Parent->NextElement(e))
		{
			sdpxml::Element& element = Parent->Element(e);
			
			if(element->Name() == sdpString("attribute"))
				{				
					sdpString attributename;
					sdpxml::GetAttribute(element, "name", attributename);
					g_return_if_fail(attributename.size());
					Results.insert(std::make_pair(attributename, element));
				}
			else
				{
					GetGTKMLAttributes(element, Results);
				}
		}
}

void GetInheritedGTKMLAttributes(sdpxml::Element& Element, GTKMLElementMap& Results)
{
	for(SDPXMLELEMENTHANDLE e = Element->FirstElement(); e; e = Element->NextElement(e))
		{
			sdpxml::Element& element = Element->Element(e);
			
			if(element->Name() == sdpString("attribute"))
				{				
					sdpString attributename;
					sdpxml::GetAttribute(element, "name", attributename);
					g_return_if_fail(attributename.size());
					
					Results.insert(std::make_pair(attributename, element));
				}
		}
		
	if(Element->ParentElement())
		GetInheritedGTKMLAttributes(Element->ParentElement(), Results);
}

sdpString QualifiedAttributeName(sdpxml::Element& Attribute)
{
	// Sanity checks ...
	g_assert(Attribute);
	
	sdpString name;
	sdpxml::GetAttribute(Attribute, "name", name);
	
	sdpString ownerclass;
	sdpxml::GetAttribute(Attribute->ParentElement(), "sdpgtk", ownerclass);
	
	sdpString ownerelement;
	sdpxml::GetAttribute(Attribute->ParentElement(), "name", ownerelement);
	
	if(ownerclass.size())
		return name + "_" + ownerclass;
		
	g_assert(ownerelement.size());
	
	return name + "_" + ownerelement;
}

void CreateElementsIndex(sdpXmlIDocument* Document)
{
	// Sanity checks ...
	g_assert(Document);
	
	std::ofstream stream("elements.html");
	g_return_if_fail(stream.good());

	GTKMLElementMap elements;
	GetGTKMLElements(Document->RootElement(), elements);
			
	StartHTMLPage("GTKML Version " + GTKMLVersion + " Elements", stream);
	Header(stream);
	
	stream << "<h1>GTKML Elements</h1>" << std::endl;

	stream << "<p>GTKML currently includes the following " << elements.size() << " elements:</p>" << std::endl;

	stream << "<table>" << std::endl;
	stream << "<tr><td class=\"BOX\">GTKML Element</td><td class=\"BOX\">Description</td>" << std::endl;
	
	for(GTKMLElementMap::iterator element = elements.begin(); element != elements.end(); element++)
		{
			sdpString name = element->first;
			
			sdpString description;
			sdpxml::GetAttribute(element->second, "description", description);
			
			stream << "<tr>";
			stream << "<td><b><a href=\"element_" << name << ".html\">" << "&lt;" << name << "&gt;" << "</a></b></td>";
			stream << "<td>" << description << "</td>";
			stream << "</tr>" << std::endl;
		}
	
	stream << "</table>" << std::endl;
	
	Footer(stream);	
	FinishHTMLPage(stream);
}

void CreateElements(sdpXmlIDocument* Document)
{
	// Sanity checks ...
	g_assert(Document);
	
	GTKMLElementMap elements;
	GetGTKMLElements(Document->RootElement(), elements);
	
	for(GTKMLElementMap::iterator element = elements.begin(); element != elements.end(); element++)
		{
			sdpString name = element->first;

			sdpString description;
			sdpxml::GetAttribute(element->second, "description", description);
			
			sdpString example;
			sdpxml::GetAttribute(element->second, "example", example);
			
			sdpString children;
			sdpxml::GetAttribute(element->second, "children", children);
			
			sdpString text = "ignored";
			sdpxml::GetAttribute(element->second, "text", text);
			
			sdpString gtk = "none";
			sdpxml::GetAttribute(element->second, "gtk", gtk);
			
			sdpString sdpgtk = "none";
			sdpxml::GetAttribute(element->second, "sdpgtk", sdpgtk);
			
			GTKMLElementMap attributes;
			GetInheritedGTKMLAttributes(element->second, attributes);
			
			std::ofstream stream("element_" + name + ".html");
			g_return_if_fail(stream.good());
			
			StartHTMLPage("GTKML Version " + GTKMLVersion + " &lt;" + name + "&gt; Element", stream);
			Header(stream);
			
			stream << "<h1>&lt;" << name << "&gt; element</h1>" << std::endl;
			stream << "<h3>description:</h3><p>" << description << "</p>" << std::endl;
//			stream << "<h3>example:</h3><pre>" << example << "</pre>" << std::endl;
			stream << "<h3>children:</h3><p>" << children << "</p>" << std::endl;
			stream << "<h3>element text:</h3><p>" << text << "</p>" << std::endl;
			stream << "<h3>attributes:</h3>" << std::endl;

			if(attributes.size())
				{
					stream << "<table cellpadding=\"4\">" << std::endl;
					stream << "<tr><td class=\"BOX\">name</td><td class=\"BOX\">allowed values</td><td class=\"BOX\">default value</td><td class=\"BOX\">required?</td></tr>" << std::endl;

					bool row = true;	
					for(GTKMLElementMap::iterator attribute = attributes.begin(); attribute != attributes.end(); attribute++)
						{
							sdpString name;
							sdpxml::GetAttribute(attribute->second, "name", name);
							
							sdpString qualifiedname = QualifiedAttributeName(attribute->second);
							
							sdpString values;
							sdpxml::GetAttribute(attribute->second, "values", values);
							
							sdpString defaultvalue;
							sdpxml::GetAttribute(attribute->second, "default", defaultvalue);
							if(0 == defaultvalue.size())
								defaultvalue = "&nbsp;";
							
							sdpString required;
							sdpxml::GetAttribute(attribute->second, "required", required);
							
							sdpString rowcolor = row ? "#FFFFFF" : "#EEEEEE";
							row = !row;
	
							stream << "<tr>";
							stream << "<td bgcolor=\"" << rowcolor << "\">" << "<a href=\"attribute_" << qualifiedname << ".html\">" << name << "</a></td>";
							stream << "<td bgcolor=\"" << rowcolor << "\">" << values << "</td>";
							stream << "<td bgcolor=\"" << rowcolor << "\">" << defaultvalue << "</td>";
							stream << "<td bgcolor=\"" << rowcolor << "\">" << required << "</td>";
							stream << "</tr>" << std::endl;
						}

					stream << "</table>" << std::endl;
				}
			else
				{
					stream << "none" << std::endl;
				}

			stream << "<h3>GTK class:</h3><p>" << gtk << "</p>" << std::endl;
			stream << "<h3>SDPGTK class:</h3><p>" << sdpgtk << "</p>" << std::endl;
	
			Footer(stream);											
			FinishHTMLPage(stream);
		}	
}

void CreateAttributesIndex(sdpXmlIDocument* Document)
{
	// Sanity checks ...
	g_assert(Document);
	
	std::ofstream stream("attributes.html");
	g_return_if_fail(stream.good());

	GTKMLElementMap attributes;
	GetGTKMLAttributes(Document->RootElement(), attributes);
			
	StartHTMLPage("GTKML Version " + GTKMLVersion + " Attributes", stream);
	Header(stream);
	
	stream << "<h1>GTKML Attributes</h1>" << std::endl;

	stream << "<p>GTKML currently includes the following " << attributes.size() << " attributes:</p>" << std::endl;

	stream << "<table>" << std::endl;
	stream << "<tr><td class=\"BOX\">GTKML Attribute</td><td class=\"BOX\">Applies To</td>" << std::endl;
	
	for(GTKMLElementMap::iterator attribute = attributes.begin(); attribute != attributes.end(); attribute++)
		{
			sdpString name = attribute->first;

			sdpString qualifiedname = QualifiedAttributeName(attribute->second);

			GTKMLElementMap appliesto;
			GetGTKMLElements(attribute->second->ParentElement(), appliesto);
			
			stream << "<tr>";
			stream << "<td><b><a href=\"attribute_" << qualifiedname << ".html\">" << "&lt;" << name << "&gt;" << "</a></b></td>";
			
			stream << "<td>";
			for(GTKMLElementMap::iterator element = appliesto.begin(); element != appliesto.end(); element++)
				{
					if(element != appliesto.begin())
						stream << ", ";
						
					stream << "<a href=\"element_" << element->first << ".html\">" << element->first << "</a>";
				}
			stream << "</td>";

			stream << "</tr>" << std::endl;
		}
	
	stream << "</table>" << std::endl;
	
	Footer(stream);
	FinishHTMLPage(stream);
}

void CreateAttributes(sdpXmlIDocument* Document)
{
	// Sanity checks ...
	g_assert(Document);
	
	GTKMLElementMap attributes;
	GetGTKMLAttributes(Document->RootElement(), attributes);
	
	for(GTKMLElementMap::iterator attribute = attributes.begin(); attribute != attributes.end(); attribute++)
		{
			sdpString name = attribute->first;
			sdpString qualifiedname = QualifiedAttributeName(attribute->second);

			sdpString description;
			sdpxml::GetAttribute(attribute->second, "description", description);
			
			sdpString example;
			sdpxml::GetAttribute(attribute->second, "example", example);
			
			sdpString values;
			sdpxml::GetAttribute(attribute->second, "values", values);
			
			sdpString defaultvalue;
			sdpxml::GetAttribute(attribute->second, "default", defaultvalue);
			
			sdpString required;
			sdpxml::GetAttribute(attribute->second, "required", required);
			
			GTKMLElementMap appliesto;
			GetGTKMLElements(attribute->second->ParentElement(), appliesto);
			
			std::ofstream stream("attribute_" + qualifiedname + ".html");
			g_return_if_fail(stream.good());
			
			StartHTMLPage("GTKML Version " + GTKMLVersion + " " + name + " Attribute", stream);
			Header(stream);

			stream << "<h1>\"" << name << "\" attribute</h1>" << std::endl;

			stream << "<h3>applies to:</h3>" << std::endl;
			stream << "<p>";
			for(GTKMLElementMap::iterator element = appliesto.begin(); element != appliesto.end(); element++)
				{
					if(element != appliesto.begin())
						stream << ", ";
						
					stream << "<a href=\"element_" << element->first << ".html\">" << element->first << "</a>";
				}
			stream << "</p>";
			
			stream << "<h3>description:</h3><p>" << description << "</p>" << std::endl;
//			stream << "<h3>example:</h3><pre>" << example << "</pre>" << std::endl;
			stream << "<h3>allowed values:</h3><p>" << values << "</p>" << std::endl;
			stream << "<h3>default value:</h3><p>" << defaultvalue << "</p>" << std::endl;
			stream << "<h3>required?:</h3><p>" << required << "</p>" << std::endl;

			Footer(stream);
			FinishHTMLPage(stream);
		}	
}

int main(int argc, char argv[])
{
	sdpxml::Document doc;
	g_return_val_if_fail(doc.LoadFile("gtkmldoc.xml"), 1);
	g_return_val_if_fail(doc.RootElement(), 2);
	g_return_val_if_fail(doc.RootElement()->Name() == sdpString("gtkmldoc"), 3);

	CreateElementsIndex(&doc);
	CreateElements(&doc);
	
	CreateAttributesIndex(&doc);
	CreateAttributes(&doc);
			
	return 0;
}
