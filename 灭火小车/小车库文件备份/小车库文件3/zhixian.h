#include<chaoshengbo.h>
#include<duoji.h>
#include<AD.h>
#define uint unsigned int //�궨��uint Ϊunsigned int����
#define  PCF8591 0x90    //PCF8591 ��ַ

// ----   ������	  -----
uint ZS(uint idata F[10])
{	
	uint idata c[10], idata d[10],i,j,q;
	for(i=0;i<9;i++) 	//�������ݴ�С��������
		for(j=0;j<9-i;j++)    
		{
		 	if(F[j]>F[j+1])
			{
			 	q=F[j];
				F[j]=F[j+1];
				F[j+1]=q;
			}
		}

	d[0]=F[0],c[0]=1,j=0;  //������
	for(i=0;i<9;i++)
	{
		if(F[i+1]!=F[i])
		{
			j++;
			c[j]=1;
			d[j]=F[i+1];
		}
		else c[j]++;
	}
	for(i=0;i<=j;i++)
	{
	for(q=0;i<=j;q++)
		{
		if(c[i]<c[q])
		break;
		else if(q==j)
			return d[i];
		}
	}	
}

// ----   �����ֵ	  -----
int abs(int t)
{
	if(t>0)
	return t;
	else
	return -t;
}

//--   �ұߺ����ഫ������ȡʮ�����ݲ���������ֵ	  --
uint DRZS()				
{	uint i,idata F[10]={0};
	for(i=0;i<10;i++)
	{
		ISendByte(PCF8591,0x40);
		F[i]=IRcvByte(PCF8591);
	}
	return ZS(F);
}

//---  ���ұߵĺ����������ֱ�ߣ���ѭ��Ƕ�ף���С����ƫ��״̬ʱ����
void RZ(uint *E,uint a)	   		/* aΪ��׼ */
{  	
 	*E=DRZS();		 		/* ��ʱEΪ����΢�����µĶ���*/
	if(*E<a)				/* ��ʹ0x01��Χƫ��Ҳ�Ƚϴ����Բ������м䷶Χ*/
	{
		 R_F(1);
	}
	else if(*E>a)
	{
		 L_F(1);
	}
	else Forward(1,200);
}

//--   ��ߺ����ഫ������ȡʮ�����ݲ���������ֵ	  --
uint DLZS()				
{	uint i,idata F[10]={0};
	for(i=0;i<10;i++)
	{
		ISendByte(PCF8591,0x41);
		F[i]=IRcvByte(PCF8591);
	}
	return ZS(F);
}

//---  ����ߵĺ����������ֱ�ߣ���ѭ��Ƕ�ף���С����ƫ��״̬ʱ����
void LZ(uint *E,uint a)	   		/* aΪ��׼ */
{  	
 	*E=DLZS();		 		/* ��ʱEΪ����΢�����µĶ���*/
	if(*E<a)				/* ��ʹ0x01��Χƫ��Ҳ�Ƚϴ����Բ������м䷶Χ*/
	{
		 L_F(1);
	}
	else if(*E>a)
	{
		 R_F(1);
	}
	else Forward(1,200);
}


 // ����ǽ��ѭ����������Ӧ����x������,��ֵ�Ƚϣ�
 void YRQ(uint x)				/* x����ǽ������ѭ���ľ���,ͻ�䣨�������̣�Ҳ������ */
{
 	uint a=0x35,Exit=0x35;
	while((Exit>x) && (a>x))				/*�ұ߽���ûǽ,����ѭ��*/
	{
		a=DRZS();				 	// ֱ��һ�ξ����֪С��ƫ��״̬
		Forward(20,200);			/** ̫�̻��жϲ���ȷ��̫�����߹�ͷ */		 
		Exit=DRZS();					
		if((abs(Exit-a))<0x02)			// Сƫ״̬�ȽϾ�����ƽ�У�ֱ�߳���  ------
		{				  /* 0x02����Ҫ�� */
			a=DRZS();
			while((Exit>x) && (a>x))
			{
				if((abs(Exit-a))>0x06) break;	  /* ͻ�䣨�������̣����� */
				else RZ(&Exit,a);
				//if(E<0x2D) break;	
			}
			break;
		}
		else if((abs(Exit-a))>=0x02/*&&abs(Exit-a)<0x05*/)		/* ��ƫ״̬,�����������һ��ѭ��ֱ�߼��ƽ�ж� */
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
//		else if(abs(Exit-a)>0x10)	 /*? Ϊʲô���������� ?*/
//		break;
	}
}

void YLQ(uint x)  			 /* x����ǽ������ѭ���ľ���,ͻ��Ҳ������ */
{
	uint a=0x35,Exit=0x35;
 	while((Exit>x)&&(a>x))
	{	
		a=DLZS();				 	// ֱ��һ�ξ����֪С��ƫ��״̬
		Forward(20,200);			/** ̫�̻��жϲ���ȷ��̫�����߹�ͷ */			 
		Exit=DLZS();					
		if((abs(Exit-a))<0x02)			// Сƫ״̬�ȽϾ�����ƽ�У�ֱ�߳���
		{				  /* 0x02����Ҫ�� */
			a=DLZS();
			while((Exit>x) && (a>x))
			{	if((abs(Exit-a))>0x06) break;
				else LZ(&Exit,a);
				//if(E<0x2D) break;	
			}
			break;
		}
		else if((abs(Exit-a))>=0x02 /*&& (abs(Exit-a)<0x05)*/)		/* ��ƫ״̬,�����������һ��ѭ��ֱ�߼��ƽ�ж� */
		{
			if(Exit>x)			/* ��Exit��⵽����Զ��(��߽�����ǽ������)����ѭ�� */	/*��߽�����ǽ*/
			{
				if(Exit>a)
				{
				 Right(1,200);	   /* PulseCount��Ҫ����F[9]-F[0]��ֵ�� */
				}
				else if(Exit<a)			
				{
				 Left(1,200);	   /* PulseCount��Ҫ����F[9]-F[0]��ֵ�� */
				}
			}
		
		}
//		else //if(abs(b-a)>0x10)   /*����ͻ������ѭ��*/
//		break;
	}
}

// // ����ǽ��ѭ���������ұ߸�Ӧ��Χ,������ǽ�����ھ�����,˫ֵ�Ƚϣ�
// void YLQW(uint x,uint r)				/* x��r����ΪС����ֵ */
//{
// 	uint a=0x35,Exit=0x35;
//	while((DRZS()<x) || (DRZS()>r))				/*�ұ߽���ûǽ,����ѭ��*/
//	{
//		a=DLZS();				 	// ֱ��һ�ξ����֪С��ƫ��״̬
//		Forward(20,200);			/** ̫�̻��жϲ���ȷ��̫�����߹�ͷ */			 
//		Exit=DLZS();					
//		if((abs(Exit-a))<0x02)			// Сƫ״̬�ȽϾ�����ƽ�У�ֱ�߳���  ------
//		{				  /* 0x02����Ҫ�� */
//			a=DLZS();
//			while((DRZS()<x) || (DRZS()>r))
//			{
//				if((abs(Exit-a))>=0x04) break;
//				else LZ(&Exit,a);
//				//if(E<0x2D) break;	
//			}
//			break;
//		}
//		else if((abs(Exit-a))>=0x02/*&&abs(b-a)<0x10*/)		/* ��ƫ״̬,�����������һ��ѭ��ֱ�߼��ƽ�ж� */
//		{
//			if(Exit>x)			/* ��Exit��⵽����Զ��(��߽�����ǽ������)����ѭ�� */	/*��߽�����ǽ*/
//			{
//				if(Exit>a)
//				{
//				 Right(2,200);	   /* PulseCount��Ҫ����F[9]-F[0]��ֵ�� */
//				}
//				else if(Exit<a)			
//				{
//				 Left(2,200);	   /* PulseCount��Ҫ����F[9]-F[0]��ֵ�� */
//				}
//			}
//		
//		}
////		else //if(abs(b-a)>0x10)   /*����ͻ������ѭ��*/
////		break;
//	}
//}

// ����ǽ��ѭ���������������������������
 
void YRC(uint x,int B)					/* x�ǳ�������Ӧ��ǰ��ǽ������ѭ���ľ���(��ƫ���ֵ) */
{
 	uint a=0x35,Exit=0x35;
	while((Exit>x) && (a>x))				/*�ұ߽���ûǽ,����ѭ��*/
	{
		if(CSB()<=B) break;
		else
		{
			a=DRZS();				 	// ֱ��һ�ξ����֪С��ƫ��״̬
			Forward(20,200);			/** ̫�̻��жϲ���ȷ��̫�����߹�ͷ */		 
			Exit=DRZS();					
			if((abs(Exit-a))<0x02)			// Сƫ״̬�ȽϾ�����ƽ�У�ֱ�߳���  ------
			{				  /* 0x02����Ҫ�� */
				a=DRZS();
				while((Exit>x) && (a>x))
				{
					RZ(&Exit,a);
					if(CSB()<=B) break;	
				}
				break;
			}
			else if((abs(Exit-a))>=0x02/*&&abs(Exit-a)<0x10*/)		/* ��ƫ״̬,�����������һ��ѭ��ֱ�߼��ƽ�ж� */
			{
				if(Exit>x)			/* ��Exit��⵽����Զ��(�ұ߽�����ǽ������)����ѭ�� */	/*�ұ߽�����ǽ*/
				{
					if(Exit>a)
					{
					 Left(2,200);	   /* PulseCount��Ҫ����F[9]-F[0]��ֵ�� */
					}
					else if(Exit<a)			
					{
					 Right(2,200);	   /* PulseCount��Ҫ����F[9]-F[0]��ֵ�� */
					}
				}
			}
//			else if(abs(Exit-a)>0x10)	 /*? Ϊʲô���������� ?*/
//			break;
		}
	}
}

void YLC(uint x,int B)  			
{
	uint a=0x35,Exit=0x35;
 	while((Exit>x) && (a>x))
	{	
		if(CSB()<=B) break;
		else
		{
			a=DLZS();				 	// ֱ��һ�ξ����֪С��ƫ��״̬
			Forward(20,200);			/** ̫�̻��жϲ���ȷ��̫�����߹�ͷ */			 
			Exit=DLZS();					
			if((abs(Exit-a))<0x02)			// Сƫ״̬�ȽϾ�����ƽ�У�ֱ�߳���
			{				  /* 0x02����Ҫ�� */
				a=DLZS();
				while((Exit>x) && (a>x))
				{	LZ(&Exit,a);
					if(CSB()<=B) break;	
				}
				break;
			}
			else if((abs(Exit-a))>=0x02/*&&abs(b-a)<0x10*/)		/* ��ƫ״̬,�����������һ��ѭ��ֱ�߼��ƽ�ж� */
			{
				if(Exit>x)			/* ��Exit��⵽����Զ��(��߽�����ǽ������)����ѭ�� */	/*��߽�����ǽ*/
				{
					if(Exit>a)
					{
					 Right(2,200);	   /* PulseCount��Ҫ����F[9]-F[0]��ֵ�� */
					}
					else if(Exit<a)			
					{
					 Left(2,200);	   /* PulseCount��Ҫ����F[9]-F[0]��ֵ�� */
					}
				}
			
			}
//			else //if(abs(b-a)>0x10)   /*����ͻ������ѭ��*/
//			break;
		}
	}
}

void RJ()		//������ǽ����ѭ����,������ɺ����ǽ��
{
	HR();
	Forward(60,200);
}

void LJ()		//������ǽ����ѭ����
{
	HL();
	Forward(30,200);
	F_R(30);
}

void ZC(int x)		//��ֱ�ߴﵽ�������������ѭ��
{
	while(CSB()>x)
	Forward(2,200);
}

void RC(int x)		//��ֱ�ߴﵽ�������������ѭ��
{
	while(CSB()>x)
	F_R(2);
}

void LTZ()  			 	/* ûѭ����������ߺ��⴫��������С��ƫ��״̬ */
{
	uint a,Exit;
	a=DLZS();				 	// ֱ��һ�ξ����֪С��ƫ��״̬
	Forward(20,200);			/** ̫�̻��жϲ���ȷ��̫�����߹�ͷ */			 
	Exit=DLZS();					
	if((abs(Exit-a))>=0x02 /*&& (abs(Exit-a)<0x05)*/)		/* ��ƫ״̬,�����������һ��ѭ��ֱ�߼��ƽ�ж� */
	{

		if(Exit>a)
		{
		 Right(1,200);	   /* PulseCount��Ҫ����F[9]-F[0]��ֵ�� */
		}
		else if(Exit<a)			
		{
		 Left(1,200);	   /* PulseCount��Ҫ����F[9]-F[0]��ֵ�� */
		}

	}
}

void RTZ()				/* ûѭ���������ұߺ��⴫��������С��ƫ��״̬ */
{
 	uint a,Exit;
	a=DRZS();				 	// ֱ��һ�ξ����֪С��ƫ��״̬
	Forward(20,200);			/** ̫�̻��жϲ���ȷ��̫�����߹�ͷ */		 
	Exit=DRZS();					
	if((abs(Exit-a))>=0x02/*&&abs(Exit-a)<0x05*/)		/* ��ƫ״̬,�����������һ��ѭ��ֱ�߼��ƽ�ж� */
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