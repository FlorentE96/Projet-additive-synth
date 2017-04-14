#include <QApplication>
#include "mainwindow.h"
#include "RtMidi.h"

#define NUM_SECONDS   (1)

MainWindow w;

int main(int argc, char *argv[])
{
//    RtMidiIn *midiin = 0;
//    // RtMidiIn constructor
//    try {
//      midiin = new RtMidiIn();
//    }
//    catch (RtMidiError &error) {
//      // Handle the exception here
//      error.printMessage();
//    }
//    // Clean up
//    delete midiin;

    QApplication a(argc, argv);

    MainWindow w;

    w.show();


    return a.exec();

}
