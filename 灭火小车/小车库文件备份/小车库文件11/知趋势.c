#include<reg51.h>    //包含单片机寄存器的头文件
#include<duoji.h>
#include<AD.h>
#include<zhixian.h>

#define uint unsigned int //宏定义uint 为unsigned int类型
#define uchar unsigned char //宏定义uchar 为unsigned char 类型
#define  PCF8591 0x90    //PCF8591 地址
 
uint i,a,b;
uint idata F[10]={0};

void main()
{	
	
	delay_nms(500);

 	//****** 以下为识别纠正小车大偏角程序	*****
delay_nms(500);
	while(1)
	{
		a=DRZS();				 	// 直走一段距离感知小车偏移状态
		Forward(10,200);			/** 看看能再改小一点吗？ */			 
		b=DRZS();					
		if(abs(b-a)<0x02)			// 小偏状态比较纠正到平行（直走程序）  ------
		{
		send_char(abs(b-a));				  /* 0x02可能要调 */
		a=DRZS();
		while(1)
			{
				Keep();
				//if(...) break;	
			}
		}
		else if(abs(b-a)>=0x02)		/* 大偏状态,改正后进入下一次循环直走检测平行度 */
		{	send_char(abs(b-a));
			if(b>a)
			{
			 Left(2,200);	   /* PulseCount需要根据F[9]-F[0]差值调 */
			}
			else if(b<a)			
			{
			 Right(2,200);	   /* PulseCount需要根据F[9]-F[0]差值调 */
			}
		} 
		//if(...) break;   /* 不走直线了 */
	}	   
}
