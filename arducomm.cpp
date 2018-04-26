#include "arducomm.h"
#include<iostream>
#include<wiringSerial.h>

#define MAX_PW 2000
#define MIN_PW 1000
#define MAX_CV 1000
#define MIN_CV 0
#define ZERO_POINT 1500
#define RANGE 500

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


void ArduComm::PrepareString(double Yaw_CV, double Pitch_CV, double Roll_CV,double Throttle_X, double Throttle_Y, double Throttle_Z){

    ArduString="";
    ArduString+="B";

    //up main
    ArduString+="A";
    tmp=Throttle_Y+Pitch_CV*0.01*RANGE+ZERO_POINT;
    if(tmp>=MAX_PW){
        tmp=MAX_PW;
    }

    if(tmp<=MIN_PW){
        tmp=MIN_PW;
    }

    UP_MAIN=(int) tmp;
    tmp=0;
    ArduString+=to_string(UP_MAIN);
    //left main
    ArduString+="A";
    tmp=0.5*Throttle_Y-0.5*Pitch_CV*0.01*RANGE+Yaw_CV*0.01*RANGE+ZERO_POINT;
    if(tmp>=MAX_PW){
        tmp=MAX_PW;
    }

    if(tmp<=MIN_PW){
        tmp=MIN_PW;
    }
    L_MAIN=(int) tmp;
    tmp=0;
    ArduString+=to_string(L_MAIN);
    //right main
    ArduString+="A";
    tmp=0.5*Throttle_Y-0.5*Pitch_CV*0.01*RANGE-Yaw_CV*0.01*RANGE+ZERO_POINT;
    if(tmp>=MAX_PW){
        tmp=MAX_PW;
    }

    if(tmp<=MIN_PW){
        tmp=MIN_PW;
    }
    R_MAIN=(int) tmp;
    tmp=0;
    ArduString+=to_string(R_MAIN);
    // up wing
    ArduString+="A";
    tmp=Throttle_X+Roll_CV*0.01*RANGE+ZERO_POINT;
    if(tmp>=MAX_PW){
        tmp=MAX_PW;
    }

    if(tmp<=MIN_PW){
        tmp=MIN_PW;
    }

    UP_WING=(int) tmp;
    tmp=0;
    ArduString+=to_string(UP_WING);
    //left wing
    ArduString+="A";
    tmp=Throttle_Z+Roll_CV*0.01*RANGE+ZERO_POINT;
    if(tmp>=MAX_PW){
        tmp=MAX_PW;
    }

    if(tmp<=MIN_PW){
        tmp=MIN_PW;
    }
    L_WING=(int) tmp;
    tmp=0;
    ArduString+=to_string(L_WING);
    //right wing
    ArduString+="A";
    tmp=Throttle_Z-Roll_CV*0.01*RANGE+ZERO_POINT;
    if(tmp>=MAX_PW){
        tmp=MAX_PW;
    }

    if(tmp<=MIN_PW){
        tmp=MIN_PW;
    }
    R_WING=(int) tmp;
    tmp=0;
    ArduString+=to_string(R_WING);
    ArduString+="EZ";

}

//A450C250EZ
//B325C125EZ
//A300D240EZ
