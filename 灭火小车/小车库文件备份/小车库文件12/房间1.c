#include<reg51.h>    //������Ƭ���Ĵ�����ͷ�ļ�
#include<zhixian.h>
#include<fan.h>

void main()
{  	
	uint x=0x32,i=0,j=0;	 /* x����ǽ������ѭ���ľ��� */
	SIG=1;			//���õ����ֹ
	SIG1=1;
	SIG2=1;
	T0_INIT();		/*�������Ķ���*/
	INT1_INIT();
	trig = 0;
	
//	YRQ(x);			  // ����ǽ��ѭ������
//	Forward(48,200);
//	Right(33,200);		
//	while((DRZS()<0x30)||(DLZS()<0x30))			//ֱ��ֱ���ұ߸�Ӧ��ǽ��������΢ƫ����
//	Forward(3,200);

					/* �����һ�������ǽ */
	YLC(162);	
	Right(33,200);			//ֱ��ֱ���ұ߸�Ӧ��ǽ��������΢ƫ����
	Forward(130,200);

	for(i=0;i<3;i++)
	{
		for(j=0;j)
//	if((SIG1==0)&&(SIG2==0)) break;
//	delay_nms(2000);
//	Right(11,200);
	}

	if(i=0) 
	{
	YLC(122);
	SIG=0;
	}
//	YLC(x);				/* ����ڶ��������ǽ */
//	Right(35,200);
//
//	x=145;				/* ��������������ǽ */
//	YLC(x);
//	Right(33,200);				 // 145 ??
//	YLC(x);				/* ������ĸ������ǽ */
//	Right(35,200);
//
//	YLC(x);
//	Left(35,200);
//	YRC(x);
//	Left(35,200);
//	YRQ(x);
	while(1);
}