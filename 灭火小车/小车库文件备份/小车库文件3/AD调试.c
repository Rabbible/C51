#include<reg51.h>
#include<zhixian.h>
#define uint unsigned int //宏定义uint 为unsigned int类型
void main()
{	
	uint a;
	Initial_com();
	while(1)
	{
		a=DLZS();
		send_char(a);
		send_char(0xff);
	}
}