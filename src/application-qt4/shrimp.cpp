#include "application_window.h"
#include <QtGui/QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    application_window w;
    w.show();

    return a.exec();
}
