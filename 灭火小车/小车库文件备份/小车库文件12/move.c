#include<reg51.h> 
#include<zhixian.h>
//#include<chaoshengbo.h>
//#include<fan.h>
#include<luxian.h>
#define uint unsigned int //�궨��uint Ϊunsigned int����

//������
void main()
{	//��ʼ��
	T0_INIT();
	INT1_INIT();
	trig = 0;
//	SIG=1;			//���ȵ����ֹ
//	SIG1=1;		//���洫����
//	SIG2=1;

	while(1)
	{
		FRHJ(1);
		while(1) Stop();
	}
}