/*
* 【编写时间】： 2019年6月9日
* 【作    者】： 清翔电子
* 【版    本】： 1.0
* 【网    站】： http://www.qxmbot.com/ 
* 【淘宝店铺】： http://qxmcu.taobao.com/ (直销店)
* 【实验平台】： QX-MCS51 单片机开发板 & QX-A51智能小车
* 【外部晶振】： 11.0592mhz	
* 【主控芯片】： STC89C52
* 【编译环境】： Keil μVisio4
* 【程序功能】： 舵机实验 舵机左右旋转
* 【使用说明】：
*/
#include <reg52.h> //51头文件
#include <intrins.h>   //包含nop等系统函数
sbit Servo = P2^7;//舵机接口
/*按键定义*/
sbit key_s2 = P3^0;
sbit key_s3 = P3^1;
sbit beep = P2^3;//蜂鸣器
void delay(unsigned int z)//毫秒级延时
{
	unsigned int x,y;
	for(x = z; x > 0; x--)
		for(y = 114; y > 0 ; y--);
}
/*舵机方波延时朝向小车正前方*/
void Delay1550us()		//@11.0592MHz
{
	unsigned char i, j;

	i = 3;
	j = 196;
	do
	{
		while (--j);
	} while (--i);
}

void Delay18450us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 34;
	j = 16;
	do
	{
		while (--j);
	} while (--i);
}
/*舵机方波延时向小车右方*/
void Delay600us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 15;
	do
	{
		while (--j);
	} while (--i);
}
void Delay19400us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 35;
	j = 197;
	do
	{
		while (--j);
	} while (--i);
}
/*舵机方波延时朝向小车左方*/
void Delay17500us()		//@11.0592MHz
{
	unsigned char i, j;

	i = 32;
	j = 93;
	do
	{
		while (--j);
	} while (--i);
}
void Delay2500us()		//@11.0592MHz
{
	unsigned char i, j;

	i = 5;
	j = 120;
	do
	{
		while (--j);
	} while (--i);
}

//初始化
void Init()
{
	Servo = 0;
	Servo = 1;
	Delay1550us();
	Servo = 0;
	Delay18450us();
	Servo = 1;
	delay(1000);
}
void keyscan()
{
	for(;;)	//死循环
	{
		if(key_s2 == 0)// 实时检测S2按键是否被按下
		{
			delay(5); //软件消抖
			if(key_s2 == 0)//再检测S2是否被按下
			{
				while(!key_s2);//松手检测
				beep = 0;	//使能有源蜂鸣器
				delay(200);//200毫秒延时
				beep = 1;	//关闭有源蜂鸣器
				break;		//退出FOR死循环
			}
		}
	}	
}

void main()
{
	char i;
	Init();
	keyscan();
	while(1)
	{		
		/*舵机0°*/
		for(i=0;i<10;i++)
		{	
			Servo = 1;
			Delay1550us();
			Servo = 0;
			Delay18450us();
		}
		delay(1000);
		/*舵机-90°*/
		for(i=0;i<10;i++)
		{	
			Servo = 1;
			Delay2500us();
			Servo = 0;
			Delay17500us();
		}
		delay(1000);
		/*舵机90°*/
		for(i=0;i<10;i++)
		{	
			Servo = 1;
			Delay600us();
			Servo = 0;
			Delay19400us();
		}
		delay(1000);		
	}
}