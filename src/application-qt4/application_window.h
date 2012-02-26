#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "src/application-qt4/scene_view.h"
#include "src/services.h"

namespace Ui {
    class application_window;
}

class application_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit application_window(QWidget *parent = 0);
    ~application_window();

public slots:
    void openSceneFile();
    void changeZoom(int zoom);

private:
    Ui::application_window *ui;
    scene_view* ui_scene_view;
    services* shrimp_services;
};

#endif // MAINWINDOW_H
