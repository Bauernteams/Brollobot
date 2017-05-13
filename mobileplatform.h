#ifndef MOBILEPLATFORM_H
#define MOBILEPLATFORM_H

#include "dcmotor.h"
#include "linesensor.h"
#include "sensordata.h"
#include <cmath>

#include <QObject>
#include <QDebug>

class MobilePlatform : public QObject
{

    enum {STOP, FORWARD, RIGHT, BACKWARD, LEFT};
    Q_OBJECT
public:
    explicit MobilePlatform(int lMotorPinA, int lMotorPinB, int lMotorPinPwm, float lfFactorRpmToPwm,
                            int rMotorPinA, int rMotorPinB, int rMotorPinPwm, float rfFactorRpmToPwm,
                            int lLineSensorPin, int rLineSensorPin);

    MobilePlatform(const MobilePlatform& m);

    void followLine();
private:
    DcMotor m_leftMotor;
    DcMotor m_rightMotor;
    LineSensor m_leftLineSensor;
    LineSensor  m_rightLineSensor;

    float m_guiSpeed;

    void sendSpeed();
    bool m_leftLineSensorIsBlack;
    bool m_rightLineSensorIsBlack;

    bool m_FollowingLineIsChecked;
    bool m_MachineIsStopped;
signals:
    void sgn_sendSpeed(int);
    void sgn_sendText(QString);
    void sgn_sendSensorData(SensorData);

public slots:
    void slot_moveDirection(int direction);
    void slot_setSpeed(float fSpeed_mps);
    void slot_followLine(bool followLine);

    void slot_update();

    void slot_checkLineSensors();

};

#endif // MOBILEPLATFORM_H
