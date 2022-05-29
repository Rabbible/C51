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
sbit SIG1=P0^0; //定义信号1接收引脚
sbit SIG2=P0^1; //定义信号2接收引脚
void main()
{
	 uint a,b,c;
	 SIG1=1;
	 SIG2=1;
	while(1)
	{
		if((SIG1==0)&&(SIG2==0)) //左右火焰传感器检测都检测到火焰
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
			delay_nms(20);
				
		   }//当左右火焰传感器都检测到火焰时对应的的操作
		    }
		if((SIG1==1)&&(SIG2==0)) //左火焰传感器检测都检测到火焰
		{
		 //左转	
	    	for(b=0;b<100;b++)
	    	{
             //静止基准时间t=1500us，大于或小于1500us将使对应端口的车轮正或反转起来
               P1_3=1;
		       delay_nus(1700);
		       P1_3=0;
							 
			   P1_2=1;
			   delay_nus(1500);
			   P1_2=0;
			   delay_nms(20);
	    	}
		}
	    if((SIG1==0)&&(SIG2==1)) //右火焰传感器检测都检测到火焰
		{
		    //右转
            for(c=0;c<100;c++)
		    {
            //静止基准时间t=1500us，大于或小于1500us将使对应端口的车轮正或反转起来
              P1_3=1;
			  delay_nus(1500);
			  P1_3=0;
							 
			  P1_2=1;
			  delay_nus(1300);
			  P1_2=0;
			  delay_nms(20);
		    }
		}	  		
	}
}
