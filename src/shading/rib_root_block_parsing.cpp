
/*
    Copyright 2010, Romain Behar <romainbehar@users.sourceforge.net>

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


#include "rib_root_block_parsing.h"

#include "../miscellaneous/logging.h"
#include "../miscellaneous/misc_string_functions.h"

#include <map>


// poor man's parser to transform valued arrays
typedef std::string::size_type string_pos;

std::vector<std::string> new_code_lines;
std::set<std::string> new_instanciations;


string_pos previous_line_start = 0;


void new_code_line (string_pos n, std::string& new_code)
{
	if (new_instanciations.size() > 0)
	{
		for (std::set<std::string>::iterator i = new_instanciations.begin(); i != new_instanciations.end(); ++i)
		{
			new_code_lines.push_back (*i);
		}
	}

	new_code_lines.push_back (new_code);
	new_code = "";

	previous_line_start = n;
	if (n > 0)
		n--;

	new_instanciations.clear();
}

std::string get_valued_variable_name (std::string name)
{
	return "valued_variable_" + name;
}

void add_declaration (std::string name, std::string index, std::set<std::string>& local_declarations)
{
	std::string declaration = "$(" + name + ":type) " + get_valued_variable_name (name);
	std::string instanciation = get_valued_variable_name (name) + " = $(" + name + ");\n";

	local_declarations.insert (declaration);
	new_instanciations.insert (instanciation);
}



// Replace:
//   $(nnn)[i]
// with
//   type nnn_i = $(nnn); // to prevent 'normalize(vvv)[i]'
//   nnn_i[i]
std::string create_array_value_variables (const std::string code, std::set<std::string>& local_declarations)
{
	new_code_lines.clear();
	new_instanciations.clear();

	bool single_line_comment = false;
	bool multi_line_comment = false;
	bool preprocessor_directive = false;
	bool in_shrimp_variable = false;
	bool in_shrimp_variable_array_index = false;

	string_pos shrimp_variable_real_start;
	string_pos shrimp_variable_start;
	string_pos shrimp_variable_end;
	std::string shrimp_variable;
	std::string shrimp_variable_array_index;

	unsigned int parenthesis_level = 0;

	char previous_character = ' ';

	std::string new_code;
	for (std::string::size_type n = 0; n < code.size(); ++n)
	{
		char c = code[n];
		new_code += c;
		if (c == ' '
			|| c == '\n'
			|| c == '\t'
			|| c == '\r'
			|| single_line_comment
			|| multi_line_comment
			)
		{
			if (single_line_comment)
			{
				if (c == '\n' && previous_character != '\\')
				{
					single_line_comment = false;

					// new code line
					string_pos new_code_line_start = new_code.size();

					string_pos p = n;
					char next_c = code[p];
					while ((p < code.size()) && (next_c == '\n' || next_c == '\r'))
					{
						++p;
						++new_code_line_start;

						next_c = code[p];
					}

					new_code_line (new_code_line_start, new_code);
				}
			}

			if (multi_line_comment)
			{
				if (c == '/' && previous_character == '*')
					multi_line_comment = false;
			}

			if (preprocessor_directive)
			{
				if (c == '\n' && previous_character != '\\')
				{
					preprocessor_directive = false;

					// new code line
					string_pos new_code_line_start = new_code.size();

					string_pos p = n;
					char next_c = code[p];
					while ((p < code.size()) && (next_c == '\n' || next_c == '\r'))
					{
						++p;
						++new_code_line_start;

						next_c = code[p];
					}

					new_code_line (new_code_line_start, new_code);
				}
			}

			continue;
		}

		if (c == '/' && previous_character == '/')
		{
			single_line_comment = true;
		}
		else if (c == '*' && previous_character == '/')
		{
			multi_line_comment = true;
		}
		else if (c == '#')
		{
			preprocessor_directive = true;
		}
		else if (c == ';')
		{
			if (parenthesis_level == 0)
			{
				string_pos new_code_line_start = new_code.size();

				string_pos p = n;
				char next_c = code[p];
				while (next_c == '\n' || next_c == '\r')
				{
					++p;
					++new_code_line_start;

					next_c = code[p];
				}

				new_code_line (new_code_line_start, new_code);
			}
		}
		else if (c == '=')
		{
		}
		else if (c == '(')
		{
			parenthesis_level++;

			if (previous_character == '$')
			{
				in_shrimp_variable = true;
				shrimp_variable_real_start = n - 1;
				shrimp_variable_start = n + 1;
			}
		}
		else if (c == ')')
		{
			parenthesis_level--;

			if (in_shrimp_variable)
			{
				in_shrimp_variable = false;
				shrimp_variable_end = n - 1;
				shrimp_variable = trim (std::string (code, shrimp_variable_start, shrimp_variable_end - shrimp_variable_start + 1));
			}
		}
		else if (c == '[' && previous_character == ')')
		{
			in_shrimp_variable_array_index = true;
			shrimp_variable_start = n + 1;
		}
		else if (c == ']')
		{
			if (in_shrimp_variable_array_index)
			{
				in_shrimp_variable_array_index = false;
				shrimp_variable_end = n - 2; //?
				shrimp_variable_array_index = trim (std::string (code, shrimp_variable_start, shrimp_variable_end - shrimp_variable_start + 1));

				// replace variable in new code
				add_declaration (shrimp_variable, shrimp_variable_array_index, local_declarations);

				string_pos replacement_start = new_code.size() - (n - shrimp_variable_real_start + 1);
				string_pos replacement_size = new_code.size() - replacement_start - 1;
				new_code.replace (replacement_start, replacement_size, get_valued_variable_name (shrimp_variable));
			}
		}

		previous_character = c;
	}

	// build shader block
	std::string shader_block = "";
	for (std::vector<std::string>::iterator i = new_code_lines.begin(); i != new_code_lines.end(); ++i)
	{
		shader_block += "\t" + *i;
	}

	return shader_block;
}


