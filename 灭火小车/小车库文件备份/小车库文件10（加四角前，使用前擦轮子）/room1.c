#include<reg51.h> //包含单片机寄存器的定义头文件
#define uint unsigned int //宏定义uint 为unsigned int类型
#define uchar unsigned char //宏定义uchar 为unsigned char 类型
sbit P1_2 = P1^2;//定义舵机PWM控制端口
sbit P1_3 = P1^3;//定义舵机PWM控制端口
//延时n微妙
void delay_nus(unsigned int i)  
{ 
  	i=i/10;
  	while(--i);
}   
//延时n毫妙
void delay_nms(unsigned int n)  
{ 
  	n=n+1;
  	while(--n)  
  	delay_nus(900);         
}   

//主函数
void main(void)
{
    uint a,b,c,d,e,f; 
    while(1)
	{
//前进
		for(a=0;a<100;a++)
		{
//静止基准时间t=1500us，大于或小于1500us将使对应端口的车轮正或反转起来
			P1_3=1;
			delay_nus(1700);
			P1_3=0;
							 
			P1_2=1;
			delay_nus(1300);
			P1_2=0;
			delay_nms(25);
				
		}
//右转
        for(b=0;b<100;b++)
		{
//静止基准时间t=1500us，大于或小于1500us将使对应端口的车轮正或反转起来
            P1_3=1;
			delay_nus(1500);
			P1_3=0;
							 
			P1_2=1;
			delay_nus(1300);
			P1_2=0;
			delay_nms(10);
		}
//前进
		for(c=0;c<100;c++)
		{
//静止基准时间t=1500us，大于或小于1500us将使对应端口的车轮正或反转起来
			P1_3=1;
			delay_nus(1700);
			P1_3=0;
							 
			P1_2=1;
			delay_nus(1300);
			P1_2=0;
			delay_nms(25);
				
		}
//左转	
		for(d=0;d<100;d++)
		{
//静止基准时间t=1500us，大于或小于1500us将使对应端口的车轮正或反转起来
            P1_3=1;
			delay_nus(1700);
			P1_3=0;
							 
			P1_2=1;
			delay_nus(1500);
			P1_2=0;
			delay_nms(10);
		}
//前进
		for(e=0;e<100;e++)
		{
//静止基准时间t=1500us，大于或小于1500us将使对应端口的车轮正或反转起来
			P1_3=1;
			delay_nus(1700);
			P1_3=0;
							 
			P1_2=1;
			delay_nus(1300);
			P1_2=0;
			delay_nms(25);
				
		}
//左转	
		for(f=0;f<100;f++)
		{
//静止基准时间t=1500us，大于或小于1500us将使对应端口的车轮正或反转起来
            P1_3=1;
			delay_nus(1700);
			P1_3=0;
							 
			P1_2=1;
			delay_nus(1500);
			P1_2=0;
			delay_nms(10);
		}			
	}
}	  	 