
//odkomentowac przy kompilacji na Rpi:
#include <wiringPi.h>
#include<wiringSerial.h>


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
    if(wiringPiSetup() == -1){
        cout<<"WiringPi setup fail!";
        int x;
        cin>>x;
        exit(1);
    }

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

    Packet Data;
    Packet PIDPacket;
    Clock clock;
    Time t;
    t=sf::milliseconds(0);
    bool Switch=0;

    double kpt=0;
    double Kit=0;
    double Kdt=0;
    double dtt=0;



    double Yaw_SP=0;
    double Roll_SP=0;
    double Pitch_SP=0;
    double Throttle_X=0;
    double Throttle_Y=0;
    double Throttle_Z=0;
    double dt=60; //ms

    // Roll_PID.Tuning(10,10,10,10);


    clock.restart();
    while(1){

        t=clock.restart();
        MPU.XAcc();
        MPU.YAcc();
        MPU.ZAcc();
        MPU.XGyro();
        MPU.YGyro();
        MPU.ZGyro();
        MPU.Roll();
        MPU.Pitch();

        MPU.PrintAll();

        if(t.asMilliseconds()>=dt){

            MPU.gx=MPU.gx*dt*0.001;
            MPU.gy=MPU.gy*dt*0.001;
            MPU.gz=MPU.gz*dt*0.001;

            Roll_PID.Compute(Roll_SP,MPU.roll);
            Pitch_PID.Compute(Pitch_SP,MPU.pitch);
        }

        cout<<"Roll PID:"<<endl;
        Roll_PID.Print();
        cout<<"Pitch PID:"<<endl;

        Pitch_PID.Print();

        //cout<<"String:"<<ARD.ArduString<<endl;
        Data.clear();

        Data<<MPU.yaw<<MPU.pitch<<MPU.roll<<Roll_PID.CV<<Pitch_PID.CV;

        SendSocket.send(Data,IP,port);
        Data.clear();

        ReceiveSocket.receive(Data,IP,receivePort);
        Data>>Switch;
        if(Switch==0){
            Data>>Yaw_SP>>Throttle_Y>>Roll_SP>>Throttle_Z;
        }
        if(Switch==1){
            Data>>Pitch_SP>>Throttle_X>>Throttle_Z;
        }

        cout<<"SPR,SPP:"<<Roll_SP<<" | "<<Pitch_SP<<endl;
        Data.clear();

        ReceiveSocket.receive(PIDPacket,IP,PIDreceivePort);

        PIDPacket>>kpt>>Kit>>Kdt>>dtt;
        Roll_PID.Tuning(kpt,Kit,Kdt,dtt);

        PIDPacket>>kpt>>Kit>>Kdt>>dtt;
        Pitch_PID.Tuning(kpt,Kit,Kdt,dtt);
        dt=dtt;

        PIDPacket.clear();

       // ARD.PrepareString(Roll_PID.CV,Pitch_PID.CV,0,Throttle_X,Throttle_Z);

        serialFlush(SerialID);
        serialPuts(SerialID,ARD.ArduString.c_str());
        serialFlush(SerialID);

        cout<<"t:"<<t.asMilliseconds()<<"ms"<<endl;
        system("clear");

    }


    return 0;
}






