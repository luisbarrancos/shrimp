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

#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "gridentity.h"
#include "iopad.h"
#include "block.h"

#include <gdk/gdk.h>
#include <gtk/gtkwidget.h>

#include <sdpxml/sdpxml.h>

#include <map>
#include <vector>

typedef std::map<std::string, Block*, ltstr> block_ids_t;

class Circuit
{
public:
	Circuit(GtkWidget* drawingarea);
	~Circuit();

	void draw(GdkPixmap* pixmap, GdkGC* gc);

	const std::string getName() { return name; }
	void setName(const std::string& new_name) { name = new_name; }
	const std::string getAbout(){ return about; }
	void setAbout(const std::string& new_about){ about = new_about; }

	//convert between coords
	int toGrid(int screen_coord) { return screen_coord / zoom; }
	int toScreen(int grid_coord) { return grid_coord * zoom; }

	void clear();
	bool resize(int new_x, int new_y);
	int getXSize() { return xSize; }
	int getYSize() { return ySize; }

	GridEntity* entityAt(int x, int y);
	bool freeSpaceAt(int x, int y, int w, int h);
	void addBlock(Block* new_block);
	void removeBlock(Block* the_block); //removes from grid but keeps in blocks
	void replaceBlock(Block* the_block); //replaces block in grid
	void deleteBlock(Block* the_block);

	void setZoom(int new_zoom);
	int getZoom(){ return zoom; }
	void writeCode(const std::string& filename);

	const std::string getShaderType() { return shader_type; }
	void setShaderType(const std::string& type) { shader_type = type; }

	Circuit* getParent() { return parent; }
	void setParent(Circuit* p) { parent = p; }

	const std::string getFilename() { return circuitFilename; }
	void setFilename(std::string f) { circuitFilename = f; }
	bool load(sdpxml::Element& circuit, const std::string& base_path);
	bool load_block(sdpxml::Element& block, block_ids_t& block_ids, const std::string& base_path);
	void saveCircuit(sdpxml::Element& circuit);

private:
	int xSize;
	int ySize;
	GridEntity** grid;
	GtkWidget* canvas;
	std::string name;
	std::string about;
	std::string circuitFilename;

	std::vector<Block*> blocks;

	/*
	enum shaderType {
		Surface,
		Displacement,
		Light,
		Volume,
		Function
	} type;*/

	std::string shader_type;

	//number of pixels per grid cell
	int zoom;

	void drawGrid(GdkPixmap* pixmap, GdkGC* gc);

	Circuit* parent;
};

#endif // CIRCUIT_H

