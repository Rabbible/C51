#include<reg51.h>    //������Ƭ���Ĵ�����ͷ�ļ�
#include<zhixian.h>
#include<luxian.h>
//#include<fan.h>
#define uint unsigned int

void main()
{	
	T0_INIT();
	INT1_INIT();
	trig = 0;
	
	
	YRQ(0x2D);
	TwoFJF();
	while(1);	
}