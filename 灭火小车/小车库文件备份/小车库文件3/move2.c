#include<reg51.h> //������Ƭ���Ĵ����Ķ���ͷ�ļ�
#include<zhixian.h>
#include<luxian.h>

//������
void main(void)
{	
	//��ʼ��
	T0_INIT();
	INT1_INIT();
	trig = 0;
//	SIG=1;			//���ȵ����ֹ
//	SIG1=1;		//���洫����
//	SIG2=1;
	YRQ(0x2E);
   	TwoFJF();
}