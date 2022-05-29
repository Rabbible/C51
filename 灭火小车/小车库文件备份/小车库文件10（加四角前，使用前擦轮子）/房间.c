#include<reg51.h>    //包含单片机寄存器的头文件
#include <I2C.H>
#define  PCF8591 0x90    //PCF8591 地址
#define uint unsigned int //宏定义uint 为unsigned int类型
#define uchar unsigned char //宏定义uchar 为unsigned char 类型


// 变量定义
unsigned char AD_CHANNEL;
unsigned long xdata  LedOut[8];
unsigned int  D[32];
sbit P2_0 = P2^0;
sbit P2_1 = P2^1;
sbit P2_2 = P2^2;
sbit P2_3 = P2^3;
sbit P1_2 = P1^2;//定义舵机PWM控制端口
sbit P1_3 = P1^3;//定义舵机PWM控制端口
int PulseCount; int Velocity;

unsigned char date;

uchar code table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,
                        0xf8,0x80,0x90};


  // 函数申明 

void display();
void delay(uchar i);
bit DACconversion(unsigned char sla,unsigned char c,  unsigned char Val);
bit ISendByte(unsigned char sla,unsigned char c);
unsigned char IRcvByte(unsigned char sla);
void Initial_com(void);
void delay_nus(unsigned int i);
void delay_nms(unsigned int n);
void Forward(PulseCount,Velocity);
void Right(PulseCount,Velocity);
void Left(PulseCount,Velocity);
void Backward(PulseCount,Velocity);
//******************************************************************/
void main()
{  

	Initial_com();
	while(1)
	{  

	/********以下AD-DA处理*************/  
	
	    switch(AD_CHANNEL)
		{
			case 0: ISendByte(PCF8591,0x41);
			     D[0]=IRcvByte(PCF8591);  //ADC0 模数转换1      光敏电阻
				 break;  
			
			case 1: ISendByte(PCF8591,0x42);
			     D[1]=IRcvByte(PCF8591);  //ADC1  模数转换2	  热敏电阻
				 break;  
			
			case 2: ISendByte(PCF8591,0x43);
			     D[2]=IRcvByte(PCF8591);  //ADC2	模数转换3	   悬空
				 break;  
			
			case 3: ISendByte(PCF8591,0x40);
			     D[3]=IRcvByte(PCF8591);  //ADC3   模数转换4	   可调0-5v
				 break;  
			
			case 4: DACconversion(PCF8591,0x40, D[4]); //DAC	  数模转换
			     break;
		 
		}




//    	D[4]=D[3];  //把模拟输入采样的信号 通过数模转换输出
			
	   if(++AD_CHANNEL>4) AD_CHANNEL=0;
	
//	   /********以下将AD的值通过串口发送出去*************/
//	 delay(200);	
//	 SBUF=D[0];		   	   
//	 delay(200);		  
//	 SBUF=D[1];			   
//	 delay(200);	
//	 SBUF=D[2];
//	 delay(200);
//	 SBUF=D[3];
//	 delay(200);
//	 if(RI)
//	{
//		date=SBUF;    //单片机接受
//		SBUF=date;    //单片机发送
//		RI=0;
//	}
		if(D[0]>0x25)	/*  D[0]右边红外传感器读数   */
		{
			if(D[0]<0x4B && D[0]>0x30)
				{ 	Right(5,200);
					delay_nms(500);
					Forward(7,200);
					delay_nms(500);
					Left(5,200);
					delay_nms(500);
				}
			else if(D[0]<0x30)
				{ 	Right(10,200);
					delay_nms(1000);
					Forward(7,200);
					delay_nms(500);
					Left(11,200);
					delay_nms(1000);
				}				  
			else if(D[0]>0x56 && D[0]<0x60 ) /*&& D[1]>(D[0]+0x10)*/
					{  	Left(5,200);
						delay_nms(500);
						Forward(7,200);
						delay_nms(500);
						Right(5,200);
						delay_nms(500);
					}
			else if(D[0]>0x56 && D[0]<0x60 ) /*&& D[1]>(D[0]+0x10)*/
					{  	Left(10,200);
						delay_nms(1000);
						Forward(7,200);
						delay_nms(500);
						Right(10,200);
						delay_nms(1000);
					}
			else Forward(1,200);
		}
		
		
//		if( D[1]>0x30 && D[1]<0x51 )	 	/*  D[1]左边边红外传感器读数   */
//		{
//				{ 	Left_Turn();
//					Forward();
//					Right_Turn();
//				}				 
//		}
//		else Forward();
		// ******   舵机  ************	 
   }
}


void delay(uchar i)
{
  uchar j,k; 
  for(j=i;j>0;j--)
    for(k=125;k>0;k--);
}

/*******************************************************************
DAC 变换, 转化函数               
*******************************************************************/
bit DACconversion(unsigned char sla,unsigned char c,  unsigned char Val)
{
   Start_I2c();              //启动总线
   SendByte(sla);            //发送器件地址
   if(ack==0)return(0);
   SendByte(c);              //发送控制字节
   if(ack==0)return(0);
   SendByte(Val);            //发送DAC的数值  
   if(ack==0)return(0);
   Stop_I2c();               //结束总线
   return(1);
}

/*******************************************************************
ADC发送字节[命令]数据函数               
*******************************************************************/
bit ISendByte(unsigned char sla,unsigned char c)
{
   Start_I2c();              //启动总线
   SendByte(sla);            //发送器件地址
   if(ack==0)return(0);
   SendByte(c);              //发送数据
   if(ack==0)return(0);
   Stop_I2c();               //结束总线
   return(1);
}

/*******************************************************************
ADC读字节数据函数               
*******************************************************************/
unsigned char IRcvByte(unsigned char sla)
{  unsigned char c;

   Start_I2c();          //启动总线
   SendByte(sla+1);      //发送器件地址
   if(ack==0)return(0);
   c=RcvByte();          //读取数据0

   Ack_I2c(1);           //发送非就答位
   Stop_I2c();           //结束总线
   return(c);
}


//*****串口初始化函数***********

//******************************
void Initial_com(void)
{
 EA=1;        //开总中断
 ES=1;        //允许串口中断
 ET1=1;        //允许定时器T1的中断
 TMOD=0x20;   //定时器T1，在方式2中断产生波特率
 PCON=0x00;   //SMOD=0
 SCON=0x50;   // 方式1 由定时器控制
 TH1=0xfd;    //波特率设置为9600
 TL1=0xfd;
 TR1=1;       //开定时器T1运行控制位

}

//***   延时与舵机驱动  ********************
void delay_nus(unsigned int i)  //延时:i>=12 ,i的最小延时单12 us
{ 
  i=i/10;
  while(--i);
}   

void delay_nms(unsigned int n)  //延时n ms
{ 
  n=n+1;
  while(--n)  
  delay_nus(900);         //延时 1ms,同时进行补偿
}

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
//***************************************************************************//
