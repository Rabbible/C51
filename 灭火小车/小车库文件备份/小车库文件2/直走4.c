#include<reg51.h> 

#include<duoji.h>
#include<zhixian.h>
#define uint unsigned int //�궨��uint Ϊunsigned int����

uint a;
void main()   	   //��ȡһ������ֵ������Ϊ��׼��ֱ�ߵĺ���
{  
	a=DRZS();
	while(1)
	{  
		RZ(a);	   //�����ұߺ�����΢����ֱ��
	}
}