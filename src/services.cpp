
/*
    Copyright 2009, Romain Behar <romainbehar@users.sourceforge.net>

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


#include "services.h"

#include "miscellaneous/logging.h"

services::services() {
	log() << aspect << "services: constructor" << std::endl;

	log() << aspect << "services: initializing scene" << std::endl;
	m_scene = new scene();
	reset_scene();
}


services::~services() {
	delete m_scene;
}


void services::reset_scene() {
	log() << aspect << "services: reset scene" << std::endl;

	m_scene->new_scene();
	m_scene_file = "";

	m_block_selection.clear();
}


block_tree_node_t services::get_block_hierarchy() {
	return m_scene->get_block_hierarchy();
}


shader_block_map_t services::get_scene_blocks() {
	return m_scene->m_blocks;
}


// selection
bool services::is_selected (const shader_block* Block) {

	std::string name = Block->name();
	block_selection_t::const_iterator i = m_block_selection.find (name);
	if (i == m_block_selection.end()) {
		return false;
	}

	return true;
}


int services::selection_size() {

	return m_block_selection.size();
}


void services::clear_selection() {

	m_block_selection.clear();
	//TODO:
	//m_groups_selection.clear();
}

void services::clear_copy_selection(){
	//TODO:
	//m_copy_selection.clear();
}


void services::set_block_selection (shader_block* Block, const bool Selection)
{
	log() << aspect << "services: set_block_selection of " << Block->name() << " with " << Selection << std::endl;

	if (!Block) {
		log() << error << "no block given for selection." << std::endl;
		return;
	}

	const std::string block_name = Block->name();
	if (Selection) {
		m_block_selection.insert (block_name);
	} else {
		m_block_selection.erase (block_name);
	}
}


void services::set_block_rolled_state (shader_block* Block, const bool Rolled)
{
	log() << aspect << "services: set_block_rolled_state of " << Block->name() << " with " << Rolled << std::endl;

	m_scene->set_block_rolled_state (Block, Rolled);
}


