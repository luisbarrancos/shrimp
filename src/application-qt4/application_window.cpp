#include "application_window.h"
#include "ui_application_window.h"

#include "src/application-qt4/system_functions.h"
#include "src/miscellaneous/logging.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QContextMenuEvent>
#include <QSignalMapper>

#include <memory>

application_window::application_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::application_window)
{
    ui->setupUi(this);

    // initialize Shrimp
    log_level_t level = ASPECT;
    std::auto_ptr<std::streambuf> filter_level (new filter_by_level_buf (level, log()));

    /*
            log() << error << "LOG = ERROR" << std::endl;
            log() << warning << "LOG = WARNING" << std::endl;
            log() << info << "LOG = INFO" << std::endl;
            log() << debug << "LOG = DEBUG" << std::endl;
            log() << aspect << "LOG = ASPECT" << std::endl;
    */

    log() << aspect << "Starting Shrimp" << std::endl;

    // create system function instance (FLTK dependent)
    std::string block_path = "../blocks";
    i_system_functions* system_instance = new system_functions();

    // create service
    shrimp_services = new services(system_instance, block_path);

    // load preferences
    preferences.initialize(shrimp_services->system_function_instance());
    renderers = preferences.get_renderer_list();
    scenes = preferences.get_scene_list();

    setupRendererCombo();

    // add the QGLWidget scene_view to the main window
    ui_scene_view = new scene_view(shrimp_services);
    ui->verticalLayout->addWidget(ui_scene_view);

    // build block popup menu
    menuNode menuRootNode;
    blockPopupMenuTree["Root"] = menuNode();
    const block_tree_node_t rootNode = shrimp_services->get_block_hierarchy();
    buildBlockSubmenu(rootNode, "Root");

    // connect events
    QObject::connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(newScene()));
    QObject::connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openSceneFile()));
    QObject::connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveScene()));
    QObject::connect(ui->actionSaveAs, SIGNAL(triggered()), this, SLOT(saveSceneAsFile()));
    QObject::connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));

    QObject::connect(ui->actionCopy, SIGNAL(triggered()), this, SLOT(copy()));
    QObject::connect(ui->actionPaste, SIGNAL(triggered()), this, SLOT(paste()));
    QObject::connect(ui->actionCut, SIGNAL(triggered()), this, SLOT(cut()));
    QObject::connect(ui->actionGroup, SIGNAL(triggered()), this, SLOT(group()));
    QObject::connect(ui->actionUngroup, SIGNAL(triggered()), this, SLOT(ungroup()));
    QObject::connect(ui->actionEditBlock, SIGNAL(triggered()), this, SLOT(editBlock()));
    QObject::connect(ui->actionDeleteBlocks, SIGNAL(triggered()), this, SLOT(deleteBlocks()));

    QObject::connect(ui->actionShowGrid, SIGNAL(toggled(bool)), this, SLOT(toggleGrid(bool)));
    QObject::connect(ui->actionSnapBlocks, SIGNAL(toggled(bool)), this, SLOT(toggleGridSnap(bool)));

    QObject::connect(ui->addBlockButton, SIGNAL(clicked()), this, SLOT(newBlockPopup()));
    QObject::connect(ui->zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(changeZoom(int)));
    QObject::connect(ui->fitSceneButton, SIGNAL(clicked()), this, SLOT(fitScene()));

    QObject::connect(ui_scene_view, SIGNAL(setSceneZoom(const double)), this, SLOT(updateSceneZoom(const double)));
}


void application_window::buildBlockSubmenu(const block_tree_node_t& treeNode, const std::string& menuNodeName)
{
    // check whether the directory has children
    for (block_tree_node_list_t::const_iterator subNode = treeNode.child_nodes.begin();
         subNode != treeNode.child_nodes.end(); ++subNode)
    {
        std::string newDir = subNode->node_name;
        blockPopupMenuTree[menuNodeName].subDirList.insert(newDir);

        blockPopupMenuTree[newDir] = menuNode();

        buildBlockSubmenu(*subNode, newDir);
    }

    for (default_block_list_t::const_iterator block = treeNode.blocks.begin();
         block != treeNode.blocks.end(); ++block)
    {
        // add menu item
        QAction* blockAction = new QAction(QString::fromStdString(block->name), this);

        menuBlock blockInfo;
        blockInfo.action = blockAction;
        blockInfo.block = *block;
        blockPopupMenuTree[menuNodeName].actionList.push_back(blockInfo);
    }
}


void application_window::setupRendererCombo()
{
    const std::string selectedRenderer = preferences.m_renderer_code;

    unsigned long rendererMenuNumber = 0;
    unsigned long currentMenuNumber = 0;

    for (general_options::renderers_t::iterator renderer = renderers.begin(); renderer != renderers.end(); ++renderer, ++currentMenuNumber)
    {
        if (renderer->first == _3delight)
        {
            ui->rendererCombo->addItem(QString::fromStdString(renderer->second.name));
        }
        else if (renderer->first == air)
        {
            ui->rendererCombo->addItem(QString::fromStdString(renderer->second.name));
        }
        else if (renderer->first == aqsis)
        {
            ui->rendererCombo->addItem(QString::fromStdString(renderer->second.name));
        }
        else if (renderer->first == entropy)
        {
            ui->rendererCombo->addItem(QString::fromStdString(renderer->second.name));
        }
        else if (renderer->first == pixie)
        {
            ui->rendererCombo->addItem(QString::fromStdString(renderer->second.name));
        }
        else if (renderer->first == prman)
        {
            ui->rendererCombo->addItem(QString::fromStdString(renderer->second.name));
        }
        else if (renderer->first == renderdotc)
        {
            ui->rendererCombo->addItem(QString::fromStdString(renderer->second.name));
        }
    }

}


void application_window::newScene()
{
    shrimp_services->reset_scene();
    ui_scene_view->fit_scene();
}


void application_window::openSceneFile()
{
    QString path = QFileDialog::getOpenFileName(this, "Find scene file", QString(), QString());
    log() << INFO << "opening file: " << path.toStdString() << std::endl;

    std::string std_path = path.toStdString();

    bool success = shrimp_services->load(std_path);
    if (!success)
    {
        std::string message = "Could not open scene file '" + std_path + "'";
        log() << ERROR << message << std::endl;

        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.setInformativeText(QString::fromStdString(message));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();

        //return false;
    }

    ui_scene_view->fit_scene();

    // Set scene name as window's title
    setWindowTitle(QString::fromStdString(shrimp_services->get_scene_name()));

    //return true;
}


void application_window::saveScene()
{
    if (!shrimp_services->save())
    {
        saveSceneAsFile();
    }
}


void application_window::saveSceneAsFile()
{
    QString path = QFileDialog::getSaveFileName(this, "Save scene as...", QString(), "Shrimp file (*.xml)");
    log() << INFO << "File save: " << path.toStdString() << std::endl;

    if (path.isEmpty())
    {
        // No file selected
        return;
    }

    // automatically add file extension
    if (!path.endsWith(".xml"))
    {
        path.append(".xml");
    }

    // check whether file already exists
    QFile saveFile(path);
    if (saveFile.exists())
    {
        QMessageBox msgBox;
        msgBox.setText("The file already exists.");
        msgBox.setInformativeText("Do you want to overwrite it?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        int answer = msgBox.exec();

        if (answer == QMessageBox::Cancel)
        {
            // File save cancelled
            return;
        }
    }

    shrimp_services->save_as(path.toStdString());
}


void application_window::copy()
{
    shrimp_services->copy_selected_blocks(ui_scene_view->get_active_block());
}


void application_window::paste()
{
    shrimp_services->paste(ui_scene_view->get_active_block());
    ui_scene_view->redraw();
}


void application_window::cut()
{
    if (shrimp_services->selection_size() >= 1)
    {
        shrimp_services->cut_selection(ui_scene_view->get_active_block());
        ui_scene_view->redraw();
    }
}


void application_window::group()
{
    if (shrimp_services->selection_size() >= 1)
    {
        shrimp_services->group_selection();
        ui_scene_view->redraw();
    }
}


void application_window::ungroup()
{
    const int selectedGroup = ui_scene_view->get_selected_group();
    if (selectedGroup)
    {
        shrimp_services->ungroup(selectedGroup);
        ui_scene_view->redraw();
    }
}


void application_window::editBlock()
{
    if (shrimp_services->selection_size() == 1)
    {
        shader_block* block = ui_scene_view->get_active_block();
        if (block)
        {
            //TODO: open Edit dialog

            // toggle block selection
            shrimp_services->clear_selection();
            shrimp_services->set_block_selection(block, !shrimp_services->is_selected(block));
        }
    }
}


void application_window::deleteBlocks()
{
    shrimp_services->delete_selection();
    ui_scene_view->redraw();
}


void application_window::toggleGrid(bool checked)
{
    ui_scene_view->set_grid_state(checked);
    ui_scene_view->redraw();
}


void application_window::toggleGridSnap(bool checked)
{
    ui_scene_view->set_snap_to_grid_state(checked);
    ui_scene_view->redraw();
}


void application_window::newBlockPopup()
{
    QMenu menu(this);

    buildContextMenuFromBlock(menu, std::string("Root"));

    QPoint localPos = ui->addBlockButton->pos();
    menu.exec(ui->addBlockButton->mapToGlobal(localPos));
}


void application_window::changeZoom(int zoom)
{
    double value = static_cast<double>(zoom) / 20.0d;

    ui_scene_view->set_size(value);
    ui_scene_view->redraw();
}


void application_window::fitScene()
{
    ui_scene_view->fit_scene();
}


void application_window::blockPopupMenu(QString blockName)
{
    log() << aspect << "Adding new block: " << blockName.toStdString() << std::endl;

    shader_block* newBlock = shrimp_services->add_predefined_block(blockName.toStdString());
    ui_scene_view->move_block_to_view_center(newBlock);
    ui_scene_view->redraw();
}


/*void application_window::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);

    buildContextMenuFromBlock(menu, std::string("Root"));

    menu.exec(event->globalPos());
}*/


void application_window::buildContextMenuFromBlock(QMenu& menu, const std::string menuName)
{
    menuNode& node = blockPopupMenuTree[menuName];

    for (std::set<std::string>::iterator dirName = node.subDirList.begin();
         dirName != node.subDirList.end(); ++dirName)
    {
        const std::string subDirName = *dirName;
        QMenu* newSubMenu = menu.addMenu(QString::fromStdString(subDirName));
        buildContextMenuFromBlock(*newSubMenu, subDirName);
    }

    QSignalMapper* signalMapper = new QSignalMapper(this);
    for (std::vector<menuBlock>::iterator entry = node.actionList.begin();
        entry != node.actionList.end(); ++entry)
    {
        QAction* newAction = menu.addAction(QString::fromStdString(entry->block.name));
        connect(newAction, SIGNAL(triggered()), signalMapper, SLOT(map()));
        signalMapper->setMapping(newAction, QString::fromStdString(entry->block.name));
    }

    connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(blockPopupMenu(QString)));
}


void application_window::updateSceneZoom(const double newZoom)
{
    ui->zoomSlider->setValue(static_cast<int>(newZoom * 20.0d));
}


application_window::~application_window()
{
    delete ui;
}
