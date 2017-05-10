#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QShortcut>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // GUI initialisieren
    ui->setupUi(this);
    pushButtonsEnable(false);
    emit sgn_setSpeed(50);
//    // Set Shortcuts
//    QShortcut *scForward = new QShortcut(QKeySequence(Qt::UpArrow), parent);
//    connect(scForward, SIGNAL(activated()),
//            ui->btnForward, SLOT(click()));
}

MainWindow::~MainWindow()
{
    delete ui;
    emit sgn_moveDirection(STOP);
}

void MainWindow::getMobilePlatformSpeed(int Speed)
{
    QString msg = QStringLiteral("Set speed to % \n").arg(Speed);
    ui->txtOutput->appendPlainText(msg);
}

//! Output a Text
void MainWindow::outputMessageText(QString msg)
{
    ui->txtOutput->appendPlainText(msg); // schreibt in der GUI den string text in das label-Fenster
}


//! Forward

void MainWindow::on_btnForward_pressed()
{
    emit sgn_moveDirection(FORWARD);
    outputMessageText("Move Forward");
}

void MainWindow::on_btnForward_released()
{
    emit sgn_moveDirection(STOP);

}

//! Right
void MainWindow::on_btnRight_pressed()
{
    emit sgn_moveDirection(RIGHT);
    outputMessageText("Turn Right");
}

void MainWindow::on_btnRight_released()
{
    emit sgn_moveDirection(STOP);
}

//! Backward
void MainWindow::on_btnBackward_pressed()
{
   emit sgn_moveDirection(BACKWARD);
   outputMessageText("Move Backward");
}

void MainWindow::on_btnBackward_released()
{
    emit sgn_moveDirection(STOP);

}

//! Left
void MainWindow::on_btnLeft_pressed()
{
    emit sgn_moveDirection(LEFT);
    outputMessageText("Turn Left");
}

void MainWindow::on_btnLeft_released()
{
    emit sgn_moveDirection(STOP);

}

//! Activate
void MainWindow::on_btnStartStop_clicked(bool state)
{

    if(!state)
    {
        pushButtonsEnable(false);
        emit sgn_moveDirection(STOP);
    }
    else
    {
        pushButtonsEnable(true);
    }
//    ui->btnStartStop->setText(text);
}

//! Enable PushButtons
void MainWindow::pushButtonsEnable(bool enable)
{
    ui->btnForward->setEnabled(enable);
    ui->btnRight->setEnabled(enable);
    ui->btnBackward->setEnabled(enable);
    ui->btnLeft->setEnabled(enable);

//    if(!enable)
//    {
//        ui->spinSpeed->setValue(0);
//    }
}


//! Define and change Speed
void MainWindow::on_spinSpeed_valueChanged(int arg1)
{

    emit sgn_setSpeed(arg1);
    outputMessageText(QStringLiteral("Set Speed to %1").arg(arg1));
}

void MainWindow::on_spinSpeed_editingFinished()
{
    outputMessageText("Editing Finished");
}

void MainWindow::on_chbFollowLine_toggled(bool checked)
{
    emit sgn_followLine(checked);
    if(checked)
    {
        outputMessageText(QStringLiteral("Start following the line").arg(checked));
    } else {
        outputMessageText(QStringLiteral("Stop following the line").arg(checked));
    }
}

void MainWindow::slot_sensorDataUpdate(SensorData data)
{
    ui->chbLeftSensor->setChecked(data.LeftSensorIsBlack);
    ui->chbRightSensor->setChecked(data.RightSensorIsBlack);
}
