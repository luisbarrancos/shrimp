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

#include "block.h"

#include <fstream>
#include <iostream>

// global reference to allow the creation of unique block names.
std::set<std::string, ltstr> block_names;

Block::Block()
{
	xpos = ypos = 5;
	xsize = 5;
	ysize = 2;

	code_written = false;
	imortal = false;
	type = "float";
	usage = "None specified";

	makeUniqueID();
}

Block::~Block()
{
	// Delete all stuff in in_pads and out_pads;
	std::vector<InputPad*>::iterator it;
	for(it = in_pads.begin(); it != in_pads.end(); it++)
		delete(*it);

	std::vector<OutputPad*>::iterator ot;
	for(ot = out_pads.begin(); ot != out_pads.end(); ot++)
		delete(*ot);

	in_pads.clear();
	out_pads.clear();

	// Remove id name;
	block_names.erase(id);
}

void Block::draw(GdkPixmap* pixmap, GdkGC* gc, int zoom)
{
	int x,y,w,h;
	int tx, ty, tw, th;

	x = (int)(zoom*(xpos + 0.2));
	y = (int)(zoom*(ypos + 0.2));
	w = (int)(zoom*(xsize - 0.4));
	h = (int)(zoom*(ysize - 0.4));

	gdk_rgb_gc_set_foreground(gc, 0xaaaaaa);
	gdk_draw_rectangle(pixmap, gc, TRUE, x, y, w, h);

	gdk_rgb_gc_set_foreground(gc, 0xdddddd);
	gdk_draw_line(pixmap, gc, x, y, x + w, y);
	gdk_draw_line(pixmap, gc, x, y, x, y + h);

	gdk_rgb_gc_set_foreground(gc, 0x666666);
	gdk_draw_line(pixmap, gc, x, y + h, x + w, y + h);
	gdk_draw_line(pixmap, gc, x + w, y, x + w, y + h);


	GdkGCValues values;
	GdkFont* font;
	gdk_gc_get_values(gc, &values);
	font = values.font;

	tw = gdk_string_measure(font, name.c_str());
	th = gdk_string_height(font, name.c_str());
	tx = x + (w - tw)/2; //centre text
	ty = y + th + zoom/3;

	gdk_rgb_gc_set_foreground(gc, 0x222222);
	gdk_draw_string(pixmap, font, gc, tx, ty, name.c_str());

	std::vector<InputPad*>::iterator it;
	InputPad* inp;
	OutputPad* link;
	for(it = in_pads.begin(); it != in_pads.end(); it++)
	{
		inp = *it;
		inp->draw(pixmap, gc, zoom);
		link = inp->getConnection();
		if(link != 0)
		{
			int x0 = (int)(zoom*(inp->getXPos()));
			int y0 = (int)(zoom*(inp->getYPos() + 0.5));
			int x1 = (int)(zoom*(link->getXPos() + 1));
			int y1 = (int)(zoom*(link->getYPos() + 0.5));

			gdk_rgb_gc_set_foreground(gc, 0x333333);
			gdk_draw_line(pixmap, gc, x0, y0, x1, y1);
		}
	}

	std::vector<OutputPad*>::iterator ot;
	for(ot = out_pads.begin(); ot != out_pads.end(); ot++)
	{
		(*ot)->draw(pixmap, gc, zoom);
	}

}

void Block::setName(const std::string& new_name)
{
	name = new_name;
	makeUniqueID();
}

void Block::setPos(const int x, const int y)
{
	int xdiff = x - xpos;
	int ydiff = y - ypos;

	std::vector<InputPad*>::iterator it;
	for(it = in_pads.begin(); it != in_pads.end(); it++)
		(*it)->setPos((*it)->getXPos() + xdiff, (*it)->getYPos() + ydiff);

	std::vector<OutputPad*>::iterator ot;
	for(ot = out_pads.begin(); ot != out_pads.end(); ot++)
		(*ot)->setPos((*ot)->getXPos() + xdiff, (*ot)->getYPos() + ydiff);

	xpos = x;
	ypos = y;
}

void Block::addInput(InputPad* ip)
{
	in_pads.push_back(ip);

	inpad_names.insert(ip->getName());

	if(ip->numTypes() > 1)
		changeBlockType(this, ip->getType());

	ip->setPos(xpos, ypos + in_pads.size());
	ip->setParent(this);

	if(in_pads.size() > ysize - 2)
		ysize++;
}

void Block::addOutput(OutputPad* op)
{
	out_pads.push_back(op);

	if(op->numTypes() > 1)
		changeBlockType(this, op->getType());

	op->setPos(xpos + xsize - 1, ypos + out_pads.size());
	op->setParent(this);

	if(out_pads.size() > ysize - 2)
		ysize++;
}

// Adds a copy of ip to the block.
InputPad* Block::newMultiInput(InputPad* ip)
{
	g_assert(ip);
	InputPad* newpad = new InputPad();

	newpad->setType(ip->getType());

	if(ip->supportsType("float"))
		newpad->addType("float");
	if(ip->supportsType("point"))
		newpad->addType("point");
	if(ip->supportsType("vector"))
		newpad->addType("vector");
	if(ip->supportsType("normal"))
		newpad->addType("normal");
	if(ip->supportsType("color"))
		newpad->addType("color");
	if(ip->supportsType("string"))
		newpad->addType("string");

	newpad->setName(getUniquePadName(ip->getBaseName()));
	newpad->setBaseName(ip->getBaseName());
	newpad->setDesc(ip->getDesc());
	newpad->setMultiPad(true);
	newpad->setCopy(true);
	newpad->setSeparator(ip->getSeparator());

	// This places the new pad at the bottom.
	// It would be better if it were placed directly below ip
	addInput(newpad);

	return newpad;
}

// Removes a previously added multipad
void Block::removeMultiInput(InputPad* ip)
{
	inpad_names.erase(ip->getName());

	// Delete the pad from in_pads
	std::vector<InputPad*>::iterator it;
	for(it = in_pads.begin(); it != in_pads.end(); it++)
	{
		if(*it != ip)
			continue;

		delete ip;
		in_pads.erase(it);
		break;
	}
}

// Disconnects all inputs
void Block::disconnectAll()
{
	std::vector<InputPad*>::iterator it;
	for(it = in_pads.begin(); it != in_pads.end(); it++)
		(*it)->disconnect();
}

// Disconnects any inputs connected to any pads on the_block
void Block::disconnectFrom(Block* the_block)
{
	std::vector<InputPad*>::iterator it;
	for(it = in_pads.begin(); it != in_pads.end(); it++)
	{
		OutputPad* link = (*it)->getConnection();
		if(link != 0)
			if(link->getParent() == the_block)
				(*it)->disconnect();
	}
}

InputPad* Block::getInputPad(const std::string& pad_name)
{
	std::vector<InputPad*>::iterator it;
	for(it = in_pads.begin(); it != in_pads.end(); it++)
		if((*it)->getName() == pad_name)
			return *it;

	std::cerr << "getInputPad: '" << pad_name << "' not found!" << in_pads.size() << std::endl;
	return 0;
}

OutputPad* Block::getOutputPad(const std::string& pad_name)
{
	std::vector<OutputPad*>::iterator ot;
	for(ot = out_pads.begin(); ot != out_pads.end(); ot++)
		if((*ot)->getName() == pad_name)
			return *ot;

	std::cerr << "getOutputPad: '" << pad_name << "' not found!" << this << std::endl;
	return 0;
}

void Block::getInputHelpString(std::string& result)
{
	if(in_pads.empty())
		result = "No inputs";
	else
	{
		std::vector<InputPad*>::iterator it;
		for(it = in_pads.begin(); it != in_pads.end(); it++)
		{
			result += (*it)->getName();
			result += ":\t" + (*it)->getDesc() + "\n";
		}
	}
}

void Block::getOutputHelpString(std::string& result)
{
	if(out_pads.empty())
		result = "No outputs";
	else
	{
		std::vector<OutputPad*>::iterator ot;
		for(ot = out_pads.begin(); ot != out_pads.end(); ot++)
		{
			result += (*ot)->getName();
			result += ":\t" + (*ot)->getDesc() + "\n";
		}
	}
}

GridEntity* Block::elementAt(const int x, const int y)
{
	if((x > 0 && x < xsize - 1) || y == 0 || y == ysize - 1)
		return this;

	if(x == 0)
	{
		if(y <= in_pads.size())
			return in_pads[ y - 1 ];
		else
			return this;
	}
	else if(x == xsize - 1)
	{
		if(y <= out_pads.size())
			return out_pads[ y - 1 ];
		else
			return this;
	}

	std::cout << "Error: coords outside block\n";
	return 0;
}

void Block::classifyIOPads(std::string& parameters, std::string& locals)
{
	std::vector<InputPad*>::iterator it;
	for(it = in_pads.begin(); it != in_pads.end(); it++)
	{
		if((*it)->isConnectable())
		{
			if((*it)->isShaderVar())
			{
/*				if((*it)->usesStringValue())
				{*/
					parameters += "\t\t" + (*it)->getType() + " " +
						id + "_" + (*it)->getName() + "=" +
						(*it)->getStringValue() + ";\n";
/*				}
				else
				{
					parameters += "\t\t" + (*it)->getType() + " " +
						id + "_" +(*it)->getName() +
						(*it)->getDecodedValue() + ";\n";
				}*/
			}
			/*else
			{
				locals += "\t" + (*it)->getType() + " " +
					id + "_" + (*it)->getName() + " = " +
					(*it)->getValue() + ";\n";
			}*/
		}
	}

	std::vector<OutputPad*>::iterator ot;
	for(ot = out_pads.begin(); ot != out_pads.end(); ot++)
	{
		locals += "\t" + (*ot)->getType() + " " +
			id + "_" + (*ot)->getName() + ";\n";
	}
}

void Block::writeIncludes(std::set<std::string, ltstr>& include_set)
{
	std::vector<std::string>::iterator it;
	for(it = includes.begin(); it != includes.end(); it++)
	{
		std::string line = "#include <" + (*it) + ">\n";
		include_set.insert(line);
	}
}

// (recursive) write the code neccessary to compute the outputs.
void Block::writeCode(std::ofstream& file)
{
	std::string r_code = code;

	//insert type name for any casts in code
	replaceVariable("$(var_type)", type);

	std::vector<InputPad*>::iterator it;
	for(it = in_pads.begin(); it != in_pads.end(); it++)
	{

		if((*it)->isMultiPad() && !(*it)->isCopy())
			expandMultiPad((*it));

		if(!(*it)->isConnectable())
		{
			OutputPad* link = (*it)->getConnection();
			if(! link->getParent()->codeWritten())
				link->getParent()->writeCode(file);
			replaceVariable("$(" + (*it)->getName() + ")",
				link->getParent()->getID() + "_" + link->getName());
		}
		else
		{
			replaceVariable("$(" + (*it)->getName() + ")", (*it)->getStringValue());
		}
	}

	std::vector<OutputPad*>::iterator ot;
	for(ot = out_pads.begin(); ot != out_pads.end(); ot++)
	{
		//rewrite the output names with unique ones
		replaceVariable("$(" + (*ot)->getName() + ")", id + "_" + (*ot)->getName());
	}

	file << code << "\n";
	code_written = true;

	//return code to original state
	code = r_code;
}

void Block::saveBlockRef(sdpxml::Element& b)
{
	b.Attributes().push_back(sdpxml::Attribute("file", filename));
	b.Attributes().push_back(sdpxml::Attribute("id", id));
	b.Attributes().push_back(sdpxml::Attribute("position", std::string(sdpToString(xpos) + " " + sdpToString(ypos))));

	std::vector<InputPad*>::iterator it;
	for(it = in_pads.begin(); it != in_pads.end(); it++)
	{
		b.Children().push_back(sdpxml::Element("input"));
		sdpxml::Element& pad(b.Children().back());

		pad.Attributes().push_back(sdpxml::Attribute("name", (*it)->getName()));
		pad.Attributes().push_back(sdpxml::Attribute("type", (*it)->getType()));

		if((*it)->isShaderVar())
			pad.Attributes().push_back(sdpxml::Attribute("shadervar", "true"));
		else
			pad.Attributes().push_back(sdpxml::Attribute("shadervar", "false"));

		if((*it)->isMultiPad())
		{
			pad.Attributes().push_back(sdpxml::Attribute("multi", "true"));
			pad.Attributes().push_back(sdpxml::Attribute("separator", (*it)->getSeparator()));

			if((*it)->isCopy())
			{
				pad.Attributes().push_back(sdpxml::Attribute("copy", "true"));
				pad.Attributes().push_back(sdpxml::Attribute("basename", (*it)->getBaseName()));
			}
		}

		if((*it)->isConnectable())
		{
			if((*it)->usesStringValue())
				pad.Attributes().push_back(sdpxml::Attribute("value", (*it)->getStringValue()));
			else
				pad.Attributes().push_back(sdpxml::Attribute("value", sdpToString((*it)->getDecodedValue())));
		}
		else
		{
			pad.Children().push_back(sdpxml::Element("connection"));
			sdpxml::Element& con(pad.Children().back());

			OutputPad* link = (*it)->getConnection();

			con.Attributes().push_back(sdpxml::Attribute("outputname", link->getName()));
			con.Attributes().push_back(sdpxml::Attribute("outputparentid", link->getParent()->getID()));
		}
	}

	std::vector<OutputPad*>::iterator ot;
	for(ot = out_pads.begin(); ot != out_pads.end(); ot++)
	{
		b.Children().push_back(sdpxml::Element("output"));
		sdpxml::Element& pad(b.Children().back());

		pad.Attributes().push_back(sdpxml::Attribute("name", (*ot)->getName()));
		pad.Attributes().push_back(sdpxml::Attribute("type", (*ot)->getType()));
	}
}

/********protected********/

void Block::replaceVariable(std::string old_var, std::string new_var)
{
	int found;
	int pos = 0;

	do
	{
		found = code.find(old_var, pos);
		if(found != code.npos)
		{
			code.replace(found, old_var.size(), new_var);
			pos = found + new_var.size();
		}
	} while(found != code.npos);

}

void Block::expandMultiPad(InputPad* ip)
{
	std::string original = "$(" + ip->getName() + ")";

	std::string nextpad = ip->getBaseName() + "_2";
	std::string expanded = original;
	for(int i = 3; inpad_names.count(nextpad) != 0; i++)
	{
		expanded = expanded + ip->getSeparator() + "$(" +
					nextpad + ")";
		nextpad = ip->getBaseName() + "_" + std::string(sdpToString<int>(i));
	}

	replaceVariable(original, expanded);
}

void Block::makeUniqueID()
{
	// Erase old id
	if(block_names.find(id) != block_names.end())
		block_names.erase(id);

	// Set new one
	id = name;

	for(int i = 2; block_names.count(id) != 0; i++)
		id = name + "_" + std::string(sdpToString<int>(i));

	block_names.insert(id);
}

std::string Block::getUniquePadName(std::string base)
{
	std::string newname = base;

	for(int i = 2; inpad_names.count(newname) != 0; i++)
		newname = base + "_" + std::string(sdpToString<int>(i));

	return newname;
}

/**********friends**********/

bool changeBlockType(Block* block, std::string new_type)
{
	bool can_change = true;

	std::vector<InputPad*>::const_iterator it = block->in_pads.begin();
	for(; it != block->in_pads.end(); it++)
		can_change &= (*it)->canChangeType(new_type);

	std::vector<OutputPad*>::iterator ot;
	for(ot = block->out_pads.begin(); ot != block->out_pads.end(); ot++)
		can_change &= (*ot)->canChangeType(new_type);

	if(!can_change)
		return false;

	for(it = block->in_pads.begin(); it != block->in_pads.end(); it++)
		(*it)->suggestType(new_type);

	for(ot = block->out_pads.begin(); ot != block->out_pads.end(); ot++)
		(*ot)->suggestType(new_type);

	block->type = new_type;

	return true;
}


