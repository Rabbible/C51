#include<reg51.h> //包含单片机寄存器的定义头文件
#define uint unsigned int //宏定义uint 为unsigned int类型
#define uchar unsigned char //宏定义uchar 为unsigned char 类型
sbit P1_2 = P1^2;//定义舵机PWM控制端口
sbit P1_3 = P1^3;//定义舵机PWM控制端口

#include<BoeBot.h>//包含舵机脉冲延时函数头文件
int PulseCount; int Velocity;
void Forward(PulseCount,Velocity)//定义向前函数，带脉冲计数参数PulseCount和脉冲宽度参数Velocity
{
    int i;
    for(i=1;i<= PulseCount;i++)//for循环控制运行时间
	{
		P1_3=1;
		delay_nus(1500+ Velocity);
        P1_3=0;
		P1_2=1;
		delay_nus(1500- Velocity);
		P1_2=0;
		delay_nms(20);
	}
}
void Right(PulseCount,Velocity) //定义左转函数，带脉冲计数参数PulseCount和脉冲宽度参数Velocity
{   
    int i;
    for(i=1;i<= PulseCount;i++)//for循环控制运行时间
	{
		P1_3=1;
		delay_nus(1500-Velocity);
        P1_3=0;
		P1_2=1;
		delay_nus(1500-Velocity);
		P1_2=0;
		delay_nms(20);
	}
}
void Left(PulseCount,Velocity) //定义右转函数，带脉冲计数参数PulseCount和脉冲宽度参数Velocity
{
    int i;
    for(i=1;i<= PulseCount;i++)//for循环控制运行时间
	{
		P1_3=1;
		delay_nus(1500+Velocity);
        P1_3=0;
		P1_2=1;
		delay_nus(1500+Velocity);
		P1_2=0;
		delay_nms(20);
	}
}
void Backward(PulseCount,Velocity)//定义向后函数，带脉冲计数参数PulseCount和脉冲宽度参数Velocity
{
    int i;
    for(i=1;i<= PulseCount;i++)//for循环控制运行时间
	{
		P1_3=1;
		delay_nus(1500-Velocity);
        P1_3=0;
		P1_2=1;
		delay_nus(1500+ Velocity);
		P1_2=0;
		delay_nms(20);
	}
}
int main(void)//主函数
{ 

	Forward(65,200);//向前
	Left(26,200);//左转
	Right(26,200);//右转
	Backward(65,200);//向后
	while(1);//程序等待
}
