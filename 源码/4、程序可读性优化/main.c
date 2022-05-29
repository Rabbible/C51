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
* 【程序功能】：QX-A51智能小车程序可读性优化			   			            			    
* 【使用说明】：接线无误后，烧写程序打开电源开关小车全速前进-后退-右转-左转-高速左转
				-高速右转-停止				 
* 【注意事项】：避免小车撞向障碍物或小车轮子堵转，小车电压不能低于6V
**********************************************************************************/
#include <reg52.h>
#include <..\CONFIG\QXA51.h>

void delay(unsigned int z)//毫秒级延时
{
	unsigned int x,y;
	for(x = z; x > 0; x--)
		for(y = 114; y > 0 ; y--);
}	

/*小车前进*/
void forward()
{
	left_motor_en; //左电机使能
	right_motor_en;//右电机使能
	left_motor_go; //左电机前进
	right_motor_go; //右电机前进
}
/*小车后退*/
void backward()
{
	left_motor_en; //左电机使能
	right_motor_en;//右电机使能
	left_motor_back; //左电机后退
	right_motor_back; //右电机后退	
}
/*小车左转*/
void left()
{
	left_motor_stops; //左电机停止
	right_motor_en;//右电机使能
	right_motor_go; //右电机前进	
}
/*小车右转*/
void right()
{
	right_motor_stops;//右电机停止
	left_motor_en;    //左电机使能
	left_motor_go;    //左电机前进
}

/*小车停止*/
void stop()
{
	right_motor_stops;//右电机停止
	left_motor_stops; //左电机停止	
}
/*小车高速左转*/
void left_rapidly()
{
	left_motor_en; //左电机使能
	right_motor_en;//右电机使能
	right_motor_go;
	left_motor_back;	
}
/*小车高速右转*/
void right_rapidly()
{
	left_motor_en; //左电机使能
	right_motor_en;//右电机使能
	left_motor_go;
	right_motor_back;	
}

void main()
{
	forward();//小车前进
	delay(3000);//毫秒级延时

	stop();//小车停止
	delay(3000);//毫秒级延时

	backward();//小车后退
	delay(3000);//毫秒级延时

	stop();//小车停止
	delay(3000);//毫秒级延时

	left();	// 小车左转
	delay(3000);//毫秒级延时
	
	stop();//小车停止
	delay(3000);//毫秒级延时
	
	right();// 小车右转
	delay(3000);//毫秒级延时

	stop();//小车停止
	delay(3000);//毫秒级延时

	left_rapidly();//小车高速左转
	delay(3000);//毫秒级延时

	stop();//小车停止
	delay(3000);//毫秒级延时

	right_rapidly();//小车高速右转
	delay(3000);//毫秒级延时
	
	stop();//小车停止	
	while(1);	
}
