#include<reg51.h>  //����51��Ƭ���Ĵ��������ͷ�ļ�
#include <chaoshengbo+.h>

//������
void main(void)
{
		init_9600();
		T0_INIT();
		INT1_INIT();
		trig = 0;
		while(1)
		{
		CSB2();
		delaynms(500);
		}	
}
