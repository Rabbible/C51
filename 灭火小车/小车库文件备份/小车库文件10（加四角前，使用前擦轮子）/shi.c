#include<reg51.h>    //������Ƭ���Ĵ�����ͷ�ļ�
#include<duoji.h>
#include<AD.h>

void main()
{
// -----  ֱ��һ�ξ�����������   ------  	
	Forward(20,200);
	ISendByte(PCF8591,0x41);
	D[0]=IRcvByte(PCF8591);
	send_char(D[0]);
	while(1);

// -----  �Ƚ�֪���ƣ�С��ƫ��״̬��   ------
	
// -----  �����Ӧ����   ------	
}