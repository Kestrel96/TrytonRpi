#ifndef ARDU_COM_H
#define ARDU_COM_H

#include<iostream>

using namespace std;

class Ardu_Com
{
private:

    string PrepareString();
    string Ardu_String;

public:
    Ardu_Com();

    double throttle;
    double throttle_limit;
    double throttle_lock;
    int signal_width;
    void PrepareValues(float T[]);



    int motor_1;
    int motor_2;
    int motor_3;
    int motor_4;
    int motor_5;
    int motor_6;

};

#endif // ARDU_COM_H
