#include "mainwindow.h"
#include "synth_engine.hpp"
#include "ui_mainwindow.h"

using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    synth = new synthEngine(ui);
    synth->env1->gate(OFF);

    ui->setupUi(this);


    ui->filterCutoffDial->setMaximum(3000);
    ui->filterCutoffDial->setMinimum(20);
    ui->filterCutoffDial->setValue(1000);

    ui->filterQDial->setMaximum(1000);
    ui->filterQDial->setMinimum(101);
    ui->filterQDial->setValue(102);

    ui->attackSlider->setMaximum(150);
    ui->decaySlider->setMaximum(10);
    ui->releaseSlider->setMaximum(150);
    ui->sustainSlider->setMaximum(1000);

    ui->echoDelay->setMaximum(1000);
    ui->echoDelay->setMinimum(10);
    ui->echoDelay->setValue(500);

    ui->echoFb->setMaximum(1000);
    ui->echoFb->setMinimum(10);
    ui->echoFb->setValue(500);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_radioButton_toggled(bool checked)
{
    if(checked)
        synth->filt1->setType(LPF);
}

void MainWindow::on_radioButton_2_toggled(bool checked)
{
    if(checked) {
        synth->filt1->setBandwidth(100);
        synth->filt1->setType(BPF);

    }
}

void MainWindow::on_radioButton_3_toggled(bool checked)
{
    if(checked)
        synth->filt1->setType(HPF);
}

void MainWindow::on_radioButton_4_toggled(bool checked)
{
    if(checked)
        synth->filt1->setOrder(2);
}

void MainWindow::on_radioButton_5_toggled(bool checked)
{
    if(checked)
        synth->filt1->setOrder(4);
}

void MainWindow::keyPressEvent(QKeyEvent* e)
{
    if(!(e->isAutoRepeat()))
        synth->env1->gate(ON);
    //e->text();
}

void MainWindow::keyReleaseEvent(QKeyEvent* e)
{
    if(!(e->isAutoRepeat()))
        synth->env1->gate(OFF);
    //e->text();
}


void MainWindow::on_selectSine_toggled(bool checked)
{
    if(checked)
        synth->osc1->setWF(wavetable_sine);
}

void MainWindow::on_selectSaw3_toggled(bool checked)
{
    if(checked)
        synth->osc1->setWF(wavetable_saw3);
}

void MainWindow::on_echoStatus_stateChanged(int arg1)
{
    if(arg1) synth->echo1->setStatus(ON);
    else synth->echo1->setStatus(OFF);
}


void MainWindow::on_filterCutoffDial_valueChanged(int value)
{
    synth->filt1->setFc((uint32_t)value);
    ui->lcdCutoff->display(value);

}

void MainWindow::on_filterQDial_valueChanged(int value)
{
     synth->filt1->setQ(((double)value/100));
     ui->lcdRes->display((double)value/100);
}




void MainWindow::on_attackSlider_valueChanged(int value)
{
    synth->env1->setAttackTime((double)value/100);
}

void MainWindow::on_decaySlider_valueChanged(int value)
{
    synth->env1->setDecayTime((double)value/100);
}

void MainWindow::on_sustainSlider_valueChanged(int value)
{
    synth->env1->setSustainLevel((double)value/1000);
}

void MainWindow::on_releaseSlider_valueChanged(int value)
{
    synth->env1->setReleaseTime((double)value/100);
}


void MainWindow::on_echoDelay_valueChanged(int value)
{
    synth->echo1->setDelayTime((double)value/1000);
}

void MainWindow::on_echoFb_valueChanged(int value)
{
    synth->echo1->setFeedbackGain((double)value/1000);
}

void MainWindow::on_echoDryWet_valueChanged(int value)
{
    (void) value;
}

