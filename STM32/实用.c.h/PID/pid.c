#include "pid.h"

typedef struct PID
{
    int Point;     //���Ŀ�� Desired Value
    long SumError; //����ۼ�

    double Proportion; //�������� Proportional Const
    double Integral;   //���ֳ��� Integral Const
    double Derivative; //΢�ֳ��� Derivative Const

    int LastError; //Error[-1]
    int PrevError; //Error[-2]

} PID;

static PID pid;
static PID *spid = &pid;

//PIDsPID;
//PID*spid = &sPID;
//float Kp = 0, Ki = 0, Kd = 0;

/**
 * ������PID���õ��� RAM ����
 * ���룺��
 * �������
 * ע�⣺�������ò���ǰʹ�á�
 * ���ӣ�PIDInit();
 * 
 */
void PIDInit(void)
{
    spid->LastError = 0;  //Error[-1]
    spid->PrevError = 0;  //Error[-2]
    spid->Proportion = 0; //�������� Proportional Const
    spid->Integral = 0;   //���ֳ��� Integral Const
    spid->Derivative = 0; //΢�ֳ��� Derivative Const
    spid->Point = 0;
    spid->SumError = 0;
}
/**
 * ������PID���γ�ʼ��
 * ���룺(int Point, double Proportion, double Integral, double Derivative)
 * �������
 * ���ӣ�PIDInit(12,20,0.5,14);
 * 
 */
void PIDinit(int Point, double Proportion, double Integral, double Derivative)
{
    spid->LastError = 0; //Error[-1]
    spid->PrevError = 0; //Error[-2]
    spid->SumError = 0;
    spid->Point = Point;
    spid->Proportion = Proportion;
    spid->Integral = Integral;
    spid->Derivative = Derivative;
}

/**
 * ����������PID���ڵ�Ŀ��ֵ
 * ���룺����ֵ
 * �������
 * ע�⣺��
 * ���ӣ�PIDSetPoint(2000); //�����綯����ת��Ϊ 2000rpm
 * 
 */
void PIDSetPoint(int setpoint)
{
    spid->Point = setpoint;
}

/**
 * ��������ȡPID�������õ�Ŀ��ֵ
 * ���룺��
 * ����������õ�����ֵ
 * ע�⣺�õ�������ֵ������ֵ����ͬһ����ֵ
 * ���ӣ�uiSpeed �� PIDSetPoint(); //��ȡ�����õ������綯��ת��
 * 
 */
int PIDGetSetpoint(void)
{
    return (spid->Point);
}
int PIDGetLast(void)
{
    return (spid->LastError);
}
int PIDGetSum(void)
{
    return (spid->SumError);
}

/**
 * ����������PID�� Kp ֵ
 * ���룺Kp ��ֵ
 * �������
 * ע�⣺�������������PID��λ��PID�ļ����д����Ų�ͬ����˼��
 *      λ��ʽPID�� Kp ���Ǳ���ϵ��
 *      ����ʽPID�� Kp �൱�� e(k) ��ϵ��Kp(1+T/Ti+Td/T)
 * ���ӣ�PIDSetKp(0.257); //���� Kp��0.257
 */
void PIDSetKp(double dKpp)
{
    spid->Proportion = dKpp;
}

/**
 * ��������ȡPID�������õ� Kp ֵ
 * ���룺��
 * �����Kp ��ֵ
 * ע�⣺�������������PID��λ��PID�ļ����д����Ų�ͬ����˼��
 *      λ��ʽPID�� Kp ���Ǳ���ϵ��
 *      ����ʽPID�� Kp �൱�� e(k) ��ϵ��Kp(1+T/Ti+Td/T)
 * ���ӣ�Kp �� PIDSetKp();
 * 
 */
double PIDGetKp(void)
{
    return (spid->Proportion);
}

/**
 * ����������PID�� Ki ֵ
 * ���룺Ki ��ֵ
 * �������
 * ע�⣺�������������PID��λ��PID�ļ����д����Ų�ͬ����˼��
 *      λ��ʽPID�� Ki �ǻ���ϵ��Kp*(T/Ti)
 *      ����ʽPID�� Ki �� e(k-1) ��ϵ��Kp*(1+2*Td/T)
 * ���ӣ�PIDSetKi(0.367); //���� Ki��0.367
 * 
 */
void PIDSetKi(double dKii)
{
    spid->Integral = dKii;
}

/**
 * ��������ȡPID�������õ� Ki ֵ
 * ���룺��
 * �����Ki ��ֵ
 * ע�⣺�������������PID��λ��PID�ļ����д����Ų�ͬ����˼��
 *      λ��ʽPID�� Ki �ǻ���ϵ��Kp*(T/Ti)
 *      ����ʽPID�� Ki �� e(k-1) ��ϵ��Kp*(1+2*Td/T)
 * ���ӣ�dKi �� PIDSetKi();
 * 
 */
double PIDGetKi(void)
{
    return (spid->Integral);
}

/**
 * ����������PID�� Kd ֵ
 * ���룺Kd ��ֵ
 * �������
 * ע�⣺�������������PID��λ��PID�ļ����д����Ų�ͬ����˼��
 *      λ��ʽPID�� Kd �ǻ���ϵ��Kp*(Td/T)
 *      ����ʽPID�� Kd �� e(k-2) ��ϵ��Kp*(Td/T)
 * ���ӣ�PIDSetKd(0.157); //���� Kd��0.157
 * 
 */
void PIDSetKd(double dKdd)
{
    spid->Derivative = dKdd;
}

/**
 * ��������ȡPID�������õ� Kd ֵ
 * ���룺��
 * �����Kd ��ֵ
 * ע�⣺�������������PID��λ��PID�ļ����д����Ų�ͬ����˼��
 *      λ��ʽPID�� Kd �ǻ���ϵ��Kp*(Td/T)
 *      ����ʽPID�� Kd �� e(k-2) ��ϵ��Kp*(Td/T)
 * ���ӣ�dKd �� PIDGetKd();
 * 
 */
double PIDGetKd(void)
{
    return (spid->Derivative);
}

/**
 * ����������ʽPID����
 * ���룺PID ���ڵ�ǰ����ֵ
 * �������������
 * ע�⣺����ʽPID�㷨��ʵ�֡�
 * ���ӣ�uiGoalvalue ���� IncPIDCalc (1998); //λ��ʽPID�����㷨ͨ������ʽ��
 * ���㷨����ʵ�֣���ǰ�����õ�ת�� 1998rpm��
 * 
 */
int IncPIDCalc(int NextPoint)
{
    register int iError, iIncpid;                   //��ǰ���
    iError = spid->Point - NextPoint;               //��������
    iIncpid = spid->Proportion * iError             //E[k]��
              + spid->Integral * spid->LastError    //E[k��1]��
              + spid->Derivative * spid->PrevError; //E[k��2]��
                                                    //�洢�������´μ���
    spid->PrevError = spid->LastError;
    spid->LastError = iError;
    //��������ֵ
    return (iIncpid);
}

/**
 * ������λ��ʽPID����
 * ���룺PID���ڵ�ǰ����ֵ
 * �����λ��ʽPID������ľ���λ��ֵ
 * ע�⣺λ��ʽʽPID�㷨��ʵ�֡�
 * ���ӣ�uiGoalvalue �� LocPIDCalc (1998); //λ��ʽPID�����㷨����ǰ�����õ�
 * ת�� 1998rpm��
 * 
 */
unsigned int LocPIDCalc(int NextPoint)
{
    register int iError, dError;
    // float y =4* (NextPoint - spid->Point) * (NextPoint - spid->Point);

    iError = spid->Point - NextPoint;  //ƫ��
    spid->SumError += iError;          //����
    dError = iError - spid->LastError; //΢��
    spid->LastError = iError;
    return (spid->Proportion * iError 
            // * y     //������
            + spid->Integral * spid->SumError //������
            + spid->Derivative * dError);     //΢����
}

float PID_Deal(int16_t Expect, int16_t Real) //PID���㣬Expect������ֵ��Real��ʵ��ֵ
{
    static float Bias, Last_Bias, Ins;
    static float PWM_Value;
    Bias = Real - Expect;
    if (Bias >= 2 || Bias <= -2)
    {
        Ins += Bias;                                                                                        //����
        PWM_Value = spid->Proportion * Bias + spid->Integral * Ins + spid->Derivative * (Bias - Last_Bias); //Bias - Last_Bias ΢��
        Last_Bias = Bias;
        if (PWM_Value > 199)
            PWM_Value = 199;
        else if (PWM_Value < -199)
            PWM_Value = -199;
        return PWM_Value;
    }
    return 0;
}
