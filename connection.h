#ifndef CONNECTION_H
#define CONNECTION_H

#include<SFML/Network.hpp>
#include"rpimpu6050.h"

using namespace sf;

class Connection
{
    IpAddress IP;
    unsigned short  SendPort;
    unsigned short ReceivePort;
    UdpSocket SendSocket;
    UdpSocket ReceiveSocket;


public:
    Packet Data;


public:
    Connection();
    void SendData(RpiMPU6050 MPU1, RpiMPU6050 MPU2);


private:

    void BindReceiveSocket();



};

#endif // CONNECTION_H
