#include<reg51.h>    //������Ƭ���Ĵ�����ͷ�ļ�
#include<duoji.h>
#include<AD.h>

#define uint unsigned int //�궨��uint Ϊunsigned int����
#define uchar unsigned char //�궨��uchar Ϊunsigned char ����
#define  PCF8591 0x90    //PCF8591 ��ַ 

void main()
{	uint i;
	uint idata F[10];
	delay_nms(1000);
	//Initial_com();

 	//****** ����Ϊ����ǽ�߳���	*****
	while(1)
	{
		Forward(6,200);					  // -----  ֱ��һ��֪С��ƫ��״̬    ------  
		for(i=0;i<10;i++)
		{
			ISendByte(PCF8591,0x40);
			F[i]=IRcvByte(PCF8591);
	//		send_char(D[0]);
		}
	//	while (D[0]>0x4F||D[0]<0x53)
		if(F[9]==F[0]) Forward(2,200);
		else if(F[9]<F[0])					   // -----  �ȽϾ�����ƽ��  ------
		{	
			if(F[9]-F[0]<0x02)			  /* 0x02����Ҫ��,Сƫ״̬ */
				{
					while(F[9]<F[0])
					{
						R_F(3);
						for(i=0;i<10;i++)
						{
						ISendByte(PCF8591,0x40);
						F[i]=IRcvByte(PCF8591);
						//send_char(D[0]);
						}
					}
					L_F(3);
				}
			else //if(F[9]-F[0]>=0x02)			/* ��ƫ״̬ */
				{
				 Right(6,200);	   /* PulseCount��Ҫ����F[9]-F[0]��ֵ�� */
				}
		}	   
		else //if(F[9]>F[0]) 
		{
			if(F[9]-F[0]<0x02)			  /* 0x02����Ҫ��,Сƫ״̬ */
				{
					while(F[9]>F[0])
					{
						L_F(3);
						for(i=0;i<10;i++)
						{
						ISendByte(PCF8591,0x40);
						F[i]=IRcvByte(PCF8591);
						//send_char(D[0]);
						}
					}
					R_F(3);
				}
			else //if(F[9]-F[0]>=0x02)			/* ��ƫ״̬ */
				{
				 Left(6,200);	   /* PulseCount��Ҫ����F[9]-F[0]��ֵ�� */
				}
		}
	}
}
	