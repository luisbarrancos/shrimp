
/*
    Copyright 2008, Romain Behar <romainbehar@users.sourceforge.net>

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


#include "scene.h"
#include "rib_root_block.h"

#include "preferences.h"

#include <fltk/filename.h>

#include "../miscellaneous/logging.h"
#include "../miscellaneous/misc_string_functions.h"
#include "../miscellaneous/misc_xml.h"

#include <fstream>
#include <iostream>


scene::scene() :
	m_file_name(std::string(""))
{
	unsigned long successful_blocks = 0;
	load_default_blocks ("./blocks", "blocks", successful_blocks, "");
	log() << aspect << "Successfully loaded " << successful_blocks << " blocks." << std::endl;

	new_scene();
}


scene::~scene() {

}


const std::string scene::name() const {

	return m_name;
}

void scene::set_name (const std::string& Name) {

	m_name = Name;
}

const std::string scene::description() const {

	return m_description;
}

void scene::set_description (const std::string& Description) {

	m_description = Description;
}

void scene::empty_scene() {

	log() << aspect << "Emptying current scene." << std::endl;

	// delete scene information
	m_name = "";
	m_description = "";
	m_file_name = "";

	// delete scene structure
	m_dag.clear();
	m_selection.clear();
	m_groups.clear();
	m_group_names.clear();

	// delete blocks
	for (shader_blocks_t::iterator block_i = m_blocks.begin(); block_i != m_blocks.end(); ++block_i) {

		delete block_i->second;
	}
	//delete m_rib_root_block;

	m_blocks.clear();
}


void scene::new_scene() {

	log() << aspect << "New scene." << std::endl;

	empty_scene();

	// create default shader and add output block
	m_name = "new_scene";

	// create RIB root block
	const std::string unique_name = get_unique_block_name ("Root block");
	m_rib_root_block = new rib_root_block (unique_name, this);
	m_blocks.insert (std::make_pair (unique_name, m_rib_root_block));
}


void scene::load_default_blocks (const std::string& BlockPath, const std::string& DirName, unsigned long& BlockCount, const std::string& Parent) {

	// read directory content
	dirent** block_files;
	const int file_count = fltk::filename_list (BlockPath.c_str(), &block_files);

	// skip empty directories
	if (file_count < 0) {
		log() << error << "tried to load blocks from empty directory '" << BlockPath << "'." << std::endl;
		return;
	}

	// scan directory
	typedef std::vector<std::string> names_t;
	names_t file_paths;
	names_t files;
	names_t block_paths;

	shader_block_builder builder;
	int successful_block_count = 0;
	for (int f = 0; f < file_count; ++f) {

		const std::string file = std::string (block_files[f]->d_name);
		const std::string file_path = BlockPath + "/" + file;
		if (fltk::filename_isdir (file_path.c_str())) {

			if (file[0] == '.') {
				// skip default directories
			}
			else {
				// save directory
				file_paths.push_back (file_path);
				files.push_back (file);
			}
		}
		else {
			const char* extension = fltk::filename_ext (file.c_str());
			if (std::string (extension) == ".xml") {

				// save XML file
				block_paths.push_back (file_path);
			}
		}

		free (block_files[f]);
	}

	free (block_files);

	// process subdirectories
	names_t::iterator path_i = file_paths.begin();
	names_t::iterator file_i = files.begin();
	for (; path_i != file_paths.end(); ++path_i, ++file_i) {

		// when this is not the root directory...
		if (!Parent.empty()) {

			// save the fact the this subdirectory has current directory as a father
			m_block_tree.insert (std::make_pair (*file_i, DirName));

			// make sure directories without blocks but with subdirectories will be processed
			default_block_list_t v;
			m_block_classification.insert (std::make_pair (DirName, v));
		}

		// load blocks from the subdirectory
		load_default_blocks (*path_i, *file_i, BlockCount, DirName);
	}

	// process blocks
	for (names_t::iterator path_i = block_paths.begin(); path_i != block_paths.end(); ++path_i) {

		// try loading the block
		shader_block* new_block = builder.build_block (*path_i);
		if (new_block) {

			successful_block_count++;

			if (m_default_blocks.find (new_block->name()) != m_default_blocks.end()) {

				// duplicate name
				log() << error << "couldn't load " << *path_i << " : a block named '" << new_block->name() << "' already exists." << std::endl;
			}
			else {

				default_block_t block_info;
				block_info.name = new_block->name();;
				block_info.path = *path_i;
				m_default_blocks.insert (std::make_pair (new_block->name(), block_info));
				++BlockCount;

				// classify it
				block_classification_t::iterator pair = m_block_classification.find (DirName);
				if (pair == m_block_classification.end()) {

					default_block_list_t v;
					v.push_back (block_info);
					m_block_classification.insert (std::make_pair (DirName, v));
				}
				else {

					pair->second.push_back (block_info);
				}
			}
		}
		else {
			log() << error << "couldn't load " << *path_i << std::endl;
		}
	}

	log() << aspect << "loading blocks from " << BlockPath << std::endl;
	log() << aspect << " loaded " << successful_block_count << " blocks." << std::endl;
}


std::string scene::get_shader_code() {

	if (rib_root_block* rib_block = dynamic_cast<rib_root_block*>(m_rib_root_block)) {
		return rib_block->show_code();
	}

	return "";
}


void scene::show_preview (const std::string& TempDir) {

	if (rib_root_block* rib_block = dynamic_cast<rib_root_block*>(m_rib_root_block)) {
		rib_block->show_preview (TempDir);
	}

}


void scene::export_scene (const std::string& Directory) {

	if (rib_root_block* rib_block = dynamic_cast<rib_root_block*>(m_rib_root_block)) {
		rib_block->export_scene (Directory);
	}

}


void scene::bounding_box (double& Left, double& Right, double& Bottom, double& Top) {

	if (m_blocks.empty())
		return;

	Left = Right = Bottom = Top = 0;
	for (shader_blocks_t::const_iterator block_i = m_blocks.begin(); block_i != m_blocks.end(); ++block_i) {

		shader_block* block = block_i->second;

		// the first block serves as reference
		if (m_blocks.begin() == block_i) {

			Left = block->m_position_x;
			Right = block->m_position_x + block->m_width;
			Bottom = block->m_position_y;
			Top = block->m_position_y - block->m_height;

			continue;
		}

		Left = std::min (Left, block->m_position_x);
		Right = std::max (Right, block->m_position_x + block->m_width);
		Bottom = std::min (Bottom, block->m_position_y);
		Top = std::max (Top, block->m_position_y - block->m_height);
	}
}


shader_block* scene::get_parent (const std::string& BlockName, const std::string& Input, std::string& ParentOutput) const {

	const io_t input (BlockName, Input);

	for (dag_t::const_iterator connection = m_dag.begin(); connection != m_dag.end(); ++connection) {

		const io_t to = connection->first;

		if (to == input) {

			const io_t from = connection->second;
			shader_blocks_t::const_iterator block = m_blocks.find(from.first);
			ParentOutput = from.second;
			return block->second;
		}
	}

	return 0;
}


