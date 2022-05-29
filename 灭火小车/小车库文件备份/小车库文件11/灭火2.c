#include<reg51.h>    //包含单片机寄存器的头文件
#include<zhixian.h>
#include<miehuo.h>
#define uint unsigned int //宏定义uint 为unsigned int类型

void main()
{ 	//初始化
	T0_INIT();
	INT1_INIT();
	trig = 0;
	SIG=1;			//风扇电机静止
	SIG1=1;		//火焰传感器
	SIG2=1;
	SIG4=1;		//灰度
 	SIG5=1;

	while(1)	//要加while传感器才会开始读取
	{

		if((SIG1==0)&&(SIG2==0)) 	//第一个角落前进灭火并回家(最后是死循环)
		OF1J();				 
		else
		{
			Left(8,200);
			if((SIG1==0)&&(SIG2==0))
			{ 	
				Right(9,200);			/* 7 ！ */
				OF1J();
			}
			else
			{	//第二个角落
				Right(17,200);				/* 7 ！ + 19 ！ */
				if((SIG1==0)&&(SIG2==0)) 	
				{
					Left(10,200);
					OF2J();
				}
				else
				{	//进第三个角落
					Right(25,200);				/* 20 ！ */
					if((SIG1==0)&&(SIG2==0))    
					OF3J();
					else //都没检测到火焰，进入下一个房间
					Right(33,200);
					
					while(1);
				}
			}
		}
		while(1) Keep();			
	}	
}