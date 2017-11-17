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

#ifndef BLOCK_H
#define BLOCK_H

#include "gridentity.h"
#include "iopad.h"

#include <gdk/gdk.h>

#include <sdpxml/sdpxml.h>

#include <set>
#include <vector>

class Block :
	public GridEntity
{
public:
	Block();
	~Block();

	bool isIOPad() { return false; }
	virtual void draw(GdkPixmap* pixmap, GdkGC* gc, int zoom);
	//virtual void writeCode(file) = 0;

	void setPos(const int x, const int y);
	void setName(const std::string& new_name);
	std::string getID() { return id; }
	std::string getUsage() { return usage; }
	void setUsage(const std::string& s) { usage = s; }

	void addInput(InputPad* ip);
	void addOutput(OutputPad* op);
	InputPad* newMultiInput(InputPad* ip);
	void removeMultiInput(InputPad* ip);
	void disconnectAll();
	void disconnectFrom(Block* the_block);
	InputPad* getInputPad(const std::string& pad_name);
	OutputPad* getOutputPad(const std::string& pad_name);
	int numInputs(){ return in_pads.size(); }
	int numOutputs(){ return out_pads.size(); }
	void getInputHelpString(std::string& result);
	void getOutputHelpString(std::string& result);

	//adds input->name and output->name to the appropriate strings for each pad
	void classifyIOPads(std::string& parameters, std::string& locals);

	void addInclude(std::string inc) { includes.push_back(inc); }
	void writeIncludes(std::set<std::string, ltstr>& include_set);

	void makeImortal(){ imortal = true; }
	bool isImortal(){ return imortal; }

	void setCode(std::string c) { code = c; }
	std::string getCode() { return code; }
	void writeCode(std::ofstream& file);
	void resetCodeWritten() { code_written = false; }
	bool codeWritten() { return code_written; }

	std::string getFilename() { return filename; }
	void setFilename(const std::string& f) { filename = f; }

	void saveBlockRef(sdpxml::Element& b);

	GridEntity* elementAt(const int x, const int y);

	friend bool changeBlockType(Block* block, std::string new_type);

protected:
	//unique identifier
	std::string id;

	//a help string detailing the blocks function
	std::string usage;

	//the file that holds the full description of this block
	std::string filename;

	//Is this block allowed to be deleted.
	//Only input/output blocks should be imortal.
	bool imortal;

	//the code to write
	std::string code;
	//replace all occurences in code of old_var with new_var
	void replaceVariable(std::string old_var, std::string new_var);

	//replace all occurences of ip pad name with all copies of pad
	//separated by the separator string.
	void expandMultiPad(InputPad* ip);

	//don't generate the code for a block more than once
	bool code_written;

	void makeUniqueID();
	std::string getUniquePadName(std::string base);

	//files to be #included in code
	std::vector<std::string> includes;

	std::vector<InputPad*> in_pads;
	std::vector<OutputPad*> out_pads;

	//record of pad names to allow the creation of unique multipad
	//names.
	std::set<std::string, ltstr> inpad_names;

	//the type that all the changeable types are
	std::string type;
};

#endif // BLOCK_H

