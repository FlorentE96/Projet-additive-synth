#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QMessageBox>
#include <cstdint>
#include <cmath>
#include <iostream>
#include <fstream>
#include "portaudio.h"
#include "global.hpp"
#include "oscillators.hpp"
#include "LUTs.hpp"
#include "filter.hpp"
#include "ADSR.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_oscPitchDial_sliderMoved(int position);

    void on_filterCutoffDial_sliderMoved(int position);

    void on_filterQDial_sliderMoved(int position);

    void on_attackSlider_sliderMoved(int position);

    void on_decaySlider_sliderMoved(int position);

    void on_sustainSlider_sliderMoved(int position);

    void on_releaseSlider_sliderMoved(int position);

    void on_radioButton_toggled(bool checked);

    void on_radioButton_2_toggled(bool checked);

    void on_radioButton_3_toggled(bool checked);

    void on_radioButton_4_toggled(bool checked);

    void on_radioButton_5_toggled(bool checked);

    void keyPressEvent(QKeyEvent* e);

    void keyReleaseEvent(QKeyEvent* e);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
