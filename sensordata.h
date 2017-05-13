#ifndef SENSORDATA_H
#define SENSORDATA_H

struct SensorData
{
public:
    SensorData(bool LeftSensor, bool RightSensor) :
        LeftSensorIsBlack(LeftSensor),
        RightSensorIsBlack(RightSensor)
    {
    }

    bool LeftSensorIsBlack;
    bool RightSensorIsBlack;
};

#endif // SENSORDATA_H
