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
		*********	 需要插上超声波模块  *********  
*开发板供电线  ：A_J5-VCC~~~B_VCC或5V0    A_J6-GND~~~B_GND （一共使用2根杜邦线）
*电机控制线    ：A_J10-P1.2至P1.7 对应接到B_P1.2至P1.7 （一共使用6根杜邦线）
*避障寻迹反馈线：A_J11-P3.2至P3.5 对应接到B_P3.2至P3.5 （一共使用4根杜邦线）
*超声波信号线：A_J2-P2.0  对应接到B_P20，A_J2-P2.1  对应接到B_P21 （一共使用2根杜邦线）
******************************************************************************
* 【程序功能】：QX-A51智能小车红外避障（跟随障碍物带停止功能）		   			            			    
* 【使用说明】：接线无误后，烧写程序打开电源开、按下S2按键后蜂鸣器发出提示音1秒后启动小车
* 【注意事项】：避免小车撞向障碍物或小车轮子堵转，小车电压不能低于6V
				当跟随的物体距离超声波5cm时，小车会停止
				1、不能在自然光强烈的条件下进行试验
				2、进行试验前必须调节好避障探头
				3、必须先搭建好实验环境（参考相关视频教程）
				4、此程序只做参考，实际运行效果需根据不同实验场地进行不同调试
**********************************************************************************/
#include <reg52.h> //51头文件
#include <..\CONFIG\QXA51.h>//QX-A51智能小车配置文件
#include <intrins.h>   //包含nop等系统函数
unsigned char pwm_left_val = 100;//左电机占空比值 取值范围0-170，0最快
unsigned char pwm_right_val = 100;//右电机占空比值取值范围0-170 ,0最快
unsigned char pwm_t;//周期

unsigned int  time = 0;//传输时间
unsigned long S = 0;//距离
bit      flag = 0;//超出测量范围标志位

sbit RX = P2^0;//ECHO超声波模块回响端
sbit TX = P2^1;//TRIG超声波模块触发端


void delay(unsigned int z)//毫秒级延时
{
	unsigned int x,y;
	for(x = z; x > 0; x--)
		for(y = 114; y > 0 ; y--);
}	

void Delay10us(unsigned char i)    	//10us延时函数 启动超声波模块时使用
{ 
   unsigned char j; 
	do{ 
		j = 10; 
		do{ 
			_nop_(); 
		}while(--j); 
	}while(--i); 
}

/*小车前进*/
void forward()
{
	left_motor_go; //左电机前进
	right_motor_go; //右电机前进
}
/*小车左转*/
void left_run()
{
	left_motor_stops; //左电机停止
	right_motor_go; //右电机前进	
}
/*小车右转*/
void right_run()
{
	right_motor_stops;//右电机停止
	left_motor_go;    //左电机前进
}
/*小车停止*/
void stop()
{
	right_motor_stops;//右电机停止
	left_motor_stops; //左电机停止	
}

/*定时器1中断输出PWM信号*/
void timer1() interrupt 3
{
	pwm_t++;//周期计时加
	if(pwm_t == 255)
		pwm_t = EN1 = EN2 = 0;
	if(pwm_left_val == pwm_t)//左电机占空比	
		EN1 = 1;		
	if(pwm_right_val == pwm_t)//右电机占空比
		EN2 = 1;			 
}
/*定时器0中断*/
void timer0() interrupt 1	//T0中断用来计数器溢出,超过测距范围
{
	flag=1;							 //中断溢出标志			 
}
void  StartModule() 		         //启动超声波模块
{
	  TX=1;			                     //启动一次模块
      Delay10us(2);
	  TX=0;
}

/*计算超声波所测距离并显示*/
void Conut()
{
	time=TH0*256+TL0;
	TH0=0;
	TL0=0;
	
	S=(float)(time*1.085)*0.17;     //算出来是MM
	if((S>=7000)||flag==1) //超出测量范围
	{	 
		flag=0;

	}
}


void Follow()//物体跟随
{
	//为0 识别障碍物 为1没有识别到障碍物
	if(left_led2 == 0 && right_led2 == 0)//左右识别到障碍物，前进跟随
	{
		forward();//前进
	}
	if(left_led2 == 1 && right_led2 == 0)//小车右侧识别到障碍物，右转跟随
	{
		right_run();//右转
	}
	if(left_led2 == 0 && right_led2 == 1)//小车左侧识别到障碍物，左转跟随
	{
		left_run();//左转
	}	
}

/*超声波避障*/
void	Avoid()
{
	if(S < 40)//设置避障距离（单位毫米）
	{
		beep = 0;//使能蜂鸣器
		stop();//停车
		delay(100);//停车时间
		do{
			stop();	 //停车
			delay(100);//停车时间

			 StartModule();	//启动模块测距
			 while(!RX);		//当RX（ECHO信号回响）为零时等待
			 TR0=1;			    //开启计数
			 while(RX);			//当RX为1计数并等待
			 TR0=0;				//关闭计数
		     Conut();			//计算距离
			}while(S < 40); //
		beep = 1;//关闭蜂鸣器
	}
}

void main()
{
	unsigned int i;
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
	delay(1000);//延时1秒
	TMOD |= 0x20;//定时器1工作模式2,8位自动重装。用于产生PWM
	TMOD |= 0x01;//定时器0工作模块1,16位定时模式。T0用测ECH0脉冲长度
	TH1 = 220; //
	TL1 = 220; //100HZ T1
	TH0	= 0;
    TL0	= 0;//T0,16位定时计数用于记录ECHO高电平时间         
    ET1	= 1;//允许T1中断
	ET0 = 1;//允许T0中断
	TR1 = 1;//启动定时器1
	EA  = 1;//启动总中断
	while(1)
	{
		 StartModule();	//启动模块测距
		 while(!RX);		//当RX（ECHO信号回响）为零时等待
		 TR0=1;			    //开启计数
		 while(RX);			//当RX为1计数并等待
		 TR0=0;				//关闭计数
	     Conut();			//计算距离
		 Avoid();			//避障
		 for(i=0; i<1800; i++)  //超声波每次测距间隔不低于65ms
		 	Follow();//物体跟随				
	}
}