#include "synth_engine.hpp"



synthEngine::synthEngine()
{
    osc1 = new Osc(wavetable_sine, DEFAULT_FREQ);
    filt1 = new Filter(LPF, 1764, 1.0f, 2);
    env1 = new ADSR;

    midiIn = new RtMidiIn();
    if ( midiIn->getPortCount() == 0 ) {
        std::cout << "No ports available!\n" << endl;
    }
    midiIn->openPort( 0 );
    midiIn->setCallback( &mycallback , NULL);
    midiIn->ignoreTypes( false, false, false );

    Pa_Initialize();
    /* Open an output-only audio stream. */
    Pa_OpenDefaultStream( &stream,
                                0,          /* no input channels */
                                2,          /* stereo output */
                                paInt16,  /* 16 bit int output */
                                SAMPLE_RATE,
                                256,        /* frames per buffer */
                                &synthEngine::myPaCallback, /*routine to execute when audio is needed */
                                this ); /*static structure representing left and right channel samples */

    Pa_StartStream( stream );

}

synthEngine::~synthEngine()
{
    delete osc1;
    delete env1;
    delete filt1;
    delete midiIn;


    Pa_StopStream( stream );
    Pa_CloseStream( stream );
    Pa_Terminate();

}

int synthEngine::myMemberCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags
                                   )
{
    /* Cast data passed through stream to our structure. */
    short* myOut;

    myOut = (short*)outputBuffer;

    for( unsigned int i=0; i<framesPerBuffer; i++ )

    {
          /*************** write samples into ouput buffer (left then right) ******************/

        *myOut++ = myData.left ;
        *myOut++ = myData.right;

              /*************** compute new values ******************/

        //acquire new osc value
        myData.left = (short)((osc1->process()*env1->process())/10);
        myData.left = filt1->filterCompute(myData.left);
        myData.right = myData.left;



    }
    return paContinue;
}

void synthEngine::mycallback( double deltatime, std::vector< unsigned char > *message, void *userData )
{
  unsigned int nBytes = message->size();
  for ( unsigned int i=0; i<nBytes; i++ )
    std::cout << "Byte " << i << " = " << (int)message->at(i) << ", ";
  if ( nBytes > 0 )
    std::cout << "stamp = " << deltatime << std::endl;
}
