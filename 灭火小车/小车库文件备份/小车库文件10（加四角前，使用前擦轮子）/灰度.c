#include<reg51.h>   
#include<duoji.h>
#include<fan.h>

void main()
{
	SIG=1;
	SIG4=1;
	SIG5=1;
	if(SIG4==0&&SIG5==0) //QTI������1��⵽��ɫ�߽�
	{	
		SIG=0;
		Left(10,200);
	}
}
