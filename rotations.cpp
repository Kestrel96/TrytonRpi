#include "rotations.h"
#include <math.h>

Rotations::Rotations(float tp)
{
    Kp_x = 1.0f;
    Ti_x = 1.0f;
    Td_x = 0.0f;

    Kp_y = 2.0f;
    Ti_y = 1.0f;
    Td_y = 0.0f;

    Kp_z = 1.0f;
    Ti_z = 1.0f;
    Td_z = 0.0f;

    setPsi = 0.0f;
    setTheta = 0.0f;
    setPhi = 0.0f;

    I_x = 0.0f;
    I_y = 0.0f;
    I_z = 0.0f;

    Tp = tp;

    ep_x = 0.0f;
    ep_y = 0.0f;
    ep_z = 0.0f;
}

void Rotations::setNewVal(float nPsi, float nTheta, float nPhi)
{
    setPsi = nPsi;
    setTheta = nTheta;
    setPhi = nPhi;
}

void Rotations::resetController(){
    I_x = 0;
    I_y = 0;
    I_z = 0;
}

float* Rotations::calculate(float cPsi, float cTheta, float cPhi)
{
    int i=0;
    int j=0;


    float e_x = setPsi - cPsi;
    float e_y = setTheta - cTheta;
    float e_z = setPhi - cPhi;

    I_x += Tp*Kp_x*e_x/Ti_x;
    I_y += Tp*Kp_y*e_y/Ti_y;
    I_z += Tp*Kp_z*e_z/Ti_z;

    float out_val_x = I_x + Kp_x * e_x + Kp_x*Td_x*(e_x - ep_x)/Tp;
    float out_val_y = I_y + Kp_y * e_y + Kp_y*Td_y*(e_y - ep_y)/Tp;
    float out_val_z = I_z + Kp_z * e_z + Kp_z*Td_z*(e_z - ep_z)/Tp;

    ep_x = e_x;
    ep_y = e_y;
    ep_z = e_z;

    // macierz rotacji - pierwszy indeks to nr wiersza, drugi indeks to nr kolumny
    float RotMatrix[3][3];

    RotMatrix[0][0] = cos(cTheta)*cos(cPhi);
    RotMatrix[0][1] = -sin(cPhi)*cos(cPsi) + cos(cPhi)*sin(cTheta)*sin(cPsi);
    RotMatrix[0][2] = sin(cPhi)*sin(cPsi) + cos(cPhi)*sin(cTheta)*cos(cPsi);
    RotMatrix[1][0] = sin(cPhi)*cos(cTheta);
    RotMatrix[1][1] = cos(cPhi)*cos(cPsi) + sin(cPhi)*sin(cTheta)*sin(cPsi);
    RotMatrix[1][2] = -cos(cPhi)*sin(cPsi) + sin(cPhi)*sin(cTheta)*cos(cPsi);
    RotMatrix[2][0] = -sin(cTheta);
    RotMatrix[2][1] = cos(cTheta)*sin(cPsi);
    RotMatrix[2][2] = cos(cTheta)*cos(cPsi);

    float determinant = 0;
    for(i = 0; i < 3; i++)
            determinant = determinant + (RotMatrix[0][i] * (RotMatrix[1][(i+1)%3] * RotMatrix[2][(i+2)%3] - RotMatrix[1][(i+2)%3] * RotMatrix[2][(i+1)%3]));
    //obsługa błędu
    if(determinant == 0)
        return 0;

    float InvMatrix[3][3];

    for(i = 0; i < 3; i++){
            for(j = 0; j < 3; j++)
                InvMatrix[i][j] = ((RotMatrix[(j+1)%3][(i+1)%3] * RotMatrix[(j+2)%3][(i+2)%3]) - (RotMatrix[(j+1)%3][(i+2)%3] * RotMatrix[(j+2)%3][(i+1)%3]))/ determinant;
        }
    float a1 = InvMatrix[0][0]*out_val_x + InvMatrix[0][1]*out_val_y + InvMatrix[0][2]*out_val_z;
    float a2 = InvMatrix[1][0]*out_val_x + InvMatrix[1][1]*out_val_y + InvMatrix[1][2]*out_val_z;
    float a3 = 2*(InvMatrix[2][0]*out_val_x + InvMatrix[2][1]*out_val_y + InvMatrix[2][2]*out_val_z)/sqrt(3);
    float a4 = 2*(InvMatrix[2][0]*out_val_x + InvMatrix[2][1]*out_val_y + InvMatrix[2][2]*out_val_z)/sqrt(3);

    float m1 = a1, m2 = a1, m3 = a1;
    float m4 = - a2 + a3 - a4;
    float m5 = a2 - a3 - a4;
    float m6 = a2 + a3 + a4;

    float* retVal = new float[6];
    retVal[0] = m1;
    retVal[1] = m2;
    retVal[2] = m3;
    retVal[3] = m4;
    retVal[4] = m5;
    retVal[5] = m6;

    float maxv = 0;
    for(int i = 0; i < 6; ++i)
    {
        if(maxv < retVal[i])
            maxv = retVal[i];
    }
    if(maxv > 1)
        for(int i = 0; i < 6; ++i)
        {
            retVal[i] = retVal[i]/maxv;
        }
    return retVal;
}
