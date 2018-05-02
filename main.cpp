
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
#include <unistd.h>

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
    cout<<"Serial ID:"<<SerialID<<endl;

    RpiMPU6050 MPU(MPU_6050_ADDRESS);

    PID Yaw_PID;
    PID Pitch_PID;
    PID Roll_PID;
    ArduComm ARD;



    UdpSocket SendSocket;
    UdpSocket ReceiveSocket;
    UdpSocket PIDsocket;
    SendSocket.setBlocking(false);
    PIDsocket.setBlocking(false);
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

    if(PIDsocket.bind(PIDreceivePort)!=ReceiveSocket.Done){
        cout<<"socket binding error!";
        int x;
        cin>>x;
        exit(1);
    }

    Packet Data;
    Packet PIDPacket;
    Clock clock;
    Time t;
    double elapsed_t;
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
    MPU.CalculateOffset();

    clock.restart();
    while(1){

        elapsed_t=(double)t.asMilliseconds();
        t=clock.restart();
        MPU.XAcc();
        MPU.YAcc();
        MPU.ZAcc();
        MPU.XGyro();
        MPU.YGyro();
        MPU.ZGyro();
        MPU.XGYroAngle(elapsed_t);
        MPU.YGYroAngle(elapsed_t);
        MPU.ZGYroAngle(elapsed_t);
        MPU.Yaw();
        MPU.Roll();
        MPU.Pitch();

        PIDsocket.receive(PIDPacket,IP,PIDreceivePort);
        PIDPacket>>Yaw_PID.kp>>Yaw_PID.Ki>>Yaw_PID.Kd>>Pitch_PID.kp>>Pitch_PID.Ki>>Pitch_PID.Kd>>Roll_PID.kp>>Roll_PID.Ki>>Roll_PID.Kd;
        PIDPacket.clear();

        Yaw_PID.dt=elapsed_t;
        Pitch_PID.dt=elapsed_t;
        Roll_PID.dt=elapsed_t;

        Data.clear();

        Data<<MPU.yaw<<MPU.pitch<<MPU.roll<<Yaw_PID.CV<<Pitch_PID.CV<<Roll_PID.CV;

        SendSocket.send(Data,IP,port);
        Data.clear();

        ReceiveSocket.receive(Data,IP,receivePort);

        Data>>Yaw_SP>>Pitch_SP>>Roll_SP>>Throttle_X>>Throttle_Y>>Throttle_Z;
        Data.clear();


//        PIDPacket>>kpt>>Kit>>Kdt;
//        Yaw_PID.Tuning(kpt,Kit,Kdt,elapsed_t);

//        PIDPacket>>kpt>>Kit>>Kdt;
//        cout<<"kpt: "<<kpt<<endl;
//        Pitch_PID.Tuning(kpt,Kit,Kdt,elapsed_t);

//        PIDPacket>>kpt>>Kit>>Kdt;
//        Roll_PID.Tuning(kpt,Kit,Kdt,elapsed_t);



        MPU.PrintAll();

      //  Yaw_PID.Ki=1; Yaw_PID.Kd=1;
        Yaw_PID.Compute(Yaw_SP,MPU.yaw);
      // Yaw_PID.I=0; Yaw_PID.D=0; Yaw_PID.CV=0;Yaw_PID.e_sum=0;
        Roll_PID.Compute(Roll_SP,MPU.roll);
        Pitch_PID.Compute(Pitch_SP,MPU.pitch);

        cout<<"Yaw PID"<<endl;
        Yaw_PID.Print();
        cout<<"Pitch PID:"<<endl;
        Pitch_PID.Print();
        cout<<"Roll PID:"<<endl;
        Roll_PID.Print();


        ARD.PrepareString(Yaw_PID.CV,Pitch_PID.CV,Roll_PID.CV,Throttle_X,Throttle_Y,Throttle_Z);
        cout<<"String:"<<ARD.ArduString<<endl;
        serialFlush(SerialID);
        usleep(500);
        serialFlush(SerialID);
        serialPrintf(SerialID,ARD.ArduString.c_str());

////////



        cout<<"RSP,PSP,YSP:"<<Roll_SP<<" | "<<Pitch_SP<<" | "<<Yaw_SP<<endl;
        cout<<"X,Y,Z: "<<Throttle_X<<Throttle_Y<<" | "<<Throttle_Z<<endl;



        cout<<"t:"<<t.asMilliseconds()<<"ms"<<" | "<<"dt: "<<elapsed_t<<endl;

        system("clear");

    }


    return 0;
}






