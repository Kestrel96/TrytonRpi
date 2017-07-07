#ifndef ARDUINO_I2C_H
#define ARDUINO_I2C_H

#include "rpimpu6050.h"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

class Arduino_i2c
{
public:
    //zmienne
    int fd;
    int8_t X;
    int8_t Y;
    int8_t Z;

    uint16_t yaw;
    uint16_t pitch;
    uint16_t roll;

    uint8_t yaw_H;
    uint8_t yaw_L;
    uint8_t pitch_H;
    uint8_t pitch_L;
    uint8_t roll_H;
    uint8_t roll_L;


    int tmp_1;
    int tmp_2;
    int tmp_3;
    //------------------------

    Arduino_i2c(int idDev);
    void PrepareToSend(RpiMPU6050 MPU1, RpiMPU6050 MPU2);
    void Write();
};

#endif // ARDUINO_I2C_H
