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

#include "circuit.h"
#include "helpers.h"
#include "mainwindow.h"

#include <gtk/gtkdrawingarea.h>

#include <fstream>

Circuit::Circuit(GtkWidget* drawingarea)
{
	parent = 0;
	name = "no_name"; // should not have spaces (name for a file)
	about = "Built with Shrimp.";
	shader_type = "surface";
	circuitFilename = "";

	// NB these values should be taken from a prefs file.
	xSize = 35;
	ySize = 25;
	grid = new GridEntity* [ xSize * ySize ];

	for(int i = 0; i < xSize*ySize; i++)
		grid[i] = 0;

	zoom = 22;

	canvas = drawingarea;
	gtk_drawing_area_size((GtkDrawingArea*)canvas, toScreen(xSize), toScreen(ySize));
}

Circuit::~Circuit()
{
	clear();
	delete [] grid;
}

void Circuit::draw(GdkPixmap* pixmap, GdkGC* gc)
{
	//clear background
	gdk_rgb_gc_set_foreground(gc, 0xbbbbbb);
	gdk_draw_rectangle(pixmap, gc, TRUE, 0, 0, canvas->allocation.width, canvas->allocation.height);

	drawGrid(pixmap, gc);

	std::vector<Block*>::iterator it;
	for(it = blocks.begin(); it != blocks.end(); it++)
		(*it)->draw(pixmap, gc, zoom);
}

void Circuit::clear()
{
	for(int i = 0; i < xSize*ySize; i++)
	grid[i] = 0;

	std::vector<Block*>::iterator it;
	for(it = blocks.begin(); it != blocks.end(); it++)
	{
		delete (*it);
	}

	blocks.clear();
}

// if resizing to a smaller size and in doing so blocks will be
// lost or chopped in half this function will not resize and return false
bool Circuit::resize(int new_x, int new_y)
{
	int old_x = xSize;
	int old_y = ySize;

	// Check we're not doing any damage
	if(old_x > new_x)
		if(!freeSpaceAt(new_x, 0, old_x - new_x, old_y))
			return false;

	if(old_y > new_y)
		if(!freeSpaceAt(0, new_y, old_x, old_y - new_y))
			return false;

	xSize = new_x;
	ySize = new_y;
	GridEntity** new_grid = new GridEntity* [ xSize * ySize ];

	for(int j = 0; j < ySize; j++)
	{
		for(int i = 0; i < xSize; i++)
		{
			if(i < old_x && j < old_y)
				new_grid[ i + j*xSize ] = grid[ i + j*old_x ];
			else
				new_grid[ i + j*xSize] = 0;
		}
	}

	delete [] grid;
	grid = new_grid;

	gtk_drawing_area_size((GtkDrawingArea*)canvas,
								toScreen(xSize),
								toScreen(ySize));

	return true;
}

void Circuit::setZoom(int new_zoom)
{
	zoom = new_zoom;
	gtk_drawing_area_size((GtkDrawingArea*)canvas,
								toScreen(xSize),
								toScreen(ySize));
}

// Returns true if there is enough space to fit a block w * h at coords (x,y)
bool Circuit::freeSpaceAt(int x, int y, int w, int h)
{
	if(x + w > xSize || y + h > ySize || x < 0 || y < 0)
		return false;

	int index = x + y*xSize;

	for(int j = 0; j < h; j++)
	{
		for(int i = 0; i < w; i++)
		{
			if(grid[ index + i + j*xSize ]  != 0)
				return false;
		}
	}

	return true;
}

// freeSpaceAt should be called immeadiately prior to this
// to make sure the operation is valid.
// The block's position should already be set.
void Circuit::addBlock(Block* new_block)
{
	int x,y,w,h;
	int index;

	x = new_block->getXPos();
	y = new_block->getYPos();
	w = new_block->getXSize();
	h = new_block->getYSize();

	index = x + y*xSize;

	for(int j = 0; j < h; j++)
	{
		for(int i = 0; i < w; i++)
		{
			grid[ index + i + j*xSize ] =
							new_block->elementAt(i, j);
		}
	}

	blocks.push_back(new_block);
}

// freeSpaceAt should be called immeadiately prior to this
// to make sure the operation is valid.
// The block should already be in the blocks vector.
void Circuit::replaceBlock(Block* the_block)
{
	int x,y,w,h;
	int index;

	x = the_block->getXPos();
	y = the_block->getYPos();
	w = the_block->getXSize();
	h = the_block->getYSize();

	index = x + y*xSize;

	for(int j = 0; j < h; j++)
	{
		for(int i = 0; i < w; i++)
		{
			grid[ index + i + j*xSize ] =
							the_block->elementAt(i, j);
		}
	}
}

void Circuit::removeBlock(Block* the_block)
{
	int x,y,w,h;
	int index;

	x = the_block->getXPos();
	y = the_block->getYPos();
	w = the_block->getXSize();
	h = the_block->getYSize();

	index = x + y*xSize;

	for(int j = 0; j < h; j++)
	{
		for(int i = 0; i < w; i++)
		{
			grid[ index + i + j*xSize ] = 0;
		}
	}
}

void Circuit::deleteBlock(Block* the_block)
{
	removeBlock(the_block);
	the_block->disconnectAll();

	std::vector<Block*>::iterator it;
	for(it = blocks.begin(); it != blocks.end(); it++)
	{
		(*it)->disconnectFrom(the_block);
	}


	//delete the_block from blocks
	for(it = blocks.begin(); it != blocks.end(); it++)
	{
		if(*it == the_block)
		{
			delete the_block;
			blocks.erase(it);
			break;
		}
	}
}

GridEntity* Circuit::entityAt(int x, int y)
{
	int index = x + y*xSize;

	if(x >= xSize || y >= ySize || x < 0 || y < 0)
		return 0;
	else
		return grid[ index ];
}

void Circuit::writeCode(const std::string& filename)
{
	std::ofstream file(filename.c_str());

	//if (checkForLoops())
	//	return; error.

	file << "/*  Shader generated by Shrimp  */\n\n";

	std::string parameters;
	std::string locals;
	std::set<std::string, ltstr>includes;
	std::vector<Block*>::iterator it;
	for(it = blocks.begin(); it != blocks.end(); it++)
	{
		(*it)->resetCodeWritten();
		(*it)->writeIncludes(includes);
		(*it)->classifyIOPads(parameters, locals);
	}

	std::set<std::string, ltstr>::iterator inc;
	for(inc = includes.begin(); inc != includes.end(); inc++)
		file << (*inc);

	file << "\n\n";
	file << shader_type << std::endl;
	file << name;
	file << "(\n" << parameters << ")\n";
	file << "{\n" << locals << "\n\n";

	//blocks[0] is always the output block
	blocks[0]->writeCode(file);

	file << "\n}\n";
	file.close();
}

void Circuit::saveCircuit(sdpxml::Element& circuit)
{
	circuit.Attributes().push_back(sdpxml::Attribute("gridsize", std::string(sdpToString<int>(xSize) + " " + sdpToString<int>(ySize))));

	std::vector<Block*>::iterator it;
	for(it = blocks.begin(); it != blocks.end(); it++)
	{
		circuit.Children().push_back(sdpxml::Element("block"));
		(*it)->saveBlockRef(circuit.Children().back());
	}
}

bool Circuit::load(sdpxml::Element& circuit, const std::string& base_path)
{
	sdpxml::AttributeCollection::iterator a;
	for(a = circuit.Attributes().begin(); a != circuit.Attributes().end(); a++)
	{
		if(a->Name() == "gridsize")
		{
			sdpVector2 size;
			size = sdpxml::GetAttribute(circuit, "gridsize", sdpVector2(0, 0));
			resize((int)size[0], (int)size[1]);
		}
	}

	// Associate block id with pointer to that block
	block_ids_t block_ids;
	// Add all block ids to map
	for(sdpxml::ElementCollection::iterator ele = circuit.Children().begin(); ele != circuit.Children().end(); ele++)
		if(ele->Name() == "block")
			load_block(*ele, block_ids, base_path);

	// Process blocks and connections
	for(sdpxml::ElementCollection::iterator ele = circuit.Children().begin(); ele != circuit.Children().end(); ele++)
	{
		if(ele->Name() == "block")
		{
			sdpxml::Attribute* block_id = sdpxml::FindAttribute(*ele, sdpxml::SameName("id"));
			Block* b = block_ids[block_id->Value()];


			// Handle other attributes
			for(sdpxml::AttributeCollection::iterator attr = ele->Attributes().begin(); attr != ele->Attributes().end(); attr++)
			{
				if(attr->Name() == "position")
				{
					sdpVector2 pos = sdpxml::GetAttribute(*ele, "position", sdpVector2(0, 0));
					b->setPos((int)pos[0], (int)pos[1]);
				}
			}

			addBlock(b);

			// Handle connections
			for(sdpxml::ElementCollection::iterator pad = ele->Children().begin(); pad != ele->Children().end(); pad++)
			{
				if(pad->Name() == "input")
				{
					// This name is used to refer to the pad not to change its name
					std::string in_name = sdpxml::GetAttribute(*pad, "name", std::string(""));
					InputPad* inpad = b->getInputPad(in_name);
					if(!inpad)
						continue;

					sdpxml::Attribute* at = sdpxml::FindAttribute(*pad, sdpxml::SameName("type"));
					inpad->setType(at->Value());

					at = sdpxml::FindAttribute(*pad, sdpxml::SameName("shadervar"));
					if(at)
						inpad->setShaderVar(at->Value() == "true");

					at = sdpxml::FindAttribute(*pad, sdpxml::SameName("value"));
					if(at)
					{
						if(isNumbers(at->Value()))
						{
							sdpVector3 tmp = sdpFromString<sdpVector3>(at->Value(), sdpVector3(0, 0, 0));
							inpad->setDecodedValue(tmp);
						}
						else
						{
							inpad->usesStringValue(true);
							inpad->setStringValue(at->Value());
						}
					}
					at = sdpxml::FindAttribute(*pad, sdpxml::SameName("multi"));
					if(at)
						inpad->setMultiPad(at->Value() == "true");

					at = sdpxml::FindAttribute(*pad, sdpxml::SameName("separator"));
					if(at)
						inpad->setSeparator(at->Value());

					sdpxml::Element* con =
						sdpxml::FindElement(*pad, sdpxml::SameName("connection"));
					if(con)
					{
						std::string out_parent_id, out_name, result;

						out_parent_id = sdpxml::GetAttribute(*con, "outputparentid", std::string(""));

						out_name = sdpxml::GetAttribute(*con, "outputname", std::string(""));

						Block* from = block_ids[ out_parent_id ];
						g_assert(from != 0);
						OutputPad* outpad = from->getOutputPad(out_name);
						g_assert(outpad != 0);

						inpad->connect(outpad);
					}
				}
				else if(pad->Name() == "output")
				{
					std::string out_name = sdpxml::GetAttribute(*pad, "name", std::string(""));
					OutputPad* outpad = b->getOutputPad(out_name);
					if(outpad)
					{
						sdpxml::Attribute* at = sdpxml::FindAttribute(*pad, sdpxml::SameName("type"));
						outpad->setType(at->Value());
						changeBlockType(b, at->Value());
					}
				}
			}
		}
	}

	return true;
}

bool Circuit::load_block(sdpxml::Element& block, block_ids_t& block_ids, const std::string& base_path)
{
	sdpxml::Attribute* block_file = sdpxml::FindAttribute(block, sdpxml::SameName("file"));
	Block* b = load_block_file(block_file->Value(), base_path);
	if(!b)
	{
		std::cout << "Error loading block " << block_file->Value() << std::endl;
		return 0;
	}

	sdpxml::Attribute* block_id = sdpxml::FindAttribute(block, sdpxml::SameName("id"));
	if(block_id)
	{
		block_ids[block_id->Value()] = b;
	}

	// Check for multi pads
	// these are not described in the file and so need to
	// be added manually before we can do connections
	for(sdpxml::ElementCollection::iterator pad = block.Children().begin(); pad != block.Children().end(); pad++)
	{
		if(pad->Name() != "input")
			continue;

		sdpxml::Attribute* at;
		at = sdpxml::FindAttribute(*pad, sdpxml::SameName("copy"));
		if(at)
		{
			if(at->Value() == std::string("true"))
			{
				InputPad* copyof;
				sdpxml::Attribute* bn;
				bn = sdpxml::FindAttribute(*pad, sdpxml::SameName("basename"));
				copyof = b->getInputPad(bn->Value());
				if(!copyof)
					continue;
				b->newMultiInput(copyof);
			}
		}
	}

	return true;
}

/******protected methods******/

void Circuit::drawGrid(GdkPixmap* pixmap, GdkGC* gc)
{
	int x, y;

	gdk_rgb_gc_set_foreground(gc, 0xcccccc);

	for(int i = 0; i <= xSize; i++)
	{
		x = toScreen(i);
		gdk_draw_line(pixmap, gc, x, 0, x, toScreen(ySize));
	}
	for(int j = 0; j <= ySize; j++)
	{
		y = toScreen(j);
		gdk_draw_line(pixmap, gc, 0, y, toScreen(xSize), y);
	}
}


