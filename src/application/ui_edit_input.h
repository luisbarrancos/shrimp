
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

#include <fltk/Button.h>
#include <fltk/CheckButton.h>
#include <fltk/Choice.h>
#include <fltk/ColorChooser.h>
#include <fltk/Group.h>
#include <fltk/Input.h>
#include <fltk/Output.h>
#include <fltk/ReturnButton.h>
#include <fltk/Window.h>

#include <iostream>
#include <string>

namespace edit_input
{

static fltk::Output* s_name = 0;
static fltk::Input* s_value = 0;
static fltk::Button* s_colour_button = 0;
static fltk::Choice* s_type = 0;
static fltk::Choice* s_storage = 0;
static fltk::CheckButton* s_shader_parameter = 0;

static void cb_colour_chooser (fltk::Widget *w, void *v) {

	uchar r = 0, g = 0, b = 0;
	//fltk::split_color(current_color, r, g, b);

	if (!fltk::color_chooser("New color:", r,g,b))
		return;

	// set new colour
	std::ostringstream new_colour;
	new_colour << ((float)r/255.0) << " " << ((float)g/255.0) << " " << ((float)b/255.0);
	s_value->text (new_colour.str().c_str());

	// redraw parent box
	w->parent()->redraw();
}

class dialog {

private:
	fltk::Window* w;
	shader_block* m_shader_block;
	std::string m_edited_input;
	types_t m_types;
	storages_t m_storage_types;

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

			s_colour_button = new fltk::Button (200,32, 120,23, "Colour");
			s_colour_button->callback (cb_colour_chooser);
			w->add (s_colour_button);
			s_colour_button->tooltip ("Colour chooser");

			// storage edition
			s_storage = new fltk::Choice (70,59, 90,23, "Type");
			s_storage->begin();
				// make sure the list isn't destroyed before the dialog closes
				m_storage_types = get_property_storage_types();
				for (storages_t::const_iterator st_i = m_storage_types.begin(); st_i != m_storage_types.end(); ++st_i) {

					new fltk::Item (st_i->c_str());
				}
			s_storage->end();
			w->add (s_storage);
			s_storage->tooltip ("Input variable storage type");

			// type edition
			s_type = new fltk::Choice (160,59, 120,23, "");
			s_type->begin();
				// make sure the list isn't destroyed before the dialog closes
				m_types = get_property_types();
				for (types_t::const_iterator t_i = m_types.begin(); t_i != m_types.end(); ++t_i) {

					new fltk::Item (t_i->c_str());
				}
			s_type->end();
			s_type->callback (cb_type_change);
			w->add (s_type);
			s_type->tooltip ("Input variable type");

			// shader parameter checkbox
			s_shader_parameter = new fltk::CheckButton (70,86, 120,23, "Shader parameter");
			w->add (s_shader_parameter);
			s_shader_parameter->tooltip ("Make the input a shader parameter");


			// OK / Cancel
			fltk::ReturnButton* rb = new fltk::ReturnButton(150,125, 70,25, "OK");
			rb->label("Ok");
			rb->callback (cb_ok, (void*)this);

			fltk::Button* cb = new fltk::Button(250,125, 70,25, "Cancel");
			cb->label("Cancel");
			cb->callback (cb_cancel, (void*)this);

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

		// set types
		const std::string storage = m_shader_block->get_input_storage (m_edited_input);
		int storage_type_number = 0;
		for (storages_t::const_iterator s_i = m_storage_types.begin(); s_i != m_storage_types.end(); ++s_i, ++storage_type_number) {

			if (storage == *s_i)
				s_storage->value (storage_type_number);
		}

		const std::string type = m_shader_block->get_input_type (m_edited_input);
		int type_number = 0;
		for (types_t::const_iterator t_i = m_types.begin(); t_i != m_types.end(); ++t_i, ++type_number) {

			if (type == *t_i)
				s_type->value (type_number);

			// colour button active when the type is 'color'
			if (type == "color")
				s_colour_button->activate();
			else
				s_colour_button->deactivate();
		}

		// set shader parameter state
		s_shader_parameter->value (m_shader_block->is_shader_parameter (m_edited_input));

		// show the dialog
		w->exec();
	}

	void on_type_change (fltk::Widget* W) {

		types_t list = get_property_types();
		const unsigned int type_number = s_type->value();
		if (type_number >= 0 && type_number < list.size()) {

			const std::string current_type = list[type_number];
			if (current_type == "color")
				s_colour_button->activate();
			else
				s_colour_button->deactivate();
		}
	}

	void on_ok (fltk::Widget* W) {

		// save value
		const std::string new_value = s_value->value();
		m_shader_block->set_input_value (m_edited_input, new_value);

		// save types
		types_t storage_list = get_property_storage_types();
		const unsigned int storage_type_number = s_storage->value();
		if (storage_type_number >= 0 && storage_type_number < storage_list.size()) {

			m_shader_block->set_input_storage (m_edited_input, storage_list[storage_type_number]);
		}

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

	void on_cancel (fltk::Widget* W) {

		W->window()->make_exec_return (false);
	}

	static void cb_type_change (fltk::Widget* W, void* Data) { ((dialog*)Data)->on_type_change (W); }
	static void cb_ok (fltk::Widget* W, void* Data) { ((dialog*)Data)->on_ok (W); }
	static void cb_cancel (fltk::Widget* W, void* Data) { ((dialog*)Data)->on_cancel (W); }
};

}

#endif // _ui_edit_input_h_

