#include<reg51.h> 
#include<zhixian.h>
#define uint unsigned int //�궨��uint Ϊunsigned int����

//������
void main()
{	
	//��ʼ��
//	T0_INIT();
//	INT1_INIT();
//	trig = 0;
	RTZ(30);
	RTZ(30);
	RTZ(30);
	RTZ(30);
	YLQ(0x2E);
	HL();
	Stop();
	Stop();
	RWQ();
	RTZ(30);
	RTZ(30);
	RTZ(20);
	//Forward(80,200);
	Left(37,200);
	Forward(110,200);
	while(1) Keep();

}