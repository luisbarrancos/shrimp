
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


#include "ui_scene_view.h"

#include "../miscellaneous/logging.h"

#include "../shading/rib_root_block.h"


#include <fltk/events.h>
#include <fltk/Item.h>
#include <fltk/MenuBar.h>
#include <fltk/PopupMenu.h>


int scene_view::handle (int Event) {

	const bool shift_key_down = fltk::event_state (fltk::SHIFT);
	const bool ctrl_key_down = fltk::event_state (fltk::CTRL);

	switch (Event) {

		// mouse wheel event
		case fltk::MOUSEWHEEL:
		{
			int wheel_move = fltk::event_dy();
			double change = - 0.3 * static_cast<double> (wheel_move);

			set_size (m_size + change);

			redraw();
		}
		return 1;

		// mouse move
		case fltk::MOVE:
		{
			// mouse move
			m_active_property = select_property();
			m_current_mouse_x = fltk::event_x();
			m_current_mouse_y = fltk::event_y();

			m_active_block = select_object();

			if (m_active_block.size()) {

										if (m_scene) {
											shader_block* block = m_scene->get_block (m_active_block);

											set_current_block(block);

										}
			}
			else {set_current_block(NULL);}
			redraw();
		}
		return 1;


		// mouse down
		case fltk::PUSH:
		{
			if ((fltk::event_button() == fltk::LeftButton) || (fltk::event_button() == fltk::RightButton)) {

				m_mouse_click_x = fltk::event_x();
				m_mouse_click_y = fltk::event_y();

				m_last_mouse_x = fltk::event_x();
				m_last_mouse_y = fltk::event_y();

				m_mouse_click = 0;

				m_active_block = select_object();
				m_active_group = select_group();

				if (fltk::event_button() == fltk::LeftButton) {

					if (shift_key_down || ctrl_key_down) {

						if (m_active_block.size()) {

							if (m_scene) {
								shader_block* block = m_scene->get_block (m_active_block);

								// toggle block selection
								m_scene->set_block_selection (block, !m_scene->is_selected (block));
							}
						}
					} else if (m_active_property.first.size()) {

						// save connection start
						m_connection_start_x = m_mouse_click_x;
						m_connection_start_y = m_mouse_click_y;
					}
				}

				if (fltk::event_button() == fltk::RightButton) {

					if (m_active_property.first.size()) {

						// mouse is over a block property
						if (m_scene) {

							shader_block* active_block = m_scene->get_block (m_active_property.first);
							const bool is_root = (active_block && active_block->m_root_block);

							fltk::PopupMenu mb (fltk::event_x(), fltk::event_y(), 0, 0, "Pad");
							mb.type (fltk::PopupMenu::POPUP3);
							mb.begin();
								int item_number = 0;

								// add the Edit menu item (except for the root block pads)
								if (!is_root) {
									++item_number;
									new fltk::Item ("Edit", 0, cb_edit_pad, (void*)this);
								}

								// add the Disconnect menu item if the block has a parent
								std::string foo;
								if (m_scene->get_parent (m_active_property.first, m_active_property.second, foo)) {
									++item_number;
									new fltk::Item ("Disconnect", 0, cb_disconnect_pad, (void*)this);
								}
							mb.end();

							if (item_number > 0) {
								mb.popup();
							}
						}

						// clear other actions
						m_mouse_click = 0;
						m_active_block = "";
						m_active_group = 0;
						m_active_property = std::make_pair ("", "");
						m_connection_start = std::make_pair ("", "");
					}
					else if (m_active_block.size()) {

						// mouse is over a block (but not over a property)
						shader_block* block = m_scene->get_block (m_active_block);
						if (m_scene) {

							const bool is_root = block->m_root_block;

							fltk::PopupMenu mb (fltk::event_x(), fltk::event_y(), 0, 0, "Block");
							mb.type (fltk::PopupMenu::POPUP3);
							mb.begin();
								if (!is_root) {
									if (m_scene->is_selected (block)) {
										new fltk::Item ("Deselect", 0, cb_deselect_block, (void*)this);
									} else {
										new fltk::Item ("Select", 0, cb_select_block, (void*)this);
									}
									if (m_scene->selection_size() > 1) {
										new fltk::Item ("Group selection", 0, cb_group_selection, (void*)this);
									}
									if (m_scene->is_rolled (block)) {
										new fltk::Item ("Unroll", 0, cb_unroll_block, (void*)this);
									} else {
										new fltk::Item ("Roll", 0, cb_roll_block, (void*)this);
									}
								}

								new fltk::Item ("Info", 0, cb_block_info, (void*)this);

								new fltk::Item ("Rename", 0, cb_rename_block, (void*)this);

								if (!is_root) {

									new fltk::Item ("Add input", 0, cb_add_input, (void*)this);
									new fltk::Item ("Add output", 0, cb_add_output, (void*)this);
									new fltk::Item ("Edit code", 0, cb_edit_code, (void*)this);

									new fltk::Item ("Delete", 0, cb_delete_block, (void*)this);
								} else {

									// RIB root block functions
									rib_root_block* rib = dynamic_cast<rib_root_block*> (block);
									if (rib) {

										new fltk::Item ("Edit RIB", 0, cb_edit_RIB, (void*)this);
									}
								}

							mb.end();

							mb.popup();
						}
					} else if (m_active_group) {

						// mouse is over a group
						fltk::PopupMenu group_menu (fltk::event_x(), fltk::event_y(), 0, 0, "Group");
						group_menu.type (fltk::PopupMenu::POPUP3);
						group_menu.begin();
							new fltk::Item ("Rename group", 0, cb_rename_group, (void*)this);
							new fltk::Item ("Ungroup", 0, cb_ungroup, (void*)this);
						group_menu.end();

						group_menu.popup();

					} else {
						// mouse's over nothing...

						// clear current actions
						m_mouse_click = 0;
						m_active_block = "";
						m_active_group = 0;
						m_active_property = std::make_pair ("", "");
						m_connection_start = std::make_pair ("", "");

						// selection menu
						if (m_scene->selection_size() > 1) {

							fltk::PopupMenu group_menu (fltk::event_x(), fltk::event_y(), 0, 0, "Menu");
							group_menu.type (fltk::PopupMenu::POPUP3);
							group_menu.begin();
							if (m_scene) {
								new fltk::Item ("Group selection", 0, cb_group_selection, (void*)this);
								new fltk::Item ("Clear selection", 0, cb_clear_selection, (void*)this);
							}
							group_menu.end();

							group_menu.popup();
						}
					}
				}
			}
		}
		return 1;

		// mouse drag
		case fltk::DRAG:
		{
			m_current_mouse_x = fltk::event_x();
			m_current_mouse_y = fltk::event_y();

			if (fltk::event_button() == fltk::LeftButton) {

				m_mouse_click++;

				const double mouse_move_x = static_cast<double>(m_current_mouse_x - m_last_mouse_x);
				const double mouse_move_y = static_cast<double>(m_current_mouse_y - m_last_mouse_y);

				const int widget_width = w();
				const int widget_height = h();

				const double move_x = mouse_move_x * (m_projection_right - m_projection_left) / static_cast<double> (widget_width);
				const double move_y = - mouse_move_y * (m_projection_top - m_projection_bottom) / static_cast<double> (widget_height);

				if (m_active_property.first.size()) {

					// do nothing

				}
				else if (m_active_block.size()) {

					// move selected block
					move_active_block (move_x / m_size, move_y / m_size);
				}
				else if (m_active_group) {

					move_active_group (move_x / m_size, move_y / m_size);
				}
				else {
					// move scene
					move_scene (move_x, move_y);
				}

				m_last_mouse_x = m_current_mouse_x;
				m_last_mouse_y = m_current_mouse_y;

				redraw();
			}
		}
		return 1;

		// mouse up
		case fltk::RELEASE:
		{
			if (fltk::event_button() == fltk::LeftButton) {

				if (m_mouse_click <= 1) {

					if (m_active_property.first != "") {

						if (m_connection_start.first == "") {

							m_connection_start = m_active_property;
							m_mouse_click_x = fltk::event_x();
							m_mouse_click_y = fltk::event_y();
						}
						else {
							if (m_connection_start.first != m_active_property.first) {

								// connect properties
								shader_block* input_block = m_scene->get_block(m_connection_start.first);
								shader_block* output_block = m_scene->get_block(m_active_property.first);
								if (input_block && output_block) {

									if (input_block->is_output (m_connection_start.second) && output_block->is_input (m_active_property.second))
										std::swap (m_connection_start, m_active_property);

									m_scene->connect (m_connection_start, m_active_property);
								}
							}

							m_connection_start = std::make_pair ("", "");
						}
					}
				}

				// actually snap block when drag ends
				if (m_snap_to_grid) {

					if (m_scene) {

						shader_block* block = m_scene->get_block (m_active_block);

						if (block) {
							double x = block->m_position_x;
							double y = block->m_position_y;
							snap_position (x, y);

							block->m_position_x = x;
							block->m_position_y = y;
						}
					}
				}
			}

			return 1;
		}

		default:
			// Let the base class handle all other events:
			return fltk::GlWindow::handle (Event);
	}
}


