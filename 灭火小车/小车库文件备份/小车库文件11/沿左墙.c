#include<reg51.h>    //������Ƭ���Ĵ�����ͷ�ļ�
#include<duoji.h>
#include<AD.h>
#include<zhixian.h>
#include<chaoshengbo.h>

void main()
{  	
	uint a,b,E=0x35;
	delay_nms(200);
	// ����ǽ��ѭ������
	while(E>0x31)
	{	
		a=DRZS();				 	// ֱ��һ�ξ����֪С��ƫ��״̬
		Forward(20,200);			/** �������ٸ�Сһ���� */			 
		b=DRZS();					
		if(abs(b-a)<0x02)			// Сƫ״̬�ȽϾ�����ƽ�У�ֱ�߳���  ------
		{				  /* 0x02����Ҫ�� */
		a=DLZS();
		while(E>0x31)
			{
				LZ(&E,a);
				//if(E<0x2D) break;	
			}
		}
		else if(abs(b-a)>=0x02)		/* ��ƫ״̬,�����������һ��ѭ��ֱ�߼��ƽ�ж� */
		{
			if(b>a)
			{
			 Right(2,200);	   /* PulseCount��Ҫ����F[9]-F[0]��ֵ�� */
			}
			else if(b<a)			
			{
			 Left(2,200);	   /* PulseCount��Ҫ����F[9]-F[0]��ֵ�� */
			}
		}
	}
	while(1)
	Keep();
}