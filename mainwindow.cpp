#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

static paTestData myData;

static int patestCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData );

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
                                &myData ); /*static structure representing left and right channel samples */

    Pa_StartStream( stream );

    ui->oscPitchDial->setMaximum(3000);
    ui->oscPitchDial->setMinimum(50);

    ui->filterCutoffDial->setMaximum(3000);
    ui->filterCutoffDial->setMinimum(50);

    ui->filterQDial->setMaximum(1000);
    ui->filterQDial->setMinimum(100);

    ui->attackSlider->setMaximum(150);
    ui->decaySlider->setMaximum(150);
    ui->releaseSlider->setMaximum(150);
    ui->sustainSlider->setMaximum(100);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_oscPitchDial_sliderMoved(int position)
{
    osc1->setFrequency(position);
    ui->lcdnumber->display(position);
}

void MainWindow::on_filterCutoffDial_sliderMoved(int position)
{
    myFilter->setFc(position);
    ui->lcdCutoff->display(position);
}

void MainWindow::on_filterQDial_sliderMoved(int position)
{
    myFilter->setQ(position/100);
    ui->lcdRes->display(position/100);
}

void MainWindow::on_attackSlider_sliderMoved(int position)
{
    env1->setAttackTime(position/100);
}

void MainWindow::on_decaySlider_sliderMoved(int position)
{
    env1->setDecayTime(position/100);
}

void MainWindow::on_sustainSlider_sliderMoved(int position)
{
    env1->setSustainLevel(position/100);
}

void MainWindow::on_releaseSlider_sliderMoved(int position)
{
    env1->setReleaseTime(position/100);
}

void MainWindow::on_radioButton_toggled(bool checked)
{
    if(checked)
        myFilter->setType(LPF);
}

void MainWindow::on_radioButton_2_toggled(bool checked)
{
    if(checked) {
        myFilter->setType(BPF);
        myFilter->setBandwidth(100);
    }
}

void MainWindow::on_radioButton_3_toggled(bool checked)
{
    if(checked)
        myFilter->setType(HPF);
}

void MainWindow::on_radioButton_4_toggled(bool checked)
{
    if(checked)
        myFilter->setOrder(2);
}

void MainWindow::on_radioButton_5_toggled(bool checked)
{
    if(checked)
        myFilter->setOrder(4);
}

void MainWindow::keyPressEvent(QKeyEvent* e)
{
    env1->gate(ON);
    //e->text();
}

void MainWindow::keyReleaseEvent(QKeyEvent* e)
{
    env1->gate(OFF);
    //e->text();
}

void MainWindow::on_pushButton_clicked()
{

}


static int patestCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData )
{
    /* Cast data passed through stream to our structure. */
    paTestData *data = (paTestData*)userData;
    int16_t *out = (int16_t*)outputBuffer;

    (void)inputBuffer;
    (void)timeInfo;
    (void)statusFlags;


    for( unsigned int i=0; i<framesPerBuffer; i++ )

    {
      /*************** write samples into ouput buffer (left then right) ******************/

    *out++ = data->left;
    *out++ = data->right;

          /*************** compute new values ******************/

    //acquire new osc value
    data->left = 0;

    data->right = data->left;



    }
    return 0;
}
