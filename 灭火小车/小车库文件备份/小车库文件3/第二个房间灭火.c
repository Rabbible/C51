#include<reg51.h>    //包含单片机寄存器的头文件
#include<zhixian.h>
#include<miehuo.h>
#define uint unsigned int //宏定义uint 为unsigned int类型

void main()
{
	uint i;
 	//初始化
	T0_INIT();
	INT1_INIT();
	trig = 0;
	SIG=1;			//风扇电机静止
	SIG1=1;		//火焰传感器
	SIG2=1;

   while(1)
   {
   		YRQ(0x2E);
   		TwoFJF();
   		if((SIG1==0)&&(SIG2==0)) 	//第一个角落前进灭火并回家(最后是死循环)
		ThreeF1J();				 
		else
		{
			Left(7,200);
			if((SIG1==0)&&(SIG2==0))
			{ 	
				Right(6,200);			/* 7 ！ */
				TwoF1J();
			}
			else
			{	
				while(1)
				{
					//第二个角落
					for(i=0;i<30;i++)
					{
						
						Right(1,200);				/* 7 ！ + 19 ！ */
						if((SIG1==0)&&(SIG2==0)) 	
						{
							Left(15,200);
							TwoF2J();
						}
						
					}
					for(i=0;i<16;i++)
					{	
	
						//进第三个角落
						Right(1,200);
						if((SIG1==0)&&(SIG2==0)) 
						{   
							Right(13-i,200);
							Left(1,200);
							TwoF3J();
						}
						
					}
						
					Right(28,200);
					//进入下一个房间
					while(1) Keep();
				}
			}
			break;
		}
		break;			
	}
		
}