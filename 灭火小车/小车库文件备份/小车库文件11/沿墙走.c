#include<reg51.h>    //������Ƭ���Ĵ�����ͷ�ļ�
#include<zhixian.h>

void main()
{  	
	uint x=0x28;	 /* x����ǽ������ѭ���ľ��� */
//	SIG=1;			//���õ����ֹ
//	SIG1=1;
//	SIG2=1;
	T0_INIT();		/*�������Ķ���*/
	INT1_INIT();
	trig = 0;
	
	YRQ(x);			  // ����ǽ��ѭ������
	Forward(48,200);
	Right(35,200);		
	while(DRZS()<0x30||DLZS()<0x30)			//ֱ��ֱ���ұ߸�Ӧ��ǽ��������΢ƫ����
	Forward(3,200);

	x=163;				/* �����һ�������ǽ */
	YLC(x);	
	Right(35,200);
	YLC(x);				/* ����ڶ��������ǽ */
	Right(35,200);

	x=145;				/* ��������������ǽ */
	YLC(x);
	Right(33,200);				 // 145 ??
	YLC(x);				/* ������ĸ������ǽ */
	Right(35,200);

	YLC(x);
	Left(35,200);
	YRC(x);
	Left(35,200);
	YRQ(x);
	while(1);
}