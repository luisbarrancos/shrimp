
/*
    Copyright 2008-2012, Romain Behar <romainbehar@users.sourceforge.net>

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


#include "preferences.h"


general_options::general_options() :
    m_preferences_file ("preferences.xml")
{
}


void general_options::initialize(i_system_functions* systemFunctions, const std::string& dataPath)
{
    m_system_functions = systemFunctions;
    m_rib_renderer_file = systemFunctions->combine_paths (dataPath, "rib/renderers.xml");
    m_rib_scene_dir = systemFunctions->combine_paths (dataPath, "rib/scenes");
    ribShaderDir = systemFunctions->combine_paths (dataPath, "rib/shaders");

    load_renderer_list();
    load_scene_list();

    load();
}


std::string general_options::renderer_file() const
{
	return m_rib_renderer_file;
}


std::string general_options::rib_scene_dir() const
{
	return m_rib_scene_dir;
}


std::string general_options::getRibShaderDirectory() const
{
    return ribShaderDir;
}


bool general_options::load()
{
	log() << aspect << "general_options::load()" << std::endl;

	// set defaults in case some values are not yet present in the loaded file
	set_defaults();

	// load preferences files
	std::string file = preferences_file();

	TiXmlDocument xml_prefs(file.c_str());
	if (!xml_prefs.LoadFile())
	{
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

						m_shading_rate = from_string (trim (a->Value()), 256.0); // keep 256.0 (not 256) to convert to double

					} else if (name == "samples_x") {

						m_samples_x = from_string (trim (a->Value()), 1.0); // keep 1.0 (not 1) to convert to double

					} else if (name == "samples_y") {

						m_samples_y = from_string (trim (a->Value()), 1.0); // keep 1.0 (not 1) to convert to double

					}else if (name == "pixel_filter") {

						m_pixel_filter = trim (a->Value());
					}
					 else if (name == "filter_width_s") {

						 m_filter_width_s = from_string (trim (a->Value()), 8.0); // keep 1.0 (not 1) to convert to double
					}
					 else if (name == "filter_width_t") {

						 m_filter_width_t = from_string (trim (a->Value()), 8.0); // keep 1.0 (not 1) to convert to double
					}
					else if (name == "scene") {

						m_scene = trim (a->Value());
					}
				}
			} else if (element == "help_reader") {

				for (TiXmlAttribute* a = c->ToElement()->FirstAttribute(); a; a = a->Next()) {

					const std::string name (a->Name());

					m_help_reader = trim (a->Value());
					if (name == "help") {

				 	m_help_reader = trim (a->Value());

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
		log() << aspect << "   pixel filter     : " << m_pixel_filter << std::endl;
		log() << aspect << "   filter_width_s   : " << m_filter_width_s << std::endl;
		log() << aspect << "   filter_width_t   : " << m_filter_width_t << std::endl;
		log() << aspect << "   scene            : " << m_scene << std::endl;

		log() << aspect << "   help reader      : " << m_help_reader << std::endl;
		log() << aspect << "   splash screen    : " << m_splash_screen << std::endl;
	}

	return true;
}


bool general_options::save() {

	xml::element prefs ("shrimp_prefs");

	xml::element renderer ("renderer");
	renderer.push_attribute ("code", m_renderer_code);
	prefs.push_child (renderer);

	xml::element compilation ("compilation_command");
	compilation.push_attribute ("compiled_extension", m_compiled_shader_extension);
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
	output.push_attribute ("pixel_filter", m_pixel_filter);
	output.push_attribute ("filter_width_s",m_filter_width_s);
	output.push_attribute ("filter_width_t",m_filter_width_t);
	output.push_attribute ("scene", string_cast (m_scene));
	prefs.push_child (output);

	xml::element help ("help_reader");
	help.push_attribute ("help", m_help_reader);
	prefs.push_child (help);

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


void general_options::set_defaults()
{
    if (m_renderers.size() > 0)
    {
        renderers_t::const_iterator renderer = m_renderers.find("aqsis");
        if (renderer == m_renderers.end())
        {
            renderer = m_renderers.begin();
        }

        m_renderer_code = renderer->first;
        m_shader_compiler = renderer->second.shader_compiler;
        m_compiled_shader_extension = renderer->second.compiled_shader_extension;
        m_renderer = renderer->second.renderer_command;
        m_renderer_display = "";
        if (renderer->second.displays.size() > 0)
        {
            m_renderer_display = renderer->second.displays.front();
        }
    }
    else
    {
        m_shader_compiler = "aqsl -DRENDERER=%r -I%i %s -o %o";
	m_compiled_shader_extension = "slx";
	m_renderer_code = "aqsis";
        m_renderer = "aqsis %s -shaders=%i";
	m_renderer_display = "framebuffer";
    }

    m_output_width = 256;
    m_output_height = 256;
    m_shading_rate = 1;
    m_samples_x = 1;
    m_samples_y = 1;
    m_filter_width_s = 8;
    m_filter_width_t = 8;
    m_pixel_filter = "sinc";

    m_help_reader =( "firefox \"./doc/index.html\"&");
    m_splash_screen = true;
}


std::string general_options::get_RIB_scene()
{
	load();

	std::vector<std::string> scene_files = m_system_functions->list_directory (m_rib_scene_dir);

	std::string scene_path ("");
	for (unsigned int f = 0; f < scene_files.size(); ++f)
	{
		const std::string file = scene_files[f];
		const std::string file_path = m_system_functions->combine_paths (m_rib_scene_dir, file);
		if (!m_system_functions->is_directory (file_path))
		{
			const std::string extension = m_system_functions->get_file_extension (file);
                        if (extension == "rib")
			{
				const std::string name (file.begin(), file.end() - 4);
				if (name == m_scene)
				{
					// found the file defined in the preferences
					scene_path = file_path;
				}
			}
		}
	}

	// load and return the file
	if (scene_path.size())
	{
		std::ifstream scene_file (scene_path.c_str());
		if (!scene_file)
		{
			log() << error << "couldn't open RIB scene template '" << scene_path << "' file." << std::endl;
		}
		else
		{
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


void general_options::load_renderer_list()
{
	// load renderer list
	TiXmlDocument xml_renderers (renderer_file().c_str());
	if (!xml_renderers.LoadFile())
	{
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
			}
			else if (element == "texture") {
				// Get attributes
				for (TiXmlAttribute* a = n->ToElement()->FirstAttribute(); a; a = a->Next()) {

					const std::string name (a->Name());
					if (name == "command") {
						new_renderer.texture_command = a->Value();
					} else if (name == "default") {
						new_renderer.texture_default = a->Value();
					} else if (name == "extension") {
						new_renderer.texture_extension = a->Value();
					}
				}

				for (TiXmlNode* c = n->ToElement()->FirstChild("texture")->FirstChild("texture_switches")->FirstChild("filter")->FirstChild("filter_type")->FirstChild(); c; c = c->NextSibling()) {

					const std::string element (c->Value());

					const std::string list = c->Value();
					std::istringstream stream (list);

					std::string new_filter;
					stream >> new_filter;
					new_renderer.filter_type.push_back (new_filter);
					while (!stream.eof()) {
						stream >> new_filter;
						new_renderer.filter_type.push_back (new_filter);
						}
					}

				for (TiXmlNode* c = n->ToElement()->FirstChild("texture")->FirstChild("texture_switches")->FirstChild("filter")->FirstChild("filter_width"); c; c = c->NextSibling()) {
					const std::string element (c->Value());
					// Get attributes
					for (TiXmlAttribute* a = c->ToElement()->FirstAttribute(); a; a = a->Next()) {
						const std::string name (a->Name());
						if (name == "default") {
							new_renderer.filter_size = a->Value();
						}
					}
				}
			}
			else if (element == "help_reader") {
				// Get attributes
				for (TiXmlAttribute* a = n->ToElement()->FirstAttribute(); a; a = a->Next()) {
					const std::string name (a->Name());
					if (name == "help") {
						m_help_reader = a->Value();
					}
				}
			}

				// TODO
			 else {
				log() << error << "unknown renderer attribute: " << element << std::endl;
			}
		}

		m_renderers.insert (std::make_pair (renderer, new_renderer));
	}
}


general_options::renderers_t general_options::get_renderer_list()
{
	return m_renderers;
}


void general_options::load_scene_list()
{
	m_scene.clear();

	// load scene list
	std::vector<std::string> scene_files = m_system_functions->list_directory (m_rib_scene_dir);

        log() << aspect << "Loading " << scene_files.size() << " scene files from " << m_rib_scene_dir << std::endl;
        for (unsigned int f = 0; f < scene_files.size(); ++f)
        {
                const std::string file = scene_files[f];
                const std::string file_path = m_system_functions->combine_paths (rib_scene_dir(), file);
                if (!m_system_functions->is_directory (file_path))
                {
                        const std::string extension = m_system_functions->get_file_extension (file);
                        if (extension == "rib")
                        {
                                // save XML file
                                const std::string name (file.begin(), file.end() - 4);

                                // add scene to the list
                                scene_t new_scene;

                                new_scene.name = name;
                                new_scene.file = file_path;

                                m_scenes.push_back (new_scene);
                        }
                }
        }
}


general_options::scenes_t general_options::get_scene_list()
{
	return m_scenes;
}


void general_options::set_renderer (const std::string& RendererCode)
{
	std::string shader_compiler ("");
	std::string compiled_shader_extension ("");
	std::string renderer ("");

	renderers_t::const_iterator r = m_renderers.find (RendererCode);
	if (r == m_renderers.end())
	{
		log() << error << "unknown renderer code: " << RendererCode << std::endl;
		return;
	}

	m_renderer_code = RendererCode;
	m_shader_compiler = r->second.shader_compiler;
	m_compiled_shader_extension = r->second.compiled_shader_extension;
	m_renderer = r->second.renderer_command;
}


void general_options::set_renderer_name(const std::string& rendererName)
{
    for (renderers_t::const_iterator r = m_renderers.begin(); r != m_renderers.end(); ++r)
    {
        if (r->second.name == rendererName)
        {
            m_renderer_code = r->first;
            m_shader_compiler = r->second.shader_compiler;
            m_compiled_shader_extension = r->second.compiled_shader_extension;
            m_renderer = r->second.renderer_command;
        }
    }
}


void general_options::set_display (const std::string& RendererDisplay)
{
	m_renderer_display = RendererDisplay;
}


void general_options::set_display_name (const std::string& displayName)
{
    renderers_t::const_iterator renderer = m_renderers.find (m_renderer_code);
    if (renderer == m_renderers.end())
    {
            log() << error << "No renderer set for display: " << displayName << std::endl;
            return;
    }

    for (general_options::displays_t::const_iterator currentDisplay = renderer->second.displays.begin(); currentDisplay != renderer->second.displays.end(); ++currentDisplay)
    {
        m_renderer_display = *currentDisplay;
    }
}


void general_options::set_scene (const std::string& Scene)
{
	m_scene = Scene;
}

void general_options::set_pixelfilter(const std::string& Pixel_filter)
{
	m_pixel_filter = Pixel_filter;
}

void general_options::set_help (const std::string& Help_Reader)
{
	m_help_reader = Help_Reader;
}

const std::string general_options::preferences_file()
{
	log() << aspect << "general_options::preferences_file()" << std::endl;

	std::string file = m_system_functions->get_user_directory();
	file += '/' + m_preferences_file;

	return file;
}


