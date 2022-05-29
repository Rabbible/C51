#include<reg51.h>    //包含单片机寄存器的头文件
#include<duoji.h>
#include<AD.h>

void main()
{
// -----  直走一段距离存距离数据   ------  	
	Forward(20,200);
	ISendByte(PCF8591,0x41);
	D[0]=IRcvByte(PCF8591);
	send_char(D[0]);
	while(1);

// -----  比较知趋势（小车偏移状态）   ------
	
// -----  舵机反应趋势   ------	
}