#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdint>
#include "global.hpp"
#include "oscillators.hpp"
#include "ADSR.hpp"
#include "LUTs.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    osc1 = new Osc(wavetable_saw3, DEFAULT_FREQ);
    myFilter = new Filter(LPF, 1764, 1.0f, 2);
    env1 = new ADSR;
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
