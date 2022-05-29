#include<reg51.h>   
#include<zhixian.h>
#include<fan.h>

void main()
{
	uint x=0x28,count,idata G[20]={};
	SIG=1;
	SIG1=1;
	SIG2=1;
	SIG4=1;
	SIG5=1;

	//YLC(x);
		/* 要调试看看什么时候检测到火焰在加到相应的地方或者循环里 */
		if((SIG1==0)&&(SIG2==0)) //左右火焰传感器检测都检测到火焰
		{
		 	 x=163;
			 YLC(x);
			 //找蜡烛模式
			 for(i=0;i<49;i++)		 // i<50 ?? 40?
			 {
			 if(G[i+1]>=G[i]/*+4*/)
				 {
				 Left(1,50);
				 G[i]=CSB();
				 }
			 else
				 {
				 	Keep();
					SIG=0;
					delay_nms(5000);
					SIG=1;
					count=i;
					break;
				 }
			while(CBS()>160)	/* 利用超声波返回转回刚才的距离 */
			Right(1,150);
			Right(35,200);		//回家了
			}
		}
//		if(SIG4==0&&SIG5==0) //QTI传感器1检测到白色边界
//		{	
//			SIG=0;		   /*风扇启动最好放在舵机执行前面*/
//			Left(10,200);
//		}
	
}
