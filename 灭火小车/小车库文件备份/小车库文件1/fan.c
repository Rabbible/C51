#include <REGX51.H>
#include< BoeBot.h>//包含舵机脉冲延时函数头文件
#define uint unsigned int //宏定义uint 为unsigned int类型
#define uchar unsigned char //宏定义uchar 为unsigned char 类型
sbit SIG = P1^0; //定义信号控制引脚
sbit SIG1 = P0^0; //定义信号1接收引脚
sbit SIG2 = P0^1; //定义信号2接收引脚
sbit P12 = P1^2;//定义舵机PWM控制端口
sbit P13 = P1^3;//定义舵机PWM控制端口

void Right_Turn(void)//向右转
{
    int i;
    for(i=1;i<=55;i++)//右转脉冲计数循环
	{
		P13=1;
		delay_nus(1450);
         P13=0;
		P12=1;
		delay_nus(1450);
		P12=0;
		delay_nms(20);
	}
}
void Left_Turn(void)//向左转
{
    int i;
    for(i=1;i<=25;i++)//左转脉冲计数循环
	{
		P13=1;
		delay_nus(1550);
        P13=0;
		P12=1;
		delay_nus(1550);
		P12=0;
		delay_nms(20);
	}
}

void main()
{
	 SIG=1;//先让电机静止
	 SIG1=1;
	 SIG2=1;
	while(1)
	{
		if((SIG1==0)&&(SIG2==0))//左右火焰传感器检测都检测到火焰		
		 {
		 	SIG =0;  
		 	Left_Turn();
		 	Right_Turn();
		 }
		else
		SIG=1;	//设置控制端口为低电平，电机运转起来		    
	}

}
