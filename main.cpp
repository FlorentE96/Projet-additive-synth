#include "mainwindow.h"
#include <QApplication>
#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdint>
#include "global.hpp"
#include "oscillators.hpp"
#include "LUTs.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
