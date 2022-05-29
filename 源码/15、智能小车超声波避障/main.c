/*
* 【编写时间】： 2016年12月9日
* 【作    者】： 清翔电子:03
* 【版    本】： 1.6
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
*超声波模块反馈线：A_J2-P20~~~B_P20    A_J2-P21~~~B_P21 （一共使用2根杜邦线）
			使用前请先以正确方式接上超声波模块与1602液晶
******************************************************************************
* 【程序功能】：QX-A51智能小车超声波避障实验		   			            			    
* 【使用说明】：接线无误后，烧写程序打开电源开、按下S2按键后蜂鸣器发出提示音1秒后启动小车
* 【注意事项】：避免小车撞向障碍物或小车轮子堵转，小车电压不能低于6V
				此程序只做参考，实际运行效果需根据不同实验场地进行不同调试
				使用前请插接上1602液晶。如果液晶上无显示字符，请顺时针调节液晶对比度电位器。
				如果显示字符过浓，请逆时针调节液晶对比度电位器
				☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
	☆☆☆☆☆☆☆☆☆☆	如果没有使用1602液晶，请把P07接到GND上，否则无法运行☆☆☆☆☆☆☆☆☆☆
				☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
**********************************************************************************/
#include <reg52.h> //51头文件
#include <intrins.h>   //包含nop等系统函数
#include <..\CONFIG\QXA51.h>//QX-A51智能小车配置文件

sbit DU = P2^6;//数码管段选
sbit RX = P2^0;//ECHO超声波模块回响端
sbit TX = P2^1;//TRIG超声波模块触发端
sbit LCM_RW = P3^6;     //定义LCD引脚
sbit LCM_RS = P3^5;
sbit LCM_E = P3^4;
#define LCM_Data  P0   //定义液晶屏数据口
#define Busy    0x80   //用于检测LCM状态字中的Busy标识

unsigned char pwm_left_val = 100;//左电机占空比值 取值范围0-170，0最快
unsigned char pwm_right_val = 110;//右电机占空比值取值范围0-170 ,0最快
unsigned char pwm_t;//周期
unsigned int  time = 0;//传输时间
unsigned long S = 0;//距离
bit      flag = 0;//超出测量范围标志位

unsigned char code Range[] ="==Range Finder==";//LCD1602显示格式
unsigned char code ASCII[13] = "0123456789.-M";
unsigned char code table[]="Distance:000.0cm";
unsigned char code table1[]="!!! Out of range";
unsigned char disbuff[4] = { 0,0,0,0};//距离显示缓存

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
 
void cmg88()//关数共阴极码管
{
    DU=1;  	  
    P0=0X00;//共阴极数码管阳极给低电平，全部熄灭
    DU=0;
} 

/************************************LCD1602液晶屏驱动函数************************************************/
//*******************读状态*************************//
unsigned char ReadStatusLCM(void)
{
	LCM_Data = 0xFF; 
	LCM_RS = 0;
	Delay10us(1); 
	LCM_RW = 1;
	Delay10us(1); 
	do{
	LCM_E = 0;
	Delay10us(1); 
	LCM_E = 0;
	Delay10us(1); 
	LCM_E = 1;
	Delay10us(1); 
	}
	while (LCM_Data & Busy); //检测忙信号
	return(LCM_Data);
}

/****************写数据************************/
void WriteDataLCM(unsigned char WDLCM) 
{
	ReadStatusLCM(); //检测忙
	LCM_Data = WDLCM;
	LCM_RS = 1;
	Delay10us(1); 
	LCM_RW = 0;
	Delay10us(1); 
	LCM_E = 0; //若晶振速度太高可以在这后加小的延时
	Delay10us(1); 
	LCM_E = 0; //延时
	Delay10us(1); 
	LCM_E = 1;
	Delay10us(1); 
}

//****************写指令*************************//
void WriteCommandLCM(unsigned char WCLCM,BuysC) //BuysC为0时忽略忙检测
{
	if (BuysC) ReadStatusLCM(); //根据需要检测忙
	LCM_Data = WCLCM;
	LCM_RS = 0;
	Delay10us(1); 
	LCM_RW = 0;	
	Delay10us(1); 
	LCM_E = 0;
	Delay10us(1); 
	LCM_E = 0;
	Delay10us(1); 
	LCM_E = 1;
	Delay10us(1); 
}



//*******************LCM初始化**********************//
void LCMInit(void) 
{
	LCM_Data = 0;
	WriteCommandLCM(0x38,0); //三次显示模式设置，不检测忙信号
	delay(5); 
	WriteCommandLCM(0x38,0);
	delay(5); 
	WriteCommandLCM(0x38,0);
	delay(5); 

	WriteCommandLCM(0x38,1); //显示模式设置,开始要求每次检测忙信号
	WriteCommandLCM(0x08,1); //关闭显示
	WriteCommandLCM(0x01,1); //显示清屏
	WriteCommandLCM(0x06,1); // 显示光标移动设置
	WriteCommandLCM(0x0c,1); // 显示开及光标设置
}

//*********************按指定位置显示一个字符***********************//
void DisplayOneChar(unsigned char X, unsigned char Y, unsigned char DData)
{
	Y &= 0x1;
	X &= 0xF; //限制X不能大于15，Y不能大于1
	if (Y) X |= 0x40; //当要显示第二行时地址码+0x40;
	X |= 0x80; //算出指令码
	WriteCommandLCM(X, 1); //发命令字
	WriteDataLCM(DData); //发数据
}

//**********************按指定位置显示一串字符*************************//
void DisplayListChar(unsigned char X, unsigned char Y, unsigned char code *DData)
{
	unsigned char ListLength;

  ListLength = 0;
	Y &= 0x1;
	X &= 0xF; //限制X不能大于15，Y不能大于1
	while (DData[ListLength]>0x19) //若到达字串尾则退出
		{
			if (X <= 0xF) //X坐标应小于0xF
				{
					DisplayOneChar(X, Y, DData[ListLength]); //显示单个字符
					ListLength++;
					X++;
				}
		}
}


/***************************************************************************/

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
	
/*小车前进*/
void forward()
{
	left_motor_go; //左电机前进
	right_motor_go; //右电机前进
}

/*PWM控制使能 小车后退*/
void backward()
{
	left_motor_back; //左电机后退
	right_motor_back; //右电机后退	
}

/*小车停止*/
void stop()
{
	right_motor_stops;//右电机停止
	left_motor_stops; //左电机停止	
}

/*PWM控制使能 小车高速左转*/
void left_rapidly()
{
	left_motor_back;
	right_motor_go;	
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
/*判断S2是否被按下*/
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

/*计算超声波所测距离并显示*/
void Conut(void)
{
	time=TH0*256+TL0;
	TH0=0;
	TL0=0;
	
	S=(float)(time*1.085)*0.17;     //算出来是MM
	if((S>=7000)||flag==1) //超出测量范围
	{	 
		flag=0;
		DisplayListChar(0, 1, table1);//1602显示数组table1
	}
	else
	{
		disbuff[0]=S/1000; //距离数值千位
		disbuff[1]=S%1000/100;//距离数值百位
		disbuff[2]=S%100/10;//距离数值十位
		disbuff[3]=S%10; //距离数值个位
	    DisplayListChar(0, 1, table); //显示：Distance:000.0cm
	    DisplayOneChar(9, 1, ASCII[disbuff[0]]); //显示千位
	    DisplayOneChar(10, 1, ASCII[disbuff[1]]);	
	    DisplayOneChar(11, 1, ASCII[disbuff[2]]);
        DisplayOneChar(12, 1, ASCII[10]);		//显示 .	
	    DisplayOneChar(13, 1, ASCII[disbuff[3]]);
	}
}

/*超声波避障*/
void	Avoid()
{
	if(S < 400)//设置避障距离 ，单位毫米	刹车距离
	{
		beep = 0;//使能蜂鸣器
		stop();//停车
		backward();//后退
		delay(100);//后退时间越长、距离越远。后退是为了留出车辆转向的空间
		do{
			left_rapidly();//高速左转
			delay(90);//时间越长 转向角度越大，与实际行驶环境有关
			stop();//停车
			delay(100);//时间越长 停止时间越久长

			StartModule();	//启动模块测距，再次判断是否
			while(!RX);		//当RX（ECHO信号回响）为零时等待
			TR0=1;			    //开启计数
			while(RX);			//当RX为1计数并等待
			TR0=0;				//关闭计数
			Conut();			//计算距离
			}while(S < 280);//判断前面障碍物距离
		beep = 1;//关闭蜂鸣器
	}
	else
	{
		forward();//前进
	}	
}

void main()
{

	
	cmg88();//关数码管
	LCMInit(); //LCM初始化
	delay(5);//延时片刻

	DisplayListChar(0, 0, Range);//1602第一行显示Range数组内容
	DisplayListChar(0, 1, table);//1602第二行显示table数组内容
	keyscan();//等待按下S2启动小车
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
		 delay(65);			//测试周期不低于60MS		  
	}
}