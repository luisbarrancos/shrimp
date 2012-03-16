
/*
    Copyright 2009-2012, Romain Behar <romainbehar@users.sourceforge.net>

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


#include "../miscellaneous/logging.h"
#include "../miscellaneous/misc_string_functions.h"

#include "opengl_view.h"


#if defined(__APPLE__) && defined (__MACH__)
    #include <OpenGL/glu.h>
#else
    #include <GL/glu.h>
#endif

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>


bool point_between (double a, double b, double c)
{
	double lb = a <= b;
	double ub = b <= c;
	double ans = lb && ub;
	return ans;
}

bool point_inside(double x,double y,double XX, double YY, double WW,double HH)
{
	bool in_lr = point_between (XX, x, WW);
	bool in_tb = point_between (YY, y, HH);
	bool inside = in_lr && in_tb;
	return inside;
}



opengl_view::opengl_view (services* services_instance) :
	m_services (services_instance),
	m_under_mouse_block (0),
	m_size (3),
	m_last_mouse_x (0),
	m_last_mouse_y (0),
	m_mouse_click (0),
	m_box_selection (false),
	m_projection_left (-10),
	m_projection_right (10),
	m_projection_bottom (-10),
	m_projection_top (10),
	m_projection_near (-1000),
	m_projection_far (1000),
	m_min_block_height (0.5),

	m_grid (false),
	m_snap_to_grid (false),
	m_overview (false),
	m_font_size (10)
{

}


void opengl_view::set_size (const double newSize)
{
        m_size = newSize;

	// set min and max
	if (m_size < 0.1) {
		m_size = 0.1;
	}
	if (m_size > 5) {
		m_size = 5;
	}

        updateSceneZoom(m_size);
}


double opengl_view::fit_scene(int window_width, int window_height)
{
	// make sure the projection is correct since below computations are based on it
	update_projection(window_width, window_height);

	// compute shaders' bounding-box
	double left = 0;
	double right = 0;
	double bottom = 0;
	double top = 0;
	shrimp::shader_blocks_t block_list = m_services->get_scene_blocks();
	for (shrimp::shader_blocks_t::const_iterator block_i = block_list.begin(); block_i != block_list.end(); ++block_i)
	{
		shader_block* block = *block_i;

		// the first block serves as reference
		if (block_list.begin() == block_i) {

			left = block->m_position_x;
			right = block->m_position_x + block->m_width;
			bottom = block->m_position_y;
			top = block->m_position_y - block->m_height;
		} else {
			left = std::min (left, block->m_position_x);
			right = std::max (right, block->m_position_x + block->m_width);
			bottom = std::min (bottom, block->m_position_y);
			top = std::max (top, block->m_position_y - block->m_height);
		}
	}

	// get ratios
	const double scene_ratio = (right - left) / (top - bottom);
	const double view_ratio = static_cast<double> (m_view_width) / static_cast<double> (m_view_height);

	if (std::fabs (scene_ratio) > std::fabs (view_ratio)) {
		// fit the width
		const double width = m_projection_right - m_projection_left;
                set_size (width / (1.2 * std::fabs (right - left)));
	} else {
		// fit the height
		const double height = m_projection_top - m_projection_bottom;
                set_size (height / (1.2 * std::fabs (bottom - top)));
	}

	// resize the bounding box position to the scene size
	const double center_x = (left + right) / 2 * m_size;
	const double center_y = (top + bottom) / 2 * m_size;
	// move to the scene centre
	center_scene (center_x, center_y);

	return m_size;
}


void opengl_view::center_scene (const double X, const double Y)
{
	const double width = m_projection_right - m_projection_left;
	const double height = m_projection_top - m_projection_bottom;

	m_projection_left = X - width / 2;
	m_projection_right = X + width / 2;
	m_projection_bottom = Y - height / 2;
	m_projection_top = Y + height / 2;
}


void opengl_view::move_active_block (const double XOffset, const double YOffset)
{
	// move selected and active blocks
	shrimp::shader_blocks_t selection = m_services->get_selected_blocks();
	if (m_under_mouse_block)
	{
		selection.insert (m_under_mouse_block);
	}

	for (shrimp::shader_blocks_t::const_iterator block_i = selection.begin(); block_i != selection.end(); ++block_i)
	{
		(*block_i)->m_position_x += XOffset;
		(*block_i)->m_position_y += YOffset;
	}

	// move groups as well
	move_active_group (XOffset,YOffset);
}


void opengl_view::move_all_blocks (const double XOffset, const double YOffset)
{
/*
	shrimp::shader_blocks_t block_list = m_services->get_scene_blocks();
	for (shrimp::shader_blocks_t::iterator block = block_list.begin(); block != block_list.end(); ++block)
	{
		block->m_position_x += XOffset;
		block->m_position_y += YOffset;
	}
*/
}


void opengl_view::move_block_to_view_center (shader_block* Block)
{
	if (!Block) {

		log() << error << "no block supplied! (move_block_to_view_center)" << std::endl;
		return;
	}

	const double center_x = (m_projection_right + m_projection_left) / 2 / m_size;
	const double center_y = (m_projection_bottom + m_projection_top) / 2 / m_size;

	Block->m_position_x = center_x;
	Block->m_position_y = center_y;
}


void opengl_view::move_scene (const double XOffset, const double YOffset)
{
	m_projection_left -= XOffset;
	m_projection_right -= XOffset;
	m_projection_bottom -= YOffset;
	m_projection_top -= YOffset;
}


void opengl_view::move_active_group (const double XOffset, const double YOffset)
{
	// move selected and active groups
	shrimp::group_set_t groups = m_services->get_selected_groups();
	if (m_under_mouse_group)
	{
		groups.insert (m_under_mouse_group);
	}

	for (shrimp::group_set_t::iterator group_i = groups.begin(); group_i != groups.end(); ++group_i)
	{
		// move all the group's blocks
		shrimp::shader_blocks_t group_blocks = m_services->get_group_blocks (*group_i);
		for (shrimp::shader_blocks_t::iterator block_i = group_blocks.begin(); block_i != group_blocks.end(); ++block_i)
		{
			(*block_i)->m_position_x += XOffset;
			(*block_i)->m_position_y += YOffset;
		}
	}
}


void opengl_view::box_selection(int window_width, int window_height)
{
	//2D opengl drawing
	glShadeModel (GL_FLAT);
	glDisable (GL_LINE_SMOOTH);
	glDisable (GL_BLEND);
	glLineWidth (1.0);

	glColor3f (0.8, 0.0, 0.0);
	glLineStipple(3, 0xAAAA);
	glEnable(GL_LINE_STIPPLE);
	glPushMatrix();
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D (0, static_cast<float> (window_width), 0, static_cast<float> (window_height));


	//Mouse marquee position
	double from_x = static_cast<float> (m_start_drag_x);
	double from_y = static_cast<float> (window_height) - static_cast<float> (m_start_drag_y);
	double to_x = static_cast<float> (m_current_mouse_x);
	double to_y = static_cast<float> (window_height) - static_cast<float> (m_current_mouse_y);


	//Rectangle selection stipple
	glBegin(GL_LINE_LOOP);
		glVertex3d(from_x, from_y,0);
		glVertex3d(from_x,to_y,0);
		glVertex3d(to_x,to_y,0);
		glVertex3d(to_x,from_y,0);
	glEnd();

	glPopMatrix();
	glDisable(GL_LINE_STIPPLE);


	//Detection of block selected
	std::map<unsigned long, const shader_block*> block_indices;
	unsigned long index = 1;

	shrimp::shader_blocks_t block_list = m_services->get_scene_blocks();
	for (shrimp::shader_blocks_t::const_iterator block_i = block_list.begin(); block_i != block_list.end(); ++block_i)
	{
		shader_block* block = *block_i;

		//Project rectangle selection in "Block" space
		GLdouble Fx,Fy,Fz;
		GLdouble Tx,Ty,Tz;

		GLint viewport[4];
		GLdouble mvmatrix[16], projmatrix[16];
		glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix );
		glGetDoublev(GL_PROJECTION_MATRIX,projmatrix );
		glGetIntegerv(GL_VIEWPORT,viewport );

	    //Mouse selection direction
	    //Fx<Tx : Ty<Fy
	    //Fx>Tx : Ty<Fy
	    //Fx>Tx : Ty>Fy
	    //Fx<Tx : Ty>Fy

		gluUnProject(from_x,from_y,0, mvmatrix, projmatrix,viewport,&Fx,&Fy,&Fz );
		gluUnProject(to_x,to_y,0, mvmatrix, projmatrix,viewport,&Tx,&Ty,&Tz );

		const int group = m_services->get_block_group (block);
		if (!group)
		{
			//Height of the block
			const double width = block->m_width;

			const unsigned long max_properties = std::max (block->input_count(), (unsigned long)block->m_outputs.size()); // cast required by some unusual compilers (e.g. gcc version 4.1.3 20070929 (prerelease))

			// set minimal block height
			const double height1 = m_services->is_rolled (block) ? width : (width * (1.0 / 3.7) * static_cast<double> (max_properties));
			const double height = (height1 < m_min_block_height) ? m_min_block_height : height1;

			//Above block
			bool block_inside = false;
			if (Fx<Tx && Ty<Fy)
			{
				//Check if rectangle surround center of the block
				if (point_inside (block->m_position_x+width/2, block->m_position_y-height/2 ,Fx,Ty,Tx,Fy))
				{
					block_inside = true;
				}
			}
			else if (Fx>Tx && Ty<Fy)
			{
				//Check if rectangle surround center of the block
				if (point_inside (block->m_position_x+width/2, block->m_position_y-height/2 ,Tx,Ty,Fx,Fy))
				{
					block_inside = true;
				}
			}
			else if (Fx>Tx && Ty>Fy)
			{
				//Check if rectangle surround center of the block
				if (point_inside (block->m_position_x+width/2, block->m_position_y-height/2 ,Tx,Fy,Fx,Ty))
				{
					block_inside = true;
				}
			}
			else if (Fx<Tx && Ty>Fy)
			{
				//Check if rectangle surround center of the block
				if (point_inside (block->m_position_x+width/2, block->m_position_y-height/2 ,Fx,Fy,Tx,Ty))
				{
					block_inside = true;
				}
			}

			//Update block selection
			m_services->set_block_selection (block, block_inside);

			glLoadName (index);

			block_indices.insert (std::make_pair (index, block));

			++index;
		}

		if (group)
		{
			group_position_t::const_iterator p = m_group_positions.find(group);

			//Get group position
			const double x = p->second.position_x;
			const double y = p->second.position_y;

			//Above group
			bool group_inside = false;

			//Check if rectangle surround center of the group
			if (Fx<Tx && Ty<Fy)
			{
				//Check if rectangle surround center of the group
				if (point_inside (x ,y ,Fx,Ty,Tx,Fy))
				{
					group_inside = true;
				}
			}
			else if (Fx>Tx && Ty<Fy)
			{
				//Check if rectangle surround center of the group
				if (point_inside (x,y ,Tx,Ty,Fx,Fy))
				{
					group_inside = true;
				}
			}
			else if (Fx>Tx && Ty>Fy)
			{
				//Check if rectangle surround center of the group
				if (point_inside (x ,y ,Tx,Fy,Fx,Ty))
				{
					group_inside = true;
				}
			}
			else if (Fx<Tx && Ty>Fy)
			{
				//Check if rectangle surround center of the group
				if (point_inside (x ,y ,Fx,Fy,Tx,Ty))
				{
					group_inside = true;
				}
			}

			//Update group selection
			m_services->set_group_selection (group, group_inside);

			glLoadName (index);

			block_indices.insert (std::make_pair (index, block));

			++index;
		}
	}
}


void opengl_view::update_projection(int window_width, int window_height)
{
	m_view_width = window_width;
	m_view_height = window_height;

	const double ratio = static_cast<double> (m_view_width) / static_cast<double> (m_view_height);
	const double centre_x = (m_projection_left + m_projection_right) / 2;
	const double centre_y = (m_projection_bottom + m_projection_top) / 2;

	if (ratio > 1) {
		// size : 100 pixels per scene unit
		const double size = static_cast<double> (m_view_height) / 100;
		m_projection_left = -ratio * size;
		m_projection_right = ratio * size;
		m_projection_bottom = -size;
		m_projection_top = size;
	} else {
		// size : 100 pixels per scene unit
		const double size = static_cast<double> (m_view_width) / 100;
		m_projection_left = -size;
		m_projection_right = size;
		m_projection_bottom = -1/ratio * size;
		m_projection_top = 1/ratio * size;
	}

	m_projection_left += centre_x;
	m_projection_right += centre_x;
	m_projection_bottom += centre_y;
	m_projection_top += centre_y;
}


shader_block* opengl_view::get_under_mouse_block(const int mouse_x, const int mouse_y)
{
        //log() << aspect << "opengl_view: get_under_mouse_block" << std::endl;

	// get current viewport
	GLint viewport[4];
	glGetIntegerv (GL_VIEWPORT, viewport);

	// setup OpenGL selection
	const GLsizei buffer_size = 1024;
	GLuint selection_buffer[buffer_size];
	glSelectBuffer (buffer_size, selection_buffer);
	glRenderMode (GL_SELECT);

	glInitNames();
	// push default name, it will be replaced using glLoadName()
	glPushName (0);

	glMatrixMode (GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		gluPickMatrix ((GLdouble)mouse_x, (GLdouble)(viewport[3] - mouse_y), 1, 1, viewport);
		glOrtho (m_projection_left, m_projection_right, m_projection_bottom, m_projection_top, m_projection_near, m_projection_far);

		transform_scene();

		std::map<unsigned long, shader_block*> block_indices;
		unsigned long index = 1;
		shrimp::shader_blocks_t block_list = m_services->get_scene_blocks();
		for (shrimp::shader_blocks_t::const_iterator block_i = block_list.begin(); block_i != block_list.end(); ++block_i) {

			shader_block* block = *block_i;

			int group = m_services->get_block_group (block);
			if (!group) {

				glLoadName (index);

				draw_block_body (block, block->m_position_x, block->m_position_y);

				block_indices.insert (std::make_pair (index, block));

				++index;
			}
		}

	glMatrixMode (GL_PROJECTION);
	glPopName();
	glPopMatrix();
	glFlush();

	// Get list of picked blocks
	GLint hits = glRenderMode (GL_RENDER);
	if (hits <= 0)
		return 0;

	GLuint closest = 0;
	GLuint dist = 0xFFFFFFFFU;
	while (hits) {

		if (selection_buffer[ (hits - 1) * 4 + 1] < dist) {

			dist = selection_buffer[ (hits - 1) * 4 + 1];
			closest = selection_buffer[ (hits - 1) * 4 + 3];
		}

		hits--;
	}

	return block_indices[closest];
}


shrimp::io_t opengl_view::get_under_mouse_property(const int mouse_x, const int mouse_y)
{
	// get current viewport
	GLint viewport[4];
	glGetIntegerv (GL_VIEWPORT, viewport);

	// setup OpenGL selection
	const GLsizei buffer_size = 1024;
	GLuint selection_buffer[buffer_size];
	glSelectBuffer (buffer_size, selection_buffer);
	glRenderMode (GL_SELECT);

	glInitNames();
	// push default name, it will be replaced using glLoadName()
	glPushName (0);

	glMatrixMode (GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		gluPickMatrix ((GLdouble)mouse_x, (GLdouble)(viewport[3] - mouse_y), 1, 1, viewport);
		glOrtho (m_projection_left, m_projection_right, m_projection_bottom, m_projection_top, m_projection_near, m_projection_far);

		transform_scene();

		m_property_indices.clear();
		m_property_index = 1;
		shrimp::shader_blocks_t block_list = m_services->get_scene_blocks();
		for (shrimp::shader_blocks_t::const_iterator block_i = block_list.begin(); block_i != block_list.end(); ++block_i) {

			const shader_block* block = *block_i;

			int group = m_services->get_block_group (block);
			if (!group) {
				positions_t property_positions;
				draw_block_properties (block, block->m_position_x, block->m_position_y, property_positions, true);
			}
		}

	glMatrixMode (GL_PROJECTION);
	glPopName();
	glPopMatrix();
	glFlush();

	// Get list of picked blocks
	GLint hits = glRenderMode (GL_RENDER);
	if (hits <= 0)
		return std::make_pair ("", "");

	GLuint closest = 0;
	GLuint dist = 0xFFFFFFFFU;
	while (hits) {

		if (selection_buffer[ (hits - 1) * 4 + 1] < dist) {

			dist = selection_buffer[ (hits - 1) * 4 + 1];
			closest = selection_buffer[ (hits - 1) * 4 + 3];
		}

		hits--;
	}

	const shader_block* selected_block = m_property_indices[closest].first;
	if (selected_block)
		return std::make_pair (m_property_indices[closest].first->name(), m_property_indices[closest].second);

	return std::make_pair ("", "");
}


int opengl_view::get_under_mouse_group(const int mouse_x, const int mouse_y)
{
	// get group list
	shrimp::group_set_t groups = m_services->group_list();

	// Get current viewport
	GLint viewport[4];
	glGetIntegerv (GL_VIEWPORT, viewport);

	// Setup OpenGL selection
	const GLsizei buffer_size = 1024;
	GLuint selection_buffer[buffer_size];
	glSelectBuffer (buffer_size, selection_buffer);
	glRenderMode (GL_SELECT);

	glInitNames();
	// Push default name, it will be replaced using glLoadName()
	glPushName (0);

	glMatrixMode (GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		gluPickMatrix ((GLdouble)mouse_x, (GLdouble)(viewport[3] - mouse_y), 1, 1, viewport);
		glOrtho (m_projection_left, m_projection_right, m_projection_bottom, m_projection_top, m_projection_near, m_projection_far);

		transform_scene();

		for (shrimp::group_set_t::const_iterator g = groups.begin(); g != groups.end(); ++g) {

			glLoadName (*g);
			draw_group_body (*g);
		}

	glMatrixMode (GL_PROJECTION);
	glPopName();
	glPopMatrix();
	glFlush();

	// Get list of picked blocks
	GLint hits = glRenderMode (GL_RENDER);
	if (hits <= 0)
		return 0;

	GLuint closest = 0;
	GLuint dist = 0xFFFFFFFFU;
	while (hits) {

		if (selection_buffer[ (hits - 1) * 4 + 1] < dist) {

			dist = selection_buffer[ (hits - 1) * 4 + 1];
			closest = selection_buffer[ (hits - 1) * 4 + 3];
		}

		hits--;
	}

	return closest;
}


void opengl_view::transform_scene()
{
	glScaled (m_size, m_size, m_size);
}


void opengl_view::set_grid_state (const bool GridState)
{
	m_grid = GridState;
}


void opengl_view::set_snap_to_grid_state (const bool SnapState)
{
	m_snap_to_grid = SnapState;
}


void opengl_view::set_overview_state (const bool OverviewState)
{
	m_overview = OverviewState;
}


void opengl_view::snap_position (double& X, double& Y)
{
	//const double grid_size = 1.0;
	const double snap_size = 0.3;

	const double x_floor = std::floor (X);
	const double x_ceil = std::ceil (X);

	if ((X - x_floor) < (x_ceil - X)) {

		if (X - x_floor < snap_size)
			X = x_floor;
	} else {

		if (x_ceil - X < snap_size)
			X = x_ceil;
	}

	const double y_floor = std::floor (Y);
	const double y_ceil = std::ceil (Y);

	if ((Y - y_floor) < (y_ceil - Y)) {

		if (Y - y_floor < snap_size)
			Y = y_floor;
	} else {

		if (y_ceil - Y < snap_size)
			Y = y_ceil;
	}
}


void opengl_view::mouse_wheel_update(double move)
{
	log() << aspect << "opengl_view: mouse_wheel_update, move=" << move << std::endl;

	double change = - 0.3 * move;

        set_size (m_size + change);
}


void opengl_view::mouse_move(int mouse_x, int mouse_y)
{
        //log() << aspect << "opengl_view: mouse_move" << std::endl;

	// mouse move
	m_active_property = get_under_mouse_property(mouse_x, mouse_y);
	m_current_mouse_x = mouse_x;
	m_current_mouse_y = mouse_y;

	m_under_mouse_block = get_under_mouse_block(mouse_x, mouse_y);
	m_under_mouse_group = get_under_mouse_group(mouse_x, mouse_y);

	//Mouse over nothing
	if (!m_under_mouse_group)
	{
		m_box_selection = false;
	}
}


void opengl_view::mouse_any_button_down(int mouse_x, int mouse_y)
{
	log() << aspect << "opengl_view: mouse_any_button_down" << std::endl;

	m_mouse_click_x = mouse_x;
	m_mouse_click_y = mouse_y;

	m_last_mouse_x = mouse_x;
	m_last_mouse_y = mouse_y;

	m_mouse_click = 0;

	m_under_mouse_block = get_under_mouse_block(mouse_x, mouse_y);
	m_under_mouse_group = get_under_mouse_group(mouse_x, mouse_y);
}


void opengl_view::mouse_left_button_down(const int mouse_x, const int mouse_y, const bool shift_key_down, const bool ctrl_key_down)
{
	log() << aspect << "opengl_view: mouse_left_button_down" << std::endl;

	if (ctrl_key_down)
	{
		if (m_under_mouse_block)
		{
			// toggle block selection
			m_services->set_block_selection (m_under_mouse_block, !m_services->is_selected (m_under_mouse_block));
		}
		if (m_under_mouse_group)
		{
			if (m_services)
			{
				m_services->set_group_selection(m_under_mouse_group, !m_services->is_group_selected(m_under_mouse_group));
			}
		}

	}

	else if (shift_key_down)
	{
		if (m_under_mouse_block)
		{
			// toggle block selection
			m_services->set_block_selection (m_under_mouse_block, 1);
		}
		if (m_under_mouse_group)
		{
			m_services->set_group_selection(m_under_mouse_group, 1);
		}
	}

	else if (m_active_property.first.size() && m_connection_start.first == "") {

		// save connection start
		m_connection_start_x = m_mouse_click_x;
		m_connection_start_y = m_mouse_click_y;
	}
	else
	{
		if (!m_under_mouse_block && !m_under_mouse_group)
		{
			m_services->clear_selection();
		}

		m_start_drag_x = mouse_x;
		m_start_drag_y = mouse_y;
	}
}


void opengl_view::mouse_right_button_down()
{
	log() << aspect << "opengl_view: mouse_right_button_down" << std::endl;

	if (m_active_property.first.size())
	{
		// mouse is over a block property, call the right-click popup menu
		shader_property_right_click (m_active_property);

		// clear other actions
		m_mouse_click = 0;
		m_under_mouse_block = 0;
		m_under_mouse_group = 0;
		m_active_property = std::make_pair ("", "");
		m_connection_start = std::make_pair ("", "");
	}
	else if (m_under_mouse_block)
	{
		// mouse is over a block (but not over a property)
		std::string block_name = m_under_mouse_block->name();
		shader_block_right_click (block_name);
	}
	else if (m_under_mouse_group)
	{
		// mouse is over a group
		block_group_right_click (m_under_mouse_group);
	}
	else
	{
		// mouse's over nothing...

		// clear current actions
		m_mouse_click = 0;
		m_under_mouse_block = 0;
		m_under_mouse_group = 0;
		m_active_property = std::make_pair ("", "");
		m_connection_start = std::make_pair ("", "");

		// selection menu
		if (m_services->selection_size() > 1)
		{
			empty_right_click();
		}
	}
}


void opengl_view::mouse_any_button_drag(const int mouse_x, const int mouse_y)
{
	log() << aspect << "opengl_view: mouse_any_button_drag" << std::endl;

	m_current_mouse_x = mouse_x;
	m_current_mouse_y = mouse_y;
}


void opengl_view::mouse_left_button_drag(const int widget_width, const int widget_height, const bool alt_key_down)
{
	log() << aspect << "opengl_view: mouse_left_button_drag" << std::endl;

	m_mouse_click++;

	const double mouse_move_x = static_cast<double>(m_current_mouse_x - m_last_mouse_x);
	const double mouse_move_y = static_cast<double>(m_current_mouse_y - m_last_mouse_y);

	const double move_x = mouse_move_x * (m_projection_right - m_projection_left) / static_cast<double> (widget_width);
	const double move_y = - mouse_move_y * (m_projection_top - m_projection_bottom) / static_cast<double> (widget_height);

	if (m_active_property.first.size())
	{
		// do nothing
	}
	else if (m_under_mouse_block)
	{
		// move selected block
		move_active_block (move_x / m_size, move_y / m_size);
	}
	else if (m_under_mouse_group)
	{
		move_active_block (move_x / m_size, move_y / m_size);
	}
	else if (alt_key_down)
	{
		// move scene when ALT key press
		move_scene (move_x, move_y);
	}
	else
	{
		// drawing of rectangle selection
		m_box_selection = true;
	}

	m_last_mouse_x = m_current_mouse_x;
	m_last_mouse_y = m_current_mouse_y;
}


void opengl_view::mouse_left_button_release(const int mouse_x, const int mouse_y, const bool shift_key_down, const bool ctrl_key_down, const bool alt_key_down)
{
	log() << aspect << "opengl_view: mouse_left_button_release" << std::endl;

	if (m_mouse_click <= 1)
	{
		if (m_active_property.first != "")
		{
			if (m_connection_start.first == "")
			{
				m_connection_start = m_active_property;
				m_mouse_click_x = mouse_x;
				m_mouse_click_y = mouse_y;
			}
			else
			{
				if (m_connection_start.first != m_active_property.first)
				{
					// connect properties
					shader_block* input_block = m_services->get_block(m_connection_start.first);
					shader_block* output_block = m_services->get_block(m_active_property.first);
					if (input_block && output_block)
					{
						if (input_block->is_output (m_connection_start.second) && output_block->is_input (m_active_property.second))
							std::swap (m_connection_start, m_active_property);

						m_services->connect (m_connection_start, m_active_property);
					}
				}

				m_connection_start = std::make_pair ("", "");
			}

		}
		//select block
		else if ((m_under_mouse_block || m_under_mouse_group) &&  !(shift_key_down || ctrl_key_down))
		{
			m_services->clear_selection();
			if (m_under_mouse_block)
			{
				// toggle block selection
				m_services->set_block_selection (m_under_mouse_block, !m_services->is_selected (m_under_mouse_block));
			}
			else if (m_under_mouse_group)
			{
				m_services->set_group_selection(m_under_mouse_group, !m_services->is_group_selected(m_under_mouse_group));
			}
		}
	}

	// actually snap block when drag ends
	if (m_snap_to_grid)
	{
		if (m_under_mouse_block)
		{
			double x = m_under_mouse_block->m_position_x;
			double y = m_under_mouse_block->m_position_y;
			snap_position (x, y);

			m_under_mouse_block->m_position_x = x;
			m_under_mouse_block->m_position_y = y;
		}
	}
}


