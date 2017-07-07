#include "connection.h"

#include<iostream>
#include"rpimpu6050.h"

using namespace std;

Connection::Connection()
{

    this->IP="10.42.0.1";
    this->ReceivePort=1234;
    this->SendPort=4576;
    this->BindReceiveSocket();
    this->SendSocket.setBlocking(false);

}

void Connection::BindReceiveSocket(){

    this->ReceiveSocket.setBlocking(false);
    if(this->ReceiveSocket.bind(this->ReceivePort)==this->ReceiveSocket.Done)
    {
        cout<<endl<<"Receieve socket: bind succesfull!"<<endl;
    }
    else{
        cout<<endl<<"Receive socket: bind error!";
        cin>>this->ReceivePort;
        exit(1);
    }

}

//sa dwa imu wiec cos trzeba przeredagowac w tej funkcji
void Connection::SendData(RpiMPU6050 MPU1,RpiMPU6050 MPU2){

    //Musi isc YAW,PITCH,ROLL, wazna kolejnosc
    this->SendSocket.send(this->Data,this->IP,this->SendPort);
    this->Data.clear();

}


