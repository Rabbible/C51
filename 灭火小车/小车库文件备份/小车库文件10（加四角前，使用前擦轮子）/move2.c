#include<reg51.h> //包含单片机寄存器的定义头文件
#include<zhixian.h>
#include<miehuo.h>

//主函数
void main()
{	
	//初始化
	T0_INIT();
	INT1_INIT();
	trig = 0;
	SIG=1;			//风扇电机静止
	SIG1=1;		//火焰传感器
	SIG2=1;

	while(1)	//要加while传感器才会开始读取
	{
		ThreeRoom();
		while(1) Stop();
	}
}