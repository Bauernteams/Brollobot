#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "sensordata.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    enum {STOP, FORWARD, RIGHT, BACKWARD, LEFT};
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void sgn_moveDirection(int direction);
    void sgn_setSpeed(float fSpeed_mps);
    void sgn_followLine(bool followLine);

private slots:
    void getMobilePlatformSpeed(int Speed);
    void outputMessageText(QString msg);

    void on_btnForward_pressed();
    void on_btnForward_released();
    void on_btnRight_pressed();
    void on_btnBackward_pressed();
    void on_btnLeft_pressed();

    void on_btnStartStop_clicked(bool state);

    void on_btnRight_released();
    void on_btnBackward_released();
    void on_btnLeft_released();

    void slot_sensorDataUpdate(SensorData);

    void on_spinSpeed_valueChanged(int arg1);

    void on_spinSpeed_editingFinished();

    void on_chbFollowLine_toggled(bool checked);

    void on_actionQuit_triggered();

private:
    Ui::MainWindow *ui;
    void pushButtonsEnable(bool enable);
    void chbFollowLineEnable(bool enable);
    void chbLineSensorsEnable(bool enable);
};

#endif // MAINWINDOW_H
