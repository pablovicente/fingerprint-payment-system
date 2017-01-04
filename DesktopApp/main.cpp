#include "mainwindow.h"
#include <QApplication>

#include <qlabel.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    if(!w.loadSettings())   {
        return 0;
    }
    else    {
        return a.exec();
    }
}
