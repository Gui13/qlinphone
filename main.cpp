#include "linphonewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LinphoneWindow w;
    w.show();

    return a.exec();
}
