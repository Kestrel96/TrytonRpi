#include "arduino_i2c.h"

#include <wiringPi.h>
#include <wiringPiI2C.h>

//#include<wiringPi/wiringPi.h>
//#include<wiringPi/wiringPiI2C.h>

#include "rpimpu6050.h"

#include <iostream>
#include <bitset>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



using namespace std;


Arduino_i2c::Arduino_i2c(int idDev)
{

    uint16_t yaw=0;
    uint16_t pitch=0;
    uint16_t roll=0;

    uint8_t yaw_H=0;
    uint8_t yaw_L=0;
    uint8_t pitch_H=0;
    uint8_t pitch_L=0;
    uint8_t roll_H=0;
    uint8_t roll_L=0;


    if((this->fd=wiringPiI2CSetup(idDev))==-1){
        cout<<"Blad inicjalizacji (Arduino), sprawdz polaczenia"<<endl;
        cin>>this->fd;
        exit(0);
    }
    cin>>this->yaw;

}


void Arduino_i2c::PrepareToSend(RpiMPU6050 MPU1, RpiMPU6050 MPU2){

    this->yaw=(uint16_t) MPU1.yaw*100;
    this->pitch=(uint16_t) MPU2.roll*100;
    this->roll=(uint16_t) MPU1.roll*100;

    //I to samo dla reszty katow, wazne zeby byly dodatnie
    this->roll_L = this->roll & 0xff;
    this->roll_H = (this->roll >> 8);
    cout<<"roll (po konwersji): "<<this->roll<<endl;
    cout<<"roll_L= "<<bitset<8>(roll_L)<<endl;
    cout<<"roll_H= "<<bitset<8>(roll_H)<<endl;

}

//Przyda sie jakis mechanizm sprawdzajacy
void Arduino_i2c::Write(){

    wiringPiI2CWrite(this->fd,this->roll_H);
    wiringPiI2CWrite(this->fd,this->roll_L);
}
