#include "dcmotor.h"



using namespace std;


//DcMotor::DcMotor(string fNameMotor, int nSpeed)
//{
//    enum {BW, FW};

//    // Read constant Constructor Data from Motor File
//    ofstream fileMotor;
//    fileMotor.open(fNameMotor);

//    // Init Variables to read from Motor File
//    int nPinA, nPinB, nPinPwm;
//    float nKFactor;

//    fileMotor >> nPinA >> nPinB >> nPinPwm >> nKFactor;

//    fileMotor.close();
//    DcMotor::DcMotor(nPinA, nPinB, nPinPwm, nKFactor, nSpeed);

//}

DcMotor::DcMotor(int nPinA, int nPinB, int nPinPwm,
                 float fFactorRpmToVoltage, float fSpeed,
                 float fMotorVoltage_Max, float fMotorDriverVoltage_Max)
{

    this->initAttributes(fFactorRpmToVoltage, fMotorVoltage_Max, fMotorDriverVoltage_Max);
    this->initPins(nPinA, nPinB, nPinPwm);
    this->setSpeed(fSpeed);
}

DcMotor::~DcMotor()
{
    //! Destructor stops Motor and deletes Object
    this->stop();
}

bool DcMotor::initAttributes(float fFactorRpmToVoltage, float fMotorVoltage_Max, float fMotorDriverVoltage_Max, int nPwmMax)
{
    // Attributes defining Rpm to MotorVoltage to PmwOutput Conversion
    m_fFactorRpmToVoltage     = fFactorRpmToVoltage;
    m_fMotorVoltage_Max       = fMotorVoltage_Max;
    m_fMotorDriverVoltage_Max = fMotorDriverVoltage_Max;

    m_nPwmMax = nPwmMax;

    m_fFactorVoltageToPwm = m_nPwmMax / m_fMotorDriverVoltage_Max;

    cout << m_fFactorRpmToVoltage << " " << m_fFactorVoltageToPwm << endl;

    return true;
}

bool DcMotor::initPins(int nPinA, int nPinB, int nPinPwm)
{
    wiringPiSetup();

    // Initialize Pins
    m_nPinA   = nPinA;
    m_nPinB   = nPinB;
    m_nPinPwm = nPinPwm;


    cout << "Motor initiated with Pins:" << m_nPinA << " " << m_nPinB << " " << m_nPinPwm << endl;

    pinMode(m_nPinA  , OUTPUT);
    pinMode(m_nPinB  , OUTPUT);

    // Set up PWM Pin for Motor
    // Due to max DcMotor voltage of 6V, but 7.2V from Motor Driver 100/120 has to be max PWM Power
    pinMode(m_nPinPwm, PWM_OUTPUT);
    softPwmCreate(m_nPinPwm, 0, m_nPwmMax);     // Define PWM Range (usually 8-bit [0, 255])

    return true;
}

//OBSOLETE
/*
void DcMotor::setMotorPins(int pinAValue, int pinBValue, int pinPwmValue)
{
    // Missing
    cout << pinAValue << pinBValue << pinPwmValue << endl;
}*/


bool DcMotor::actionMotor()
{
    // Convert Speed in RPM to PWM Output (via MotorVoltage equivalent)
    float fMotorVoltage = convertRpmToVolts(m_fSpeed_rpm);
    fMotorVoltage = clip(fMotorVoltage, m_fMotorVoltage_Max, 0);
    int nPwm = convertVoltsToPwm(fMotorVoltage);

    // Clip for safety of Motor
    nPwm = clip(nPwm, m_fMotorVoltage_Max/m_fMotorDriverVoltage_Max * m_nPwmMax, 0);

    // Set Pins Output
    softPwmWrite(m_nPinPwm, nPwm);      // Set Pwm to Pin

    // Set Direction-Pins FW or BW
    switch (m_bDirection)
    {
    case FORWARD:
        digitalWrite(m_nPinA, HIGH);
        digitalWrite(m_nPinB, LOW);
        break;

    case BACKWARD:
        digitalWrite(m_nPinA, LOW);
        digitalWrite(m_nPinB, HIGH);
        break;

    default:
        cout << "Impossible State!!!";
        break;
    }

    cout << "Motor run at speed " << m_fSpeed_rpm << " =Volt=> " << fMotorVoltage <<
            " =PWM=> " << nPwm << " = " << 3.3 * nPwm/m_nPwmMax << " V" << " in Direction " << m_bDirection << endl;

    // TODO: 3.3 define as var LogicLevel_voltage

    return true;
}

void DcMotor::stop()
{
    setSpeed(0.0);

    digitalWrite(m_nPinA, LOW);
    digitalWrite(m_nPinB, LOW);

    cout << "Motor stopped" << endl;
}

//! Public Set Speed for positive or negative value
void DcMotor::setSpeed(float fSpeed_rpm)
{
    //TODO split into direction and absoulute speed functions

    m_bDirection = (fSpeed_rpm >= 0 ? FORWARD : BACKWARD);     //if given speed is positive ==> direction formward else backwards
    m_fSpeed_rpm = abs(fSpeed_rpm);                         //given speed is absolutified

    cout << "Set Speed to " << m_fSpeed_rpm << " in Direction " << m_bDirection << endl;

    actionMotor();
}


void DcMotor::setDirection(bool direction)
{
    // Set direction FW (1) or Backwards (0)
    m_bDirection = direction;

    cout << "Set Direction to " << m_bDirection << endl;

    actionMotor();
}

void DcMotor::setFactorRpmToPwm(float fFactorRpmToPwm)
{
    m_fFactorRpmToVoltage = fFactorRpmToPwm;
}

/// Conversion
float DcMotor::convertRpmToVolts(float fSpeed_rpm)
{
    float fMotorVoltage = m_fFactorRpmToVoltage * fSpeed_rpm;
    return fMotorVoltage;
}

int DcMotor::convertVoltsToPwm(float fMotorVoltage)
{
    int nPwm = m_fFactorVoltageToPwm * fMotorVoltage;
    nPwm = clip(nPwm, m_nPwmMax, 0);
    return nPwm;
}

///Getters
float DcMotor::getSpeed()
{
    return m_fSpeed_rpm;
}

bool DcMotor::getDirection()
{
    return m_bDirection;
}


bool DcMotor::isRunning()
{
    return m_fSpeed_rpm > 0;
}



