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
		if((SIG1==0)&&(SIG2==0))//���һ��洫������ⶼ��⵽����
		{
			SIG =0;
			delay_nms(300);//�����һ��洫��������⵽����ʱ��Ӧ�ĵĲ���
		}
		else  //�����һ��洫������û�м�⵽����ʱ��Ӧ�ĵĲ���
	    {
			Keep(); 
     	}
	}
}