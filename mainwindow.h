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

class synthEngine;

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

    void on_filterCutoffDial_valueChanged(int value);

    void on_filterQDial_valueChanged(int value);

    void on_oscPitchDial_valueChanged(int value);

    void on_attackSlider_valueChanged(int value);

    void on_decaySlider_valueChanged(int value);

    void on_sustainSlider_valueChanged(int value);

    void on_echoDelay_valueChanged(int value);

    void on_echoFb_valueChanged(int value);

    void on_echoDryWet_valueChanged(int value);

    void on_releaseSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    synthEngine * synth;
};

#endif // MAINWINDOW_H
