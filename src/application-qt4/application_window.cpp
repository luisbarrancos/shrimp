#include "application_window.h"
#include "ui_application_window.h"

#include "src/services.h"
#include "src/application-qt4/system_functions.h"
#include "src/miscellaneous/logging.h"

#include <memory>

application_window::application_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::application_window)
{
    ui->setupUi(this);

    // initialize Shrimp
    log_level_t level = ERROR;
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
    i_system_functions* system_instance = new system_functions();

    // create service
    services* service_instance = new services(system_instance);


    // add the QGLWidget scene_view to the main window
    ui_scene_view = new scene_view(service_instance);
    ui->verticalLayout->addWidget(ui_scene_view);
}

application_window::~application_window()
{
    delete ui;
}
