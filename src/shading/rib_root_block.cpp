
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


#include "rib_root_block.h"

#include "scene.h"
#include "preferences.h"

#include "../miscellaneous/logging.h"
#include "../miscellaneous/misc_string_functions.h"

#include <fstream>


rib_root_block::rib_root_block (const std::string& Name, scene* Scene) :
	shader_block (Name, "", true),
	m_scene (Scene),
	m_AOV (true),
	root_type ("RIB")
{

	// add inputs
	add_input ("Ci", "color", "varying", "Incident ray colour", "0", "");
	add_input ("Oi", "color", "varying", "Incident ray opacity", "1", "");
	add_input ("P", "point", "varying", "Displaced surface position", "P", "");
	add_input ("N", "normal", "varying", "Displaced surface shading normal", "N", "");
	add_input ("Cl", "color", "varying", "Outgoing light ray colour", "0", "");
	// we have problems with Ol, PRMan (and not only PRMan) protest about Ol)
	// still, doesn't makes much sense having light opacity (?!)
	add_input ("Ol", "color", "varying", "Outgoing light ray opacity", "1", "");
	add_input ("Cv", "color", "varying", "Attenuated ray colour", "0", "");
	add_input ("Ov", "color", "varying", "Attenuated ray opacity", "1", "");
	add_input ("Cm", "color", "varying", "Output pixel colour", "0", "");
	add_input ("Om", "color", "varying", "Output pixel opacity", "1", "");
	add_input ("AOV", "color", "varying", "AOV preview output", "1", "");
}


bool rib_root_block::has_surface_network() {

	std::string foo;

	// check for Ci's input parent
	if (m_scene->get_parent (name(), "Ci", foo)) {
		return true;
	}

	// check for Oi's input parent
	if (m_scene->get_parent (name(), "Oi", foo)) {
		return true;
	}

	return false;
}


bool rib_root_block::has_displacement_network() {

	std::string foo;

	// check for P's input parent
	if (m_scene->get_parent (name(), "P", foo)) {
		return true;
	}

	// check for N's input parent
	if (m_scene->get_parent (name(), "N", foo)) {
		return true;
	}

	return false;
}


bool rib_root_block::has_light_network() {

	std::string foo;

	// check for Cl's input parent
	if (m_scene->get_parent (name(), "Cl", foo)) {
		return true;
	}

	// check for Ol's input parent
	if (m_scene->get_parent (name(), "Ol", foo)) {
		return true;
	}

	return false;
}


bool rib_root_block::has_atmosphere_network() {

	std::string foo;

	// check for Cv's input parent
	if (m_scene->get_parent (name(), "Cv", foo)) {
		return true;
	}

	// check for Ov's input parent
	if (m_scene->get_parent (name(), "Ov", foo)) {
		return true;
	}

	return false;
}


bool rib_root_block::has_AOV_input (std::string& ParentName) {

	// check for an input parent
	if (m_scene->get_parent (name(), "AOV", ParentName)) {
		return true;
	}

	return false;
}


std::string rib_root_block::build_shader_file (const shader_t ShaderType, const std::string& ShaderName) {

	// get the list of blocks composing the shader
	scene::shader_blocks_t shader_blocks;
	switch (ShaderType) {

		case SURFACE:
		{
			// get surface parents (Ci and Oi)
			std::string Ci_output_name;
			shader_block* Ci_parent = m_scene->get_parent (name(), "Ci", Ci_output_name);
			std::string Oi_output_name;
			shader_block* Oi_parent = m_scene->get_parent (name(), "Oi", Oi_output_name);

			// make sure there's something to build
			if (!Ci_parent && !Oi_parent) {

				log() << info << "there's no surface block connected to the root block." << std::endl;
				return "";
			}

			// make the list of connected blocks
			m_scene->upward_blocks (Ci_parent, shader_blocks);
			m_scene->upward_blocks (Oi_parent, shader_blocks);
		}
		break;

		case DISPLACEMENT:
		{
			// get displacement parents (N and P)
			std::string N_output_name;
			shader_block* N_parent = m_scene->get_parent (name(), "N", N_output_name);
			std::string P_output_name;
			shader_block* P_parent = m_scene->get_parent (name(), "P", P_output_name);

			// make sure there's something to build
			if (!N_parent && !P_parent) {

				log() << info << "there's no displacement block connected to the root block." << std::endl;
				return "";
			}

			// make the list of connected blocks
			m_scene->upward_blocks (N_parent, shader_blocks);
			m_scene->upward_blocks (P_parent, shader_blocks);
		}
		break;

		case LIGHT:
		{
			// get light parents (Cl and Ol)
			std::string Cl_output_name;
			shader_block* Cl_parent = m_scene->get_parent (name(), "Cl", Cl_output_name);
			std::string Ol_output_name;
			shader_block* Ol_parent = m_scene->get_parent (name(), "Ol", Ol_output_name);

			// make sure there's something to build
			if (!Cl_parent && !Ol_parent) {

				log() << info << "there's no light block connected to the root block." << std::endl;
				return "";
			}

			// make the list of connected blocks
			m_scene->upward_blocks (Cl_parent, shader_blocks);
			m_scene->upward_blocks (Ol_parent, shader_blocks);
		}
		break;

		case VOLUME:
		{
			// get atmosphere parents (Cv and Ov)
			std::string Cv_output_name;
			shader_block* Cv_parent = m_scene->get_parent (name(), "Cv", Cv_output_name);
			std::string Ov_output_name;
			shader_block* Ov_parent = m_scene->get_parent (name(), "Ov", Ov_output_name);

			// make sure there's something to build
			if (!Cv_parent && !Ov_parent) {

				log() << info << "there's no atmosphere block connected to the root block." << std::endl;
				return "";
			}

			// make the list of connected blocks
			m_scene->upward_blocks (Cv_parent, shader_blocks);
			m_scene->upward_blocks (Ov_parent, shader_blocks);
		}
		break;

		default:
			log() << error << "unhandled shader type.";
			return "";
	}

	// start code
	std::string shader_code ("");
	shader_code += "/*  Shader generated by Shrimp  */\n\n";

	// initialize Shrimp's renderer constants with integer values
	general_options prefs;
	prefs.load();

	general_options::renderers_t m_renderers = prefs.get_renderer_list();
	unsigned long renderer_number = 1001;

	shader_code += "/* Renderer constants */\n";
	for (general_options::renderers_t::iterator r_i = m_renderers.begin(); r_i != m_renderers.end(); ++r_i, ++renderer_number) {

		//shader_code += "#ifndef " + r_i->first + "\n";
		shader_code += " #define " + r_i->first + " " + string_cast (renderer_number) + "\n";
		//shader_code += "#endif\n";
	}
	shader_code += "/* Shrimp headers */\n";

	/* all blocks should be aware of the AOV macros, so instead of including
	 * shrimp_aov.h in all blocks, we might as well make it a part of the
	 * standard shader body. */
	shader_code += "#include \"rsl_shrimp_aov.h\"\n";

	// initialize code build process, get includes, parameters and locals
	std::set<std::string> includes;
	std::string parameters;
	std::string locals;
	std::string shader_outputs;
	for (scene::shader_blocks_t::const_iterator block = shader_blocks.begin(); block != shader_blocks.end(); ++block) {

		shader_block* sb = block->second;

		sb->reset_code_written();
		sb->get_includes (includes);

		// get parameter values (inputs that are not connected)
		for (shader_block::properties_t::const_iterator input = sb->m_inputs.begin(); input != sb->m_inputs.end(); ++input) {

			if (m_scene->is_connected (scene::io_t (sb->name(), input->m_name))) {
				continue;
			}

			if (input->m_shader_parameter) {
				parameters += "\t\t" + sb->input_type (input->m_name) + " " +
						sb->sl_name() + "_" + input->m_name + " = " + input->value_as_sl_string() + ";\n";
			}
		}

		// get output values (as local or output variables)
		//TODO test that each name is unique
		for (shader_block::properties_t::const_iterator output = sb->m_outputs.begin(); output != sb->m_outputs.end(); ++output) {

			if (!output->m_shader_output) {
				locals += "\t" + sb->output_type (output->m_name) + " " +
						sb->sl_name() + "_" + output->m_name + ";\n";
			} else {
				shader_outputs += "\t\toutput ";
				const std::string storage = sb->output_storage (output->m_name);
				if (storage != "varying") {
					shader_outputs += storage + " ";
				}
				shader_outputs += sb->output_type (output->m_name) + " " + output->m_name;
				shader_outputs += " = 0;\n";
			}
		}
	}

	// add required headers
	for (std::set<std::string>::const_iterator i = includes.begin(); i != includes.end(); ++i)
		shader_code += "#include \"" + *i + "\"\n";

	shader_code += "\n//main\n";

	// shader type
	switch (ShaderType) {

		case SURFACE:
			// Preset AOVs, shader arguments, so we initialize them
			shader_code += "surface " + ShaderName
				+ "(\n\tDEFAULT_AOV_OUTPUT_PARAMETERS\n";
		break;

		case DISPLACEMENT:
			shader_code += "displacement " + ShaderName
				+ "(\n\tDEFAULT_AOV_OUTPUT_PARAMETERS\n";
		break;

		case LIGHT:
		/* NOTE: we could use light categories for nondiffuse and
		 * nonspecular instead */
			shader_code += "light " + ShaderName
				+ "(\n"
				+ "\t/* predefined light outputs */\n"
				+ "\toutput uniform float __nondiffuse = 0;\n"
				+ "\toutput uniform float __nonspecular = 0;\n"
				+ "\toutput uniform string __category = \"\";\n"
				+ "\toutput varying color __shadow = color(0);\n"
				+ "\tDEFAULT_AOV_OUTPUT_PARAMETERS\n";
		break;

		case VOLUME:
			shader_code += "volume " + ShaderName
				+ "(\n\tDEFAULT_AOV_OUTPUT_PARAMETERS\n";
		break;

		default:
			log() << error << "unhandled shader type.";
	}

	// add function's parameters
	shader_code += parameters + "/* User set parameters */\n";
	shader_code += shader_outputs;
	shader_code += "\t)\n";

	// open function and write locals
	shader_code += "{\n";
	shader_code += "\tINIT_AOV_PARAMETERS\n";
	shader_code += "\t/* Local variables */\n";
	shader_code += locals;

	shader_code += "/* Blocks follow */\n";

	// actual function code
	switch (ShaderType) {

		case SURFACE:
		{
			// get surface parents (Ci and Oi)
			std::string Ci_output_name;
			shader_block* Ci_parent = m_scene->get_parent (name(), "Ci", Ci_output_name);
			std::string Oi_output_name;
			shader_block* Oi_parent = m_scene->get_parent (name(), "Oi", Oi_output_name);

			// build code
			std::string surface_code = "\tCi = $(Ci);\n\tOi = $(Oi);";

			if (Ci_parent) {

				build_shader_code (Ci_parent, shader_code);
				replace_variable (surface_code, "$(Ci)", Ci_parent->sl_name() + "_" + Ci_output_name);
			} else {
				replace_variable (surface_code, "$(Ci)", get_input_value ("Ci"));
			}

			if (Oi_parent) {

				// make sure the parent block is not output twice (if connected to both root block inputs)
				if (!Oi_parent->m_code_written) {
					build_shader_code (Oi_parent, shader_code);
				}
				replace_variable (surface_code, "$(Oi)", Oi_parent->sl_name() + "_" + Oi_output_name);
			} else {
				replace_variable (surface_code, "$(Oi)", get_input_value ("Oi"));
			}

			shader_code += surface_code;
			shader_code += "\n";			
			// call getshadows macro to store __shadow into aov_shadows
			// add a comment to the code
			shader_code += "\t// call macro to accumulate __shadow into aov_shadows\n";
			shader_code += "\tgetshadows(P);\n";
			shader_code += "\n";
		}
		break;

		case DISPLACEMENT:
		{
			// get displacement parents (N and P)
			std::string N_output_name;
			shader_block* N_parent = m_scene->get_parent (name(), "N", N_output_name);
			std::string P_output_name;
			shader_block* P_parent = m_scene->get_parent (name(), "P", P_output_name);

			// build code
			std::string displacement_code = "\tN = $(N);\n\tP = $(P);";

			if (N_parent) {

				build_shader_code (N_parent, shader_code);
				replace_variable (displacement_code, "$(N)", N_parent->sl_name() + "_" + N_output_name);
			} else {
				replace_variable (displacement_code, "$(N)", get_input_value ("N"));
			}

			if (P_parent) {

				// make sure the parent block is not output twice (if connected to both root block inputs)
				if (!P_parent->m_code_written) {
					build_shader_code (P_parent, shader_code);
				}
				replace_variable (displacement_code, "$(P)", P_parent->sl_name() + "_" + P_output_name);
			} else {
				replace_variable (displacement_code, "$(P)", get_input_value ("P"));
			}

			shader_code += displacement_code;
			shader_code += "\n";
		}
		break;

		case LIGHT:
		{
			// get light parents (Cl and Ol)
			std::string Cl_output_name;
			shader_block* Cl_parent = m_scene->get_parent (name(), "Cl", Cl_output_name);
			std::string Ol_output_name;
			shader_block* Ol_parent = m_scene->get_parent (name(), "Ol", Ol_output_name);

			// build code
			std::string light_code = "\tCl = $(Cl);\n\tOl = $(Ol);";

			if (Cl_parent) {

				build_shader_code (Cl_parent, shader_code);
				replace_variable (light_code, "$(Cl)", Cl_parent->sl_name() + "_" + Cl_output_name);
			} else {
				replace_variable (light_code, "$(Cl)", get_input_value ("Cl"));
			}

			if (Ol_parent) {

				// make sure the parent block is not output twice (if connected to both root block inputs)
				if (!Ol_parent->m_code_written) {
					build_shader_code (Ol_parent, shader_code);
				}
				replace_variable (light_code, "$(Ol)", Ol_parent->sl_name() + "_" + Ol_output_name);
			} else {
				replace_variable (light_code, "$(Ol)", get_input_value ("Ol"));
			}

			shader_code += light_code;
			shader_code += "\n";
		}
		break;

		case VOLUME:
		{
			// get atmosphere parents (Cv and Ov)
			std::string Cv_output_name;
			shader_block* Cv_parent = m_scene->get_parent (name(), "Cv", Cv_output_name);
			std::string Ov_output_name;
			shader_block* Ov_parent = m_scene->get_parent (name(), "Ov", Ov_output_name);

			// build code
			std::string atmosphere_code = "\tCi = $(Cv);\n\tOi = $(Ov);";

			if (Cv_parent) {

				build_shader_code (Cv_parent, shader_code);
				replace_variable (atmosphere_code, "$(Cv)", Cv_parent->sl_name() + "_" + Cv_output_name);
			} else {
				replace_variable (atmosphere_code, "$(Cv)", get_input_value ("Cv"));
			}

			if (Ov_parent) {

				// make sure the parent block is not output twice (if connected to both root block inputs)
				if (!Ov_parent->m_code_written) {
					build_shader_code (Ov_parent, shader_code);
				}
				replace_variable (atmosphere_code, "$(Ov)", Ov_parent->sl_name() + "_" + Ov_output_name);
			} else {
				replace_variable (atmosphere_code, "$(Ov)", get_input_value ("Ov"));
			}

			shader_code += atmosphere_code;
			shader_code += "\n";
		}
		break;

		default:
			log() << error << "unhandled shader type.";
	}

	shader_code += "\n}\n";

	return shader_code;
}


void rib_root_block::build_shader_code (shader_block* Block, std::string& ShaderCode) {

	log() << aspect << "building code for block '" << Block->name() << "'" << std::endl;

	// get block's code
	std::string code = Block->get_code();

	// replace block name
	replace_variable (code, "$(blockname)", Block->sl_name());

	// replace variable types: $(p:type) -> float (in case p is a float)
	for (shader_block::properties_t::const_iterator input = Block->m_inputs.begin(); input != Block->m_inputs.end(); ++input) {

		const std::string tag = "$(" + input->m_name + ":type)";
		replace_variable (code, tag, input->get_type());
	}
	for (shader_block::properties_t::const_iterator output = Block->m_outputs.begin(); output != Block->m_outputs.end(); ++output) {

		const std::string tag = "$(" + output->m_name + ":type)";
		replace_variable (code, tag, output->get_type());
	}

	// process input parents
	for (shader_block::properties_t::const_iterator input = Block->m_inputs.begin(); input != Block->m_inputs.end(); ++input) {

		std::string parent_output;
		shader_block* parent = m_scene->get_parent (Block->name(), input->m_name, parent_output);

		if (parent) {

			if (!input->is_multi_operator() and input->m_multi_operator_parent_name.empty()) {

				// process "normal" input
				if (!parent->m_code_written && !parent->is_shader_output (parent_output)) {
					build_shader_code (parent, ShaderCode);
				}

				// replace the variable with parent's output variable name (except with shader outputs)
				if (!parent->is_shader_output (parent_output)) {
					replace_variable (code, "$(" + input->m_name + ")", parent->sl_name() + "_" + parent_output);
				} else {
					// replace with the shader output name string
					replace_variable (code, "$(" + input->m_name + ")", '"' + parent_output + '"');
				}
			} else if (input->is_multi_operator()) {

				// get list of child inputs
				std::vector<std::string> children;
				children.push_back (input->m_name);
				Block->get_multi_input_child_list (input->m_name, children);

				// get values
				std::vector<std::string> values;
				for (std::vector<std::string>::const_iterator c = children.begin(); c != children.end(); ++c) {

					std::string input_parent_output ("");
					shader_block* input_parent = m_scene->get_parent (Block->name(), *c, input_parent_output);
					if (!input_parent->m_code_written && !input_parent->is_shader_output (input_parent_output)) {
						build_shader_code (input_parent, ShaderCode);
					}

					// replace the variable with parent's output variable name (except with shader outputs)
					if (!input_parent->is_shader_output (input_parent_output)) {
						values.push_back (input_parent->sl_name() + "_" + input_parent_output);
					} else {
						// replace with the shader output name string
						values.push_back (input_parent_output);
					}
				}

				// build the value string, using the operator
				std::string single_value ("");
				unsigned long value_number = 0;
				for (std::vector<std::string>::const_iterator v = values.begin(); v != values.end(); ++v) {

					++value_number;
					if (value_number > 1) {

						single_value = single_value + ' ' + input->m_multi_operator + ' ';
					}

					single_value = single_value + *v;
				}

				// replace the value
				replace_variable (code, "$(" + input->m_name + ")", single_value);

			} else if (!input->m_multi_operator_parent_name.empty()) {
				// not processed here, but with the multi-operator
			}
		}
		else {
			if (!input->m_shader_parameter) {
				// directly replace with the value
				replace_variable (code, "$(" + input->m_name + ")", Block->get_input_value_as_sl_string (input->m_name));
			} else {
				// replace with the variable name (the one defined by default as a shader parameter)
				replace_variable (code, "$(" + input->m_name + ")", Block->sl_name() + "_" + input->m_name);
			}
		}
	}

	for (shader_block::properties_t::const_iterator output = Block->m_outputs.begin(); output != Block->m_outputs.end(); ++output) {

		// rewrite the output names with unique ones (except with shader outputs)
		if (!output->m_shader_output) {
			replace_variable (code, "$(" + output->m_name + ")", Block->sl_name() + "_" + output->m_name);
		} else {
			replace_variable (code, "$(" + output->m_name + ")", output->m_name);
		}
	}

	// save resulting code
	ShaderCode += code;
	ShaderCode += "\n";

	Block->m_code_written = true;
}


std::string rib_root_block::build_k3d_meta_file (const shader_t ShaderType, const std::string& ShaderName) {

	// get the list of blocks composing the shader
	scene::shader_blocks_t shader_blocks;
	switch (ShaderType) {

		case SURFACE:
		{
			// get surface parents (Ci and Oi)
			std::string Ci_output_name;
			shader_block* Ci_parent = m_scene->get_parent (name(), "Ci", Ci_output_name);
			std::string Oi_output_name;
			shader_block* Oi_parent = m_scene->get_parent (name(), "Oi", Oi_output_name);

			// make sure there's something to build
			if (!Ci_parent && !Oi_parent) {

				log() << info << "there's no surface block connected to the root block." << std::endl;
				return "";
			}

			// make the list of connected blocks
			m_scene->upward_blocks (Ci_parent, shader_blocks);
			m_scene->upward_blocks (Oi_parent, shader_blocks);
		}
		break;

		case DISPLACEMENT:
		{
			// get displacement parents (N and P)
			std::string N_output_name;
			shader_block* N_parent = m_scene->get_parent (name(), "N", N_output_name);
			std::string P_output_name;
			shader_block* P_parent = m_scene->get_parent (name(), "P", P_output_name);

			// make sure there's something to build
			if (!N_parent && !P_parent) {

				log() << info << "there's no displacement block connected to the root block." << std::endl;
				return "";
			}

			// make the list of connected blocks
			m_scene->upward_blocks (N_parent, shader_blocks);
			m_scene->upward_blocks (P_parent, shader_blocks);
		}
		break;

		case LIGHT:
		{
			// get light parents (Cl and Ol)
			std::string Cl_output_name;
			shader_block* Cl_parent = m_scene->get_parent (name(), "Cl", Cl_output_name);
			std::string Ol_output_name;
			shader_block* Ol_parent = m_scene->get_parent (name(), "Ol", Ol_output_name);

			// make sure there's something to build
			if (!Cl_parent && !Ol_parent) {

				log() << info << "there's no light block connected to the root block." << std::endl;
				return "";
			}

			// make the list of connected blocks
			m_scene->upward_blocks (Cl_parent, shader_blocks);
			m_scene->upward_blocks (Ol_parent, shader_blocks);
		}
		break;

		case VOLUME:
		{
			// get atmosphere parents (Cv and Ov)
			std::string Cv_output_name;
			shader_block* Cv_parent = m_scene->get_parent (name(), "Cv", Cv_output_name);
			std::string Ov_output_name;
			shader_block* Ov_parent = m_scene->get_parent (name(), "Ov", Ov_output_name);

			// make sure there's something to build
			if (!Cv_parent && !Ov_parent) {

				log() << info << "there's no atmosphere block connected to the root block." << std::endl;
				return "";
			}

			// make the list of connected blocks
			m_scene->upward_blocks (Cv_parent, shader_blocks);
			m_scene->upward_blocks (Ov_parent, shader_blocks);
		}
		break;

		default:
			log() << error << "unhandled shader type.";
			return "";
	}

	// start code
	std::string meta_file ("");
	meta_file += "<k3dml>\n";

	// get parameters and outputs
	std::string parameters;
	std::string shader_outputs;
	for (scene::shader_blocks_t::const_iterator block = shader_blocks.begin(); block != shader_blocks.end(); ++block) {

		shader_block* sb = block->second;

		sb->reset_code_written();

		// get parameter values (inputs that are not connected)
		for (shader_block::properties_t::const_iterator input = sb->m_inputs.begin(); input != sb->m_inputs.end(); ++input) {

			if (m_scene->is_connected (scene::io_t (sb->name(), input->m_name))) {
				continue;
			}

			if (input->m_shader_parameter) {
				parameters += "\t\t\t<argument name=\"" + sb->sl_name() + "_" + input->m_name + "\""
						+ " storage_class=\"" + input->get_storage() + "\""
						+ " type=\"" + sb->input_type (input->m_name) + "\""
						+ " extended_type=\"" + sb->input_type (input->m_name) + "\"" // TODO
						+ " array_count=\"" + "1" + "\"" // TODO
						+ " space=\"" + "\"" // TODO
						+ " output=\"false\""
						+ " default_value=\"" + input->value_as_sl_string()
						+ "\"/>\n";
			}
		}

		// get output values
		//TODO test that each name is unique
		for (shader_block::properties_t::const_iterator output = sb->m_outputs.begin(); output != sb->m_outputs.end(); ++output) {

			if (!output->m_shader_output) {
				continue;
			} else {
				shader_outputs += "\t\t\t<argument name=\"" + sb->sl_name() + "_" + output->m_name + "\""
						+ " storage_class=\"" + sb->output_storage (output->m_name) + "\""
						+ " type=\"" + sb->output_type (output->m_name) + "\""
						+ " extended_type=\"" + sb->output_type (output->m_name) + "\"" // TODO
						+ " array_count=\"" + "1" + "\"" // TODO
						+ " space=\"" + "\"" // TODO
						+ " output=\"true\""
						+ "\"/>\n";
			}
		}
	}

	meta_file += "\t<shaders>\n";

	// shader type
	meta_file += "\t\t<shader type=\"";
	switch (ShaderType) {

		case SURFACE:
			// Preset AOVs, shader arguments, so we initialize them
			meta_file += "surface\" name=\"" + ShaderName + "\">\n";
		break;

		case DISPLACEMENT:
			meta_file += "displacement\" name=\"" + ShaderName + "\">\n";
		break;

		case LIGHT:
			meta_file += "light\" name=\"" + ShaderName + "\">\n";
		break;

		case VOLUME:
			meta_file += "volume\" name=\"" + ShaderName + "\">\n";
		break;

		default:
			log() << error << "unhandled shader type.";
	}

	// description and authors
	meta_file += "\t\t\t<description></description>\n";
	meta_file += "\t\t\t<authors></authors>\n";

	// add function's parameters
	meta_file += parameters;
	meta_file += shader_outputs;

	meta_file += "\t\t</shader>\n";
	meta_file += "\t</shaders>\n";
	meta_file += "</k3dml>\n";

	return meta_file;
}


std::string rib_root_block::show_code() {

	std::string shader_list ("");

	const std::string surface = build_shader_file (SURFACE, "preview_surface");
	const std::string displacement = build_shader_file (DISPLACEMENT, "preview_displacement");
	const std::string light = build_shader_file (LIGHT, "preview_light");
	const std::string volume = build_shader_file (VOLUME, "preview_volume");

	shader_list += surface + "\n" + displacement + "\n" + light + "\n" + volume + "\n";

	return shader_list;
}


bool rib_root_block::export_shader (const shader_t ShaderType, const std::string& ShaderName, const std::string& ShaderFile) {

	const std::string surface = build_shader_file (ShaderType, ShaderName);

	std::ofstream file (ShaderFile.c_str());

	file << surface;

	file.close();

	return true;
}


bool rib_root_block::export_k3d_slmeta (const shader_t ShaderType, const std::string& ShaderName, const std::string& ShaderFile) {

	const std::string surface = build_k3d_meta_file (ShaderType, ShaderName);

	std::ofstream file ((ShaderFile + "meta").c_str());

	file << surface;

	file.close();

	return true;
}


std::string rib_root_block::shader_compilation_command (const std::string& Shader, const std::string& ShaderPath, const std::string& DestinationName, const std::string& DestinationPath, const std::string& IncludePath) {

	general_options prefs;
	prefs.load();

	//std::string compiled_shader = change_file_extension(Shader, prefs.m_compiled_shader_extension);
	std::string compiled_shader = DestinationName + '.' + prefs.m_compiled_shader_extension;

	std::string command = prefs.m_shader_compiler;
	replace_variable (command, "%r", prefs.m_renderer_code);
	replace_variable (command, "%i", IncludePath);
	replace_variable (command, "%s", ShaderPath + '/' + Shader);
	replace_variable (command, "%o", DestinationPath + '/' + compiled_shader);

	log() << aspect << " Shader compilation command : " << command << std::endl;

	return command;
}

std::string rib_root_block::scene_rendering_command (const std::string& RIBFile, const std::string& ShaderPath) {

	general_options prefs;
	prefs.load();

	std::string command = prefs.m_renderer;
	replace_variable(command, "%i", ShaderPath);
	replace_variable(command, "%s", RIBFile);

	log() << aspect << " Scene rendering command : " << command << std::endl;

	return command;
}


void rib_root_block::write_RIB (const std::string& RIBFile, const std::string& TempDir, const std::string& SurfaceName, const std::string& DisplacementName, const std::string& LightName, const std::string& AtmosphereName, const std::string& ImagerName) {

	// open file
	std::ofstream file (RIBFile.c_str());

	// options
	general_options prefs;
	prefs.load();

	// get the scene template
	std::string scene_template (prefs.get_RIB_scene());


	// create the shader statements
	std::string imager_shader ("");
	std::string surface_shaders ("");
	std::string displacement_shaders ("");
	std::string volume_shaders ("");
	std::string light_shaders ("");

	// light
	if (!LightName.empty()) {
		light_shaders += "\tLightSource \"" + LightName + "\" 0\n";
	} else {

		light_shaders += "LightSource \"ambientlight\" 0 \"intensity\" [1.0] \"lightcolor\" [1 1 1]\n";
		light_shaders += "\tLightSource \"distantlight\" 1 \"intensity\" [1.0] \"lightcolor\" [1 1 1] \"from\" [-1 1 -1] \"to\" [0 0 0]\n";
		light_shaders += "\tLightSource \"distantlight\" 2 \"intensity\" [0.8] \"lightcolor\" [1 1 1] \"from\" [1 1 1] \"to\" [0 0 0]\n";
		light_shaders += "\tLightSource \"distantlight\" 3 \"intensity\" [0.65] \"lightcolor\" [1 1 1] \"from\" [1 -1 -1] \"to\" [0 0 0]\n";

	}

	// imager
	m_imager_statement = trim (m_imager_statement);
	if (!m_imager_statement.empty()) {

		const std::string beginning = m_imager_statement.substr (0, 6);
		if (beginning == "Imager" || beginning == "imager") {
			imager_shader += m_imager_statement + "\n";
		} else {

			imager_shader += "Imager " + m_imager_statement + "\n";
		}
	}

	// atmosphere
	if (!AtmosphereName.empty()) {
		volume_shaders += "\tAtmosphere \"" + AtmosphereName + "\"\n";
	}


	// surface
	if (SurfaceName.empty()) {
		surface_shaders += "Surface \"matte\"\n";
	} else {
		surface_shaders += "Surface \"" + SurfaceName + "\"\n";
	}

	// displacement
	if (!DisplacementName.empty()) {
		displacement_shaders += "Displacement \"" + DisplacementName + "\"\n";
		displacement_shaders += "\t\tAttribute \"displacementbound\" \"float sphere\" [0.5] \"string coordinatesystem\" [\"shader\"]\n";
		//displacement_shaders += "Attribute \"render\" \"patch_multiplier\" 1.0\n";
	}


	// replace the shader values
	replace_variable (scene_template, "$(imager_shader)", imager_shader);
	replace_variable (scene_template, "$(surface_shaders)", surface_shaders);
	replace_variable (scene_template, "$(displacement_shaders)", displacement_shaders);
	replace_variable (scene_template, "$(volume_shaders)", volume_shaders);
	replace_variable (scene_template, "$(light_shaders)", light_shaders);

	std::string all_other_shaders = surface_shaders + "\n" + displacement_shaders + "\n" + volume_shaders + "\n" + light_shaders;
	replace_variable (scene_template, "$(shaders)", all_other_shaders);

	// prepare display (defaults to "framebuffer")
	std::string display = prefs.m_renderer_display;
	if (display.empty()) {
		display = "framebuffer";
	}

	// prepare AOV preview (if connected)
	std::string parent_name ("");
	bool AOV = get_AOV() && has_AOV_input (parent_name);

	// write the RIB file
	file << "# Shrimp preview scene\n";
	file << "\n";
	file << "Option \"searchpath\" \"string resource\" [\"@:./:./data/rib/scenes:$HOME/.shrimp/temp:&\"]\n";
	file << "\n";
	file << "Display \"outputimage.tif\" \"" << display << "\" \"rgba\"\n";
	if (AOV) {
		// standard/predefined AOVs ( from shrimp_aov.h )
		// the user can create AOV blocks later, but that means updating the
		// RIB file, displays type, etc.., so we'll provide for a start, a good
		// set of presets, such as diffuse, specular, reflection, etc...
		// note that the string should be
		// "+/whatever/path/aov_name.tif" "file" "type aov_name"
		// displays descriptions in renderer .xml file needs to be updated to
		// include these preset AOVs, but for a secondaries display option
		// AOV presets
		file << "# AOVs here\n";
		file << "Display \"+" + TempDir + "/" + "aov_surfacecolor"
			 + ".tif" + "\" \"file\" \"varying color aov_surfacecolor\" "
			 + "\"quantize\" [0 255 0 255]\n";
		file << "Display \"+" + TempDir + "/" + "aov_ambient" + ".tif"
			+ "\" \"file\" \"varying color aov_ambient\" "
			+ "\"quantize\" [0 255 0 255]\n";
		file << "Display \"+" + TempDir + "/" + "aov_diffuse" + ".tif"
			+ "\" \"file\" \"varying color aov_diffuse\" "
			+ "\"quantize\" [0 255 0 255]\n";
		file << "Display \"+" + TempDir + "/" + "aov_specular" + ".tif"
			+ "\" \"file\" \"varying color aov_specular\" "
			+ "\"quantize\" [0 255 0 255]\n";
		file << "Display \"+" + TempDir + "/" + "aov_specularcolor" + ".tif"
			+ "\" \"file\" \"varying color aov_specularcolor\" "
			+ "\"quantize\" [0 255 0 255]\n";
		file << "Display \"+" + TempDir + "/" + "aov_reflection"
			+ ".tif" + "\" \"file\" \"varying color aov_reflection\" "
			+ "\"quantize\" [0 255 0 255]\n";
		file << "Display \"+" + TempDir + "/" + "aov_refraction"
			+ ".tif" + "\" \"file\" \"varying color aov_refraction\" "
			+ "\"quantize\" [0 255 0 255]\n";
		file << "Display \"+" + TempDir + "/" + "aov_rimlighting" + ".tif"
			+ "\" \"file\" \"varying color aov_rimlighting\" "
			+ "\"quantize\" [0 255 0 255]\n";
		file << "Display \"+" + TempDir + "/" + "aov_scattering"
			+ ".tif" + "\" \"file\" \"varying color aov_scattering\" "
			+ "\"quantize\" [0 255 0 255]\n";
		file << "Display \"+" + TempDir + "/" + "aov_translucence"
			+ ".tif" + "\" \"file\" \"varying color aov_translucence\" "
			+ "\"quantize\" [0 255 0 255]\n";
		file << "Display \"+" + TempDir + "/" + "aov_shadows"
			+ ".tif" + "\" \"file\" \"varying color aov_shadows\" "
			+ "\"quantize\" [0 255 0 255]\n";
		file << "Display \"+" + TempDir + "/" + "aov_occlusion"
			+ ".tif" + "\" \"file\" \"varying float aov_occlusion\" "
			+ "\"quantize\" [0 255 0 255]\n";
		file << "Display \"+" + TempDir + "/" + "aov_opacity"
			+ ".tif" + "\" \"file\" \"varying color aov_opacity\" "
			+ "\"quantize\" [0 255 0 255]\n";
	}
	
	file << "# User set root block RIB statements\n";
	file << m_general_statements << "\n";
	file << "# Preview scene\n";
	file << "Format " << prefs.m_output_width << " " << prefs.m_output_height << " 1\n";
	file << "PixelSamples " << prefs.m_samples_x << " " << prefs.m_samples_y << "\n";
	file << "ShadingRate " << prefs.m_shading_rate << "\n";
	file << "Exposure 1 1\n";
	file << "Quantize \"rgba\" 255 0 255 0.5\n";
	file << "ShadingInterpolation \"smooth\"\n";
	file << "Clipping 0.01 100\n";
	file << "\n";
	file << scene_template << std::endl;

	file.close();
}


void rib_root_block::write_scene_and_shaders (const std::string& Directory, command_list_t& CommandList) {

	const std::string shader_path = system_functions::get_absolute_path("./data/rib/shaders");

	// compile the shaders from the template scene
	general_options prefs;
	prefs.load();
	std::string scene_template (prefs.get_RIB_scene());

	CommandList.push_back( parse_scene_shader (scene_template, shader_path, Directory, "Surface") );
	CommandList.push_back( parse_scene_shader (scene_template, shader_path, Directory, "Displacement") );
	CommandList.push_back( parse_scene_shader (scene_template, shader_path, Directory, "LightSource") );
	CommandList.push_back( parse_scene_shader (scene_template, shader_path, Directory, "Atmosphere") );

	// build the default shaders
	CommandList.push_back( shader_compilation_command("ambientlight.sl", shader_path, "ambientlight", Directory, shader_path) );
	CommandList.push_back( shader_compilation_command("distantlight.sl", shader_path, "distantlight", Directory, shader_path) );

	// build Shrimp generated shaders
	std::string surface_shader ("");
	std::string displacement_shader ("");
	std::string light_shader ("");
	std::string atmosphere_shader ("");

	if (has_surface_network()) {

		// RenderMan surface shader
		surface_shader = "preview_surface";
		export_shader (SURFACE, surface_shader, Directory + '/' + surface_shader + ".sl");
		CommandList.push_back( shader_compilation_command (surface_shader + ".sl", Directory, surface_shader, Directory, shader_path) );

		// K-3D meta file
		export_k3d_slmeta (SURFACE, surface_shader, Directory + '/' + surface_shader + ".sl");
	}

	if (has_displacement_network()) {

		// RenderMan displacement shader
		displacement_shader = "preview_displacement";
		export_shader (DISPLACEMENT, displacement_shader, Directory + '/' + displacement_shader + ".sl");
		CommandList.push_back( shader_compilation_command (displacement_shader + ".sl", Directory, displacement_shader, Directory, shader_path) );

		// K-3D meta file
		export_k3d_slmeta (DISPLACEMENT, displacement_shader, Directory + '/' + displacement_shader + ".sl");
	}

	if (has_light_network()) {

		// RenderMan light shader
		light_shader = "preview_light";
		export_shader (LIGHT, light_shader, Directory + '/' + light_shader + ".sl");
		CommandList.push_back( shader_compilation_command (light_shader + ".sl", Directory, light_shader, Directory, shader_path) );

		// K-3D meta file
		export_k3d_slmeta (LIGHT, light_shader, Directory + '/' + light_shader + ".sl");
	}

	if (has_atmosphere_network()) {

		// RenderMan atmosphere shader
		atmosphere_shader = "preview_atmosphere";
		export_shader (VOLUME, atmosphere_shader, Directory + '/' + atmosphere_shader + ".sl");
		CommandList.push_back( shader_compilation_command (atmosphere_shader + ".sl", Directory, atmosphere_shader, Directory, shader_path) );

		export_k3d_slmeta (VOLUME, atmosphere_shader, Directory + '/' + atmosphere_shader + ".sl");
	}

	// output scene
	std::string rib_preview = Directory + '/' + "preview.rib";

	write_RIB (rib_preview, Directory, surface_shader, displacement_shader, light_shader, atmosphere_shader);

	CommandList.push_back( scene_rendering_command (rib_preview, Directory) );
}


void rib_root_block::show_preview (const std::string& SceneDirectory) {

	command_list_t commands;
	write_scene_and_shaders (SceneDirectory, commands);

	// output commands in a file for debugging purposes
	const std::string command_file (SceneDirectory + '/' + "command_debug.txt");
	write_command_list (commands, command_file);

	// execute commands
	for (command_list_t::const_iterator c = commands.begin(); c != commands.end(); ++c) {

		system_functions::execute_command (*c);
	}

/*
	int pid = fork();
	if(pid == -1)
	{
		std::cout << "Error creating new process\n";
		//system(cleanup.c_str());
	}
	else if(pid == 0)
	{
		int status;
		int pid2 = fork();
		if(pid2 == -1)
		{
			std::cout << "Error creating new process\n";
		}
		else if(pid2 == 0)
		{
			std::cout << render_command << std::endl;
			char* argv[4];
			argv[0] = "sh";
			argv[1] = "-c";
			argv[2] = const_cast<char*>(render_command.c_str());
			argv[3] = 0;
			execve("/bin/sh", argv, environ);
			//exit(127);
		}
	}
*/
}


void rib_root_block::export_scene (const std::string& SceneDirectory) {

	// output scene, get commmand list
	command_list_t commands;
	write_scene_and_shaders (SceneDirectory, commands);

	// write command file
	const std::string command_file (SceneDirectory + '/' + "command_list.txt");
	write_command_list (commands, command_file);
}


void rib_root_block::set_general_statements (const std::string& Statements) {

	m_general_statements = Statements;
}


std::string rib_root_block::get_general_statements() {

	return m_general_statements;
}


void rib_root_block::set_imager_statement (const std::string& Statement) {

	m_imager_statement = Statement;
}


std::string rib_root_block::get_imager_statement() {

	return m_imager_statement;
}


void rib_root_block::set_AOV (const bool State) {

	m_AOV = State;
}


bool rib_root_block::get_AOV() {

	return m_AOV;
}

std::string rib_root_block::parse_scene_shader (const std::string& RIBscene, const std::string ShaderPath, const std::string& TempDir, const std::string ShaderType) {

	std::string commands = "";

	// find shaders
	size_t pos = 0;
	do {
		pos = RIBscene.find (ShaderType, pos);
		if (pos != RIBscene.npos) {
			pos += 7;
			while (RIBscene[pos] != '"' && pos < RIBscene.size()) {
				++pos;
			}
			size_t name_start = pos++;
			while (RIBscene[pos] != '"' && pos < RIBscene.size()) {
				++pos;
			}
			size_t name_end = pos++;

			if (name_start < name_end && name_end < RIBscene.size()) {

				const std::string shader_name = RIBscene.substr (name_start + 1, name_end - name_start - 1);
				std::string shader_compilation = shader_compilation_command (shader_name + ".sl", ShaderPath, shader_name, TempDir, ShaderPath);

				if (!commands.empty())
					commands += "; ";

				commands += shader_compilation;
			}

		}
	}
	while (pos != RIBscene.npos);

	return commands;
}


void rib_root_block::write_command_list (const command_list_t& CommandList, const std::string& AbsoluteFileName) {

	std::ofstream file (AbsoluteFileName.c_str());

	for (command_list_t::const_iterator c = CommandList.begin(); c != CommandList.end(); ++c) {

		file << *c << std::endl;
	}

	file.close();
}


