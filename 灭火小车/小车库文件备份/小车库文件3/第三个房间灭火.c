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

   while(1)
   {
   		if((SIG1==0)&&(SIG2==0)) 	//第一个角落前进灭火并回家(最后是死循环)
		TF1J();				 
		else
		{
			Left(5,200);
			if((SIG1==0)&&(SIG2==0))
			{ 	
				Right(5,200);			/* 7 ！ */
				TF1J();
			}
			else
			{	//第二个角落
				Right(11,200);				/* 7 ！ + 19 ！ */
				if((SIG1==0)&&(SIG2==0)) 	
				{
					Left(10,200);
					TF2J();
				}
				else
				{	//进第三个角落
					Right(25,200);				/* 20 ！ */
					if((SIG1==0)&&(SIG2==0))    
					TF3J();
					else //都没检测到火焰，进入下一个房间
					Right(33,200);
					//进入下一个房间
					while(1);
				}
			}
		}
	
		while(1) Keep();			
	}		
}