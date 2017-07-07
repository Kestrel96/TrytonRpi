#ifndef RPIMPU6050_H
#define RPIMPU6050_H


class RpiMPU6050
{


public:

    int fd;
    //trzeba to dac jako private
    double ax, ay, az,yaw,pitch,roll;
    RpiMPU6050(int idDev);
    double ReadAccelerometer(int reg_H, int reg_L);
    void PrintAll();
    void XAcc();
    void YAcc();
    void ZAcc();

    void Yaw();
    void Roll();
    void Pitch();
};

#endif // RPIMPU6050_H
