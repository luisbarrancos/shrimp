
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

#include "../miscellaneous/logging.h"


bool scene::is_selected (const shader_block* Block) {

	std::string name = Block->name();
	selection_t::const_iterator i = m_selection.find (name);
	if (i == m_selection.end()) {
		return false;
	}

	return true;
}


int scene::selection_size() {

	return m_selection.size();
}


void scene::clear_selection() {

	m_selection.clear();
}


void scene::set_block_selection (shader_block* Block, const bool Selection) {

	if (!Block) {
		log() << error << "no block given for selection." << std::endl;
		return;
	}

	const std::string block_name = Block->name();
	if (Selection) {
		m_selection.insert (block_name);
	} else {
		m_selection.erase (block_name);
	}
}


