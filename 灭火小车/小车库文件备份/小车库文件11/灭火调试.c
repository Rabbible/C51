#include <REG51.H>
#include<zhixian.h>
#include<fan.h>

void main()
{	 SIG = 1;
	 SIG1=1;
	 SIG2=1;
	while(1)
	{
		SIG = 1;
		if((SIG1==0)&&(SIG2==0))//左右火焰传感器检测都检测到火焰
		{
			SIG =0;
			delay_nms(300);//当左右火焰传感器都检测到火焰时对应的的操作
		}
		else  //当左右火焰传感器都没有检测到火焰时对应的的操作
	    {
			Keep(); 
     	}
	}
}