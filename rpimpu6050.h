#ifndef RPIMPU6050_H
#define RPIMPU6050_H


class RpiMPU6050
{


public:

    int fd;
    double ax, ay, az, gx, gy, gz, yaw, pitch, roll;

    RpiMPU6050(int idDev);

    double ReadRegister(int reg_H, int reg_L);
    void PrintAll();

    void XAcc();
    void YAcc();
    void ZAcc();

    void XGyro();
    void YGyro();
    void ZGyro();

    void Yaw(double tau);
    void Reset_Yaw();
    void Roll();
    void Pitch();
};

#endif // RPIMPU6050_H
