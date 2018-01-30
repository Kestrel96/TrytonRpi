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
    tmp=(int) (CV1/100)*MAX_PW;
    if (tmp<=MIN_PW){
        tmp=MIN_PW;
    }
    ArduString+=to_string(tmp);
    ArduString+="B";
    tmp=(int) (CV2/100)*MAX_PW;
   // if (tmp<=MIN_PW){
     //   tmp=MIN_PW;
    //}

    ArduString+=to_string(tmp);
    ArduString+='E';

}
