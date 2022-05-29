#include<reg51.h>    //包含单片机寄存器的头文件
#include<AD.h>

void main()
{
	Initial_com();
	while(1)
	{
	/********AD-DA处理*************/
	ISendByte(PCF8591,0x41);	/*0x41是第一个AD输入接口，0x40是第二个*/ 
	D[0]=IRcvByte(PCF8591);
	ISendByte(PCF8591,0x40);	
	D[1]=IRcvByte(PCF8591);	
	 
	  /********以下将AD的值通过串口发送出去*************/	
	send_char(D[1]);
	}
}