#include<reg51.h> 
#include<zhixian.h>
#define uint unsigned int //宏定义uint 为unsigned int类型

//主函数
void main(void)
{	
	
	uint x=0x2D,a=0x35,Exit=0x35; 
	//Initial_com();
	a=DLZS();
	while((Exit>x)&&(a>x))
	{
		LZ(&Exit,a);
		//send_char(Exit);
	}
	while(1);

//	F_L(100);
//	F_R(100);
}