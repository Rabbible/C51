#include<reg51.h> 
#include<duoji.h>
#include<AD.h>
#include<zhixian.h>

#define uint unsigned int //�궨��uint Ϊunsigned int����



void main()
{  	uint a,b,E=0x35;
	delay_nms(300);
	while(1)
	{
		a=DRZS();				 	// ֱ��һ�ξ����֪С��ƫ��״̬
		Forward(20,200);			/** �������ٸ�Сһ����̫�����߹�ͷ */			 
		b=DRZS();					
		if(abs(b-a)<0x02)			// Сƫ״̬�ȽϾ�����ƽ�У�ֱ�߳���  ------
		{				  /* 0x02����Ҫ�� */
		a=DRZS();
		while(1)
			{
				RZ(&E,a);
				//if(...) break;	
			}
		}
		else if(abs(b-a)>=0x02)		/* ��ƫ״̬,�����������һ��ѭ��ֱ�߼��ƽ�ж� */
		{
			if(b>a)
			{
			 Left(2,200);	   /* PulseCount��Ҫ����F[9]-F[0]��ֵ�� */
			}
			else if(b<a)			
			{
			 Right(2,200);	   /* PulseCount��Ҫ����F[9]-F[0]��ֵ�� */
			}
		} 
		//if(...) break;   /* ����ֱ���� */
	}
}
