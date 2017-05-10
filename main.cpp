#include "controlsystem.h"
#include "mobileplatform.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    //                  WiringPI: GPIO:
    #define MotorR_1     0        //17
    #define MotorR_2     2        //27
    #define MotorR_PWM   3        //22
    #define MotorL_1    12        //10
    #define MotorL_2    13        //9
    #define MotorL_PWM  14        //11
    #define LineSensorL  28        //20
    #define LineSensorR  29        //21

    float fFactorMpsToVolts = 1.0 / 50;

    MobilePlatform mobilePlatform(MotorL_1,MotorL_2,MotorL_PWM,fFactorMpsToVolts,
                                  MotorR_1,MotorR_2,MotorR_PWM,fFactorMpsToVolts,
                                  LineSensorL, LineSensorR); // UMBEDINGT ERSETZEN DURCH PINS AUF DEM PI
    MainWindow mainWindow;
    ControlSystem controlSystem(&mobilePlatform, &mainWindow);
    mainWindow.show();


    return a.exec();
}
