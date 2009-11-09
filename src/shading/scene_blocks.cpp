
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
#include <iostream>

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

	// one block and not a group
	if (selection_size()==1 && m_groups_selection.size()==0) {
		//Avoid to delete Root block
		if (BlockName != "Root block"){
			// disconnect all pads

			shader_block* block = get_block (BlockName);
			for (shader_block::properties_t::const_iterator input = block->m_inputs.begin();
				input != block->m_inputs.end(); ++input) {

				if (block->m_inputs.size())disconnect (io_t (BlockName, input->m_name));
			}
			for (shader_block::properties_t::const_iterator output = block->m_outputs.begin();
				output != block->m_outputs.end(); ++output) {

				if (block->m_outputs.size())disconnect (io_t (BlockName, output->m_name));
			}

			// safely remove it from the network
			m_blocks.erase (BlockName);

			// finally delete it
			delete block;
		}
	}

	// multi selecion
	else if (selection_size()>=1){
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

										if (block->m_inputs.size())disconnect (io_t (BlockNameSelect, input->m_name));
										}
									for (shader_block::properties_t::const_iterator output = block->m_outputs.begin();
											output != block->m_outputs.end(); ++output) {

										if (block->m_outputs.size())disconnect (io_t (BlockNameSelect, output->m_name));
										}
									// safely remove it from the network
										m_blocks.erase (BlockNameSelect);

									// finally delete it
										delete block;

								}
							}

				}

		}
		// groups selected
		if (m_groups_selection.size())
		{

			int Group = 0;
			for (scene::groups_selection_t::const_iterator g = m_groups_selection.begin(); g != m_groups_selection.end(); ++g)
			{

				for (scene:: shader_blocks_t::const_iterator block_i = m_blocks.begin(); block_i != m_blocks.end(); ++block_i) {
				const shader_block* blockSel = block_i->second;
				int groupSel = group(blockSel);
				Group = *g;


				if (groupSel==Group)
					{
					const std::string  BlockNameSelect = blockSel->name();
					if (BlockNameSelect != "Root block"){
						for (shader_block::properties_t::const_iterator input = blockSel->m_inputs.begin();
								input != blockSel->m_inputs.end(); ++input) {


							if (blockSel->m_inputs.size())disconnect (io_t (BlockNameSelect, input->m_name));
							}
						for (shader_block::properties_t::const_iterator output = blockSel->m_outputs.begin();
								output != blockSel->m_outputs.end(); ++output) {

							if (blockSel->m_outputs.size())disconnect (io_t (BlockNameSelect, output->m_name));
							}
						// safely remove it from the network
							m_blocks.erase (BlockNameSelect);

						// delete the block itself
						delete blockSel;
						}
					}
				}
			// safely remove from group
			if (Group!=0){
				ungroup(Group);
				m_group_names.erase(Group);
				}

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

	if ((input_block && output_block) ||(m_dag == m_dag_copy)) {

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

// copy block
void scene::copy_blocks(const std::string& Name,const int Group)
{

	shader_block* BlockToCopy = get_block(Name);

	// temp name
			const std::string Temp = "Copy";
			std::string NewName;
	// create block
		shader_block* new_block = new shader_block (Temp, "",0);

	// set new name
		NewName = get_unique_block_name(Name);
		new_block->set_name(NewName);

	// copy description
		new_block->m_description = BlockToCopy->m_description;

	// copy author
		new_block->m_author = BlockToCopy->m_author;
	// copy usage
		new_block->set_usage(BlockToCopy->m_usage);

	// copy properties
	// input and output properties

		// input and output properties
		typedef std::vector<property> properties_t;

		if (BlockToCopy->m_inputs.size()){
			for (properties_t::const_iterator input = BlockToCopy->m_inputs.begin(); input != BlockToCopy->m_inputs.end(); ++input) {

					new_block->add_input (input->m_name, input->get_type(), input->get_type_extension(), input->get_storage(), input->m_description, input->get_value(), input->m_multi_operator, input->m_shader_parameter);

			}
		}

		if (BlockToCopy->m_outputs.size()){
			for (properties_t::iterator output = BlockToCopy->m_outputs.begin(); output != BlockToCopy->m_outputs.end(); ++output) {

				new_block->add_output (output->m_name, output->get_type(), output->get_type_extension(), output->get_storage(), output->m_description, output->m_shader_output);

			}
		}


	// copy block position, size and rolled state in scene
		new_block->m_position_x = BlockToCopy->m_position_x+0.5;
		new_block->m_position_y = BlockToCopy->m_position_y+0.5;
		new_block->m_width = BlockToCopy->m_width ;
		new_block->m_height = BlockToCopy->m_height ;
		new_block->m_rolled = BlockToCopy->m_rolled ;

	// copy shader code
		new_block->m_includes = BlockToCopy->m_includes;
		new_block->m_code = BlockToCopy->m_code;
		new_block->m_code_written = BlockToCopy->m_code_written;

		const scene::copy_block_t New (NewName, new_block);
		const scene::copy_block_t Org (Name,BlockToCopy);

	// 	copy new block to buffer and selection
		m_copy_buffer.insert (std::make_pair (Org,New));
		m_copy_selection.insert (std::make_pair (Org,New));

	if (Group){
		int num_groups =0;

			for (groups_t::const_iterator g = m_groups.begin(); g != m_groups.end(); ++g) {
					if(g->second > num_groups)
						num_groups = g->second;
					}

	// add group if block part of a group
		m_groups_buffer.insert(std::make_pair(NewName,(Group+num_groups)));
	}
}

void scene::copy_connections()
{
	// copy connections

			for (dag_t::const_iterator connection = m_dag.begin(); connection != m_dag.end(); ++connection) {


						const scene::copy_block_t to = (std::make_pair (connection->first.first,get_block(connection->first.first)));
						const scene::copy_block_t from = (std::make_pair (connection->second.first,get_block(connection->second.first)));


						// found connections to copy
						shader_blocks_copy_t::const_iterator i = m_copy_selection.find(to);
							shader_block* check_block = i->first.second;
							shader_block* check_block_end = m_copy_selection.end()->first.second;


							if (!(check_block == check_block_end)) {


								const scene::io_t to_copy = (std::make_pair (i->second.first,connection->first.second));

								shader_blocks_copy_t::const_iterator j = m_copy_selection.find(from);

								shader_block* check_block2 = j->first.second;
								shader_block* check_block_end2 = m_copy_selection.end()->first.second;
								if (!(check_block2 == check_block_end2)) {


									const scene::io_t from_copy = (std::make_pair (j->second.first,connection->second.second));

									// add connection to the m_dag_copy structure
									m_dag_copy.insert (std::make_pair (to_copy,from_copy));

									}

								}
						}

}

void scene::paste_blocks()
{
	// pasted blocks
	for (shader_blocks_copy_t::iterator new_block = m_copy_buffer.begin(); new_block != m_copy_buffer.end(); ++new_block){
		shader_block* paste =new_block->second.second;

		const std::string paste_name = paste->name();
		add_block (paste_name,"",paste);

		// create new_groups (pasted groups)
			groups_t::const_iterator g = m_groups_buffer.find(paste_name);
			if(!(g == m_groups_buffer.end()))
			{
					const int Group = g->second;
			 		m_groups.insert (std::make_pair(paste_name, Group));
			}
	}

	// pasted connection of pasted blocks
	for (dag_t::const_iterator connection = m_dag_copy.begin(); connection != m_dag_copy.end(); ++connection) {
		const scene::io_t to = connection->first;
		const scene::io_t from = connection->second;
		connect (to, from);
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


