#include<reg51.h>  //包含51单片机寄存器定义的头文件

#define uint unsigned int 
#define uchar unsigned char 

#define true  1 
#define false 0 
	
uchar datah,datal;
uint int_count=0;//中断计数
uint int_count_r=0;//红色滤波器中断计数
uint int_count_b=0;//蓝色滤波器中断计数
uint int_count_g=0;//绿色滤波器中断计数
uint t0_count=0;//定时溢出计数
uint t0_count_r=0;//红色滤波器溢出计数
uint t0_count_b=0;//蓝色滤波器溢出计数
uint t0_count_g=0;//绿色滤波器溢出计数

char flag_white_balance = false;//白平衡操作标志
char flag_check_r = false;//红色滤波器操作标志
char flag_check_b = false;//蓝色滤波器操作标志
char flag_check_g = false;//绿色滤波器操作标志

sbit S0=P0^3;
sbit S1=P1^1;
sbit LED=P3^7;
sbit OUT=P2^5;
sbit tes=P2^7;
sbit S2=P0^7;
sbit S3=P2^3;
sbit ss=P2^6;

//串口初始化
void init_9600(void)
{
		TMOD = 0x20;			
		TH1 = 0xFD;		
		TL1 = 0xFD;
		SCON = 0x50;			
		PCON &= 0xef;		
		TR1 = 1;				
	
		IE = 0x0;		

}
//发送一个字节
void send_char(unsigned char txd)
{
		SBUF = txd;
		while(!TI);			
		TI = 0;					
}
//定时器0初始化
T0_INIT()
{
		TMOD &= 0xF0; /* Timer 0 mode 1 with software gate */ 
		TMOD |= 0x01; /* GATE0=0; C/T0#=0; M10=0; M00=1; */ 
		TH0 = 0x00; /* init values */ 
		TL0 = 0x00; 
		ET0=1; /* enable timer0 interrupt */ 
		//EA=1; /* enable interrupts */ 
		//TR0=1; /* timer0 run */
}
//外部中断1初始化
INT1_INIT()
{
	
	IT1=1;//负跳变中断产生
	EX1=1;//启动外部0中断
	//EA=1;
}
 
//延时函数1毫秒
void delay1ms()
{
   unsigned char i,j;	
	 for(i=0;i<10;i++)
	  for(j=0;j<33;j++)
	   ;		 
 }

//延时函数，n毫秒
 void delaynms(unsigned int n)
 {
   unsigned int i;
	for(i=0;i<n;i++)
	   delay1ms();
 }

//颜色检测
void color_check()
{
		T0_INIT();
		INT1_INIT();
	
		//选定输出比例因子为1 ：1
		S0=1;
		S1=1;
		//点亮LED灯
		LED=1;
	
		//选通红色滤波器
		S2=0;
		S3=0;
		//其他数据量的设定
		flag_white_balance = false;
		flag_check_r = true;
		flag_check_b = false;
		flag_check_g = false;
		int_count=0;//计数255
		t0_count=0;//计数red滤波器时定时器溢出数
		TH0 = 0x0ff; //定时器时间初值,溢出时间为0.1ms
		TL0 = 0x0a3;
		ss=1;//P2.6信号测试口
		//开启中断和计数
		EX1=1;//外部0中断开启
		EA=1;//总中断开启
		TR0=1;//定时器0启动定时
		while(t0_count_r!=t0_count);//等待红色滤波器时间基准到
		
		int_count_r = int_count;//时间基准到脉冲数计数值
		datal = int_count_r;
		datah = int_count_r>>8;
		
		send_char(datah);
		send_char(datal);

		//选通蓝色滤波器
		S2=0;
		S3=1;
		//其他数据量的设定
		flag_white_balance = false;
		flag_check_r = false;
		flag_check_b = true;
		flag_check_g = false;
		int_count=0;//计数255
		t0_count=0;//计数red滤波器时定时器溢出数
		TH0 = 0x0ff; //定时器时间初值,溢出时间为0.1ms
		TL0 = 0x0a3;
		ss=1;//P2.6信号测试口
		//开启中断和计数
		EX1=1;//外部0中断开启
		//EA=1;//总中断开启
		TR0=1;//定时器0启动定时
		while(t0_count_b!=t0_count);//等待蓝色滤波器时间基准到
		
		int_count_b = int_count;//时间基准到脉冲数计数值
		datal = int_count_b;
		datah = int_count_b>>8;
		
		send_char(datah);
		send_char(datal);
		
		//选通绿色滤波器
		S2=1;
		S3=1;
		//其他数据量的设定
		flag_white_balance = false;
		flag_check_r = false;
		flag_check_b = false;
		flag_check_g = true;
		int_count=0;//计数255
		t0_count=0;//计数red滤波器时定时器溢出数
		TH0 = 0x0ff; //定时器时间初值,溢出时间为0.1ms
		TL0 = 0x0a3;
		ss=1;//P2.6信号测试口
		//开启中断和计数
		EX1=1;//外部0中断开启
		//EA=1;//总中断开启
		TR0=1;//定时器0启动定时
		while(t0_count_g!=t0_count);//等待绿色滤波器时间基准到
		
		int_count_g = int_count;//时间基准到脉冲数计数值
		datal = int_count_g;
		datah = int_count_g>>8;
		
		send_char(datah);
		send_char(datal);
		
		//关闭电源
		S0=0;
		S1=0;
		//关闭LED灯
		LED = 0;
		//关总中断
		EA=0;
		//while(1);
		
}
//白平衡
void color_white_balance()
{
		T0_INIT();
		INT1_INIT();
		flag_white_balance = true;
		flag_check_r = false;
		flag_check_b = false;
		flag_check_g = false;
		//选定输出比例因子为1 ：1
		S0=1;
		S1=1;
		//点亮LED灯
		LED=1;
	
		//选通红色滤波器
		S2=0;
		S3=0;
		//其他数据量的设定
		int_count=0;//计数255
		t0_count=0;//计数red滤波器时定时器溢出数
		TH0 = 0x0ff; //定时器时间初值,溢出时间为0.1ms
		TL0 = 0x0a3;
		ss=1;//P2.6信号测试口
		//开启中断和计数
		EX1=1;//外部0中断开启
		EA=1;//总中断开启
		TR0=1;//定时器0启动定时
		while(255!=int_count);//计数255到
		
		t0_count_r = t0_count;
		datal = t0_count_r;
		datah = t0_count_r>>8;
		
		send_char(datah);
		send_char(datal);
		
		//选通蓝色滤波器
		S2=0;
		S3=1;
		//其他数据量的设定
		int_count=0;//计数255
		t0_count=0;//计数red滤波器时定时器溢出数
		TH0 = 0x0ff; //定时器时间初值,溢出时间为0.1ms
		TL0 = 0x0a3;
		ss=1;//P2.6信号测试口
		//开启中断和计数
		EX1=1;//外部0中断开启
		//EA=1;//总中断开启
		TR0=1;//定时器0启动定时
		while(255!=int_count);//计数255到
		
		t0_count_b = t0_count;
		datal = t0_count_b;
		datah = t0_count_b>>8;
		
		send_char(datah);
		send_char(datal);
		
		//选通绿色滤波器
		S2=1;
		S3=1;
		//其他数据量的设定
		int_count=0;//计数255
		t0_count=0;//计数red滤波器时定时器溢出数
		TH0 = 0x0ff; //定时器时间初值,溢出时间为0.1ms
		TL0 = 0x0a3;
		ss=1;//P2.6信号测试口
		//开启中断和计数
		EX1=1;//外部0中断开启
		//EA=1;//总中断开启
		TR0=1;//定时器0启动定时
		while(255!=int_count);//计数255到
		
		t0_count_g = t0_count;
		datal = t0_count_g;
		datah = t0_count_g>>8;
		
		send_char(datah);
		send_char(datal);
		
		//关闭电源
		S0=0;
		S1=0;
		//关闭LED灯
		LED = 0;
		//关总中断
		EA=0;
		//while(1);

}
//外部中断1中断服务函数
void it_INT1(void) interrupt 2 
{ 
	IE1 = 0; 
	int_count++;//脉冲数计数
	if(flag_white_balance == true)
	{
			if(255==int_count)
			{
				EX1=0;
				TR0=0;
				ss=0;//P2.6信号测试口
			}
	}
	
	tes = ~tes;
	
}
//定时器0中断服务函数
void it_timer0(void) interrupt 1 
{ 
	TF0 = 0; 

	TH0 = 0x0ff; 
	TL0 = 0x0a3;
	t0_count++;//定时器溢出数计数
	if(flag_check_r == true)
	{
			if(t0_count_r==t0_count)//与白平衡基准时间一致
			{
				EX1=0;
				TR0=0;
				ss=0;//P2.6信号测试口
			}
	}
	if(flag_check_b == true)
	{
			if(t0_count_b==t0_count)//与白平衡基准时间一致
			{
				EX1=0;
				TR0=0;
				ss=0;//P2.6信号测试口
			}
	}
	if(flag_check_g == true)
	{
			if(t0_count_g==t0_count)//与白平衡基准时间一致
			{
				EX1=0;
				TR0=0;
				ss=0;//P2.6信号测试口
			}
	}
		
}

//主函数
void main(void)
{
		init_9600();
		tes=0;
		ss=0;
		delaynms(1000);
		color_white_balance();//白平衡
		delaynms(1000);
		while(1)
		{
			color_check();//颜色检测
			send_char(0xff);
			delaynms(3000);
			//while(1);
		}
}
