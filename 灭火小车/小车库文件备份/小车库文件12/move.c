#include<reg51.h> 
#include<zhixian.h>
//#include<chaoshengbo.h>
//#include<fan.h>
#include<luxian.h>
#define uint unsigned int //宏定义uint 为unsigned int类型

//主函数
void main()
{	//初始化
	T0_INIT();
	INT1_INIT();
	trig = 0;
//	SIG=1;			//风扇电机静止
//	SIG1=1;		//火焰传感器
//	SIG2=1;

	while(1)
	{
		FRHJ(1);
		while(1) Stop();
	}
}