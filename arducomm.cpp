#include "arducomm.h"
#include<iostream>
#include<wiringSerial.h>

#define MAX_PW 2000
#define MIN_PW 1050
#define MAX_CV 950
#define MIN_CV 0

using namespace std;

ArduComm::ArduComm()
{

}


void ArduComm::PrepareString(double CV1, double CV2){

    if(CV1>=0){
    ArduString="A";
    }
    else{
        CV1=CV1*-1;
        ArduString="B";
    }
    int tmp=0;

    CV1=CV1/100 * (MAX_PW-MIN_PW);
  //  CV1=CV1+MIN_PW;

    tmp=(int) CV1;
    if (tmp<=MIN_CV){
        tmp=MIN_CV;
    }
    if (tmp>=MAX_CV){
        tmp=MAX_CV;
    }
    ArduString+=to_string(tmp);
    if(CV2>=0){
    ArduString+="C";}
    else{
        CV2=CV2*-1;
        ArduString+="D";
    }

    CV2=CV2/100 * (MAX_PW-MIN_PW);
   // CV2=CV2+MIN_PW;


    tmp=(int) CV2;
    if (tmp<=MIN_CV){
        tmp=MIN_CV;
    }
    if (tmp>=MAX_CV){
        tmp=MAX_CV;
    }

    ArduString+=to_string(tmp);
    ArduString+='E';
    ArduString+='Z';
    ArduString+='\n';

}
