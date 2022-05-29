#include<reg51.h>  //包含51单片机寄存器定义的头文件
#include <chaoshengbo+.h>

//主函数
void main(void)
{
		init_9600();
		T0_INIT();
		INT1_INIT();
		trig = 0;
		while(1)
		{
		CSB2();
		delaynms(500);
		}	
}
