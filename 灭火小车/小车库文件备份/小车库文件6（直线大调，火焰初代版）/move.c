#include<reg51.h> 
#include<zhixian.h>
#include<luxian.h>
#define uint unsigned int //�궨��uint Ϊunsigned int����

//������
void main()
{	
	//��ʼ��
//	T0_INIT();
//	INT1_INIT();
//	trig = 0;
	YRQ(0x2D);
	while(1) Keep();

}