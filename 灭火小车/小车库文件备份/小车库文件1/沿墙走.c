#include<reg51.h>    //包含单片机寄存器的头文件
#include <I2C.H>
#include<duoji.h>
#include<AD.h>
#include<chaoshengbo.h>

void main()
{  
	Initial_com();	 //*****串口初始化函数***********
	init_9600();   /*超声波的定义*/
	T0_INIT();
	INT1_INIT();
	trig = 0;
	
	while(1)
	{  
	  	AD ();/********AD-DA处理*************/  		
	   if(++AD_CHANNEL>4) AD_CHANNEL=0;

	   if(D[0]<0x2D||D[1]<0x2D) break;				  /*  跳出循环   */
		if(D[0]>0x2D)	 /*  刚开始只有右边沿墙，控制在中间范围   */
		{

			if(D[0]<0x53)			 /*  要调控好范围、和循环次数   */
			{
				 R_F(1);			/******     舵机  ************/
			}
			else if(D[0]>0x4F)
			{
				 L_F(1);
			}
			else Forward(1,200);
		}
		else if(D[0]<0x2D&&D[1]>0x40)	  		 /*  沿左边墙走完   */
		{	
			
			 if(D[1]<0x53)			 /*  要调控好范围、和循环次数   */
			{
				 L_F(1);
			}
			else if(D[1]>0x4F)
			{
				 R_F(1);
			}
			else Forward(1,200);
				
		}	
	}

	Right(36,200);				 /*  右转90°  */
	Forward(100,200);
		while(1)
	{  
	  	AD ();/********AD-DA处理*************/  		
	  	if(++AD_CHANNEL>4) AD_CHANNEL=0;

	  	if(CSB()<=122) break;				  /*  跳出循环   */
		if(D[1]>0x40)	  		 /*  沿左边墙走   */
		{	
			 if(D[1]<0x53)			 /*  范围小了会出现在范围区，太大容易歪   */
			{
				 L_F(1);
			}
			else if(D[1]>0x4F)
			{
				 R_F(1);
			}
			else Forward(1,200);
					/*超声波*/	
		}	
	}
	Right(36,200);	/*  右转90°  */
}