#include<reg51.h> //������Ƭ���Ĵ����Ķ���ͷ�ļ�
#include<duoji.h>
#include<AD.h>
#define uint unsigned int //�궨��uint Ϊunsigned int����
#define uchar unsigned char //�궨��uchar Ϊunsigned char ����

//������
void main(void)
{	
	uint i;
	Initial_com();
		Forward(6,200);	
		for(i=0;i<10;i++)
		{
		ISendByte(PCF8591,0x40);
		D[0]=IRcvByte(PCF8591);
		send_char(D[0]);
		}
		Keep();
		delay_nms(10000);


}