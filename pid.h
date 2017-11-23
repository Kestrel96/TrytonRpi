#ifndef PID_H
#define PID_H

#include<iostream>

//zakomentowac na rpi
#include<SFML/System/Time.hpp>
#include<SFML/System/Clock.hpp>
#include<SFML/Network.hpp>



using namespace std;
using namespace sf;


class PID
{

private:

    bool COMPUTE;

public:

    double Kp;
    double Kd;
    double Ki;
    double tau;

    Clock clock;
    Time T;

    double setpoint;
    double pv;

    double error;
    long double I_error;
    double last_error;

    double output;
    double max_output;

    double CVP;
    double offset;

    double P;
    double I;
    double D;


    void Compute();
    void PrintAll();
    void Reset();
    void CheckTime();
    void Tuning(double KP, double KI, double KD, double CVp, double dt);
//    void StartTimer();
//    void RestartTimer();

    PID();
};

#endif // PID_H
