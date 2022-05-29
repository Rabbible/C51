#include<duoji.h>
#include<AD.h>
#define uint unsigned int //�궨��uint Ϊunsigned int����
#define uchar unsigned char
#define  PCF8591 0x90    //PCF8591 ��ַ

// ----   �����ֵ	  -----
int abs(int t)
{
	if(t>0)
	return t;
	else
	return -t;
}

float Average(uchar idata G[10])
{
	uint i;
	float idata F[10];
	for(i=0;i<10;i++)
	{
	 	F[i]=(float)G[i];	   //ʮ����������ת����float����
	}
	for(i=0;i<9;i++)			//ȥͻ��ֵ��ʣ�µ���ƽ��
	{
		if(abs(F[i+1]-F[i])>5)
		{
			if(F[i+1]>F[i])
			F[i+1]=F[i];
		}
		else F[i+1]=(F[i+1]+F[i])/2.000;
	}
	return F[9];
}

//--   �ұߺ����ഫ������ȡʮ�����ݲ���������ֵ	  --
float DRPJ()				
{	uint i;
	uchar idata G[10]={0x2D};
	for(i=0;i<10;i++)
	{
		ISendByte(PCF8591,0x40);
		G[i]=IRcvByte(PCF8591);
	}
	return Average(G);
}

//--   ��ߺ����ഫ������ȡʮ�����ݲ���������ֵ	  --
float DLPJ()				
{	uint i;
	uchar idata G[10]={0x2D};
	for(i=0;i<10;i++)
	{
		ISendByte(PCF8591,0x41);
		G[i]=IRcvByte(PCF8591);
	}
	return Average(G);
}

//---  ���ұߵĺ����������ֱ�ߣ���ѭ��Ƕ�ף���С����ƫ��״̬ʱ����
void RZ(float *E,float a)	   		/* aΪ��׼ */
{  	
 	*E=DRPJ();		 		/* ��ʱEΪ����΢�����µĶ���*/
	if(*E<a)				/* ��ʹ0x01��Χƫ��Ҳ�Ƚϴ����Բ������м䷶Χ*/
	{
		 R_F(2);
	}
	else if(*E>a)
	{
		 L_F(2);
	}
	else Forward(2,300);
}

//---  ����ߵĺ����������ֱ�ߣ���ѭ��Ƕ�ף���С����ƫ��״̬ʱ����
void LZ(float *E,float a)	   		/* aΪ��׼ */
{  	
 	*E=DLPJ();		 		/* ��ʱEΪ����΢�����µĶ���*/
	if(*E<a)				/* ��ʹ0x01��Χƫ��Ҳ�Ƚϴ����Բ������м䷶Χ*/
	{
		 L_F(2);
	}
	else if(*E>a)
	{
		 R_F(2);
	}
	else Forward(2,300);
}

// ����ǽ��ѭ����������Ӧ����x������,��ֵ�Ƚϣ�
void YRQ(float x)				/* x����ǽ������ѭ���ľ���,ͻ�䣨�������̣�Ҳ������ */
{
 	float a=53.0,Exit=53.0;
	while((Exit>x) && (a>x))				/*�ұ߽���ûǽ,����ѭ��*/
	{
		a=DRPJ();				 	// ֱ��һ�ξ����֪С��ƫ��״̬
		Forward(15,300);			/** ̫�̻��жϲ���ȷ��̫�����߹�ͷ */		 
		Exit=DRPJ();					
		if((abs(Exit-a))<=1.0)			// Сƫ״̬�ȽϾ�����ƽ�У�ֱ�߳���  ------
		{				  /* 0x02����Ҫ�� */
			a=DRPJ();
			while((Exit>x) && (a>x))
			{
				if((abs(Exit-a))>9) 	break;	  	/* ͻ�䣨�������̣����� */
				else RZ(&Exit,a);	
			}
			break;
		}
		else if((abs(Exit-a))>1.0/*&&abs(Exit-a)<0x05*/)		/* ��ƫ״̬,�����������һ��ѭ��ֱ�߼��ƽ�ж� */
		{
			if(Exit>x)			/* ��Exit��⵽����Զ��(�ұ߽�����ǽ������)����ѭ�� */	/*�ұ߽�����ǽ*/
			{
				if(Exit>a)
				{
					Left(1,200);	   /* PulseCount��Ҫ����F[9]-F[0]��ֵ�� */
				}
				else if(Exit<a)			
				{
					Right(1,200);	   /* PulseCount��Ҫ����F[9]-F[0]��ֵ�� */
				}
			}
			  
		}
	}
}