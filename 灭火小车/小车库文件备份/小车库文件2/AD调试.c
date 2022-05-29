#include<reg51.h>    //包含单片机寄存器的头文件
#include<AD.h>
#include<ZS.h>
#define uint unsigned int //宏定义uint 为unsigned int类型
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