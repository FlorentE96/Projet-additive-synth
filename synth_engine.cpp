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
    else{
        midiIn->openPort( 0 );
        midiIn->setCallback( &synthEngine::s_mycallback, (void *)this);
        midiIn->ignoreTypes( false, false, false );
    }

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

void synthEngine::mycallback( double deltatime, std::vector< unsigned char > *message )
{
//  unsigned int nBytes = message->size();
//  for ( unsigned int i=0; i<nBytes; i++ )
//    std::cout << "Byte " << i << " = " << (int)message->at(i) << ", ";
//  if ( nBytes > 0 )
//    std::cout << "stamp = " << deltatime << std::endl;

  uint32_t id_key = (uint32_t)message->at(0);
  uint32_t id_note = (uint32_t)message->at(1);
  uint32_t value = (uint32_t)message->at(2);

  if(id_key == 144){ //Press Key
        uint32_t frequency;
        if (id_note < 69){
            frequency = (uint32_t)(1/pow(2, ((double)(69-id_note))/((double)12) )*440.0f);
        }
        else{
            frequency = (uint32_t)(pow(2, ((double)(id_note-69))/((double)12) )*440.0f);
        }
        cout << "ID : " << id_note <<" | Freq : "<< frequency << endl;
        osc1->setFrequency(frequency);
        env1->gate(ON);
  }
  else if(id_key == 128){ //Release Key
        env1->gate(OFF);
  }

  else if(id_key == 176){ //Potentiometer or other button
      if(id_note == 8 ){
          uint32_t f = (uint32_t)(((float)3000/128)*value);
          if (f<1) f=1;
          filt1->setFc(f);
      }
      else if (id_note == 9){
          float q = ((float)10/128)*value;
          if (q < 1.0f) q=1.0f;
          filt1->setQ(q );
      }
  }
}
