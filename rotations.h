#ifndef ROTATIONS_H
#define ROTATIONS_H


class Rotations
{
public:
    float Kp_x;
    float Ti_x;
    float Td_x;

    float Kp_y;
    float Ti_y;
    float Td_y;

    float Kp_z;
    float Ti_z;
    float Td_z;

    float Tp;

    Rotations(float tp);
    void setNewVal(float nPsi, float nTheta, float nPhi);
    void resetController();
    float* calculate(float cPsi, float cTheta, float cPhi);

private:

    float setPsi;
    float setTheta;
    float setPhi;

    float I_x;
    float I_y;
    float I_z;

    float ep_x;
    float ep_y;
    float ep_z;
};

#endif // ROTATIONS_H
