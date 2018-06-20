#include "jstestwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    JSTestWindow w;
    w.show();


    return a.exec();
}
