#include "rpimpu6050.h"

#include <wiringPi.h>
#include <wiringPiI2C.h>

//#include<wiringPi/wiringPi.h>
//#include<wiringPi/wiringPiI2C.h>

#include <stdlib.h>
#include<math.h>
#include<iostream>
#include<stdint.h>

using namespace std;

//Registers etc.
#define    MPU6050_ADDRESS            0x68
#define    MAG_ADDRESS                0x0C

#define    ACCEL_XH     0x3B
#define    ACCEL_XL     0x3C
#define    ACCEL_YH     0x3D
#define    ACCEL_YL     0x3E
#define    ACCEL_ZH     0x3F
#define    ACCEL_ZL     0x40

#define    GYRO_FULL_SCALE_250_DPS    0x00
#define    GYRO_FULL_SCALE_500_DPS    0x08
#define    GYRO_FULL_SCALE_1000_DPS   0x10
#define    GYRO_FULL_SCALE_2000_DPS   0x18

#define    ACC_FULL_SCALE_2_G        0x00
#define    ACC_FULL_SCALE_4_G        0x08
#define    ACC_FULL_SCALE_8_G        0x10
#define    ACC_FULL_SCALE_16_G       0x18

#define GYRO_XH     0x43
#define GYRO_XL     0x44
#define GYRO_YH     0x45
#define GYRO_YL     0x46
#define GYRO_ZH     0x47
#define GYRO_ZL     0x48

#define ACCEL_CONSTANT 16834
#define GYRO_CONSTANT 131



RpiMPU6050::RpiMPU6050(int idDev)
{


   if((this->fd=wiringPiI2CSetup(idDev))==-1){
       cout<<"Blad inicjalizacji, sprawdz polaczenia"<<endl;
       cin>>this->fd;
       exit(0);
   }

    wiringPiI2CWriteReg8(fd, 0x6B, 0);
    wiringPiI2CWriteReg8(fd, 0x3B, 8);
    wiringPiI2CWriteReg8(fd,29,0x06);
    wiringPiI2CWriteReg8(fd,26,0x06);
    wiringPiI2CWriteReg8(fd,27,GYRO_FULL_SCALE_250_DPS);
    wiringPiI2CWriteReg8(fd,28,ACC_FULL_SCALE_2_G);
    wiringPiI2CWriteReg8(fd,0x37,0x02);
    wiringPiI2CWriteReg8(fd,0x0A,0x16);

}

void RpiMPU6050::Yaw(){
    this->yaw=gzA;
}

void RpiMPU6050::Roll(){

    this->roll=-atan2(this->ay,this->az)*180/M_PI;

}

void RpiMPU6050::Pitch(){
    this->pitch=atan2(this->ax, sqrt(this->ay*this->ay + this->az*this->az))*180/M_PI;

}

void RpiMPU6050::XAcc(){
    this->ax=ReadAccelerometer(ACCEL_XH,ACCEL_XL);
}

void RpiMPU6050::YAcc(){
    this->ay=ReadAccelerometer(ACCEL_YH,ACCEL_YL);
}

void RpiMPU6050::ZAcc(){
    this->az=ReadAccelerometer(ACCEL_ZH,ACCEL_ZL);
}

void RpiMPU6050::XGyro(){
    gx=ReadGyro(GYRO_XH,GYRO_XL)-gxOffset;
}

void RpiMPU6050::YGyro(){
    gy=ReadGyro(GYRO_YH,GYRO_YL)-gyOffset;
}

void RpiMPU6050::ZGyro(){
      gz=ReadGyro(GYRO_ZH,GYRO_ZL)-gzOffset;
}


double RpiMPU6050::ReadAccelerometer(int reg_H, int reg_L){

    double a=0;
    uint8_t tmp=0;
    int16_t a16=0;
    a16=wiringPiI2CReadReg8(this->fd,reg_H);
    tmp=wiringPiI2CReadReg8(this->fd,reg_L);
    a16=a16<<8;
    a16=a16 | tmp;
    a=(double) a16/ACCEL_CONSTANT;


   return a;


}

double RpiMPU6050::ReadGyro(int reg_H, int reg_L){
    double a=0;
    uint8_t tmp=0;
    int16_t a16=0;
    a16=wiringPiI2CReadReg8(this->fd,reg_H);
    tmp=wiringPiI2CReadReg8(this->fd,reg_L);
    a16=a16<<8;
    a16=a16 | tmp;
    a=(double) a16/GYRO_CONSTANT;


   return a;
}

void RpiMPU6050::XGYroAngle(double dt){
    gxA=gxA+gx*dt*0.001;

}

void RpiMPU6050::YGYroAngle(double dt){
    gyA=gyA+gy*dt*0.001;

}

void RpiMPU6050::ZGYroAngle(double dt){
    gzA=gzA+gz*dt*0.001;

}

void RpiMPU6050::CalculateOffset(){
    gxOffset=0;
    gyOffset=0;
    gzOffset=0;
    int l = 100;
    for(int i=0;i<l;i++){
        XGyro();
        YGyro();
        ZGyro();
        gxOffset=gxOffset+ReadGyro(GYRO_XH,GYRO_XL);
        gyOffset=gyOffset+ReadGyro(GYRO_YH,GYRO_YL);
        gzOffset=gzOffset+ReadGyro(GYRO_ZH,GYRO_ZL);

    }
    gxOffset=gxOffset/l;
    gzOffset=gzOffset/l;
    gyOffset=gyOffset/l;
}

void RpiMPU6050::PrintAll(){

    cout<<"Akcelerometry: "<<endl;
    cout<<"ax :"<<this->ax<<"g"<<endl;
    cout<<"ay :"<<this->ay<<"g"<<endl;
    cout<<"az :"<<this->az<<"g"<<endl;
    cout<<"Gyro: "<<endl;
    cout<<"gx :"<<this->gx<<"deg/s"<<" | "<<"XAngle: "<<this->gxA<<" | "<<"Xoffset: "<<gxOffset<<endl;
    cout<<"gx :"<<this->gy<<"deg/s"<<" | "<<"YAngle: "<<this->gyA<<" | "<<"Yoffset: "<<gyOffset<<endl;
    cout<<"gx :"<<this->gz<<"deg/s"<<" | "<<"ZAngle: "<<this->gzA<<" | "<<"ZAngle: "<<gzOffset<<endl;
    cout<<"Euler: "<<endl;
    cout<<"yaw: "<<this->yaw<<"deg"<<endl;
    cout<<"roll: "<<this->roll<<"deg"<<endl;
    cout<<"pitch: "<<this->pitch<<"deg"<<endl;

}



