#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QStringList list(qApp->libraryPaths());


/*
    QStringList aux;


    aux << "plugins" << "";

    qApp->setLibraryPaths(aux);
*/
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
