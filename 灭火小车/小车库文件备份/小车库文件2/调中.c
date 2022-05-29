#include<reg51.h>    //包含单片机寄存器的头文件
#include <I2C.H>
#include<duoji.h>
#include<AD.h>

void main()
{
// -----  左右转一个角度并获取距墙一系列数值   ------  	
	uint A[40],i;
	uint B[40]={0xFF};

	for(i=0;i<20;i++)		 /* 循环与转的角度相关 */
	{
		Left(1,100);
		ISendByte(PCF8591,0x41); 
		D[0]=IRcvByte(PCF8591);
		A[i]=D[0];
	}
	Right(20,100);		/* 回到初始状态 注意要将硬件和舵机函数调好*/
	for(i=0;i<20;i++)
	{
		Right(1,100);
		ISendByte(PCF8591,0x41); 
		D[0]=IRcvByte(PCF8591);
		A[i]=D[0];
	} 

// -----  找距离的最小值   ------
	for(i=0;i<39;i++)
	{
	 	if(A[i+1]>0x2D)
		{
			if(B[i]>A[i+1])
			B[i]=A[i+1];	/* B[i]赋予最小值，即B[38] */
		}
	}

// -----  调整为读到最小距离时的状态   ------	
	for(i=0;i<40;i++)		/* 寻找该状态时的A[i],并提取i，调整角度 */
	{
	 	if(A[i]==B[38])
		{
		 	if(i<20)  Left(i,100);
			else  Right(i,100);
			break;
		}
	}	
// -----  舵机前进   ------
	  while(1)
	  {	
	  	AD();
		if(D[0]<0x2D||D[1]<0x2D) break;				  /*  跳出循环   */
		if(D[0]>0x2D)	 /*  刚开始只有右边沿墙，调整方向  */
			{
				if(D[0]<B[38]+0x02)			 /*  要调控好范围、和循环次数   */
				{
					 R_F(1);			/******     舵机  ************/
				}
				else if(D[0]>B[38]-0x02)
				{
					 L_F(1);
				}
				else Forward(1,200);
			}
		else if(D[0]<0x2D&&D[1]>0x4F)	  		 /*  沿左边墙走完   */
			{	
			
				 if(D[1]<B[38]+0x02)			 /*  要调控好范围、和循环次数   */
				{
					 L_F(1);
				}
				else if(D[1]>B[38]-0x02)
				{
					 R_F(1);
				}
				else Forward(1,200);
					
			}
		}
		
		while(1);/* 等待 */	
}