
/*
    Copyright 2009-2010, Romain Behar <romainbehar@users.sourceforge.net>

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

#ifndef _ui_opengl_view_h_
#define _ui_opengl_view_h_

#include "../services.h"

class opengl_view
{
  public:
    // constructor
    explicit opengl_view(services*);

    virtual ~opengl_view() = default;

    // fits whole scene into window
    double fit_scene(int window_width, int window_height);

    // sets scene scale
    void set_size(const double);

    double get_size()
    {
        return m_size;
    }

    shader_block* get_active_block()
    {
        return m_under_mouse_block;
    }
    int get_selected_group()
    {
        return m_under_mouse_group;
    }

    // options
    void set_grid_state(const bool GridState);
    void set_snap_to_grid_state(const bool SnapState);
    void set_overview_state(const bool OverviewState);

    // move block to the view center
    void move_block_to_view_center(shader_block* Block);

    // draw scene
    void draw_scene(bool valid, int window_width, int window_height);

    virtual void drawGlText(
        const std::string Text,
        const double X,
        const double Y,
        const double Z,
        const double Size,
        const bool Bold)
    {
    }

    // event functions
    void mouse_wheel_update(int move);
    void mouse_move(int mouse_x, int mouse_y);
    void mouse_any_button_down(int mouse_x, int mouse_y);

    void mouse_left_button_down(
        const int mouse_x,
        const int mouse_y,
        const bool shift_key_down,
        const bool ctrl_key_down);

    void mouse_right_button_down();

    void mouse_any_button_drag(const int mouse_x, const int mouse_y);

    void mouse_left_button_drag(
        const int widget_width,
        const int widget_height,
        const bool alt_key_down);

    void mouse_left_button_release(
        const int mouse_x,
        const int mouse_y,
        const bool shift_key_down,
        const bool ctrl_key_down,
        const bool alt_key_down);

    // GUI events
    virtual void shader_property_right_click(shrimp::io_t&) {}
    virtual void shader_block_right_click(std::string&) {}
    virtual void block_group_right_click(int) {}
    virtual void empty_right_click() {}

    virtual void updateSceneZoom(const double) {}

  protected:
    // store the scene being drawn
    services* m_services;

  private:
    // store active block
    shader_block* m_under_mouse_block;
    shrimp::io_t m_active_property;

    // store active group
    int m_under_mouse_group{};

    // store current connection start
    shrimp::io_t m_connection_start;

    typedef std::map<unsigned long, std::pair<const shader_block*, std::string>>
        property_indices_t;
    property_indices_t m_property_indices;

    unsigned long m_property_index{};

    // draws a block
    struct position
    {
        position(const double X, const double Y)
            : position_x(X)
            , position_y(Y)
        {
        }

        double position_x;
        double position_y;
    };
    typedef std::map<shrimp::io_t, position> positions_t;

    // handle block groups
    typedef std::map<int, position> group_position_t;
    group_position_t m_group_positions;

    // stores scene size
    double m_size;

    // store previous mouse position
    int m_last_mouse_x;
    int m_last_mouse_y;

    // stores mouse click (false if there's a drag)
    unsigned long m_mouse_click;

    int m_mouse_click_x{};
    int m_mouse_click_y{};
    int m_current_mouse_x{};
    int m_current_mouse_y{};
    int m_start_drag_x{};
    int m_start_drag_y{};

    bool m_box_selection;

    // store connection start position
    int m_connection_start_x{};
    int m_connection_start_y{};

    // store OpenGL camera projection values
    double m_projection_left;
    double m_projection_right;
    double m_projection_bottom;
    double m_projection_top;
    double m_projection_near;
    double m_projection_far;

    // save view width and height
    int m_view_width{};
    int m_view_height{};

    const double m_min_block_height;

    // options
    bool m_grid;
    bool m_snap_to_grid;
    bool m_overview;
    int m_font_size;

    // set the OpenGL view projection
    void update_projection(int window_width, int window_height);

    // set scene centre
    void center_scene(const double X, const double Y);

    // move active block by given offset
    void move_active_block(const double XOffset, const double YOffset);

    // move all blocks by given offset
    void move_all_blocks(const double XOffset, const double YOffset);

    // move scene by given offset
    void move_scene(const double XOffset, const double YOffset);

    // move active group
    void move_active_group(const double XOffset, const double YOffset);

    // snap function (snaps given coordinates)
    void snap_position(double& X, double& Y);

    // draw grid
    void draw_grid();

    // draws active shader
    void draw_shader(int window_width, int window_height);

    // draw a rectangle of selection
    void box_selection(int window_width, int window_height);

    // OpenGL selection
    shader_block* get_under_mouse_block(const int mouse_x, const int mouse_y);
    shrimp::io_t get_under_mouse_property(const int mouse_x, const int mouse_y);

    int get_under_mouse_group(const int mouse_x, const int mouse_y);

    // OpenGL scene transformation
    void transform_scene();

    void draw_block(
        shader_block* Block,
        const double X,
        const double Y,
        positions_t& PropertyPositions);

    void draw_block_body(shader_block* Block, const double X, const double Y);
    void draw_rolled_block_body(shader_block* Block, const double X, const double Y);
    void draw_block_name(const shader_block* Block, const double X, const double Y);

    void draw_block_properties(
        const shader_block* Block,
        const double X,
        const double Y,
        positions_t& PropertyPositions,
        const bool Selection = false);

    // draws a block property
    void draw_property(
        const std::string& Name,
        const std::string& Type,
        bool Shader_param,
        const double X,
        const double Y,
        const double Size,
        const bool Multi = false);

    // draws block groups
    void draw_groups();
    void draw_group_body(int Group);
    void draw_group_body(const double X, const double Y, const int current_group);
};

#endif // _ui_opengl_view_h_
