#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "oscillators.hpp"
#include "ADSR.hpp"
#include "filter.hpp"

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

private:
    Ui::MainWindow *ui;
    Osc* osc1;
    Filter* myFilter;
    ADSR* env1;
};

#endif // MAINWINDOW_H
