#include <iostream>
#include <cmath>

#include <wiringPi.h>
#include <softPwm.h>

#include "tools.h"

using namespace std;
#ifndef DCMOTOR_H
#define DCMOTOR_H

#endif // DCMOTOR_H



class DcMotor
{
    enum {BACKWARD, FORWARD};

    public:
        //DcMotor(string fNameMotor, int nSpeed);
        DcMotor(int nPinA, int nPinB, int nPinPwm,
                float fFactorRpmToPwm, float fSpeed=0,
                float fMotorVoltage_Max=6, float fMotorDriverVoltage_Max=9);

        // TODO Somehow Voltage of Motor is musch too high!!!

        ~DcMotor();

        // Setters
        void  setSpeed(float fSpeed_rpm);            // Set rotation speed in RPM
        void  setDirection(bool direction=FORWARD);
        void  setSpeedAbs(float fSpeed_rpm);
        void  setFactorRpmToPwm(float fFactorRpmToPwm);

        // Getters
        float getSpeed();
        bool  getDirection();
        float getFactorRpmToPwm();
        bool  isRunning();


        // Public Methods
        void stop();


    private:
        // Private Attributes
         // Properties
        int   m_nPinA;
        int   m_nPinB;
        int   m_nPinPwm;

        float m_fFactorRpmToVoltage;
        float m_fFactorVoltageToPwm;

        float m_fMotorVoltage_Max;
        float m_fMotorDriverVoltage_Max;
        float m_nPwmMax;

         // Status
        float m_fSpeed_rpm;
        bool  m_bDirection;



        // Private Methods
        bool initAttributes(float fFactorRpmToVoltage, float fMotorVoltage_Max, float fMotorDriverVoltage_Max, int nPwmMax=255);          //TODO
        bool initPins(int nPinA, int nPinB, int nPinPwm);

        bool actionMotor();

        //helper functions
        float convertRpmToVolts(float fSpeed_rpm);
        int convertVoltsToPwm(float fMotorVoltage);
};
