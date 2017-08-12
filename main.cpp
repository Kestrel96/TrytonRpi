
//odkomentowac przy kompilacji na Rpi:
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include<softPwm.h>
#include<wiringSerial.h>
//Potrzebne na pc, na Rpi komentowac:
//#include<wiringPi/softPwm.h>
//#include<wiringPi/wiringPi.h>
//#include<wiringPi/wiringPiI2C.h>
//#include<wiringPi/wiringSerial.h>

//Moje klasy
#include"rpimpu6050.h"
#include "arduino_i2c.h"


#include<SFML/Network.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define    MPU_6050_ADDRESS   0x68
#define    MPU_6050_ADDRESS_2 0x69
#define    ARDUINO_ADDRESS    0xA

using namespace std;
using namespace sf;

int main()
{
    if(wiringPiSetup() == -1)
    exit(1);
    
    pinMode(4,INPUT);

    int Serial;

    if((Serial=serialOpen("/dev/ttyAMA0",9600))==-1){
    cout<<"Serial error"<<endl;
    cin>>Serial;
    exit(1);
    }

    RpiMPU6050 MPU(MPU_6050_ADDRESS);
    RpiMPU6050 MPU2(MPU_6050_ADDRESS_2);
    Arduino_i2c Arduino(ARDUINO_ADDRESS);

    UdpSocket SendSocket;
    UdpSocket ReceiveSocket;
    SendSocket.setBlocking(false);
    ReceiveSocket.setBlocking(false);
    IpAddress IP="10.42.0.1";
    unsigned short int port=4567;
    unsigned short int receivePort=1234;

    if(ReceiveSocket.bind(receivePort)!=ReceiveSocket.Done){
         cout<<"socket binding error!";
               int x;
         cin>>x;
         exit(1);
    }

    sf::Packet Data;

    while(1){
        MPU.XAcc();
        MPU.YAcc();
        MPU.ZAcc();
        MPU.Roll();
        MPU.Pitch();

        MPU2.XAcc();
        MPU2.YAcc();
        MPU2.ZAcc();
        MPU2.Roll();
        MPU2.Pitch();

        MPU.PrintAll();
        cout<<"MPU2: "<<endl;
        MPU2.PrintAll();

        Data<<MPU.yaw<<MPU.roll<<MPU2.roll;

        SendSocket.send(Data,IP,port);
        Data.clear();
        ReceiveSocket.receive(Data,IP,receivePort);
        int x,y,z,r;

       Data>>x>>y>>z>>r;

       cout<<"x: "<<x<<endl;
       cout<<"y: "<<y<<endl;
       cout<<"z: "<<z<<endl;
       cout<<"r: "<<r<<endl;


        Arduino.PrepareToSend(MPU,MPU2);
              
        Data.clear();

        //delay(10);
        system("clear");
    }


    return 0;
}



