#ifndef SYNTH_ENGINE_HPP
#define SYNTH_ENGINE_HPP

#include "global.hpp"
#include "LUTs.hpp"
#include "oscillators.hpp"
#include "filter.hpp"
#include "ADSR.hpp"

class synth_engine
{
public:
    typedef struct
    {
        int16_t left;
        int16_t right;
    }
    paTestData;
    synth_engine();
    Osc * osc1;
    Filter * filt1;
    ADSR * env1;

private:
    PaStream *stream;
    static paTestData myData;
};

#endif // SYNTH_ENGINE_HPP
