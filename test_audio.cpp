#include <cstdint>
#include <cmath>
#include "portaudio.h"
#include "oscillators.hpp"
#include "global.hpp"
#include "LUTs.hpp"
#include "filter.hpp"

#define NUM_SECONDS   (3)

typedef struct
{
    uint16_t left;
    uint16_t right;
}
paTestData;

Osc* sine;
Filter* LP;


static int patestCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData )
{
    /* Cast data passed through stream to our structure. */
    paTestData *data = (paTestData*)userData;
    uint16_t *out = (uint16_t*)outputBuffer;


    for( unsigned int i=0; i<framesPerBuffer; i++ )

    {

    // write samples into ouput buffer (left then right)
    *out++ = data->left;
    *out++ = data->right;

    /*out++;
    *out = data->left;
    out++;
    *out = data->right;*/


		// compute new values
		data->left = sine->process();
    //data->left = LP->filterCompute(data->left);

    //sine->setFrequency(i);
    data->right = data->left;




    }
    return 0;
}


static paTestData data;

int main(void){
    data.left = 0;
    data.right = 0;

    sine = new Osc();
    sine->setFrequency(2000);

    LP = new Filter(LPF, 220, 1.0f, 2);

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

    Pa_Sleep(NUM_SECONDS*1000); /*streaming duration*/

    Pa_StopStream( stream );

    Pa_CloseStream( stream );

    Pa_Terminate();

    return 0;
}
