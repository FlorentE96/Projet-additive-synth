#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdint>
#include "global.hpp"
#include "oscillators.hpp"
#include "LUTs.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    osc1_ptr = new Osc(wavetable_saw3, DEFAULT_FREQ);
    ui->oscPitchDial->setMaximum(3000);
    ui->oscPitchDial->setMinimum(50);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_oscPitchDial_sliderMoved(int position)
{
    osc1_ptr->setFrequency(position);
}
