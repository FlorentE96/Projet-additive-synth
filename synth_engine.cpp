#include "synth_engine.hpp"

synth_engine::synth_engine()
{
    osc1 = new Osc(wavetable_saw3, DEFAULT_FREQ);
    filt1 = new Filter(LPF, 1764, 1.0f, 2);
    env1 = new ADSR;

    Pa_Initialize();

    /* Open an output-only audio stream. */
    Pa_OpenDefaultStream( &stream,
                                0,          /* no input channels */
                                2,          /* stereo output */
                                paInt16,  /* 16 bit int output */
                                SAMPLE_RATE,
                                256,        /* frames per buffer */
                                patestCallback, /*routine to execute when audio is needed */
                                &myData ); /*static structure representing left and right channel samples */

    Pa_StartStream( stream );
}

synth_engine::~synth_engine()
{
    delete osc1;
    delete env1;
    delete myFilter;

    Pa_StopStream( stream );
    Pa_CloseStream( stream );
    Pa_Terminate();
}
