#include "../QLicensorWindow/qlicensorwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLicensorWindow w;
    w.setWindowTitle("QLicensor - Simple tool for sourcecode licensing");
    w.setWindowState(Qt::WindowMaximized);
    w.show();

    return a.exec();
}
