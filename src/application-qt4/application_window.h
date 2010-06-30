#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "src/application-qt4/scene_view.h"

namespace Ui {
    class application_window;
}

class application_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit application_window(QWidget *parent = 0);
    ~application_window();

private:
    Ui::application_window *ui;
    scene_view* ui_scene_view;
};

#endif // MAINWINDOW_H
