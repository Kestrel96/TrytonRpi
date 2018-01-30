#include "arducomm.h"
#include<iostream>
#include<wiringSerial.h>

#define MAX_PW 5200
#define MIN_PW 520

using namespace std;

ArduComm::ArduComm()
{

}


void ArduComm::PrepareString(double CV1, double CV2){

    ArduString="A";
    int tmp=0;
    CV1=CV1/100 * MAX_PW;
    tmp=(int) CV1;
    if (tmp<=MIN_PW){
        tmp=MIN_PW;
    }
    ArduString+=to_string(tmp);
    ArduString+="B";
    CV2=CV2/100 * MAX_PW;

    tmp=(int) CV2;
    if (tmp<=MIN_PW){
        tmp=MIN_PW;
    }

    ArduString+=to_string(tmp);
    ArduString+='E';

}
