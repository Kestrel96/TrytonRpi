#include "arducomm.h"
#include<iostream>
#include<wiringSerial.h>

#define MAX_PW 2000
#define MIN_PW 1000
#define MAX_CV 500
#define MIN_CV 0

using namespace std;

ArduComm::ArduComm()
{

}


void ArduComm::PrepareString(double CV1, double CV2, double CV3, double Throttle_X, double Throttle_Z){

    ArduString+="B";

    ArduString+="A";
    ArduString+=to_string(CV1*500*0.01);
    ArduString+="A";
    ArduString+=to_string(CV1*500*0.01);
    ArduString+="A";
    ArduString+=to_string(CV1*500*0.01);

    ArduString+="A";
    ArduString+=to_string(CV2*500*0.01);
    ArduString+="A";
    ArduString+=to_string(CV2*500*0.01);
    ArduString+="A";
    ArduString+=to_string(CV2*500*0.01);

    ArduString+='E';
    ArduString+='Z';
    ArduString+='\n';

}

//A450C250EZ
//B325C125EZ
//A300D240EZ
