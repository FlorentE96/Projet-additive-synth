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
#include "effects.hpp"

class synthEngine
{
public:
    typedef struct
    {
        int16_t left;
        int16_t right;
    }
    paTestData;
    synthEngine();
    ~synthEngine();
    Osc * osc1;
    Filter * filt1;
    ADSR * env1;
    Echo * echo1;
    void mycallback( double deltatime, std::vector< unsigned char > *message);

    static void s_mycallback( double deltatime, std::vector< unsigned char > *message, void *userData )
    {
        ((synthEngine*)userData)->mycallback(deltatime, message);
    }


    int myMemberCallback(const void *input, void *output,
      unsigned long frameCount,
      const PaStreamCallbackTimeInfo* timeInfo,
      PaStreamCallbackFlags statusFlags);

    static int myPaCallback(
      const void *input, void *output,
      unsigned long frameCount,
      const PaStreamCallbackTimeInfo* timeInfo,
      PaStreamCallbackFlags statusFlags,
      void *userData )
    {
      return ((synthEngine*)userData)
         ->myMemberCallback(input, output, frameCount, timeInfo, statusFlags);
    }
	


private:
    PaStream * stream;
    RtMidiIn * midiIn;
    paTestData myData;
};

#endif // SYNTH_ENGINE_HPP
