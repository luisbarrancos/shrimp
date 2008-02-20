
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


#ifndef _ui_edit_input_h_
#define _ui_edit_input_h_

#include "../miscellaneous/logging.h"

#include <fltk/CheckButton.h>
#include <fltk/Choice.h>
#include <fltk/Group.h>
#include <fltk/Input.h>
#include <fltk/Output.h>
#include <fltk/ReturnButton.h>
#include <fltk/Window.h>

#include <string>

namespace edit_input
{

static fltk::Output* s_name = 0;
static fltk::Input* s_value = 0;
static fltk::Choice* s_type = 0;
static fltk::CheckButton* s_shader_parameter = 0;


class dialog {

private:
	fltk::Window* w;
	shader_block* m_shader_block;
	std::string m_edited_input;
	types_t m_types;

public:
	dialog (shader_block* Block) :
		m_shader_block (Block) {

		// build dialog window
		w = new fltk::Window(340, 160, "Edit input");
		w->begin();

			// name
			s_name = new fltk::Output (70,5, 120,23, "Name");
			w->add (s_name);
			s_name->tooltip ("Edited output name");

			// value edition
			s_value = new fltk::Input (70,32, 120,23, "Value");
			w->add (s_value);
			s_value->tooltip ("Input value");

			// variable type edition
			s_type = new fltk::Choice (70,59, 120,23, "Type");
			s_type->begin();
				// make sure the list isn't destroyed before the dialog closes
				m_types = get_property_types();
				for (types_t::const_iterator t_i = m_types.begin(); t_i != m_types.end(); ++t_i) {

					new fltk::Item (t_i->c_str());
				}
			s_type->end();
			w->add (s_type);
			s_type->tooltip ("Input variable type");

			// shader parameter checkbox
			s_shader_parameter = new fltk::CheckButton (70,86, 120,23, "Shader parameter");
			w->add (s_shader_parameter);
			s_shader_parameter->tooltip ("Make the input a shader parameter");


			// OK / Cancel
			fltk::ReturnButton* rb = new fltk::ReturnButton(150,125, 70,25, "OK");
			rb->label("Ok");
			rb->callback(cb_ok, (void*)this);

			fltk::Button* cb = new fltk::Button(250,125, 70,25, "Cancel");
			cb->label("Cancel");
			cb->callback(cb_cancel, (void*)this);

		w->end();
	}

	~dialog() {

		delete w;
	}

	void edit_input (std::string& InputName) {

		m_edited_input = InputName;

		// set name
		s_name->text (InputName.c_str());

		// set value
		const std::string value = m_shader_block->get_input_value (m_edited_input);
		s_value->text (value.c_str());

		// set type
		std::string type = m_shader_block->get_input_type (m_edited_input);
		if (m_shader_block->is_input_uniform (m_edited_input)) {
			type = "uniform " + type;
		}

		int type_number = 0;
		for (types_t::const_iterator t_i = m_types.begin(); t_i != m_types.end(); ++t_i, ++type_number) {

			if (type == *t_i)
				s_type->value (type_number);
		}

		// set shader parameter state
		s_shader_parameter->value (m_shader_block->is_shader_parameter (m_edited_input));

		// show the dialog
		w->exec();
	}

	void on_ok (fltk::Widget* W) {

		// save value
		const std::string new_value = s_value->value();
		m_shader_block->set_input_value (m_edited_input, new_value);

		// save type
		types_t list = get_property_types();
		const unsigned int type_number = s_type->value();
		if (type_number >= 0 && type_number < list.size()) {

			m_shader_block->set_input_type (m_edited_input, list[type_number]);
		}

		// save parameter state
		const bool shader_parameter = s_shader_parameter->value();
		m_shader_block->set_shader_parameter (m_edited_input, shader_parameter);

		// close the dialog
		W->window()->make_exec_return (false);
	}

	void on_cancel(fltk::Widget* W) {

		W->window()->make_exec_return (false);
	}

	static void cb_ok(fltk::Widget* W, void* Data) { ((dialog*)Data)->on_ok(W); }
	static void cb_cancel(fltk::Widget* W, void* Data) { ((dialog*)Data)->on_cancel(W); }
};

}

#endif // _ui_edit_input_h_

