#include<reg51.h>    //������Ƭ���Ĵ�����ͷ�ļ�
#include<AD.h>
#include<ZS.h>
#define uint unsigned int //�궨��uint Ϊunsigned int����
void main()
{	
	uint a;
	Initial_com();
	while(1)
	{
		a=DZS();
		send_char(a);
		send_char(0xff);
	}
}