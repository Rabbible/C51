#include<reg51.h>    //������Ƭ���Ĵ�����ͷ�ļ�
#include<zhixian.h>
#include<miehuo.h>
#define uint unsigned int //�궨��uint Ϊunsigned int����
uint r;
void main()
{ 	
	
	//��ʼ��
	T0_INIT();
	INT1_INIT();
	trig = 0;
	SIG=1;			//���ȵ����ֹ
	SIG1=1;		//���洫����
	SIG2=1;

	while(1)	//Ҫ��while�������ŻῪʼ��ȡ
	{	
		FRJF();
		FourRoom();
		//ȥ��һ������
		ThreeRJF();
		ThreeRoom();
		TwoRJF(&r);
		TwoRoom(r);
		ORJF();
		ORoom();

		while(1) Keep();			
	}	
}

