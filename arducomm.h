#ifndef ARDUCOMM_H
#define ARDUCOMM_H

#include<iostream>

using namespace std;


class ArduComm
{
public:
    ArduComm();
    void PrepareString(double CV1, double CV2, double CV3, double Throttle_X, double Throttle_Z);
    string ArduString;

};

#endif // ARDUCOMM_H
