#ifndef LINESENSOR_H
#define LINESENSOR_H

#include <QTimer>

#endif // LINESENSOR_H


class LineSensor
{
public:
    LineSensor(int nPin);
    ~LineSensor();

    // Setters and Getters
    bool isBlack();

    // Methods
    bool initPins(int nPin);

private:
    int m_nPin;
};
