#include<uart.h>//����ͷ�ļ�uart.h
int main(void)
{
	int i;//�������i
	uart_Init();//���ڳ�ʼ��
	i = 36*29;//i=7��11
	printf("What's 36 X 29 ?\n");//��ӡWhat's 7 X 11?
	printf("The fucking answer is : %d\n\n",i);//��ӡi�Ľ��
	while(1);//����ȴ�
}