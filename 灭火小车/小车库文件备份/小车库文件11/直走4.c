#include<reg51.h> 

#include<duoji.h>
#include<zhixian.h>
#define uint unsigned int //宏定义uint 为unsigned int类型

uint a;
void main()   	   //读取一个距离值，以它为基准走直线的函数
{  
	a=DRZS();
	while(1)
	{  
		RZ(a);	   //根据右边红外测距微调走直线
	}
}