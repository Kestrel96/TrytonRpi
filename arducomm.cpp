#include "arducomm.h"
#include<iostream>
#include<wiringSerial.h>

#define MAX_PW 2000
#define MIN_PW 1000
#define MAX_CV 1000
#define MIN_CV 0
#define ZERO_POINT 50

using namespace std;

int UP_MAIN=0;
int UP_WING=0;
int L_MAIN=0;
int L_WING=0;
int R_MAIN=0;
int R_WING=0;
double tmp=0;

ArduComm::ArduComm()
{

}


void ArduComm::PrepareString(double Yaw_CV, double Pitch_CV, double Roll_CV, double Throttle_Y, double Throttle_Z){

    ArduString="";
    ArduString+="B";

    //up main
    ArduString+="A";
    tmp=Throttle_Y+Pitch_CV*0.01*500+MIN_PW;
    cout<<"tmp: "<<tmp<<endl;
    UP_MAIN=(int) tmp;
    cout<<"UP: "<<UP_MAIN<<endl;
    tmp=0;
    ArduString+=to_string(UP_MAIN);

    ArduString+="EZ";

}

//A450C250EZ
//B325C125EZ
//A300D240EZ
