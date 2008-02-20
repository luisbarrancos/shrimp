
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


#ifndef _ui_edit_output_h_
#define _ui_edit_output_h_

#include "../miscellaneous/logging.h"

#include <fltk/LightButton.h>
#include <fltk/Output.h>
#include <fltk/ReturnButton.h>
#include <fltk/Window.h>

#include <string>

namespace edit_output
{

static fltk::Output* s_name = 0;
static fltk::Choice* s_type = 0;
static fltk::LightButton* s_shader_output = 0;


class dialog {

private:
	fltk::Window* w;
	shader_block* m_shader_block;
	std::string m_edited_output;
	types_t m_types;

public:
	dialog (shader_block* Block) :
		m_shader_block (Block) {

		// build dialog window
		w = new fltk::Window (340, 130, "Edit output");
		w->begin();

			// name
			s_name = new fltk::Output (70,5, 120,23, "Name");
			w->add (s_name);
			s_name->tooltip ("Edited output name");

			// type edition
			s_type = new fltk::Choice (70,32, 120,23, "Type");
			s_type->begin();
				// make sure the list isn't destroyed before the dialog closes
				m_types = get_property_types();
				for (types_t::const_iterator t_i = m_types.begin(); t_i != m_types.end(); ++t_i) {

					new fltk::Item (t_i->c_str());
				}
			s_type->end();
			w->add (s_type);
			s_type->tooltip ("Output variable type");

			// shader output state (inactive)
			s_shader_output = new fltk::LightButton (70,59, 120,23, "Shader output");
			w->add (s_shader_output);
			s_shader_output->tooltip ("Make it a shader output for message passing");
			s_shader_output->deactivate();


			// OK / Cancel
			fltk::ReturnButton* rb = new fltk::ReturnButton (150,95, 70,25, "OK");
			rb->label("Ok");
			rb->callback(cb_ok, (void*)this);

			fltk::Button* cb = new fltk::Button (250,95, 70,25, "Cancel");
			cb->label("Cancel");
			cb->callback(cb_cancel, (void*)this);

		w->end();
	}

	~dialog() {

		delete w;
	}

	void edit_output (std::string& OutputName) {

		m_edited_output = OutputName;

		// set name
		s_name->text (OutputName.c_str());

		// set type
		std::string type = m_shader_block->get_output_type (m_edited_output);
		if (m_shader_block->is_output_uniform (m_edited_output)) {
			type = "uniform " + type;
		}

		int type_number = 0;
		for (types_t::const_iterator t_i = m_types.begin(); t_i != m_types.end(); ++t_i, type_number++) {

			if (type == *t_i)
				s_type->value (type_number);
		}

		// set shader output state
		s_shader_output->value (m_shader_block->is_shader_output (OutputName));


		// show the dialog
		w->exec();
	}

	void on_ok (fltk::Widget* W) {

		// save type
		types_t list = get_property_types();
		const unsigned int type_number = s_type->value();
		if (type_number >= 0 && type_number < list.size()) {

			m_shader_block->set_output_type (m_edited_output, list[type_number]);
		}

		// save shader output state
		//m_shader_block->set_shader_output (m_edited_output, s_shader_output->value());

		W->window()->make_exec_return (false);
	}

	void on_cancel (fltk::Widget* W) {

		W->window()->make_exec_return (false);
	}

	static void cb_ok (fltk::Widget* W, void* Data) { ((dialog*)Data)->on_ok(W); }
	static void cb_cancel (fltk::Widget* W, void* Data) { ((dialog*)Data)->on_cancel(W); }
};

}

#endif // _ui_edit_output_h_

