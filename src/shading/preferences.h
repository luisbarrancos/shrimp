
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


#ifndef _preferences_h_
#define _preferences_h_

#include "../miscellaneous/logging.h"
#include "../miscellaneous/misc_string_functions.h"
#include "../miscellaneous/misc_system_functions.h"
#include "../miscellaneous/misc_xml.h"

#include <fstream>
#include <string>

// all renderers must be referenced here, they're used by FLTK's callbacks
// and serve as renderer identifiers through the -DRENDERER=... option
static const char _3delight[] = "_3delight";
static const char air[] = "air";
static const char aqsis[] = "aqsis";
static const char entropy[] = "entropy";
static const char pixie[] = "pixie";
static const char prman[] = "prman";
static const char renderdotc[] = "renderdotc";

class general_options
{
	const std::string m_preferences_file;
	const std::string m_rib_renderer_file;
	const std::string m_rib_scene_dir;

public:
	// renderer list
	typedef std::vector<std::string> displays_t;
	typedef struct renderer_t {

		std::string name;
		std::string shader_compiler;
		std::string compiled_shader_extension;
		std::string renderer_symbol;
		std::string renderer_command;
		displays_t displays;
	};
	typedef std::map<std::string, renderer_t> renderers_t;
	renderers_t m_renderers;

public:
	general_options() :
		m_preferences_file ("preferences.xml"),
		m_rib_renderer_file ("./data/rib/renderers.xml"),
		m_rib_scene_dir ("./data/rib/scenes")
	{
		load_renderer_list();
	}

	const std::string renderer_file() const {

		return m_rib_renderer_file;
	}

	const std::string rib_scene_dir() const {

		return m_rib_scene_dir;
	}

	bool load() {

		// set defaults in case some values are not yet present in the loaded file
		set_defaults();

		// load preferences files
		std::string file = preferences_file();

		TiXmlDocument xml_prefs(file.c_str());
		if (!xml_prefs.LoadFile()) {

			log() << aspect << "Preferences file not found (" << file << "), creating the default one." << std::endl;
			save();

			return false;

		} else {

			for (TiXmlNode* c = xml_prefs.FirstChild()->FirstChild(); c; c = c->NextSibling()) {

				const std::string element(c->Value());
				if (element == "renderer") {

					for (TiXmlAttribute* a = c->ToElement()->FirstAttribute(); a; a = a->Next()) {

						const std::string name (a->Name());
						if (name == "code") {

							m_renderer_code = trim (a->Value());
						}
					}
				}
				else if (element == "compilation_command") {

					for (TiXmlAttribute* a = c->ToElement()->FirstAttribute(); a; a = a->Next()) {

						const std::string name (a->Name());
						if (name == "compiled_extension") {
							m_compiled_shader_extension = trim (a->Value());
						} else if (name == "renderer_symbol") {
							m_renderer_symbol = trim (a->Value());
						}
					}

					m_shader_compiler = trim (c->FirstChild()->ToText()->Value());
				}
				else if (element == "rendering_command") {

					for (TiXmlAttribute* a = c->ToElement()->FirstAttribute(); a; a = a->Next()) {

						const std::string name (a->Name());
						if (name == "display") {
							m_renderer_display = trim (a->Value());
						}
					}

					m_renderer = trim (c->FirstChild()->ToText()->Value());
				}
				else if (element == "output") {

					for (TiXmlAttribute* a = c->ToElement()->FirstAttribute(); a; a = a->Next()) {

						const std::string name (a->Name());
						if (name == "width") {

							m_output_width = from_string (trim (a->Value()), 256);

						} else if (name == "height") {

							m_output_height = from_string (trim (a->Value()), 256);

						} else if (name == "shading_rate") {

							m_shading_rate = from_string (trim (a->Value()), 256);

						} else if (name == "samples_x") {

							m_samples_x = from_string (trim (a->Value()), 1);

						} else if (name == "samples_y") {

							m_samples_y = from_string (trim (a->Value()), 1);
						} else if (name == "scene") {

							m_scene = trim (a->Value());
						}
					}
				} else if (element == "splash") {

					for (TiXmlAttribute* a = c->ToElement()->FirstAttribute(); a; a = a->Next()) {

						const std::string name (a->Name());
						if (name == "show") {

							m_splash_screen = from_string (trim (a->Value()), true);
						}
					}
				}
			}

			log() << aspect << "Loaded preferences :" << std::endl;
			log() << aspect << "   shader compiler  : " << m_shader_compiler << std::endl;
			log() << aspect << "   shader extension : " << m_compiled_shader_extension << std::endl;
			log() << aspect << "   renderer         : " << m_renderer << std::endl;
			log() << aspect << "   output width     : " << m_output_width << std::endl;
			log() << aspect << "   output height    : " << m_output_height << std::endl;
			log() << aspect << "   shading rate     : " << m_shading_rate << std::endl;
			log() << aspect << "   pixel samples X  : " << m_samples_x << std::endl;
			log() << aspect << "   pixel samples Y  : " << m_samples_y << std::endl;
			log() << aspect << "   scene            : " << m_scene << std::endl;

			log() << aspect << "   splash screen    : " << m_splash_screen << std::endl;
		}

		return true;
	}

	bool save() {

		xml::element prefs ("shrimp_prefs");

		xml::element renderer ("renderer");
		renderer.push_attribute ("code", m_renderer_code);
		prefs.push_child (renderer);

		xml::element compilation ("compilation_command");
		compilation.push_attribute ("compiled_extension", m_compiled_shader_extension);
		compilation.push_attribute ("renderer_symbol", m_renderer_symbol);
		compilation.set_text (m_shader_compiler);
		prefs.push_child (compilation);

		xml::element rendering ("rendering_command");
		rendering.push_attribute ("display", m_renderer_display);
		rendering.set_text (m_renderer);
		prefs.push_child (rendering);

		xml::element output ("output");
		output.push_attribute ("width", string_cast (m_output_width));
		output.push_attribute ("height", string_cast (m_output_height));
		output.push_attribute ("shading_rate", string_cast (m_shading_rate));
		output.push_attribute ("samples_x", string_cast (m_samples_x));
		output.push_attribute ("samples_y", string_cast (m_samples_y));
		output.push_attribute ("scene", string_cast (m_scene));
		prefs.push_child (output);

		xml::element splash ("splash");
		splash.push_attribute ("show", string_cast (m_splash_screen));
		prefs.push_child (splash);

		std::string file = preferences_file();
		std::ofstream out_file;
		out_file.open (file.c_str(), std::ios::out | std::ios::trunc);
		xml::output_tree (prefs, out_file);
		out_file.close();

		return true;
	}

	void set_defaults() {

		m_shader_compiler = "aqsl -I%i %s -o %o";
		m_compiled_shader_extension = "slx";
		m_renderer_symbol = "-DRENDERER=aqsis";
		m_renderer = "aqsis %s -shaders=%i";
		m_renderer_display = "framebuffer";

		m_output_width = 256;
		m_output_height = 256;
		m_shading_rate = 1;
		m_samples_x = 1;
		m_samples_y = 1;

		m_splash_screen = true;
	}

	std::string get_RIB_scene() {

		load();

		dirent** scene_files;
		const int scene_count = fltk::filename_list (m_rib_scene_dir.c_str(), &scene_files);

		std::string scene_path ("");
		for (int f = 0; f < scene_count; ++f) {

			const std::string file = std::string (scene_files[f]->d_name);
			const std::string file_path = m_rib_scene_dir + "/" + file;
			if (!fltk::filename_isdir (file_path.c_str())) {

				const char* extension = fltk::filename_ext (file.c_str());
				if (std::string (extension) == ".rib") {

					const std::string name (file.begin(), file.end() - 4);
					if (name == m_scene) {

						// found the file defined in the preferences
						scene_path = file_path;
					}
				}
			}

			free (scene_files[f]);
		}

		free (scene_files);

		// load and return the file
		if (scene_path.size()) {

			std::ifstream scene_file (scene_path.c_str());
			if (!scene_file) {

				log() << error << "couldn't open RIB scene template '" << scene_path << "' file." << std::endl;
			} else {

				std::stringstream buffer;
				buffer << scene_file.rdbuf();

				scene_file.close();

				return buffer.str();
			}
		}

		// else return default scene (none found)
		log() << aspect << "returning default RIB scene." << std::endl;

		std::string default_scene ("");
		default_scene += "FrameBegin 1\n";
		default_scene += "$(imager_shader)\n";
		default_scene += "Projection \"perspective\" \"fov\" 40\n";
		default_scene += "WorldBegin\n";
		default_scene += "$(shaders)\n";
		default_scene += "Color [ 1 1 1 ]\n";
		default_scene += "Translate 0 0 3\n";
		default_scene += "Rotate -90 1 0 0\n";
		default_scene += "Sphere 0.8 -0.8 0.8 360\n";
		default_scene += "WorldEnd\n";
		default_scene += "FrameEnd\n";

		return default_scene;
	}

	void load_renderer_list() {

		// load renderer list
		TiXmlDocument xml_renderers (renderer_file().c_str());
		if (!xml_renderers.LoadFile()) {

			log() << error << "couldn't load renderer file '" << renderer_file() << "' (not found or malformed)." << std::endl;
			return;
		}

		for (TiXmlNode* n = xml_renderers.FirstChild()->FirstChild(); n; n = n->NextSibling()) {

			renderer_t new_renderer;

			const std::string renderer (n->Value());

			for (TiXmlAttribute* a = n->ToElement()->FirstAttribute(); a; a = a->Next()) {

				const std::string name (a->Name());
				if (name == "name") {
					new_renderer.name = a->Value();
				}
			}

			for (TiXmlNode* c = n->FirstChild(); c; c = c->NextSibling()) {

				const std::string element (c->Value());

				if (element == "shader_compiler") {
					new_renderer.shader_compiler = c->FirstChild()->ToText()->Value();
				} else if (element == "renderer_symbol") {

					// update the option with the renderer's code name
					std::string option = c->FirstChild()->ToText()->Value();
					replace_variable (option, "%s", renderer);
					new_renderer.renderer_symbol = option;

				} else if (element == "compiled_shader_extension") {
					new_renderer.compiled_shader_extension = c->FirstChild()->ToText()->Value();
				} else if (element == "renderer_command") {
					new_renderer.renderer_command = c->FirstChild()->ToText()->Value();
				} else if (element == "displays") {
					const std::string list = c->FirstChild()->ToText()->Value();
					std::istringstream stream (list);

					std::string new_display;
					stream >> new_display;
					new_renderer.displays.push_back (new_display);
					while (!stream.eof()) {
						stream >> new_display;
						new_renderer.displays.push_back (new_display);
					}
				} else {
					log() << error << "unknown renderer attribute: " << element << std::endl;
				}
			}

			m_renderers.insert (std::make_pair (renderer, new_renderer));
		}
	}

	renderers_t get_renderer_list() {

		return m_renderers;
	}

private:
	const std::string preferences_file() {

		std::string file = system_functions::get_shrimp_user_directory();
		file += '/' + m_preferences_file;

		return file;
	}

public:
	bool m_splash_screen;

	std::string m_renderer_code;
	std::string m_shader_compiler;
	std::string m_compiled_shader_extension;
	std::string m_renderer_symbol;
	std::string m_renderer;
	std::string m_renderer_display;

	double m_output_width;
	double m_output_height;
	double m_shading_rate;
	double m_samples_x;
	double m_samples_y;

	std::string m_scene;
};

#endif // _preferences_h_

