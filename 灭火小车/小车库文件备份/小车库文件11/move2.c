#include<reg51.h> //������Ƭ���Ĵ����Ķ���ͷ�ļ�
#include<zhixian.h>
#include<miehuo.h>

//������
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
		ThreeRoom();
		while(1) Stop();
	}
}