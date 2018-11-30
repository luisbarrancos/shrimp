/*
    Copyright 2010, Romain Behar <romainbehar@users.sourceforge.net>

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

#ifndef scene_view_h
#define scene_view_h

#include "../opengl_view/opengl_view.h"
#include "../services.h"

#include <QGLWidget>

class scene_view
    : public QGLWidget,
      public opengl_view
{
  public:
    Q_OBJECT

    services* m_services{};

  public:
    explicit scene_view(services* services_instance);
    ~scene_view() override;

    QSize sizeHint() const override;
    void redraw();

    double fit_scene();

  protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

    void drawGlText(
        const std::string Text,
        const double X,
        const double Y,
        const double Z,
        const double Size,
        const bool Bold) override;

    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    void wheelEvent(QWheelEvent*) override;

    void updateSceneZoom(const double) override;

    // callbacks
    void shader_property_right_click(shrimp::io_t& Property) override;
    void shader_block_right_click(std::string& Block) override;
    void block_group_right_click(int Group) override;
    void empty_right_click() override;

  signals:
    void setSceneZoom(const double);
    void shaderBlockRightClick(const std::string blockName);
    void shaderPropertyRightClick(const shrimp::io_t property);
    void blockGroupRightClick(const int group);
    void emptyRightClick();

  private:
    QSize currentSize;
    QFont currentFont;
};

#endif // scene_view_h
