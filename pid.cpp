#include "pid.h"


#include<iostream>
#define MAX_CV 100
#define MIN_CV 0 //np dla drona min 0, dla trytona min -100 (windup)


using namespace std;
PID::PID()
{
    Ti=1000;
    Td=1;
    kp=1;
    e=0;
    last_e=0;
    dt=0.1;//s

}


void PID::Compute (double sp, double pv,double WP, double PD_on_big_e){

    SP=sp;
    e=SP-pv;
    P=kp*e;
    I=Ki*e_sum;
    D=Kd*(e-last_e)/dt;

    if(e>=PD_on_big_e || e<=-PD_on_big_e){
        I=0;
        e_sum=0;
    }

    CV=P+I+D+WP;

    if (CV>=MAX_CV){
        CV=MAX_CV;
    }

    if (CV<=MIN_CV){
        CV=MIN_CV;
    }


}

void PID::Tuning(double kp, double Ki, double Kd, double dt){

    this->kp=kp;
    this->Ki=Ki;
    this->Kd=Kd;
    this->dt=dt/1000;

}

void PID::Reset(){

   this->kp=0;
   this->Ki=1000;
   this->Kd=0;

}

void PID::Print(){

    cout<<"Kp:"<<kp<<" "<<"Ki:"<<Ki<<" "<<"Kd:"<<Kd<<endl;
    cout<<"P:"<<P<<"I:"<<I<<"D"<<D<<endl;
    cout<<"SP:"<<SP<<endl;
    cout<<"e:"<<e<<endl;
    cout<<"CV:"<<CV<<endl;
    cout<<"err_sum:"<<e_sum<<endl;



}
