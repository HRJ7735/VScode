#ifndef __PID_H
#define __PID_H
#include "stm32f4xx_hal.h"

extern float Kp, Ki, Kd;

void PIDInit(void);
void PIDinit(int Point, double Proportion, double Integral, double Derivative);
int PIDGetLast(void);
int PIDGetSum(void);
void PIDSetPoint(int setpoint);
int PIDGetSetpoint(void);

void PIDSetKp(double dKpp);
double PIDGetKp(void);

void PIDSetKi(double dKii);
double PIDGetKi(void);

void PIDSetKd(double dKdd);
double PIDGetKd(void);

int IncPIDCalc(int NextPoint);
unsigned int LocPIDCalc(int NextPoint);

float PID_Deal(int16_t Expect, int16_t Real); 

#endif /* __PID_H */
