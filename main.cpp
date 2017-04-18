#include <QApplication>
#include "mainwindow.h"


#define NUM_SECONDS   (1)


int main(int argc, char* argv[])
{


    QApplication a(argc, argv);

    MainWindow w;

    w.show();


    return a.exec();


}
