#include<reg51.h>    //包含单片机寄存器的头文件
#include<duoji.h>
#include<AD.h>

#define uint unsigned int //宏定义uint 为unsigned int类型
#define uchar unsigned char //宏定义uchar 为unsigned char 类型
#define  PCF8591 0x90    //PCF8591 地址 

void main()
{	uint i;
	uint idata F[10];
	delay_nms(1000);
	//Initial_com();

 	//****** 以下为沿右墙走程序	*****
	while(1)
	{
		Forward(6,200);					  // -----  直走一段知小车偏移状态    ------  
		for(i=0;i<10;i++)
		{
			ISendByte(PCF8591,0x40);
			F[i]=IRcvByte(PCF8591);
	//		send_char(D[0]);
		}
	//	while (D[0]>0x4F||D[0]<0x53)
		if(F[9]==F[0]) Forward(2,200);
		else if(F[9]<F[0])					   // -----  比较纠正到平行  ------
		{	
			if(F[9]-F[0]<0x02)			  /* 0x02可能要调,小偏状态 */
				{
					while(F[9]<F[0])
					{
						R_F(3);
						for(i=0;i<10;i++)
						{
						ISendByte(PCF8591,0x40);
						F[i]=IRcvByte(PCF8591);
						//send_char(D[0]);
						}
					}
					L_F(3);
				}
			else //if(F[9]-F[0]>=0x02)			/* 大偏状态 */
				{
				 Right(6,200);	   /* PulseCount需要根据F[9]-F[0]差值调 */
				}
		}	   
		else //if(F[9]>F[0]) 
		{
			if(F[9]-F[0]<0x02)			  /* 0x02可能要调,小偏状态 */
				{
					while(F[9]>F[0])
					{
						L_F(3);
						for(i=0;i<10;i++)
						{
						ISendByte(PCF8591,0x40);
						F[i]=IRcvByte(PCF8591);
						//send_char(D[0]);
						}
					}
					R_F(3);
				}
			else //if(F[9]-F[0]>=0x02)			/* 大偏状态 */
				{
				 Left(6,200);	   /* PulseCount需要根据F[9]-F[0]差值调 */
				}
		}
	}
}
	