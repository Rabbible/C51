#include<reg51.h>    //������Ƭ���Ĵ�����ͷ�ļ�
#include<duoji.h>
#include<AD.h>
#include<zhixian.h>

#define uint unsigned int //�궨��uint Ϊunsigned int����
#define uchar unsigned char //�궨��uchar Ϊunsigned char ����
#define  PCF8591 0x90    //PCF8591 ��ַ
 
uint i,a,b;
uint idata F[10]={0};

void main()
{	
	
	delay_nms(500);

 	//****** ����Ϊʶ�����С����ƫ�ǳ���	*****
delay_nms(500);
	while(1)
	{
		a=DRZS();				 	// ֱ��һ�ξ����֪С��ƫ��״̬
		Forward(10,200);			/** �������ٸ�Сһ���� */			 
		b=DRZS();					
		if(abs(b-a)<0x02)			// Сƫ״̬�ȽϾ�����ƽ�У�ֱ�߳���  ------
		{
		send_char(abs(b-a));				  /* 0x02����Ҫ�� */
		a=DRZS();
		while(1)
			{
				Keep();
				//if(...) break;	
			}
		}
		else if(abs(b-a)>=0x02)		/* ��ƫ״̬,�����������һ��ѭ��ֱ�߼��ƽ�ж� */
		{	send_char(abs(b-a));
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
