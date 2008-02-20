
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


#ifndef _ui_scene_view_h_
#define _ui_scene_view_h_

#include "../shading/scene.h"

#include <fltk/run.h>

#include <fltk/GlWindow.h>
#include <fltk/gl.h>
#include <FL/Fl_Menu_Item.H>
#include <fltk/PopupMenu.h>

#include <stdlib.h>

class scene_view :
	public fltk::GlWindow
{
public:
	scene_view (int x, int y, int w, int h, const char* l = 0);

	// set the OpenGL view projection
	void update_projection();

	// OpenGL widget draw() override
	void draw();

	// OpenGL widget handle(int Event) override
	int handle (int Event);

	// set and return the scene to draw
	void set_scene (scene* Scene);
	scene* get_scene();

	// sets scene scale
	void set_size (double Size);

	// set scene centre
	void center_scene (const double X, const double Y);

	// fits whole scene into window
	double fit_scene();

	// move active block by given offset
	void move_active_block (const double XOffset, const double YOffset);

	// move all blocks by given offset
	void move_all_blocks (const double XOffset, const double YOffset);

	// move block to the view center
	void move_block_to_view_center (shader_block* Block);

	// move scene by given offset
	void move_scene (const double XOffset, const double YOffset);

	// move active group
	void move_active_group (const double XOffset, const double YOffset);

	double get_zoom_change() { return m_zoom_change; }
	void reset_zoom_change() { m_zoom_change = 0; }

	// options
	void set_grid_state (const bool GridState);
	void set_snap_to_grid_state (const bool SnapState);
	void set_overview_state (const bool OverviewState);

	// snap function (snaps given coordinates)
	void snap_position (double& X, double& Y);

private:
	// store the scene being drawn
	scene* m_scene;

	// store active block
	std::string m_active_block;
	scene::io_t m_active_property;

	// store active group
	int m_active_group;

	// store current connection start
	scene::io_t m_connection_start;

	// draw grid
	void draw_grid();

	// draws active shader
	void draw_shader();
	const double m_min_block_height;

	std::string select_object();

	typedef std::map<unsigned long, std::pair<const shader_block*, std::string> > property_indices_t;
	property_indices_t m_property_indices;
	unsigned long m_property_index;
	scene::io_t select_property();

	// OpenGL scene transformation
	void transform_scene();

	// draws a block
	struct position {
		position(const double X, const double Y) :
			position_x(X), position_y(Y)
		{
		}

		double position_x;
		double position_y;
	};
	typedef std::map<scene::io_t, position> positions_t;

	void draw_block (const shader_block* Block, const double X, const double Y, positions_t& PropertyPositions);
	void draw_block_body (const shader_block* Block, const double X, const double Y);
	void draw_block_name (const shader_block* Block, const double X, const double Y);
	void draw_block_properties (const shader_block* Block, const double X, const double Y, positions_t& PropertyPositions, const bool Selection = false);
	// draws a block property
	void draw_property (const std::string& Name, const std::string& Type, const double X, const double Y, const double Size, const bool Multi = false);

	// draws block groups
	void draw_groups();
	void draw_group_body (int Group);
	void draw_group_body (const double X, const double Y);

	int select_group();

	// handle block groups
	typedef std::map<int, position> group_position_t;
	group_position_t m_group_positions;

	// stores scene size
	double m_size;

	// store mouse position when drag began
	int m_start_drag_mouse_x;
	int m_start_drag_mouse_y;
	// store previous mouse position
	int m_last_mouse_x;
	int m_last_mouse_y;
	// stores mouse click (false if there's a drag)
	unsigned long m_mouse_click;
	int m_mouse_click_x;
	int m_mouse_click_y;
	int m_current_mouse_x;
	int m_current_mouse_y;

	// store OpenGL camera projection values
	double m_projection_left;
	double m_projection_right;
	double m_projection_bottom;
	double m_projection_top;
	double m_projection_near;
	double m_projection_far;

	// save view width and height
	int m_view_width;
	int m_view_height;

	// store zoom change value (for the application window to pick and reset)
	double m_zoom_change;

	// options
	bool m_grid;
	bool m_snap_to_grid;
	bool m_overview;

	// callbacks
	void on_select_block (fltk::Widget* W, void* Data);
	static void cb_select_block (fltk::Widget* W, void* Data) { ((scene_view*)Data)->on_select_block (W, Data); }
	void on_deselect_block (fltk::Widget* W, void* Data);
	static void cb_deselect_block (fltk::Widget* W, void* Data) { ((scene_view*)Data)->on_deselect_block (W, Data); }
	void on_group_selection (fltk::Widget* W, void* Data);
	static void cb_group_selection(fltk::Widget* W, void* Data) { ((scene_view*)Data)->on_group_selection (W, Data); }
	void on_clear_selection (fltk::Widget* W, void* Data);
	static void cb_clear_selection(fltk::Widget* W, void* Data) { ((scene_view*)Data)->on_clear_selection (W, Data); }
	void on_rename_group (fltk::Widget* W, void* Data);
	static void cb_rename_group(fltk::Widget* W, void* Data) { ((scene_view*)Data)->on_rename_group (W, Data); }
	void on_ungroup (fltk::Widget* W, void* Data);
	static void cb_ungroup(fltk::Widget* W, void* Data) { ((scene_view*)Data)->on_ungroup (W, Data); }
	void on_block_info (fltk::Widget* W, void* Data);
	static void cb_block_info(fltk::Widget* W, void* Data) { ((scene_view*)Data)->on_block_info (W, Data); }
	void on_rename_block (fltk::Widget* W, void* Data);
	static void cb_rename_block(fltk::Widget* W, void* Data) { ((scene_view*)Data)->on_rename_block (W, Data); }
	void on_delete_block (fltk::Widget* W, void* Data);
	static void cb_delete_block(fltk::Widget* W, void* Data) { ((scene_view*)Data)->on_delete_block (W, Data); }

	void on_add_input (fltk::Widget* W, void* Data);
	static void cb_add_input (fltk::Widget* W, void* Data) { ((scene_view*)Data)->on_add_input (W, Data); }
	void on_add_output (fltk::Widget* W, void* Data);
	static void cb_add_output (fltk::Widget* W, void* Data) { ((scene_view*)Data)->on_add_output (W, Data); }
	void on_edit_code (fltk::Widget* W, void* Data);
	static void cb_edit_code (fltk::Widget* W, void* Data) { ((scene_view*)Data)->on_edit_code (W, Data); }
	void on_edit_pad (fltk::Widget* W, void* Data);
	static void cb_edit_pad (fltk::Widget* W, void* Data) { ((scene_view*)Data)->on_edit_pad (W, Data); }
	void on_edit_RIB (fltk::Widget* W, void* Data);
	static void cb_edit_RIB (fltk::Widget* W, void* Data) { ((scene_view*)Data)->on_edit_RIB (W, Data); }
	void on_disconnect_pad (fltk::Widget* W, void* Data);
	static void cb_disconnect_pad (fltk::Widget* W, void* Data) { ((scene_view*)Data)->on_disconnect_pad (W, Data); }
};

#endif // _ui_scene_view_h_

