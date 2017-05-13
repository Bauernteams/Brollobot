#include <iostream>
#include <wiringPi.h>

#include "linesensor.h"

LineSensor::LineSensor(int nPin)
{
    this->initPins(nPin);
}

LineSensor::~LineSensor()
{

}

bool LineSensor::initPins(int nPin)
{
    wiringPiSetup();
    m_nPin   = nPin;
    pinMode(m_nPin, INPUT);
    return true;
}

bool LineSensor::isBlack()
{
    return digitalRead(m_nPin);
}
