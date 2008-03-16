
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


#include "ui_application_window.h"
#include "ui_code_preview.h"
#include "ui_shader_properties.h"
#include "ui_preferences.h"

#include "../miscellaneous/logging.h"
#include "../miscellaneous/misc_string_functions.h"
#include "../miscellaneous/misc_system_functions.h"
#include "../miscellaneous/misc_xml.h"

#include <fltk/Color.h>
#include <fltk/Divider.h>
#include <fltk/Input.h>
#include <fltk/Item.h>
#include <fltk/ItemGroup.h>
#include <fltk/MenuBar.h>
#include <fltk/ReturnButton.h>
#include <fltk/TextEditor.h>
#include <fltk/ToggleItem.h>

#include <fltk/ask.h>
#include <fltk/events.h>
#include <fltk/file_chooser.h>
#include <fltk/filename.h>

#include <fltk/DoubleBufferWindow.h>

#include <fstream>
#include <iostream>


// File menu : New
void application_window::on_menu_file_new (fltk::Widget*) {

	m_scene->new_scene();
	m_scene_file = "";

	// fit scene
	const double new_size = m_scene_view->fit_scene();
	m_zoom_slider.value (new_size);
}


bool application_window::load_scene (const std::string& File) {

	if (!m_scene->load (File)) {

		const std::string alert = "Couldn't open '" + File + "'.";
		fltk::alert (alert.c_str());

		return false;
	}

	m_scene_file = File;

	m_scene_view->set_scene (m_scene);
	const double new_size = m_scene_view->fit_scene();

	m_zoom_slider.value (new_size);

	return true;
}


// File menu : Open
void application_window::on_menu_file_open (fltk::Widget*) {

	// get current directory
	char result[2048];
	fltk::filename_absolute (result, 2048, ".");

	// choose shader file
	const char* file = fltk::file_chooser ("Open Shader", "*.xml", result);
	if(!file)
		return;

	load_scene (file);
}

// File menu : Save
void application_window::on_menu_file_save (fltk::Widget*) {

	if (!m_scene_file.empty()) {

		log() << aspect << "saving project (" << m_scene_file << ")" << std::endl;
		m_scene->save_as (m_scene_file);

	} else {

		save_scene_as();
	}
}

// File menu : Save As...
void application_window::on_menu_file_save_as (fltk::Widget*) {

	save_scene_as();
}

// File menu : Shader Properties
void application_window::on_menu_shader_properties (fltk::Widget*) {

	std::string name (m_scene->name());
	std::string description (m_scene->description());
	if(shader_properties::sp_dialog (name, description)) {

		m_scene->set_name (shader_properties::name->value());
		m_scene->set_description (shader_properties::description->text());
	}
}

// File menu : Code Preview...
void application_window::on_menu_code_preview (fltk::Widget*) {

	std::string surface_code ("");
/*
	if (m_scene_view->get_scene()->has_surface_network()) {

		surface_code = m_scene_view->get_scene()->build_shader_file (scene::SURFACE, "surface_preview");
	}
*/
	surface_code = m_scene->get_shader_code();

	code_preview::dialog d;
	d.open (surface_code);
}

// File menu : Render Options...
void application_window::on_menu_file_options (fltk::Widget*, void*) {

	preferences::dialog d;
	d.pref_dialog();
}


// File menu : Export Shader...
void application_window::on_menu_file_export_shader (fltk::Widget*) {

// TODO
	log() << error << "unimplemented - File -> Export Shader" << std::endl;

	// Choose export name
	//const char* file = fltk::file_chooser("Export Shader As", "*.sl", result);
	//m_scene_view->get_scene()->export_shader_as("test.sl");
}

// File menu : Quit
void application_window::on_menu_file_quit (fltk::Widget*, void*) {

	exit (0);
}

void application_window::on_menu_view_toggle_grid (fltk::Widget*) {

	const bool grid_state = m_menu_show_grid->state();
	m_scene_view->set_grid_state (grid_state);
}

void application_window::on_menu_view_toggle_grid_snap (fltk::Widget*) {

	const bool snap_to_grid_state = m_menu_snap_to_grid->state();
	m_scene_view->set_snap_to_grid_state (snap_to_grid_state);
}

void application_window::on_menu_view_toggle_overview (fltk::Widget*) {

	const bool overview_state = m_menu_overview->state();
	m_scene_view->set_overview_state (overview_state);
}

// Help menu : About
#include "ui_about.h"
#include <fltk/Monitor.h>

void application_window::on_menu_help_about (fltk::Widget*, void*) {

	fltk::Window* o = about_window();
	o->show();
}

void application_window::on_zoom(fltk::Slider* o, void*) {

	m_scene_view->set_size((double)o->value());
	m_scene_view->redraw();
}

void application_window::on_button_fit_scene (fltk::Widget*) {

	const double new_size = m_scene_view->fit_scene();

	m_zoom_slider.value (new_size);
}


void application_window::on_custom_block() {

	// create a custom block
	shader_block* new_block = m_scene->add_custom_block();

	// put it in the middle of the view
	m_scene_view->move_block_to_view_center (new_block);

	// refresh
	m_scene_view->redraw();
}


// Shader preview
void application_window::on_preview() {

	std::string tempdir = system_functions::get_tmp_directory();
	m_scene->show_preview (tempdir);
}


void application_window::on_renderer_choice (fltk::Widget* W, void* Data) {

	const std::string renderer_name ((const char*)Data);
	general_options::renderers_t::const_iterator r = m_renderers.find (renderer_name);
	if (r == m_renderers.end()) {
		log() << error << "unknown renderer: '" << renderer_name << "'" << std::endl;
		return;
	}

	// update the display chooser according to the current renderer
	m_renderer_display_chooser->remove_all();
	m_renderer_display_chooser->begin();
	for (general_options::displays_t::const_iterator display = r->second.displays.begin(); display != r->second.displays.end(); ++display) {
		new fltk::Item (display->c_str(), 0, cb_renderer_display, (void*)display->c_str());
	}
	m_renderer_display_chooser->end();
}


void application_window::on_renderer_display_choice (fltk::Widget* W, void* Data) {

	const std::string display_name ((const char*)Data);
log() << error << "Display : " << display_name << std::endl;
}


application_window::application_window() :
	Window (fltk::USEDEFAULT, fltk::USEDEFAULT, 700, 550, "Scene", true),
	m_zoom_slider (80, 525, 400, 19, "Zoom"),
	m_block_menu (20, 22, 80, 24,"Add block"),
	m_custom_block (110, 22, 100, 24, "Custom block")
{
	log() << aspect << "Application window constructor" << std::endl;

	application_pointer = this;

	// create material structure
	log() << aspect << "Creating default material" << std::endl;
	m_scene = new scene();
	m_scene_file = "";

	// create UI
	log() << aspect << "Creating UI" << std::endl;
	user_data((void*)(this));
	begin();

		// main menu bar
		fltk::MenuBar* left_menu_bar = new fltk::MenuBar (0, 0, 700, 20, "Left menu");
		left_menu_bar->begin();

			// file menu
			fltk::ItemGroup* menu_file = new fltk::ItemGroup ("&File");
			menu_file->begin();

				fltk::Item* menu_file_new = new fltk::Item("New");
				menu_file_new->shortcut(fltk::CTRL + 'n');
				menu_file_new->callback((fltk::Callback*)cb_menu_file_new, this);

				fltk::Item* menu_file_open = new fltk::Item("Open");
				menu_file_open->shortcut(fltk::CTRL + 'o');
				menu_file_open->callback((fltk::Callback*)cb_menu_file_open, this);

				new fltk::Divider();

				fltk::Item* menu_file_save = new fltk::Item("Save");
				menu_file_save->shortcut(fltk::CTRL + 's');
				menu_file_save->callback((fltk::Callback*)cb_menu_file_save, this);

				fltk::Item* menu_file_save_as = new fltk::Item("Save as...");
				menu_file_save_as->shortcut(fltk::SHIFT + fltk::CTRL + 's');
				menu_file_save_as->callback((fltk::Callback*)cb_menu_file_save_as, this);

				new fltk::Divider();

				fltk::Item* menu_file_shader_properties = new fltk::Item("Shader Properties");
				menu_file_shader_properties->shortcut(fltk::CTRL + 'p');
				menu_file_shader_properties->callback((fltk::Callback*)cb_menu_shader_properties, this);

				fltk::Item* menu_file_code_preview = new fltk::Item("Code Preview");
				menu_file_code_preview->shortcut(fltk::CTRL + 'w');
				menu_file_code_preview->callback((fltk::Callback*)cb_menu_code_preview, this);

				fltk::Item* menu_file_export_shader = new fltk::Item("Export Shader");
				menu_file_export_shader->shortcut(fltk::CTRL + 'e');
				menu_file_export_shader->callback((fltk::Callback*)cb_menu_file_export_shader, this);

				new fltk::Divider();

				fltk::Item* menu_file_options = new fltk::Item("Options");
				menu_file_options->shortcut(fltk::CTRL + 't');
				menu_file_options->callback((fltk::Callback*)on_menu_file_options, this);

				new fltk::Divider();

				fltk::Item* menu_file_quit = new fltk::Item("Quit");
				menu_file_quit->shortcut(fltk::CTRL + 'q');
				menu_file_quit->callback((fltk::Callback*)on_menu_file_quit);

			menu_file->end();

			// view menu
			fltk::ItemGroup* menu_view = new fltk::ItemGroup("&View");
			menu_view->begin();

				m_menu_show_grid = new fltk::ToggleItem("Show grid");
				m_menu_show_grid->shortcut(fltk::CTRL + 'g');
				m_menu_show_grid->callback((fltk::Callback*)cb_menu_view_toggle_grid, this);

				m_menu_snap_to_grid = new fltk::ToggleItem("Snap blocks");
				m_menu_snap_to_grid->shortcut(fltk::CTRL + 'a');
				m_menu_snap_to_grid->callback((fltk::Callback*)cb_menu_view_toggle_grid_snap, this);

				m_menu_overview = new fltk::ToggleItem("Overview");
				m_menu_overview->shortcut(fltk::CTRL + 'v');
				m_menu_overview->callback((fltk::Callback*)cb_menu_view_toggle_overview, this);

			menu_view->end();

		left_menu_bar->end();

		// help menu
		fltk::MenuBar* right_menu_bar = new fltk::MenuBar(650, 0, 39, 20);
		right_menu_bar->begin();

			fltk::ItemGroup* menu_help = new fltk::ItemGroup("&Help");
			menu_help->begin();

				fltk::Item* menu_help_about = new fltk::Item("About");
				menu_help_about->callback((fltk::Callback*)on_menu_help_about);

			menu_help->end();

		right_menu_bar->end();

		// block menu
		m_block_menu.callback ((fltk::Callback*)block_menu_callback);
		m_block_menu.begin();

			for (scene::block_classification_t::iterator d = m_scene->m_block_classification.begin(); d != m_scene->m_block_classification.end(); ++d) {

				// check whether the directory has a parent
				scene::block_tree_t::const_iterator tree_parent = m_scene->m_block_tree.find (d->first);
				if (tree_parent != m_scene->m_block_tree.end())
					// it has a parent, thus is not at the root : skip it
					continue;

				log() << aspect << "building shader menu" << std::endl;
				build_menu (d->first, d->second);
			}

		m_block_menu.end();

		// custom block button
		m_custom_block.callback ((fltk::Callback*)cb_custom_block, this);

		// renderer chooser
		general_options prefs;
		prefs.load();
		m_renderers = prefs.get_renderer_list();
		fltk::Choice* renderer_chooser = new fltk::Choice (300, 22, 100, 24, "Renderer");

		renderer_chooser->begin();
		for (general_options::renderers_t::iterator r_i = m_renderers.begin(); r_i != m_renderers.end(); ++r_i) {
			if (r_i->first == _3delight)
				new fltk::Item (r_i->second.name.c_str(), 0, cb_renderer, (void*)_3delight);
			else if (r_i->first == air)
				new fltk::Item (r_i->second.name.c_str(), 0, cb_renderer, (void*)air);
			else if (r_i->first == aqsis)
				new fltk::Item (r_i->second.name.c_str(), 0, cb_renderer, (void*)aqsis);
			else if (r_i->first == entropy)
				new fltk::Item (r_i->second.name.c_str(), 0, cb_renderer, (void*)entropy);
			else if (r_i->first == pixie)
				new fltk::Item (r_i->second.name.c_str(), 0, cb_renderer, (void*)pixie);
			else if (r_i->first == prman)
				new fltk::Item (r_i->second.name.c_str(), 0, cb_renderer, (void*)prman);
			else if (r_i->first == renderdotc)
				new fltk::Item (r_i->second.name.c_str(), 0, cb_renderer, (void*)renderdotc);
			else
				log() << error << "unknown renderer: " << r_i->second.name << std::endl;
		}
		renderer_chooser->end();

		// renderer display chooser
		m_renderer_display_chooser = new fltk::Choice (460, 22, 100, 24, "Display");

		// preview button
		fltk::Button* preview_button = new fltk::Button (580, 22, 100, 24, "Preview");
		preview_button->callback ((fltk::Callback*)cb_preview, this);

		// OpenGL view
		fltk::Group* main_view = new fltk::Group (2, 48, 692, 450);
		main_view->begin();

			fltk::InvisibleBox* frame = new fltk::InvisibleBox (0, 0, 692, 450);
			frame->box (fltk::DOWN_BOX);
			frame->color ((fltk::Color)(56));
			frame->selection_color ((fltk::Color)(69));

			m_scene_view = new scene_view (2, 2, 692, 450);

		main_view->end();
		resizable (main_view);

		// zoom slider
		m_zoom_slider.labelfont (fltk::HELVETICA_BOLD);
		m_zoom_slider.labelcolor ((fltk::Color)136);
		m_zoom_slider.minimum (0);
		m_zoom_slider.maximum (5);
		m_zoom_slider.step (0.02);
		m_zoom_slider.value (4);
		m_zoom_slider.callback ((fltk::Callback*)cb_zoom_slider, this);
		m_zoom_slider.align (fltk::ALIGN_LEFT);
		m_zoom_slider.type (fltk::Slider::TICK_ABOVE);

		// fit scene button
		fltk::Button* fit_button = new fltk::Button (490, 520, 100, 24, "Fit scene");
		fit_button->callback ((fltk::Callback*)cb_button_fit_scene, this);

	end();

	// setup view
	log() << aspect << "Setting default shader" << std::endl;
	m_scene_view->set_scene (m_scene);
}

application_window::~application_window() {

	log() << aspect << "Application window destructor" << std::endl;
	delete m_scene;
}

void application_window::build_menu (const std::string& name, scene::default_block_list_t& list) {

	log() << aspect << "building block menu..." << name << std::endl;
	fltk::ItemGroup* current_group = new fltk::ItemGroup (name.c_str());
	current_group->begin();

	// check whether the directory has children
	for (scene::block_tree_t::const_iterator tree_node = m_scene->m_block_tree.begin();
		tree_node != m_scene->m_block_tree.end(); ++tree_node)
	{
		if (tree_node->second == name) {

			// create child tree
			scene::block_classification_t::iterator d = m_scene->m_block_classification.find (tree_node->first);
			if (d == m_scene->m_block_classification.end())
				log() << error << "menu's child node not found!" << std::endl;
			else
				build_menu (d->first, d->second);
		}
	}

	for (scene::default_block_list_t::iterator b = list.begin(); b != list.end(); ++b) {

		new fltk::Item ((*b).name.c_str());
	}

	current_group->end();
}

void application_window::block_menu_action (fltk::Widget* w, void*) {

	fltk::PopupMenu* menu = (fltk::PopupMenu*)w;
	fltk::Widget* item = menu->get_item();
	if (!item)
		log() << error << "invalid menu item (block_menu_action)." << std::endl;
	else {
		// add block and put it in the view center
		shader_block* new_block = m_scene->add_predefined_block (item->label());
		m_scene_view->move_block_to_view_center (new_block);

		// refresh
		m_scene_view->redraw();
	}
}

int application_window::handle (int event) {

	// update the zoom slider if necessary
	double new_zoom = m_scene_view->get_zoom_change();
	if (new_zoom != 0) {

		double current_value = m_zoom_slider.value();
		m_zoom_slider.value (current_value + new_zoom);

		m_scene_view->reset_zoom_change();
	}

	// do overriden function's work
	return fltk::Window::handle(event);
}


void application_window::save_scene_as() {

	// get current directory
	char result[2048];
	fltk::filename_absolute (result, 2048, ".");

	// choose shader file
	const char* file = fltk::file_chooser ("Save Shader As", "*.xml", result);
	if(!file)
		return;

	// automatically add the .xml extension
	std::string real_file_name = file;
	const char* extension = fltk::filename_ext (file);
	if (std::string (extension) != ".xml")
		real_file_name += ".xml";

	// check whether file already exists
	if (std::ifstream (real_file_name.c_str())) {

		const std::string message = "Do you want to overwrite '" + std::string (fltk::filename_name (real_file_name.c_str())) + "'?";
		if (!fltk::ask (message.c_str())) {

			return;
		}
	}

	log() << aspect << "saving project as " << file << std::endl;
	m_scene->save_as (real_file_name);

	m_scene_file = real_file_name;
}


