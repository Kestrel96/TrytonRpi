#ifndef ARDUCOMM_H
#define ARDUCOMM_H

#include<iostream>

using namespace std;


class ArduComm
{
public:
    ArduComm();
    void PrepareString(double Yaw_CV, double Pitch_CV, double Roll_CV, double Throttle_Y, double Throttle_Z);
    string ArduString;

};

#endif // ARDUCOMM_H
