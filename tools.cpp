#include <iostream>

#include "tools.h"

using namespace std;

int clip(int value, int upper, int lower)
{
    /// Function to clip value, if it extends given bounds
    value = value < lower ? lower : value;
    value = value > upper ? upper : value;

    return value;
}

double map(double inX,  double inMax, double inMin, double outMax, double outMin)
{
    if (inMax > outMax)
        cout << "ATTENTION! inMax = " << inMax << " < " << outMax << " = outMax" << endl;

    //! Maps a value from one Range to another by Linear doubleerpolation
    double normX = (inX - inMin) / (inMax - inMin); // Normalizes inX from Input Range to (0, 1)
    return normX * (outMax - outMin) + outMin;      // Expands normalized X to Output Range
}
