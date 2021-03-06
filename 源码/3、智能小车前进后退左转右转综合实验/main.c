/*********************************************************************************
* 【编写时间】： 2016年12月2日
* 【作    者】： 清翔电子:03
* 【版    本】： 1.0
* 【网    站】： http://www.qxmcu.com/ 
* 【淘宝店铺】： http://qxmcu.taobao.com/ (直销店)
* 【实验平台】： QX-MCS51 单片机开发板 & QX-A51智能小车
* 【外部晶振】： 11.0592mhz	
* 【主控芯片】： STC89C52
* 【编译环境】： Keil μVisio4
* ********************************【接线说明】********************************
				                 以下"A_"表示智能小车底板~~~"B_"表示开发板     
*开发板供电线  ：A_J5-VCC~~~B_VCC或5V0    A_J6-GND~~~B_GND （一共使用2根杜邦线）
*电机控制线    ：A_J10-P1.2至P1.7 对应接到B_P1.2至P1.7 （一共使用6根杜邦线）
*避障寻迹反馈线：A_J11-P3.2至P3.5 对应接到B_P3.2至P3.5 （一共使用4根杜邦线）
******************************************************************************
* 【程序功能】：智能小车前进后退左转右转综合实验  			   			            			    
* 【使用说明】：接线无误后，烧写程序打开电源开关小车全速前进-后退-右转-左转-停止 
* 【注意事项】：避免小车撞向障碍物或小车轮子堵转，小车电压不能低于6V
**********************************************************************************/
#include <reg52.h>

sbit IN1 = P1^2; //为1 左电机反转
sbit IN2 = P1^3; //为1 左电机正转
sbit IN3 = P1^6; //为1 右电机正转
sbit IN4 = P1^7; //为1 右电机反转
sbit EN1 = P1^4; //为1 左电机使能
sbit EN2 = P1^5; //为1 右电机使能

void delay(unsigned int z)//毫秒级延时
{
	unsigned int x,y;
	for(x = z; x > 0; x--)
		for(y = 114; y > 0 ; y--);
}	

void main()
{
	//小车直行
	EN1 = 1;  //为1 左电机使能
	EN2 = 1;  //为1 右电机使能
	IN1 = 0;//为1 左电机反转
	IN2 = 1;//为1 左电机正转
	IN3 = 1;//为1 右电机正转
	IN4 = 0;//为1 右电机反转	
	delay(3000);//毫秒级延时

	//小车停止
	EN1 = 0;  //为1 左电机使能
	EN2 = 0;  //为1 右电机使能
	delay(3000);//毫秒级延时
	
	//小车后退
	EN1 = 1;  //为1 左电机使能
	EN2 = 1;  //为1 右电机使能
	IN1 = 1;//为1 左电机反转
	IN2 = 0;//为1 左电机正转
	IN3 = 0;//为1 右电机正转
	IN4 = 1;//为1 右电机反转
	delay(3000);//毫秒级延时	
	
	//小车停止
	EN1 = 0;  //为1 左电机使能
	EN2 = 0;  //为1 右电机使能
	delay(3000);//毫秒级延时

	//小车右转
	EN1 = 1; //为1 左电机使能
	EN2 = 1; //为1 右电机使能
	IN1 = 0; //为1 左电机反转
	IN2 = 1; //为1 左电机正转
	IN3 = 0; //为1 右电机正转
	IN4 = 0; //为1 右电机反转
	delay(3000);//毫秒级延时

	//小车停止
	EN1 = 0;  //为1 左电机使能
	EN2 = 0;  //为1 右电机使能
	delay(3000);//毫秒级延时

	//小车左转
	EN1 = 1; //为1 左电机使能
	EN2 = 1; //为1 右电机使能
	IN1 = 1; //为1 左电机反转
	IN2 = 1; //为1 左电机正转
	IN3 = 1; //为1 右电机正转
	IN4 = 0; //为1 右电机反转
	delay(3000);//毫秒级延时

	//小车停止
	EN1 = 0;  //为1 左电机使能
	EN2 = 0;  //为1 右电机使能		
	while(1);	
}
