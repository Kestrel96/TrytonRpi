#include "pid.h"
#include<iostream>
#define MAX_CV 100
#define MIN_CV -100

using namespace std;
PID::PID()
{
    Ki=1000;
    Kd=1;
    kp=0;
    e=0;
    last_e=0;
    dt=0.06;//s

}


void PID::Compute (double sp, double pv){

    SP=sp;
    e=SP-pv;
    P=kp*e;
    //I=Ki*e_sum*dt;
    I=Ki*e_sum;
    D=Kd*(e-last_e)/dt;

    last_e=e;

    e_sum+=e*dt;

//    if(e>=PD_on_big_e){
//        e_sum=0;
//    }
//    if(e<=-PD_on_big_e){
//        e_sum=0;
//    }


    CV=P+I+D;

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
   // this->dt=dt/1000;

}

void PID::Reset(){

   this->kp=0;
   this->Ki=1000;
   this->Kd=0;

}

void PID::Print(){

    cout<<"Kp:"<<kp<<" "<<"Ki:"<<Ki<<" "<<"Kd:"<<Kd<<"dt:"<<dt<<endl;
    cout<<"P:"<<P<<"I:"<<I<<"D"<<D<<endl;
    cout<<"SP:"<<SP<<endl;
    cout<<"e:"<<e<<endl;
    cout<<"CV:"<<CV<<endl;
    cout<<"err_sum:"<<e_sum<<endl;



}
