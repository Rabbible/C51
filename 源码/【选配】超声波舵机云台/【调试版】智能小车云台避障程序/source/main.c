/*
* 【编写时间】： 2019年7月23日
* 【作    者】： 清翔电子:01
* 【版    本】： 1.6
* 【网    站】： http://www.qxmcu.com/ 
* 【淘宝店铺】： http://qxmcu.taobao.com/ 
* 【实验平台】： QX-MCS51 单片机开发板 & QX-A51智能小车
* 【外部晶振】： 11.0592mhz	
* 【主控芯片】： STC89C52
* 【编译环境】： Keil μVisio4
* 【程序功能】： 调试版本云台避障，超声波云台与红外避障，1602液晶显示距离
* 【使用说明】： 1、必须接上1602液晶显示器
				 2、请将接在主控板的P32-P35的4P杜邦线拔掉
				 3、再把小车底盘上P34接到主控板的P10上，P35接到主控板的P11上

				 液晶第一行显示云台测距方向，分别为D、F前方，L左面,R右面
				 第二行是显示的距离，单位毫米
				 可以通过这个显示信息来调节智能小车避障逻辑，理论上不同实验环境
				 下都需要调试才能达到理想效果。
				 执行逻辑app.c文件夹内PTZ_Avoid();函数
* 【注意事项】： 云台不防撞
*/

#define  _MAIN_C
#include "config.h"
#include "motor.h"
#include "Delay.h"
#include "timer_ISR.h"
#include "LCD1602.h"
#include "ultrasonic.h"
#include "app.h"
#include "Servo.h"
#include "main.h"

uchar LeftSpeed, RightSpeed;//设置左右轮速度
void main()
{
	LeftSpeed	= 100;//设置左轮速度
	RightSpeed	= 130;//设置右轮速度
	IntRegInit();//中断寄存器初始化
	Timer0Init();//PWM调速初始化
	Timer1Init();//初始化定时器
	Init_LCD1602(); //LCD1602初始化
	ServoFront(); //初始化舵机朝向	
	while(1)
	{
		PTZ_Avoid();//舵机云台避障
	}
} 