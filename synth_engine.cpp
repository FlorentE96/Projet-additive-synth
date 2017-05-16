#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "synth_engine.hpp"

synthEngine::synthEngine(Ui::MainWindow *_ui)
{
    osc1 = new Osc(wavetable_sine, DEFAULT_FREQ);
    filt1 = new Filter(LPF, 1764, 1.0f, 2);
    env1 = new ADSR;
    echo1 = new Echo();
    ui = _ui;

    midiIn = new RtMidiIn();
    if ( midiIn->getPortCount() == 0 ) {
        std::cout << "No ports available!\n" << endl;
    }
    else{
        midiIn->openPort( 0 );
        midiIn->setCallback( &synthEngine::myStaticMidiCallback, (void *)this);
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
                                &synthEngine::myStaticSoundCallback, /*routine to execute when audio is needed */
                                this ); /*static structure representing left and right channel samples */

    Pa_StartStream( stream );

}

synthEngine::~synthEngine()
{
    delete osc1;
    delete env1;
    delete filt1;
    delete echo1;
    delete midiIn;


    Pa_StopStream( stream );
    Pa_CloseStream( stream );
    Pa_Terminate();

}

int synthEngine::mySoundCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags
                                   )
{
    /* Cast data passed through stream to our structure. */
    uint16_t* myOut;
    (void) inputBuffer;
    (void) timeInfo;
    (void) statusFlags;
    myOut = (uint16_t*)outputBuffer;

    for( unsigned int i=0; i<framesPerBuffer; i++ )

    {
          /*************** write samples into ouput buffer (left then right) ******************/

        *myOut++ = myData.left ;
        *myOut++ = myData.right;

              /*************** compute new values ******************/

        //acquire new osc value
        myData.left = (uint16_t)((osc1->process()*env1->process())/10);
        myData.left = (uint16_t)echo1->process(myData.left);
        myData.left = filt1->filterCompute(myData.left);
        myData.right = myData.left;



    }
    return paContinue;
}

void synthEngine::myMidiCallback( double deltatime, std::vector< unsigned char > *message )
{
  static uint32_t gate = 0;
  static uint32_t freq_buf[10];

  uint32_t id_key = (uint32_t)message->at(0);
  uint32_t id_note = (uint32_t)message->at(1);
  uint32_t value = (uint32_t)message->at(2);
  (void) deltatime;
  if(id_key == 144){ //Press Key
        gate++;

        uint32_t frequency;
        if (id_note < 69){
            frequency = (uint32_t)(1/pow(2, ((double)(69-id_note))/((double)12) )*440.0f);
        }
        else{
            frequency = (uint32_t)(pow(2, ((double)(id_note-69))/((double)12) )*440.0f);
        }
        //cout << "ID : " << id_note <<" | Freq : "<< frequency << endl;
        freq_buf[gate-1] = frequency;
        cout << gate << endl;
        cout << freq_buf[gate-1] << endl;
        osc1->setFrequency(freq_buf[gate-1]);
        env1->gate(ON);
  }
  else if(id_key == 128){ //Release Key
        gate--;
        if(gate == 0)
            env1->gate(OFF);
        else
            osc1->setFrequency(freq_buf[gate-1]);

  }

  else if(id_key == 176){ //Potentiometer or other button
      if(id_note == 8 ){
          uint32_t f = (uint32_t)scale(value, 0, 127, ui->filterCutoffDial->minimum(), ui->filterCutoffDial->maximum());
          ui->filterCutoffDial->setValue(f);
      }
      else if (id_note == 9){
          float q = scale(value, 0, 127, ui->filterQDial->minimum() , ui->filterQDial->maximum());
          ui->filterQDial->setValue((int)q);
          //filt1->setQ(q );
      }
      else if(id_note == 13){
          float q = scale(value, 0, 127, ui->attackSlider->minimum() , ui->attackSlider->maximum());
          ui->attackSlider->setValue((int)q);
      }
      else if(id_note == 14){
          float q = scale(value, 0, 127, ui->decaySlider->minimum() , ui->decaySlider->maximum());
          ui->decaySlider->setValue((int)q);
      }
      else if(id_note == 15){
          float q = scale(value, 0, 127, ui->sustainSlider->minimum() , ui->sustainSlider->maximum());
          ui->sustainSlider->setValue((int)q);
      }
      else if(id_note == 7){
          float q = scale(value, 0, 127, ui->releaseSlider->minimum() , ui->releaseSlider->maximum());
          ui->releaseSlider->setValue((int)q);
      }
  }
}
