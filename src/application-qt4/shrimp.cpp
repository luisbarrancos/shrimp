#include <QtGui/QApplication>
#include "application_window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    application_window w;
    w.show();

    return a.exec();
}
