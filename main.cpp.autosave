
//odkomentowac przy kompilacji na Rpi:
#include <wiringPi.h>
#include<wiringSerial.h>


//Potrzebne na pc, na Rpi komentowac:
//#include<wiringPi/softPwm.h>
//#include<wiringPi/wiringPi.h>
//#include<wiringPi/wiringPiI2C.h>

//#include<SFML/System/Clock.hpp>
//#include<SFML/System/Time.hpp>


//Moje klasy
#include"rpimpu6050.h"
#include"pid.h"
#include"arducomm.h"

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

    int SerialID=0;
   SerialID=serialOpen("/dev/ttyAMA0", 115200);
   cout<<SerialID<<endl;
    RpiMPU6050 MPU(MPU_6050_ADDRESS);
    PID Pitch_PID;
    PID Roll_PID;
    ArduComm ARD;



    UdpSocket SendSocket;
    UdpSocket ReceiveSocket;
    SendSocket.setBlocking(false);
    ReceiveSocket.setBlocking(false);
    IpAddress IP="10.42.0.1";
    unsigned short int port=4567;
    unsigned short int receivePort=1234;
    unsigned short int PIDreceivePort=5678;

    if(ReceiveSocket.bind(receivePort)!=ReceiveSocket.Done){
         cout<<"socket binding error!";
               int x;
         cin>>x;
         exit(1);
    }

    sf::Packet Data;
    sf::Packet PIDPacket;
    Clock clock;
    Time t;
    t=sf::milliseconds(0);

    double kpt=0;
    double Kit=0;
    double Kdt=0;
    double dtt=0;
    double offset_t=0;

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
            Roll_PID.Compute(SP,MPU.roll,40,5);
            Pitch_PID.Compute(SP,MPU.pitch,40,5);
        }

        cout<<"Roll PID:"<<endl;
        Roll_PID.Print();
        cout<<"Pitch PID:"<<endl;
        Pitch_PID.Print();
        t.asMilliseconds();
        cout<<"t:"<<t.asMilliseconds()<<"ms"<<endl;
        cout<<"String:"<<ARD.ArduString<<endl;
        Data.clear();

        Data<<MPU.yaw<<MPU.pitch<<MPU.roll;

        SendSocket.send(Data,IP,port);
        Data.clear();

        ReceiveSocket.receive(Data,IP,receivePort);
        ReceiveSocket.receive(PIDPacket,IP,PIDreceivePort);
        PIDPacket>>kpt>>Kit>>Kdt>>dtt>>offset_t;
        Roll_PID.Tuning(kpt,Kit,Kdt,dtt);
        PIDPacket>>kpt>>Kit>>Kdt>>dtt>>offset_t;
        Pitch_PID.Tuning(kpt,Kit,Kdt,dtt);
        PIDPacket.clear();

        ARD.PrepareString(Roll_PID.CV,Pitch_PID.CV);

        serialPuts(SerialID,ARD.ArduString.c_str());

        system("clear");
    }


    return 0;
}






