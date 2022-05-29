#include<reg51.h>   
#include<duoji.h>
#include<fan.h>

void main()
{
	SIG=1;
	SIG4=1;
	SIG5=1;
	if(SIG4==0&&SIG5==0) //QTI传感器1检测到白色边界
	{	
		SIG=0;
		Left(10,200);
	}
}
