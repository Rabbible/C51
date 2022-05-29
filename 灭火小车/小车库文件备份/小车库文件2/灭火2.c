#include<reg51.h>    //包含单片机寄存器的头文件
#include<zhixian.h>
#include<miehuo.h>
#define uint unsigned int //宏定义uint 为unsigned int类型

void main()
{ 
	if((SIG1==0)&&(SIG2==0)) 	//第一个角落前进灭火并回家(最后是死循环)
	OF1J();					
	while(1);
//	Right(11,200);				/* 19 ！ */
//	if((SIG1==0)&&(SIG2==0)) 	
//	2F2J();					
//
//	Right(11,200);				/* 20 ！ */
//	if((SIG1==0)&&(SIG2==0)) 	
//	3F3J();					
//	
//	Right(33,200);
//	YRC(x);			/* 15 ! */
//	Left(33,200);	//进房间的相反量
//	YRQ(0x28);
//	Forward(48,200); /* 16 !确认 */
//	Right(33,200);
//	//进第二个房间

}