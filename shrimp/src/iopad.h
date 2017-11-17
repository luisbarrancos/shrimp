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

#ifndef IOPAD_H
#define IOPAD_H

#include "gridentity.h"

#include <gdk/gdk.h>

#include <sdptypes/sdptypes.h>

#include <set>

class Block;
bool changeBlockType(Block* block, std::string new_type);

struct ltstr
{
	bool operator()(const std::string& s1, const std::string& s2) const
	{
		return(s1 < s2);
	}
};

class IOPad :
	public GridEntity
{
public:
	IOPad();

	virtual void draw(GdkPixmap* pixmap, GdkGC* gc, int zoom);

	bool isIOPad() { return true; }

	Block* getParent() { return parent; }
	void setParent(Block* p) { parent = p; }

	virtual bool isInput() = 0;
	virtual bool isConnectable() = 0;

	virtual bool canChangeType(std::string new_type) = 0;
	virtual void suggestType(std::string new_type) = 0;
	bool changeType(std::string new_type);
	bool supportsType(std::string new_type) { return types.count(new_type); }

	std::string getType() { return type; }
	virtual void setType(std::string t) { type = t; }
	void addType(std::string t) { types.insert(t); }
	void clearTypes() { types.clear(); }
	int numTypes() { return types.size(); }
protected:
	//block the pad belongs to
	Block* parent;

	//current type
	std::string type;
	//set of allowable types
	std::set<std::string, ltstr> types;
};

class OutputPad:
	public IOPad
{
public:
	OutputPad() :
		links(0)
	{
	}

	bool isInput() { return false; }
	bool isConnectable() { return links == 0; }

	bool canChangeType(std::string new_type);
	void suggestType(std::string new_type);

	void ref() { links++; }
	void unref() { links--; }

private:
	int links;
};

class InputPad:
	public IOPad
{
public:
	InputPad();

	void setName(std::string new_name){ name = base_name = new_name; }

	void connect(OutputPad* op);
	void disconnect();

	bool isInput() { return true; }
	bool isConnectable() { return connection == 0; }
	OutputPad* getConnection() { return connection; }

	bool canChangeType(std::string new_type);
	void suggestType(std::string new_type);
	void setType(std::string new_type);

	bool isShaderVar() { return is_shader_var; }
	void setShaderVar(bool b) { is_shader_var = b; }

	bool usesStringValue() { return use_string_val; }
	void usesStringValue(bool b){ use_string_val = b; }
	std::string getStringValue() { return string_val; }
	void setStringValue(std::string v);
	sdpVector3 getDecodedValue() { return decoded_val; }
	void setDecodedValue(sdpVector3 v);

	bool isMultiPad() { return  is_multipad; }
	void setMultiPad(bool b) { is_multipad = b; }
	bool isCopy(){ return is_copy; }
	void setCopy(bool b){ is_copy = b; }
	std::string getSeparator(){ return separator; }
	void setSeparator(std::string s){ separator = s; }
	std::string getBaseName(){ return base_name; }
	void setBaseName(std::string n){ base_name = n; }

protected:
	//whether variable appears in the shader interface
	bool is_shader_var;
	//whether we should use the string or the decoded value
	bool use_string_val;
	std::string string_val;
	sdpVector3 decoded_val;

	//whether the pad can have multiple instances
	bool is_multipad;
	//whether this pad is a copy of a multi pad,
	//ie whether this pad is described in the block file
	bool is_copy;
	//The string to be planted between each maultipad value
	std::string separator;
	//the base name to add extensions to.
	std::string base_name;

	OutputPad* connection;
};

#endif // IOPAD_H

