#include <QApplication>
#include "portaudio.h"
#include "mainwindow.h"
#include "RtMidi.h"

#define NUM_SECONDS   (1)

using namespace std;

typedef struct
{
    int16_t left;
    int16_t right;
}
paTestData;

static paTestData data;

MainWindow w;

static int patestCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData );

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

    data.left = 0;
    data.right = 0;

    sine = new Osc(wavetable_saw3, 500);

    LP = new Filter(LPF, 500, 1.0f, 2);

    PaStream *stream;
    /* Initialize library */
    Pa_Initialize();

    /* Open an output-only audio stream. */
    Pa_OpenDefaultStream( &stream,
                                0,          /* no input channels */
                                2,          /* stereo output */
                                paInt16,  /* 16 bit int output */
                                SAMPLE_RATE,
                                256,        /* frames per buffer */
                                patestCallback, /*routine to execute when audio is needed */
                                &data ); /*static structure representing left and right channel samples */

    Pa_StartStream( stream );

    int j = 0;

    QApplication a(argc, argv);

    w = new MainWindow();

    w.show();

    Pa_StopStream( stream );

    Pa_CloseStream( stream );

    Pa_Terminate();

    return a.exec();

}
