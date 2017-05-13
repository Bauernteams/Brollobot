#include "mobileplatform.h"

#include <cassert>

MobilePlatform::MobilePlatform(int lMotorPinA, int lMotorPinB, int lMotorPinPwm, float lfFactorRpmToPwm,
                               int rMotorPinA, int rMotorPinB, int rMotorPinPwm, float rfFactorRpmToPwm,
                               int lLineSensorPin, int rLineSensorPin) :
            m_leftMotor(lMotorPinA, lMotorPinB, lMotorPinPwm, lfFactorRpmToPwm),
            m_rightMotor(rMotorPinA, rMotorPinB, rMotorPinPwm, rfFactorRpmToPwm),
            m_leftLineSensor(lLineSensorPin), m_rightLineSensor(rLineSensorPin),
            m_guiSpeed(100) //

{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),
            this, SLOT(slot_update()));
    timer->start(50);   // für Debugzwecke 1s, sollte für die Regelung auf einen niedrigeren Wert gesetzt werden
    //followLine();
}

void MobilePlatform::followLine()
{
    //while(true) {

        float turnSpeed = 50;
        float forwardSpeed = 70;

        m_leftLineSensorIsBlack = m_leftLineSensor.isBlack();
        m_rightLineSensorIsBlack = m_rightLineSensor.isBlack();

        if(m_leftLineSensorIsBlack && !m_rightLineSensorIsBlack)
        {
            //slot_moveDirection(STOP);
            m_guiSpeed = turnSpeed;
            slot_moveDirection(LEFT);

        } else if(m_rightLineSensorIsBlack && !m_leftLineSensorIsBlack)
        {
            //slot_moveDirection(STOP);
            m_guiSpeed = turnSpeed;
            slot_moveDirection(RIGHT);

        } else if(m_leftLineSensorIsBlack && m_rightLineSensorIsBlack)
        {
            // This should never happen!!!
            //std::cerr << "Beide Sensoren zeigen schwarz?! Dulli Roboter" << std::endl;
            //assert(false);
            slot_moveDirection(STOP);

        } else if(!(m_leftLineSensorIsBlack || m_rightLineSensorIsBlack)) {
            m_guiSpeed = forwardSpeed;
            slot_moveDirection(FORWARD);
        } else {
            // Should never happen!!!
            assert(false);
        }

        // Wenn der Bot am Ende der Linie angekommen ist, dann soll er anhalten, irgendwie?! Dirty hack
    //}

}

void MobilePlatform::sendSpeed()
{
    float lMotorSpeed = m_leftMotor.getSpeed();
    float rMotorSpeed = m_rightMotor.getSpeed();
    float vehicleSpeed = sqrt( pow(lMotorSpeed,2) + pow(rMotorSpeed,2));
    emit sgn_sendSpeed(vehicleSpeed);
}

void MobilePlatform::slot_moveDirection(int direction)
{
    switch (direction)
    {
    case FORWARD:
        m_leftMotor.setSpeed(m_guiSpeed);
        m_rightMotor.setSpeed(m_guiSpeed);
        break;

    case BACKWARD:
        m_leftMotor.setSpeed(-m_guiSpeed);
        m_rightMotor.setSpeed(-m_guiSpeed);
        break;

    case LEFT:
        m_leftMotor.setSpeed(0);
        m_rightMotor.setSpeed(m_guiSpeed);
        break;

    case RIGHT:
        m_leftMotor.setSpeed(m_guiSpeed);
        m_rightMotor.setSpeed(0);
        break;

    case STOP:
        m_leftMotor.setSpeed(0);
        m_rightMotor.setSpeed(0);
        break;

    default:
        m_leftMotor.setSpeed(0);
        m_rightMotor.setSpeed(0);
        cout << "Impossible State!!!";
        break;
    }
}

void MobilePlatform::slot_setSpeed(float fSpeed_mps)
{
    m_guiSpeed = fSpeed_mps;
}

void MobilePlatform::slot_followLine(bool followLineIsChecked)
{
    m_FollowingLineIsChecked = followLineIsChecked;
}

void MobilePlatform::slot_checkLineSensors()
{
    m_leftLineSensorIsBlack = m_leftLineSensor.isBlack();
    m_rightLineSensorIsBlack = m_rightLineSensor.isBlack();
    qDebug() << "Sensor states are:" << QStringLiteral("LeftSensor: %1 - RightSensor: %2").arg(m_leftLineSensorIsBlack).arg(m_rightLineSensorIsBlack) << endl;
//    emit sgn_sendText(QStringLiteral("LeftSensor: %1 - RightSensor: %2").arg(m_leftLineSensorIsBlack).arg(m_rightLineSensorIsBlack));
}

void MobilePlatform::slot_update()
{
    if(m_FollowingLineIsChecked)
    {
        followLine();
        m_MachineIsStopped = false;
    } else {
        if(!m_MachineIsStopped)
        {
            slot_moveDirection(STOP);
            m_MachineIsStopped = true;
        }
    }

    slot_checkLineSensors();
    emit sgn_sendSensorData(SensorData(m_leftLineSensorIsBlack, m_rightLineSensorIsBlack));
}
