#include<reg51.h> 
#include<duoji.h>
#include<AD.h>
#include<zhixian.h>

#define uint unsigned int //宏定义uint 为unsigned int类型



void main()
{  	uint a,b,E=0x35;
	delay_nms(300);
	while(1)
	{
		a=DRZS();				 	// 直走一段距离感知小车偏移状态
		Forward(20,200);			/** 看看能再改小一点吗？太长会走过头 */			 
		b=DRZS();					
		if(abs(b-a)<0x02)			// 小偏状态比较纠正到平行（直走程序）  ------
		{				  /* 0x02可能要调 */
		a=DRZS();
		while(1)
			{
				RZ(&E,a);
				//if(...) break;	
			}
		}
		else if(abs(b-a)>=0x02)		/* 大偏状态,改正后进入下一次循环直走检测平行度 */
		{
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
