#include "controlsystem.h"

ControlSystem::ControlSystem(MobilePlatform *mobilePlatform, MainWindow *mainWindow, QObject *parent) :
    QObject(parent)
{
    m_mobilePlatform = mobilePlatform;
    m_mainWindow = mainWindow;
    setupConnection();
}

void ControlSystem::setupConnection()
{
    connect(m_mainWindow, SIGNAL(sgn_moveDirection(int)),
            m_mobilePlatform, SLOT(slot_moveDirection(int)) ); // connecting gui Button with MobilePlatform

    connect(m_mainWindow, SIGNAL(sgn_setSpeed(float)),
            m_mobilePlatform, SLOT(slot_setSpeed(float)));

    connect(m_mainWindow, SIGNAL(sgn_followLine(bool)),
            m_mobilePlatform, SLOT(slot_followLine(bool)));

    connect(m_mobilePlatform, SIGNAL(sgn_sendSensorData(SensorData)),
            m_mainWindow, SLOT(slot_sensorDataUpdate(SensorData)));

    connect(m_mobilePlatform, SIGNAL(sgn_sendSpeed(float)),
            m_mainWindow, SLOT(getMobilePlatformSpeed(float)));

    connect(m_mobilePlatform, SIGNAL(sgn_sendText(QString)),
            m_mainWindow, SLOT(outputMessageText(QString)));

}
