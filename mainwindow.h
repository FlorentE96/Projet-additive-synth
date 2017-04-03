#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
    //Osc* osc1_ptr;
};

#endif // MAINWINDOW_H
