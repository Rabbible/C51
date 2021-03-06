#include<reg51.h>    //包含单片机寄存器的头文件
#include<zhixian.h>

void main()
{  	
	uint x=0x28;	 /* x是沿墙走跳出循环的距离 */
//	SIG=1;			//先让电机静止
//	SIG1=1;
//	SIG2=1;
	T0_INIT();		/*超声波的定义*/
	INT1_INIT();
	trig = 0;
	
	YRQ(x);			  // 沿右墙走循环函数
	Forward(48,200);
	Right(35,200);		
	while(DRZS()<0x30||DLZS()<0x30)			//直走直到右边感应到墙，考虑上微偏距离
	Forward(3,200);

	x=163;				/* 房间第一个角落的墙 */
	YLC(x);	
	Right(35,200);
	YLC(x);				/* 房间第二个角落的墙 */
	Right(35,200);

	x=145;				/* 房间第三个角落的墙 */
	YLC(x);
	Right(33,200);				 // 145 ??
	YLC(x);				/* 房间第四个角落的墙 */
	Right(35,200);

	YLC(x);
	Left(35,200);
	YRC(x);
	Left(35,200);
	YRQ(x);
	while(1);
}