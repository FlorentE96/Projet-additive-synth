#include <cstdint>
#include <cmath>
#include "portaudio.h"
#include "oscillators.hpp"
#include "global.hpp"
#include "LUTs.hpp"
#include "filter.hpp"

#define NUM_SECONDS   (1)

typedef struct
{
    int16_t left;
    int16_t right;
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
    int16_t *out = (int16_t*)outputBuffer;


    for( unsigned int i=0; i<framesPerBuffer; i++ )

    {
      /*************** write samples into ouput buffer (left then right) ******************/

    *out++ = data->left;
    *out++ = data->right;

		  /*************** compute new values ******************/

    //acquire new osc value
		data->left = (int16_t)(sine->process()/10);

    //filtering
    data->left = LP->filterCompute(data->left);

    data->right = data->left;



    }
    return 0;
}


static paTestData data;

int main(void){
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

    while(j<4){

      if(j==0){
        LP->setFc(300);
        LP->setQ(1.0f);
      }
      else if (j==1){
        LP->setFc(500);
        LP->setQ(3.0f);
      }
      else if (j==2){
        LP->setFc(800);
        LP->setQ(6.0f);
      }
      else{
        LP->setFc(1000);
        LP->setQ(10.0f);
      }

      for(unsigned int i = 0; i < NUM_SECONDS*1000; i++){

        sine->setFrequency(i);
        Pa_Sleep(1);    //sleeping time in ms

      }

      for(unsigned int i = NUM_SECONDS*1000; i>0; i--){

        sine->setFrequency(i);
        Pa_Sleep(1);

      }
      j++;
    }




    Pa_StopStream( stream );

    Pa_CloseStream( stream );

    Pa_Terminate();

    return 0;
}
