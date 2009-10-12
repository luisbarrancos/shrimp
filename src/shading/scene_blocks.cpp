
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


#include "scene.h"
#include "rib_root_block.h"

#include "../miscellaneous/logging.h"
#include "../miscellaneous/misc_string_functions.h"


void scene::add_block (const std::string& BlockId, const std::string& BlockFile, shader_block* Block) {

	const std::string unique_name = get_unique_block_name (BlockId);
	Block->set_name (unique_name);
	m_blocks.insert (std::make_pair (unique_name, Block));
}


shader_block* scene::add_predefined_block (const std::string& BlockName) {

	// catch custom block
	if (BlockName == "Custom block") {
		return add_custom_block();
	}

	// create existing block
	default_blocks_t::const_iterator block_i = m_default_blocks.find (BlockName);
	if (block_i == m_default_blocks.end()) {

		log() << error << "block '" << BlockName << "' not found" << std::endl;
		return 0;
	}

	shader_block_builder builder;
	shader_block* block = builder.build_block (block_i->second.path);
	add_block (BlockName, block_i->second.path, block);

	return block;
}


shader_block* scene::add_custom_block (const std::string& Name, const bool RootBlock) {

	const std::string unique_name = get_unique_block_name (Name);

	shader_block* block = new shader_block (unique_name, "", RootBlock);
	block->set_name (unique_name);
	m_blocks.insert (std::make_pair (unique_name, block));

	return block;
}


void scene::delete_block (const std::string& BlockName) {

	int total = selection_size();
	//If multi selecion
		if (total>1){
				for (scene::selection_t::const_iterator block_i = m_selection.begin(); block_i != m_selection.end(); ++block_i) {

							std::string current_selection = *block_i;

							shader_block* block = get_block(current_selection);

							if (!block) {

									log() << error << "active block '" << current_selection << "' not found." << std::endl;
									return;
								}

							int Group = group (block);
							if (!Group) {

								const std::string  BlockNameSelect = block->name();
								//Avoid to delete Root block
								if (BlockNameSelect != "Root block"){
									// disconnect all pads
									for (shader_block::properties_t::const_iterator input = block->m_inputs.begin();
											input != block->m_inputs.end(); ++input) {

											disconnect (io_t (BlockNameSelect, input->m_name));
										}
									for (shader_block::properties_t::const_iterator output = block->m_outputs.begin();
											output != block->m_outputs.end(); ++output) {

											disconnect (io_t (BlockNameSelect, output->m_name));
										}
									// safely remove it from the network
										m_blocks.erase (BlockNameSelect);

									// finally delete it
										delete block;
								}
							}

				}

		}

	else {
		//Avoid to delete Root block
		if (BlockName != "Root block"){
			// disconnect all pads
			shader_block* block = get_block (BlockName);
			for (shader_block::properties_t::const_iterator input = block->m_inputs.begin();
				input != block->m_inputs.end(); ++input) {

				disconnect (io_t (BlockName, input->m_name));
			}
			for (shader_block::properties_t::const_iterator output = block->m_outputs.begin();
				output != block->m_outputs.end(); ++output) {

				disconnect (io_t (BlockName, output->m_name));
			}

			// safely remove it from the network
			m_blocks.erase (BlockName);

			// finally delete it
			delete block;
		}
	}

}


shader_block* scene::get_block (const std::string& Name) {

	shader_blocks_t::const_iterator block = m_blocks.find (Name);
	if (m_blocks.end() == block)
		return 0;

	return block->second;
}


shader_block* scene::get_root_block() {

	for (shader_blocks_t::iterator block = m_blocks.begin(); block != m_blocks.end(); ++block) {

		if (block->second->m_root_block)
			return block->second;
	}

	log() << error << "couldn't find root block." << std::endl;

	return 0;
}


std::string scene::get_unique_block_name (const std::string& Name) const {

	if (m_blocks.find (Name) == m_blocks.end())
		// name is already unique
		return Name;

	// append a number to make it unique
	for (int i = 2; ; i++) {

		const std::string new_name = Name + "_" + string_cast (i);

		if (m_blocks.find (new_name) == m_blocks.end())
			return new_name;
	}
}


void scene::set_block_name (shader_block* Block, const std::string& NewName) {

	const std::string old_name = Block->name();
	const std::string new_name = get_unique_block_name (NewName);

	// update DAG
	dag_t new_dag;
	for (dag_t::iterator d = m_dag.begin(); d != m_dag.end(); ++d) {

		if (d->first.first == old_name) {

			// block was the input
			io_t input (new_name, d->first.second);
			io_t output = d->second;
			new_dag.insert (std::make_pair (input, output));

		} else if (d->second.first == old_name) {

			// block was the output
			io_t input (d->first);
			io_t output (new_name, d->second.second);
			new_dag.insert (std::make_pair (input, output));

		} else {

			// another block
			new_dag.insert (*d);
		}
	}

	m_dag = new_dag;

	// update the block list
	m_blocks.erase (old_name);
	m_blocks.insert (std::make_pair(new_name, Block));

	// update selection and groups
	m_selection.erase (old_name);
	m_groups.erase (old_name);

	// we can now safely rename the block
	Block->set_name (new_name);
}


void scene::connect (const io_t& Input, const io_t& Output) {

	shader_block* input_block = get_block (Input.first);
	shader_block* output_block = get_block (Output.first);

	if (input_block && output_block) {

		if ((input_block->is_input (Input.second) && output_block->is_output (Output.second))) {

			if (input_block->is_input_multi_operator (Input.second)) {

				// special case : multi-inputs

				// check whether it's already connected
				if (m_dag.find (Input) == m_dag.end()) {

					// not connected, connect it
					m_dag.insert (std::make_pair (Input, Output));
				} else {

					// make sure this output is not connected to one of the 'multi' inputs
					// TODO

					// add a 'child' input
					const std::string new_input = input_block->add_multi_input (Input.second);
					// connect to that new input
					m_dag.insert (std::make_pair (io_t (Input.first, new_input), Output));
				}

				return;
			} else {

				// normal block connection

				// remove existing connection if any
				if (m_dag.find (Input) != m_dag.end()) {
					m_dag.erase (Input);
				}

				// connect the blocks
				m_dag.insert (std::make_pair (Input, Output));

				// change the parent's output type to the input's one (except with shader outputs)
				if (!output_block->is_shader_output (Output.second)) {
					if (!output_block->set_output_type (Output.second, input_block->get_input_type (Input.second))) {

						log() << warning << "connecting to an input that doesn't have a valid type: '" << input_block->get_input_type (Input.second) << "' from " << input_block->name() << " -> " << Input.second << std::endl;
					}
				} else {
					// root block's AOV input takes the parent's type
					if (dynamic_cast<rib_root_block*>(input_block)) {
						if (Input.second == "AOV") {
							input_block->set_input_type (Input.second, output_block->get_output_type (Output.second));
						}
					}
				}

				return;
			}
		}
	}

	log() << error << "connection failed : " << Input.first << "::" << Input.second << " must be an input, and " << Output.first << "::" << Output.second << " must be an output" << std::endl;
}


void scene::disconnect (const io_t& IO) {

	// check whether IO is an input
	dag_t::const_iterator connection = m_dag.find (IO);
	if (connection != m_dag.end()) {

		// remove the connection
		m_dag.erase (IO);
		return;
	}

	// remove all connections containing IO as output
	dag_t new_dag;
	for (dag_t::const_iterator connection = m_dag.begin(); connection != m_dag.end(); ++connection) {

		if (connection->second != IO) {

			new_dag.insert (*connection);
		}
	}

	if (new_dag.size() < m_dag.size()) {

		// at least one connection was removed
		m_dag = new_dag;
	} else {
		//log() << warning << "no connection contains " << IO.first << "::" << IO.second << " as input or output." << std::endl;
	}
}


bool scene::is_connected (const io_t& Input) {

	if (m_dag.find (Input) != m_dag.end()) {
		return true;
	}

	return false;
}


void scene::upward_blocks (shader_block* StartingBlock, shader_blocks_t& List) {

	if (!StartingBlock) {

		return;
	}

	List.insert (std::make_pair (StartingBlock->name(), StartingBlock));

	for (shader_block::properties_t::const_iterator input = StartingBlock->m_inputs.begin();
		input != StartingBlock->m_inputs.end(); ++input) {

		// get input's parent
		std::string output_name;
		shader_block* new_block = get_parent (StartingBlock->name(), input->m_name, output_name);

		// add the parent (except for shader outputs)
		if (new_block && !new_block->is_shader_output (output_name)) {

			// check whether it's already in the list
			if (List.find (new_block->name()) == List.end()) {

				List.insert (std::make_pair (new_block->name(), new_block));
				upward_blocks (new_block, List);
			}
		}
	}
}


bool scene::is_rolled (const shader_block* Block) const {

	return Block->is_rolled();
}


int scene::rolled_block_count() {

	int rolled_block_count = 0;

	for (shader_blocks_t::iterator block = m_blocks.begin(); block != m_blocks.end(); ++block) {

		if (block->second->is_rolled())
			++rolled_block_count;
	}

	return rolled_block_count;
}


void scene::unroll_all_blocks() {

	for (shader_blocks_t::iterator block = m_blocks.begin(); block != m_blocks.end(); ++block) {

		block->second->roll (false);
	}
}


void scene::set_block_rolled_state (shader_block* Block, const bool Rolled) {

	if (!Block) {
		log() << error << "no block given for roll/unroll." << std::endl;
		return;
	}

	Block->roll (Rolled);
}


