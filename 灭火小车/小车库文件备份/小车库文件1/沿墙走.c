#include<reg51.h>    //������Ƭ���Ĵ�����ͷ�ļ�
#include <I2C.H>
#include<duoji.h>
#include<AD.h>
#include<chaoshengbo.h>

void main()
{  
	Initial_com();	 //*****���ڳ�ʼ������***********
	init_9600();   /*�������Ķ���*/
	T0_INIT();
	INT1_INIT();
	trig = 0;
	
	while(1)
	{  
	  	AD ();/********AD-DA����*************/  		
	   if(++AD_CHANNEL>4) AD_CHANNEL=0;

	   if(D[0]<0x2D||D[1]<0x2D) break;				  /*  ����ѭ��   */
		if(D[0]>0x2D)	 /*  �տ�ʼֻ���ұ���ǽ���������м䷶Χ   */
		{

			if(D[0]<0x53)			 /*  Ҫ���غ÷�Χ����ѭ������   */
			{
				 R_F(1);			/******     ���  ************/
			}
			else if(D[0]>0x4F)
			{
				 L_F(1);
			}
			else Forward(1,200);
		}
		else if(D[0]<0x2D&&D[1]>0x40)	  		 /*  �����ǽ����   */
		{	
			
			 if(D[1]<0x53)			 /*  Ҫ���غ÷�Χ����ѭ������   */
			{
				 L_F(1);
			}
			else if(D[1]>0x4F)
			{
				 R_F(1);
			}
			else Forward(1,200);
				
		}	
	}

	Right(36,200);				 /*  ��ת90��  */
	Forward(100,200);
		while(1)
	{  
	  	AD ();/********AD-DA����*************/  		
	  	if(++AD_CHANNEL>4) AD_CHANNEL=0;

	  	if(CSB()<=122) break;				  /*  ����ѭ��   */
		if(D[1]>0x40)	  		 /*  �����ǽ��   */
		{	
			 if(D[1]<0x53)			 /*  ��ΧС�˻�����ڷ�Χ����̫��������   */
			{
				 L_F(1);
			}
			else if(D[1]>0x4F)
			{
				 R_F(1);
			}
			else Forward(1,200);
					/*������*/	
		}	
	}
	Right(36,200);	/*  ��ת90��  */
}