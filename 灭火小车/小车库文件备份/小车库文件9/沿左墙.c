#include<reg51.h>    //包含单片机寄存器的头文件
#include<duoji.h>
#include<AD.h>
#include<zhixian.h>
#include<chaoshengbo.h>

void main()
{  	
	uint a,b,E=0x35;
	delay_nms(200);
	// 沿左墙走循环函数
	while(E>0x31)
	{	
		a=DRZS();				 	// 直走一段距离感知小车偏移状态
		Forward(20,200);			/** 看看能再改小一点吗？ */			 
		b=DRZS();					
		if(abs(b-a)<0x02)			// 小偏状态比较纠正到平行（直走程序）  ------
		{				  /* 0x02可能要调 */
		a=DLZS();
		while(E>0x31)
			{
				LZ(&E,a);
				//if(E<0x2D) break;	
			}
		}
		else if(abs(b-a)>=0x02)		/* 大偏状态,改正后进入下一次循环直走检测平行度 */
		{
			if(b>a)
			{
			 Right(2,200);	   /* PulseCount需要根据F[9]-F[0]差值调 */
			}
			else if(b<a)			
			{
			 Left(2,200);	   /* PulseCount需要根据F[9]-F[0]差值调 */
			}
		}
	}
	while(1)
	Keep();
}