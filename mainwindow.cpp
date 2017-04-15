#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->oscPitchDial->setMaximum(3000);
    ui->oscPitchDial->setMinimum(50);
    ui->oscPitchDial->setValue(440);

    ui->filterCutoffDial->setMaximum(3000);
    ui->filterCutoffDial->setMinimum(50);
    ui->filterCutoffDial->setValue(3000);

    ui->filterQDial->setMaximum(1000);
    ui->filterQDial->setMinimum(101);
    ui->filterQDial->setValue(102);

    ui->attackSlider->setMaximum(150);
    ui->decaySlider->setMaximum(150);
    ui->releaseSlider->setMaximum(150);
    ui->sustainSlider->setMaximum(1000);

    synth = new synthEngine();
    synth->env1->gate(OFF);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_oscPitchDial_sliderMoved(int position)
{
    synth->osc1->setFrequency((uint32_t)position);
    ui->lcdnumber->display(position);
}

void MainWindow::on_filterCutoffDial_sliderMoved(int position)
{
    synth->filt1->setFc((uint32_t)position);
    ui->lcdCutoff->display(position);
}

void MainWindow::on_filterQDial_sliderMoved(int position)
{
    synth->filt1->setQ((float)position/100);
    ui->lcdRes->display((float)position/100);
}

void MainWindow::on_attackSlider_sliderMoved(int position)
{
    synth->env1->setAttackTime((float)position/100);
}

void MainWindow::on_decaySlider_sliderMoved(int position)
{
    synth->env1->setDecayTime((float)position/100);
}

void MainWindow::on_sustainSlider_sliderMoved(int position)
{
    synth->env1->setSustainLevel((float)position/1000);
}

void MainWindow::on_releaseSlider_sliderMoved(int position)
{
    synth->env1->setReleaseTime((float)position/100);
}

void MainWindow::on_radioButton_toggled(bool checked)
{
    if(checked)
        synth->filt1->setType(LPF);
}

void MainWindow::on_radioButton_2_toggled(bool checked)
{
    if(checked) {
        synth->filt1->setType(BPF);
        synth->filt1->setBandwidth(100);
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
