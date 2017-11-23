//odkomentowac przy kompilacji na Rpi:
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include<softPwm.h>


//Potrzebne na pc, na Rpi komentowac:
//#include<wiringPi/softPwm.h>
//#include<wiringPi/wiringPi.h>
//#include<wiringPi/wiringPiI2C.h>

#include<wiringSerial.h>

//Moje klasy
#include "rpimpu6050.h"
#include "rotations.h"
#include "pid.h"

#include<SFML/Network.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define    MPU_6050_ADDRESS 0x68
#define    MPU_6050_ADDRESS_2 0x69
using namespace std;
using namespace sf;


//QUATERNION OUTPUT
//YAW!!!!!!!!!!!!!!



int main()
{
    if(wiringPiSetup() == -1)
        exit(1);

    RpiMPU6050 MPU(MPU_6050_ADDRESS);
    unsigned short int port=4567;
    unsigned short int receive_port=1234;
    unsigned short int PID_port=5678;
    UdpSocket SendSocket;
    UdpSocket ReceiveSocket;
    UdpSocket PID_Socket;
    SendSocket.setBlocking(false);
    ReceiveSocket.setBlocking(false);
    PID_Socket.setBlocking(false);
    PID_Socket.bind(PID_port);
    ReceiveSocket.bind(receive_port);



{       
//    //serial:
//    if ((fd = serialOpen ("/dev/ttyAMA0", 9600)) < 0)
//      {
//        fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
//        return 1 ;
//    }
}
    sf::IpAddress IP="10.42.0.1";
    sf::Packet Data;

    int pitch_setpoint=0;
    int roll_setpoint=0;
    int throttle_setpoint=0;

    PID PID1,PID2;

    while(1){

        MPU.XAcc();
        MPU.YAcc();
        MPU.ZAcc();
        MPU.ZGyro();
        MPU.Roll();
        MPU.Pitch();
        MPU.Yaw(10);
        MPU.PrintAll();

        PID1.pv=MPU.roll;
        PID2.pv=MPU.pitch;

        PID1.Compute();
        PID2.Compute();


        Data<<MPU.yaw<<MPU.roll<<MPU.roll;
        SendSocket.send(Data,"10.42.0.1",port);
        Data.clear();

        ReceiveSocket.receive(Data,IP,receive_port);
        Data>>pitch_setpoint>>roll_setpoint>>throttle_setpoint;
        PID1.CVP=throttle_setpoint;
        PID1.CVP=PID2.CVP;
        PID1.setpoint=roll_setpoint;
        PID2.setpoint=pitch_setpoint;
        PID1.PrintAll();
        PID2.PrintAll();

        Data.clear();

        PID_Socket.receive(Data,IP,PID_port);
        Data>>PID1.Ki>>PID1.Kp>>PID1.Kd>>PID1.tau>>PID1.offset>>PID2.Ki>>PID2.Kp>>PID2.Kd>>PID2.tau>>PID2.offset;


//        serialPuts(fd,ArduString);

        delay(10);
        Data.clear();
        system("clear");
    }


    return 0;
}

