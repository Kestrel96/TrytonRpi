#include "pid.h"
#include<iostream>
using namespace std;


PID::PID()
{

    this->last_error=0;
    this->max_output=100;

    //doArduCom
//    this->signal_width=500;
//    this->throttle_limit=0.75;
//    this->throttle_lock=0;
    //this->T=0;

    this->tau=1;
    this->Reset();
    this->clock.restart();
    this->CVP=0;
}


void PID::PrintAll(){

    cout<<"PID"<<endl;
    cout<<"Kp: "<<this->Kp<<" ";
    cout<<"Ki: "<<this->Ki<<" ";
    cout<<"Kd: "<<this->Kd<<endl;
    cout<<"error: "<<this->error<<endl;
    cout<<"I_error: "<<this->I_error<<endl;
    cout<<"Output: "<<this->output<<endl;
    cout<<"T: "<<this->clock.getElapsedTime().asMilliseconds()<<"ms"<<endl;
}



void PID::Reset(){
    this->Kp=0;
    this->Kd=0;
    this->Ki=0;
}

void PID::Compute(){

    this->CheckTime();

    if(this->COMPUTE==1){

        setpoint=setpoint-offset;

        //error
        this->error=this->setpoint-this->pv;

        //Proportional
        this->P=this->Kp*this->error;

        //Integral
        this->I_error+=this->error*this->tau;
        this->I=this->Ki*(this->I_error*this->tau);

        //Derivative
        this->D=this->Kd*(this->error-this->last_error)/this->tau;

        this->last_error=error;

        this->output=this->CVP+this->P+this->I+this->D;

        if(this->output>this->max_output){
            this->output=this->max_output;
        }

        //wersja jak dla drona, dla trytona musi byc -max
        if(this->output< -this->max_output){
            this->output=0;
        }



    }


}


void PID::Tuning(double KP, double KI, double KD, double CVp, double dt){

    this->Kp=KP;
    this->Ki=KI;
    this->Kd=KD;
    this->CVP=CVp;
    this->tau=dt;
}


void PID::CheckTime(){

    this->T=this->clock.getElapsedTime();

    if(this->T.asMilliseconds()>=tau){

        this->COMPUTE=1;
        this->clock.restart();

    }
    else{
        this->COMPUTE=0;
    }

}


