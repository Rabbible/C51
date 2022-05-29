#include <reg51.H>
#include<duoji.h>
#include<fan.h>
#define uint unsigned int //宏定义uint 为unsigned int类型
#define uchar unsigned char //宏定义uchar 为unsigned char 类型

void main()
{
	 SIG=1;			//先让电机静止
	 SIG1=1;
	 SIG2=1;
	while(1)
	{
		if((SIG1==0)&&(SIG2==0))//左右火焰传感器检测都检测到火焰		
		 {
		 	SIG =0;  		 //设置控制端口为低电平，电机运转起来
		 	Left(25,200);
		 }
		else
		SIG=1;			    
	}

}
