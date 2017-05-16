#ifndef SYNTH_ENGINE_HPP
#define SYNTH_ENGINE_HPP

#include <cstdint>
#include "portaudio.h"
#include "global.hpp"
#include "LUTs.hpp"
#include "oscillators.hpp"
#include "filter.hpp"
#include "ADSR.hpp"
#include "RtMidi.h"
#include "echo.hpp"
#include "mainwindow.h"

class synthEngine
{
public:
    typedef struct
    {
        int16_t left;
        int16_t right;
    }
    paTestData;
    synthEngine(Ui::MainWindow *_ui);
    ~synthEngine();
    Osc * osc1;
    Filter * filt1;
    ADSR * env1;
    Echo * echo1;

    void myMidiCallback( double deltatime, std::vector< unsigned char > *message);

    static void myStaticMidiCallback( double deltatime, std::vector< unsigned char > *message, void *userData )
    {
        ((synthEngine*)userData)->myMidiCallback(deltatime, message);
    }


    int mySoundCallback(const void *input, void *output,
      unsigned long frameCount,
      const PaStreamCallbackTimeInfo* timeInfo,
      PaStreamCallbackFlags statusFlags);

    static int myStaticSoundCallback(
      const void *input, void *output,
      unsigned long frameCount,
      const PaStreamCallbackTimeInfo* timeInfo,
      PaStreamCallbackFlags statusFlags,
      void *userData )
    {
      return ((synthEngine*)userData)
         ->mySoundCallback(input, output, frameCount, timeInfo, statusFlags);
    }
	


private:
    PaStream * stream;
    RtMidiIn * midiIn;
    paTestData myData;
    Ui::MainWindow *ui;
};

#endif // SYNTH_ENGINE_HPP
