#include<reg51.h>   
#include<zhixian.h>
#include<fan.h>

void main()
{
	uint x=0x28,count,idata G[20]={};
	SIG=1;
	SIG1=1;
	SIG2=1;
	SIG4=1;
	SIG5=1;

	//YLC(x);
		/* Ҫ���Կ���ʲôʱ���⵽�����ڼӵ���Ӧ�ĵط�����ѭ���� */
		if((SIG1==0)&&(SIG2==0)) //���һ��洫������ⶼ��⵽����
		{
		 	 x=163;
			 YLC(x);
			 //������ģʽ
			 for(i=0;i<49;i++)		 // i<50 ?? 40?
			 {
			 if(G[i+1]>=G[i]/*+4*/)
				 {
				 Left(1,50);
				 G[i]=CSB();
				 }
			 else
				 {
				 	Keep();
					SIG=0;
					delay_nms(5000);
					SIG=1;
					count=i;
					break;
				 }
			while(CBS()>160)	/* ���ó���������ת�ظղŵľ��� */
			Right(1,150);
			Right(35,200);		//�ؼ���
			}
		}
//		if(SIG4==0&&SIG5==0) //QTI������1��⵽��ɫ�߽�
//		{	
//			SIG=0;		   /*����������÷��ڶ��ִ��ǰ��*/
//			Left(10,200);
//		}
	
}
