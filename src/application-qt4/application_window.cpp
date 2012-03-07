#include "application_window.h"
#include "ui_application_window.h"

#include "src/application-qt4/system_functions.h"
#include "src/miscellaneous/logging.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QContextMenuEvent>

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


    // add the QGLWidget scene_view to the main window
    ui_scene_view = new scene_view(shrimp_services);
    ui->verticalLayout->addWidget(ui_scene_view);

    // build block popup menu
    menuNode menuRootNode;
    blockPopupMenuTree["Root"] = menuNode();
    const block_tree_node_t rootNode = shrimp_services->get_block_hierarchy();
    buildBlockSubmenu(rootNode, "Root");

    // connect events
    QObject::connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openSceneFile()));
    QObject::connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));

    QObject::connect(ui->zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(changeZoom(int)));
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
        //connect(blockAction, SIGNAL(triggered()), this, SLOT(blockPopupMenu(QWidget*)));

        menuBlock blockInfo;
        blockInfo.action = blockAction;
        blockInfo.block = *block;
        blockPopupMenuTree[menuNodeName].actionList.push_back(blockInfo);
    }
}


void application_window::openSceneFile()
{
    QString path = QFileDialog::getOpenFileName(this, "Find scene file", QString(), QString());
    log() << INFO << "opening file: " << path.toStdString() << std::endl;

    std::string std_path = path.toStdString();

    bool success = shrimp_services->load(std_path);
    if (!success) {
        std::string message = "Could not open scene file '" + std_path + "'";
        log() << ERROR << message << std::endl;

        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.setInformativeText(QString::fromStdString(message));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();

        //return false;
    }

    const double new_size = ui_scene_view->fit_scene();
    ui->zoomSlider->setValue(static_cast<int>(new_size * 100.0d));

    // Set scene name as window's title
    //label (m_services->get_scene_name().c_str());

    //return true;
}

void application_window::changeZoom(int zoom)
{
    double value = static_cast<double>(zoom) / 20.0d;

    ui_scene_view->set_size(value);
    ui_scene_view->redraw();
}


void application_window::blockPopupMenu(QWidget* parent)
{

}


void application_window::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);

    buildContextMenuFromBlock(menu, std::string("Root"));

    menu.exec(event->globalPos());
}


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

    for (std::vector<menuBlock>::iterator entry = node.actionList.begin();
        entry != node.actionList.end(); ++entry)
    {
        menu.addAction(entry->action);
    }
}


application_window::~application_window()
{
    delete ui;
}
