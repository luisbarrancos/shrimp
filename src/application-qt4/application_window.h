
/*
    Copyright 2010-2012, Romain Behar <romainbehar@users.sourceforge.net>

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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "src/application-qt4/scene_view.h"
#include "src/services.h"
#include "src/shading/preferences.h"

namespace Ui {
    class application_window;
}


// context menu pop tree structure
struct block_tree_node_t;
typedef std::vector<block_tree_node_t> block_tree_node_list_t;

struct menuBlock
{
    QAction* action;
    default_block_t block;
};

struct menuNode
{
    std::set<std::string> subDirList;
    std::vector<menuBlock> actionList;
};


class application_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit application_window(QWidget *parent = 0);
    ~application_window();

public slots:
    // File menu
    void newScene();
    void openSceneFile();
    void saveScene();
    void saveSceneAsFile();

    // Edit menu
    void copy();
    void paste();
    void cut();
    void group();
    void ungroup();
    void editBlock();
    void deleteBlocks();

    // View menu
    void toggleGrid(bool);
    void toggleGridSnap(bool);

    void newBlockPopup();
    void changeRenderer(const QString&);
    void changeDisplay(const QString&);
    void changeRenderScene(const QString&);
    void renderScene();

    void changeZoom(int zoom);
    void fitScene();
    void updateSceneZoom(const double);
    void blockPopupMenu(QString);

protected:
    //void contextMenuEvent(QContextMenuEvent *event);
    void buildContextMenuFromBlock(QMenu&, const std::string);

private:
    Ui::application_window *ui;
    scene_view* ui_scene_view;
    i_system_functions* systemFunctions;
    services* shrimp_services;

    general_options preferences;
    general_options::renderers_t renderers;
    general_options::scenes_t scenes;

    std::string findDataDirectory(const std::string& directoryName);
    void buildBlockSubmenu(const block_tree_node_t&, const std::string& menuNodeName);
    typedef std::map<std::string, menuNode> blockPopupMenuTree_t;
    blockPopupMenuTree_t blockPopupMenuTree;

    void setupRendererCombo(const std::string&);
    void setupDisplayCombo(const std::string&);
    void setupSceneCombo();
};

#endif // MAINWINDOW_H
