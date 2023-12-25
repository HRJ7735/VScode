#include "pid.h"

typedef struct PID
{
    int Point;     //设计目标 Desired Value
    long SumError; //误差累计

    double Proportion; //比例常数 Proportional Const
    double Integral;   //积分常数 Integral Const
    double Derivative; //微分常数 Derivative Const

    int LastError; //Error[-1]
    int PrevError; //Error[-2]

} PID;

static PID pid;
static PID *spid = &pid;

//PIDsPID;
//PID*spid = &sPID;
//float Kp = 0, Ki = 0, Kd = 0;

/**
 * 描述：PID所用到的 RAM 清零
 * 输入：无
 * 输出：无
 * 注意：请在设置参数前使用。
 * 例子：PIDInit();
 * 
 */
void PIDInit(void)
{
    spid->LastError = 0;  //Error[-1]
    spid->PrevError = 0;  //Error[-2]
    spid->Proportion = 0; //比例常数 Proportional Const
    spid->Integral = 0;   //积分常数 Integral Const
    spid->Derivative = 0; //微分常数 Derivative Const
    spid->Point = 0;
    spid->SumError = 0;
}
/**
 * 描述：PID带参初始化
 * 输入：(int Point, double Proportion, double Integral, double Derivative)
 * 输出：无
 * 例子：PIDInit(12,20,0.5,14);
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
 * 描述：设置PID调节的目标值
 * 输入：期望值
 * 输出：无
 * 注意：无
 * 例子：PIDSetPoint(2000); //期望电动机的转速为 2000rpm
 * 
 */
void PIDSetPoint(int setpoint)
{
    spid->Point = setpoint;
}

/**
 * 描述：读取PID调节设置的目标值
 * 输入：无
 * 输出：所设置的期望值
 * 注意：得到的期望值将和数值的是同一个数值
 * 例子：uiSpeed ＝ PIDSetPoint(); //读取所设置的期望电动机转速
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
 * 描述：设置PID的 Kp 值
 * 输入：Kp 数值
 * 输出：无
 * 注意：这个参数在增量PID和位置PID的计算中代表着不同的意思。
 *      位置式PID中 Kp 就是比例系数
 *      增量式PID中 Kp 相当于 e(k) 的系数Kp(1+T/Ti+Td/T)
 * 例子：PIDSetKp(0.257); //设置 Kp＝0.257
 */
void PIDSetKp(double dKpp)
{
    spid->Proportion = dKpp;
}

/**
 * 描述：读取PID中所设置的 Kp 值
 * 输入：无
 * 输出：Kp 数值
 * 注意：这个参数在增量PID和位置PID的计算中代表着不同的意思。
 *      位置式PID中 Kp 就是比例系数
 *      增量式PID中 Kp 相当于 e(k) 的系数Kp(1+T/Ti+Td/T)
 * 例子：Kp ＝ PIDSetKp();
 * 
 */
double PIDGetKp(void)
{
    return (spid->Proportion);
}

/**
 * 描述：设置PID的 Ki 值
 * 输入：Ki 数值
 * 输出：无
 * 注意：这个参数在增量PID和位置PID的计算中代表着不同的意思。
 *      位置式PID中 Ki 是积分系数Kp*(T/Ti)
 *      增量式PID中 Ki 是 e(k-1) 的系数Kp*(1+2*Td/T)
 * 例子：PIDSetKi(0.367); //设置 Ki＝0.367
 * 
 */
void PIDSetKi(double dKii)
{
    spid->Integral = dKii;
}

/**
 * 描述：读取PID中所设置的 Ki 值
 * 输入：无
 * 输出：Ki 数值
 * 注意：这个参数在增量PID和位置PID的计算中代表着不同的意思。
 *      位置式PID中 Ki 是积分系数Kp*(T/Ti)
 *      增量式PID中 Ki 是 e(k-1) 的系数Kp*(1+2*Td/T)
 * 例子：dKi ＝ PIDSetKi();
 * 
 */
double PIDGetKi(void)
{
    return (spid->Integral);
}

/**
 * 描述：设置PID的 Kd 值
 * 输入：Kd 数值
 * 输出：无
 * 注意：这个参数在增量PID和位置PID的计算中代表着不同的意思。
 *      位置式PID中 Kd 是积分系数Kp*(Td/T)
 *      增量式PID中 Kd 是 e(k-2) 的系数Kp*(Td/T)
 * 例子：PIDSetKd(0.157); //设置 Kd＝0.157
 * 
 */
void PIDSetKd(double dKdd)
{
    spid->Derivative = dKdd;
}

/**
 * 描述：读取PID中所设置的 Kd 值
 * 输入：无
 * 输出：Kd 数值
 * 注意：这个参数在增量PID和位置PID的计算中代表着不同的意思。
 *      位置式PID中 Kd 是积分系数Kp*(Td/T)
 *      增量式PID中 Kd 是 e(k-2) 的系数Kp*(Td/T)
 * 例子：dKd ＝ PIDGetKd();
 * 
 */
double PIDGetKd(void)
{
    return (spid->Derivative);
}

/**
 * 描述：增量式PID计算
 * 输入：PID 调节当前采样值
 * 输出：计算增量
 * 注意：增量式PID算法的实现。
 * 例子：uiGoalvalue ＋＝ IncPIDCalc (1998); //位置式PID控制算法通过增量式控
 * 制算法递推实现，当前采样得到转速 1998rpm。
 * 
 */
int IncPIDCalc(int NextPoint)
{
    register int iError, iIncpid;                   //当前误差
    iError = spid->Point - NextPoint;               //增量计算
    iIncpid = spid->Proportion * iError             //E[k]项
              + spid->Integral * spid->LastError    //E[k－1]项
              + spid->Derivative * spid->PrevError; //E[k－2]项
                                                    //存储误差，用于下次计算
    spid->PrevError = spid->LastError;
    spid->LastError = iError;
    //返回增量值
    return (iIncpid);
}

/**
 * 描述：位置式PID计算
 * 输入：PID调节当前采样值
 * 输出：位置式PID计算出的绝对位置值
 * 注意：位置式式PID算法的实现。
 * 例子：uiGoalvalue ＝ LocPIDCalc (1998); //位置式PID控制算法，当前采样得到
 * 转速 1998rpm。
 * 
 */
unsigned int LocPIDCalc(int NextPoint)
{
    register int iError, dError;
    // float y =4* (NextPoint - spid->Point) * (NextPoint - spid->Point);

    iError = spid->Point - NextPoint;  //偏差
    spid->SumError += iError;          //积分
    dError = iError - spid->LastError; //微分
    spid->LastError = iError;
    return (spid->Proportion * iError 
            // * y     //比例项
            + spid->Integral * spid->SumError //积分项
            + spid->Derivative * dError);     //微分项
}

float PID_Deal(int16_t Expect, int16_t Real) //PID计算，Expect：期望值，Real：实际值
{
    static float Bias, Last_Bias, Ins;
    static float PWM_Value;
    Bias = Real - Expect;
    if (Bias >= 2 || Bias <= -2)
    {
        Ins += Bias;                                                                                        //积分
        PWM_Value = spid->Proportion * Bias + spid->Integral * Ins + spid->Derivative * (Bias - Last_Bias); //Bias - Last_Bias 微分
        Last_Bias = Bias;
        if (PWM_Value > 199)
            PWM_Value = 199;
        else if (PWM_Value < -199)
            PWM_Value = -199;
        return PWM_Value;
    }
    return 0;
}
