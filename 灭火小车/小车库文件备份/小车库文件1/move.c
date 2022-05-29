#include<reg51.h> //包含单片机寄存器的定义头文件
#include<duoji.h>
#include<AD.h>
#define uint unsigned int //宏定义uint 为unsigned int类型
#define uchar unsigned char //宏定义uchar 为unsigned char 类型

//主函数
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