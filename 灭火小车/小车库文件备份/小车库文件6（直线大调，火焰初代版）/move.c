#include<reg51.h> 
#include<zhixian.h>
#include<luxian.h>
#define uint unsigned int //宏定义uint 为unsigned int类型

//主函数
void main()
{	
	//初始化
//	T0_INIT();
//	INT1_INIT();
//	trig = 0;
	YRQ(0x2D);
	while(1) Keep();

}