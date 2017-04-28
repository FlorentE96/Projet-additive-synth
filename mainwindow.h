#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QMessageBox>
#include <cstdint>
#include <cmath>
#include <ctime>
#include <iostream>
#include <fstream>

namespace Ui {
class MainWindow;
}

//#include "synth_engine.hpp"
class synthEngine;

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

    void on_selectSine_toggled(bool checked);

    void on_selectSaw3_toggled(bool checked);

    void on_echoStatus_stateChanged(int arg1);

    void on_echoDelay_sliderMoved(int position);

    void on_echoFb_sliderMoved(int position);

    void on_echoDryWet_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    synthEngine * synth;
};

#endif // MAINWINDOW_H
