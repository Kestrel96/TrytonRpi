#ifndef PID_H
#define PID_H


class PID
{
public:

    PID();
    void Compute(double sp, double pv);
    void Tuning(double kp, double Ki, double Kd, double dt);
    void Reset();
    void Print();


    double CV;

private:

    double kp;
    double Ki;
    double Kd;
    double dt;

    double SP;
    double e;
    double last_e;
    long double e_sum;

    double P;
    double I;
    double D;

};

#endif // PID_H
