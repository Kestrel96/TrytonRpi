#include "arducomm.h"
#include<iostream>
#include<wiringSerial.h>

#define MAX_PW 2000
#define MIN_PW 1000
#define MAX_CV 500
#define MIN_CV 0
#define ZERO_POINT 50

using namespace std;

ArduComm::ArduComm()
{

}

int tmp=0;

int MOT1,MOT2,MOT3,MOT4,MOT5,MOT6;

void ArduComm::PrepareString(double Pitch_CV, double Roll_CV, double Yaw_CV, double Throttle_Y, double Throttle_Z){

    ArduString+="B";

    ArduString+="A";

//    if(Pitch_CV>=ZERO_POINT){
//        //gora glowny
//       tmp=0;
//       tmp=(int) (Throttle_Y+Pitch_CV*MAX_CV*0.01);
//       ArduString+=to_string(tmp);
//       ArduString+="A";
//       tmp=0;
//       tmp=(int) (Throttle_Y+Pitch_CV*MAX_CV*0.01);



//    }

//    ArduString+="A";
//    ArduString+=to_string(CV1*500*0.01);
//    ArduString+="A";
//    ArduString+=to_string(CV1*500*0.01);

//    ArduString+="A";
//    ArduString+=to_string(CV2*500*0.01);
//    ArduString+="A";
//    ArduString+=to_string(CV2*500*0.01);
//    ArduString+="A";
//    ArduString+=to_string(CV2*500*0.01);

//    ArduString+='E';
//    ArduString+='Z';
//    ArduString+='\n';

}

//A450C250EZ
//B325C125EZ
//A300D240EZ
