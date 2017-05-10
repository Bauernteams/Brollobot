#ifndef TOOLS_H
#define TOOLS_H

#endif // TOOLS_H

#include <time.h>

//! Limit a value to a secific range
int clip(int num, int max=100, int min=0);

//! Map a value from one range to another (by means of Linear Interpolation)
double map(double inX,  double inMax, double inMin=0, double outMax=100, double outMin=0);


//void sleep(unsigned int mseconds)
//{
//    clock_t goal = mseconds + clock();
//    while (goal > clock());
//}
