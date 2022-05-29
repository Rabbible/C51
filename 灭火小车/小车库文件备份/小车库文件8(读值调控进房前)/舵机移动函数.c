#include<reg51.h> //包含单片机寄存器的定义头文件
#define uint unsigned int //宏定义uint 为unsigned int类型
#define uchar unsigned char //宏定义uchar 为unsigned char 类型
sbit P1_2 = P1^2;//定义舵机PWM控制端口
sbit P1_3 = P1^3;//定义舵机PWM控制端口
#include<BoeBot.h>//包含舵机脉冲延时函数头文件

void Forward(void)//向前行走
{	int i;
    for(i=1;i<=65;i++)
	{
    P1_3=1;
	delay_nus(1700);
    P1_3=0;
	P1_2=1;
	delay_nus(1300);
	P1_2=0;
	delay_nms(20);
	}
}
void Right_Turn(void)//向右转
{
    int i;
    for(i=1;i<=26;i++)//右转脉冲计数循环
	{
		P1_3=1;
		delay_nus(1300);
         P1_3=0;
		P1_2=1;
		delay_nus(1300);
		P1_2=0;
		delay_nms(20);
	}
}
void Left_Turn(void)//向左转
{
    int i;
    for(i=1;i<=26;i++)//左转脉冲计数循环
	{
		P1_3=1;
		delay_nus(1700);
        P1_3=0;
		P1_2=1;
		delay_nus(1700);
		P1_2=0;
		delay_nms(20);
	}
}
void Backward(void)//后退
{
    int i;
    for(i=1;i<=65;i++)//后退脉冲计数循环
	{
		P1_3=1;
		delay_nus(1300);
         P1_3=0;
		P1_2=1;
		delay_nus(1700);
		P1_2=0;
		delay_nms(20);
	}
}

int main(void)//主函数
{
	{
		if((P2_4state()==0)&&(P2_3state()==0))//判断左右两个晶须状态，并依此分析是否该往哪个方向行走。左右两个晶须均碰到障碍物，则先后退，再左转，再左转
		{
			Backward(); //向后
			Left_Turn();//向左
			Left_Turn();//向左
		}
		else if(P1_4state()==0)//如果是右晶须碰到障碍物，则后退，再向左转
		{
			Backward();//向后
			Left_Turn();//向左
		} 
        else if(P2_3state()==0)//如果是左晶须碰到障碍物，则向右转
		{
			Backward();//向后
			Right_Turn();//向右
		}
		else //如果没有碰到任何障碍物，则向前直行
			Forward();//向前
	}
}
