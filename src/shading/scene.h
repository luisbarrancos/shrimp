
/*
    Copyright 2008-2009, Romain Behar <romainbehar@users.sourceforge.net>

    This file is part of Shrimp 2.

    Shrimp 2 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Shrimp 2 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Shrimp 2.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef _scene_h_
#define _scene_h_

#include "shader_block.h"

#include "../miscellaneous/misc_xml.h"

#include <map>
#include <set>
#include <string>
#include <vector>


// the scene object (contains shaders)
class scene {

public:

	//////////// DAG and block data structures

	// definition of a pad, as a pair of strings:
	// the first is the block name, the second is the pad name
	typedef std::pair <std::string, std::string> io_t;

	// store connections as a directed acyclic graph, Output -> Input,
	// in a map as <input, output>, an input receives only one output
	typedef std::map <io_t, io_t> dag_t;
	dag_t m_dag;

	// the list of blocks
	typedef std::map<std::string, shader_block*> shader_blocks_t;
	shader_blocks_t m_blocks;


	//////////// Menu helpers
	// sort the blocks using the directory names they're stored in

	struct default_block_t {

		std::string name;
		std::string path;
	};
	typedef std::vector <default_block_t> default_block_list_t;
	typedef std::map <std::string, std::vector <default_block_t> > block_classification_t;
	typedef std::map <std::string, std::string> block_tree_t;
	block_classification_t m_block_classification;
	block_tree_t m_block_tree;


	//////////// Selection, rolled blocks and group data structures

	typedef std::set<std::string> selection_t;
	selection_t m_selection;

	typedef std::map<std::string, int> groups_t;;
	groups_t m_groups;

	typedef std::set<int> groups_selection_t;;
	groups_selection_t m_groups_selection;

	typedef std::map<int, std::string> group_names_t;
	group_names_t m_group_names;


	//////////// Functions

	scene();
	~scene();

	// get and set name, description
	const std::string name() const;
	void set_name (const std::string& Name);
	const std::string description() const;
	void set_description (const std::string& Description);

	// reset scene
	void empty_scene();
	// create default elements
	void new_scene();

	// load predefined Shrimp blocks
	void load_default_blocks (const std::string& BlockPath, const std::string& DirName, unsigned long& BlockCount, const std::string& Parent);


	//////////// Blocks

	// add a block to the scene
	void add_block (const std::string& BlockId, const std::string& BlockFile, shader_block* Block);
	// create a block from the predefined block list and add it to the scene
	shader_block* add_predefined_block (const std::string& BlockName);
	// add a new (empty) block to the scene
	shader_block* add_custom_block (const std::string& Name = "New block", const bool RootBlock = false);
	// remove a block from the network and delete it
	void delete_block (const std::string& BlockName);

	// get a block's pointer from its name
	shader_block* get_block (const std::string& Name);
	// find the root block
	shader_block* get_root_block();
	// make a block name unique in the scene
	std::string get_unique_block_name (const std::string& Name) const;
	// set a block's name, making sure it's unique
	void set_block_name (shader_block* Block, const std::string& NewName);

	// connect two blocks
	void connect (const io_t& Input, const io_t& Output);
	// disconnect an input or output from the network
	void disconnect (const io_t& IO);
	// tell whether an input is connected to an output
	bool is_connected (const io_t& Input);

	// list of upward blocks in the DAG (parents + parents' parents + etc)
	void upward_blocks (shader_block* StartingBlock, shader_blocks_t& List);

	//////////// Serialization

	// load and save a scene (a network of blocks with additional information, in an XML file)
	bool load (const std::string& Scene);
	bool save_as (const std::string& ShaderFile);

	// return an XML representation of the shader
	xml::element xml_network();


	//////////// Selection

	// returns whether a block is selected
	bool is_selected (const shader_block* Block);

	// returns the size of the selection set
	int selection_size();

	// clear current selection
	void clear_selection();

	// toggle block selection state
	void set_block_selection (shader_block* Block, const bool Selection);




	//////////// Rolled blocks

	// returns whether a block is rolled
	bool is_rolled (const shader_block* Block) const;

	// returns the number of rolled blocks
	int rolled_block_count();

	// unroll all blocks
	void unroll_all_blocks();

	// toggle block rolled / unrolled (normal)
	void set_block_rolled_state (shader_block* Block, const bool Rolled);


	//////////// Grouping

	// useful function to retrieve groups (not used for storage)
	typedef std::set<int> group_set_t;
	group_set_t group_list();

	// turn current selection into a group
	void group_selection();

	// add a block to a group
	void add_to_group (const std::string& Block, const int Group);

	// returns the number of the group the block belongs to (0 == no group)
	int group (const shader_block* Block);

	// dismantles a group
	void ungroup (const int Group);

	// group name functions
	const std::string get_group_name (const int Group) const;
	void set_group_name (const int Group, const std::string& Name);

	std::string get_shader_code();
	void show_preview (const std::string& TempDir);

	// save current scene's RIB and shader files to a directory
	void export_scene (const std::string& Directory);

	// toggle group selection state
	void set_group_selection (const int Group , const bool Selection);

	// returns whether a group is selected
	bool is_selected (const int Group);

	//////////// Misc

	void bounding_box (double& Left, double& Right, double& Bottom, double& Top);
	shader_block* get_parent (const std::string& BlockName, const std::string& Input, std::string& ParentOutput) const;


private:

	//////////// Scene

	// scene name
	std::string m_name;
	// scene description
	std::string m_description;

	// the current scene file name (when saving)
	std::string m_file_name;

	rib_root_block* m_rib_root_block;


	//////////// List of available default blocks
	// the ones that come with the application and are loaded at launch

	typedef std::map <std::string, default_block_t> default_blocks_t;
	default_blocks_t m_default_blocks;

};

#endif // _scene_h_

