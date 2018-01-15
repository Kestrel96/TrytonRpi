
//odkomentowac przy kompilacji na Rpi:
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include<softPwm.h>

//Potrzebne na pc, na Rpi komentowac:
//#include<wiringPi/softPwm.h>
//#include<wiringPi/wiringPi.h>
//#include<wiringPi/wiringPiI2C.h>

//#include<SFML/System/Clock.hpp>
//#include<SFML/System/Time.hpp>


//Moje klasy
#include"rpimpu6050.h"
#include"pid.h"

#include<SFML/Network.hpp>
#include<SFML/System.hpp>
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

    RpiMPU6050 MPU(MPU_6050_ADDRESS);
    PID Pitch_PID;
    PID Roll_PID;

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
    Clock clock;
    Time t;
    t=sf::milliseconds(0);

    double SP=0;
    double dt=10; //ms

	Roll_PID.Tuning(10,10,10,10);


    clock.restart();
    while(1){

        t=clock.restart();
        MPU.XAcc();
        MPU.YAcc();
        MPU.ZAcc();
        MPU.Roll();
        MPU.Pitch();

        MPU.PrintAll();
        if(t.asMilliseconds()>=dt){
            Roll_PID.Compute(SP,MPU.roll,40,10);
            Pitch_PID.Compute(SP,MPU.pitch,40,10);
        }

        cout<<"Roll PID:"<<endl;
        Roll_PID.Print();
        cout<<"Pitch PID:"<<endl;
        Pitch_PID.Print();
        t.asMilliseconds();
        cout<<"t:"<<t.asMilliseconds()<<"ms"<<endl;

        Data<<MPU.yaw<<MPU.pitch<<MPU.roll;

        Data.clear();
        SendSocket.send(Data,IP,port);
        Data.clear();
        ReceiveSocket.receive(Data,IP,receivePort);


       
        system("clear");
    }


    return 0;
}






