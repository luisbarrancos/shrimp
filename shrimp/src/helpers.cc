//============================================================================
//
// Shrimp Shader Generator
// Copyright (C) 2000-2004 Andy Gill
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
//============================================================================

#include "helpers.h"

#include <sdptypes/sdptypes.h>

#include <iostream>

bool isNumbers(const std::string& s)
{
	sdpString temp(s);

	//remove commas, brackets, decimal points and exponents
	temp.replaceall(",", "");
	temp.replaceall("(", "");
	temp.replaceall(")", "");
	temp.replaceall(".", "");
	temp.replaceall("e", "");
	temp.replaceall("E", "");
	temp.replaceall("-", "");
	temp.replaceall("+", "");
	temp.replaceall(" ", "");

	temp.trim();

	return temp.isnumeric();
}

void process_types(IOPad* pad, const std::string& types)
{
	std::string temp;
	std::istringstream stream(types);

	pad->clearTypes();

	stream >> temp;
	pad->addType(temp);
	pad->setType(temp); //default type is first in the list.

	//add any other types.
	while(!stream.eof())
	{
		stream >> temp;
		pad->addType(temp);
	}
}

Block* load_block_file(const std::string& filename, const std::string& base_path)
{
	std::string block_path = sdpAppendPath(base_path.c_str(), "blocks");
	std::string f_name = sdpAppendPath(block_path.c_str(), filename.c_str());

	sdpxml::Document doc(f_name);
	doc.Load(f_name);

	if(doc.Name() != "shrimp")
	{
		std::cout << "Error, " << filename << " is not a Shrimp block\n";
		return 0;
	}

	Block* b = new Block();

	for(sdpxml::AttributeCollection::iterator attr = doc.Attributes().begin(); attr != doc.Attributes().end(); attr++)
	{
		if(attr->Name() == std::string("name"))
			b->setName(std::string(attr->Value()));
		else if(attr->Name() == std::string("description"))
			b->setDesc(std::string(attr->Value()));
	}

	for(sdpxml::ElementCollection::iterator ele = doc.Children().begin(); ele != doc.Children().end(); ele++)
	{
		if(ele->Name() == std::string("input"))
		{
			InputPad* ip = new InputPad();

			// Get type first
			sdpxml::Attribute* at = sdpxml::FindAttribute(*ele, sdpxml::SameName("type"));
			if(at)
				process_types(ip, std::string(at->Value()));

			for(sdpxml::AttributeCollection::const_iterator attr = ele->Attributes().begin(); attr != ele->Attributes().end(); attr++)
			{
				if(attr->Name() == std::string("name"))
					ip->setName(std::string(attr->Value()));
				else if(attr->Name() == std::string("description"))
					ip->setDesc(std::string(attr->Value()));
				/*else if(attr->Name() == std::string("type"))
					process_types(ip, std::string(attr->Value()));*/
				else if(attr->Name() == std::string("default"))
				{
					sdpVector3 tmp;
					if(isNumbers(attr->Value()))
					{
						tmp = sdpFromString<sdpVector3>(attr->Value(), sdpVector3(0, 0, 0));
						ip->setDecodedValue(tmp);
					}
					else
					{
						ip->usesStringValue(true);
						ip->setStringValue(std::string(attr->Value()));
					}
				}
				else if(attr->Name() == std::string("shadervar"))
					ip->setShaderVar(attr->Value() == std::string("true"));
				else if(attr->Name() == std::string("multi"))
					ip->setMultiPad(attr->Value() == std::string("true"));
				else if(attr->Name() == std::string("separator"))
					ip->setSeparator(std::string(attr->Value()));
			}

			if(!ip->usesStringValue())
				ip->setDecodedValue(ip->getDecodedValue()); //recalculate now we have all info about pad
			b->addInput(ip);
		}
		else if(ele->Name() == "output")
		{
			OutputPad* op = new OutputPad();
			for(sdpxml::AttributeCollection::const_iterator attr = ele->Attributes().begin(); attr != ele->Attributes().end(); attr++)
			{
				if(attr->Name() == std::string("name"))
					op->setName(std::string(attr->Value()));
				else if(attr->Name() == std::string("description"))
					op->setDesc(std::string(attr->Value()));
				else if(attr->Name() == std::string("type"))
					process_types(op, std::string(attr->Value()));
			}

			b->addOutput(op);
		}
		else if(ele->Name() == std::string("code"))
		{
			b->setCode(std::string(ele->Text()));
		}
		else if(ele->Name() == std::string("usage"))
		{
			b->setUsage(std::string(ele->Text()));
		}
		else if(ele->Name() == std::string("include"))
		{
			b->addInclude(std::string(ele->Text()));
		}
	}

	b->setFilename(filename);

	return b;
}


