#include<fan.h>
#include<luxian.h>

//在左边的蜡烛附近吹灭火焰 ，总转头 180°
void L_Chui()
{	
	uint i;
	int idata v[50]={127};
	for(i=0;i<49;i++)				 //检测墙角>45°便退出开风扇
	{
		v[i+1]=CSB();
		if((v[i+1]-v[i])>=30) 
		{
			SIG=0;
			break;
		}
		else Left(5,60);
	}
	SIG=0;
	delay_nms(1000);
	if((SIG1==0)&&(SIG2==0))
	{
		Left2(40,50);	//120，50 /230,40 --45°  //转一下停三秒，保证能吹灭
		delay_nms(1000);
		Left2(40,50);	
		delay_nms(3000);
		Left2(40,50);	
		delay_nms(5000);
		SIG=1;
	}
	else 
	{
		Left(10,200);
		SIG=1;
	}
}

//第一个角落前进灭火并回家(最后是死循环)
void OR1J()
{
	YLC(0x02,135);         /* 8 ! */
	L_Chui();
	//灭火完成
	Left(36,200);	/* 9 ! */
	//回家
	ORHJ();
}

void OR2J()
{
	YLC(0x02,155);			 /* >8 ! */
	Right(33,200);		 /* 90°大一点点 */
	YLC(0x02,127);			 /* 8 ! */
	L_Chui();  //灭火完成
	Left(50,200);		 /* 2 ! */
	YRC(0x02,121);
	Left(33,200);
	//回家
	ORHJ();
}

void OR3J()
{
	Forward(80,200);
	SIG=0;
	delay_nms(4000);
	Right2(30,70);	
	delay_nms(4000);
	Right2(30,70);	
	delay_nms(4000);										   
	Right2(30,70);	
	delay_nms(4000);
	SIG=1;
	//灭火完成
	Left(10,200);
	Backward(85,200);
	Right(32,200);
	//回家
	ORHJ();
}


void FR1J()		/* 接对应的角度火焰感应 */
{
	YLC(0x02,127);         /* 8 ! */
	L_Chui();
	//灭火完成
	Left(38,200);	/* 9 ! */
	FRHJ();
}

void FR2J()		/* 接对应的角度火焰感应 */
{
	LTZ(20);
	LTZ(20);
	YLC(0x02,150);
	Right(36,200);
	ZC(127);
	L_Chui();
	Left(48,200);
	Forward(20,200);
	RTZ(20);
	RTZ(20);
	YRC(0x01,160);
	Left(38,200);
	Right(1,200);
	//回家
	FRHJ();
}

void FR3J()		/* 接对应的角度火焰感应 */
{	
	YLC(0x01,127);
	SIG=0;
	delay_nms(1000);
	Right2(30,70);	
	delay_nms(2000);
	Right2(30,70);	
	delay_nms(2000);										   
	Right2(30,70);	
	delay_nms(4000);
	SIG=1;
	//灭火完成
	Left(19,200);
	BC(340);
	Right(36,200);
	//回家
	FRHJ();
}

void ThreeR1J()		/* 接对应的角度火焰感应 */
{
	YLC(0x02,135);         /* 8 ! */
	L_Chui();
	//灭火完成
	Left(36,200);	/* 9 ! */
	ThreeRHJ();
}

void ThreeR2J()		/* 接对应的角度火焰感应 */
{
	YLC(0x02,155);			 /* >8 ! */
	Right(33,200);		 /* 90°大一点点 */
	YLC(0x02,127);			 /* 8 ! */
	L_Chui();  //灭火完成
	Left(50,200);		 /* 2 ! */
	YRC(0x02,121);
	Left(55,200);
	ThreeRHJ();
}


void ThreeR3J()		/* 接对应的角度火焰感应 */
{
	Forward(135,200);
	SIG=0;
	delay_nms(4000);
	Right2(30,70);	
	delay_nms(4000);
	Right2(30,70);	
	delay_nms(4000);										   
	Right2(30,70);	
	delay_nms(4000);
	SIG=1;
	//灭火完成
	Left(11,200);
	Backward(150,200);
	Right(33,200);
	ThreeRHJ();
}

void TwoR1J()		/* 接对应的角度火焰感应 */
{
	YLC(0x02,135);         /* 8 ! */
	L_Chui();
	//灭火完成
	Left(36,200);	/* 9 ! */
	TwoRHJ();
}

void TwoR2J()		/* 接对应的角度火焰感应 */
{
	YLC(0x02,155);			 /* >8 ! */
	Right(33,200);		 /* 90°大一点点 */
	YLC(0x02,127);			 /* 8 ! */
	L_Chui();  //灭火完成
	Left(50,200);		 /* 2 ! */
	YRC(0x02,121);
	Left(33,200);
	TwoRHJ();
}


void TwoR3J()		/* 接对应的角度火焰感应 */
{
	Forward(100,200);
	RTZ(20);
	RTZ(20);
	RTZ(20);
	Forward(20,200);
	SIG=0;
	delay_nms(4000);
	Right2(30,70);	
	delay_nms(4000);
	Right2(30,70);	
	delay_nms(4000);										   
	Right2(30,70);	
	delay_nms(4000);
	SIG=1;
	//灭火完成
	Left(11,200);
	Backward(270,200);
	Right(35,200);
	TwoRHJ();
}


//总房间函数（检测+灭火+调头+回家）	 有火焰会回家并故意卡在此程序里
void FourRoom()
{
	if((SIG1==0)&&(SIG2==0)) 	//第一个角落前进灭火并回家(最后是死循环)
	{
		Left(7,200);   // 3!    1.
		if((SIG1==0)&&(SIG2==0))
		{
			Right(7,200); // 1!  2.
			FR1J();	 
		}
		else 
		{
			Right(7,200);	// 1!   2.
			FR2J();
		}
	}

	else
	{
		Left(7,200);
		if((SIG1==0)&&(SIG2==0))
		{	
			Right(7,200);
			FR1J();
		}
		else
		{
			uint i;
			Right(7,200);
			for(i=0;i<25;i++)			//  20改了！
			{
				Right(1,200);	// 4!  3.	 
				if((SIG1==0)&&(SIG2==0))
				{	
					Right(24-i,200);
					Right(15,200);	 //  2!  4.
					if((SIG1==0)&&(SIG2==0))
					{
						Left(11,200);  //  5!  5.
						FR3J();
					}
					else
					{
						Left(36,200);  //  1!  7.
						FR2J();
					}
				}
				else continue;
			}
			
			for(i=0;i<23;i++)
			{
				Right(1,200);	 //  2!  4.
				if((SIG1==0)&&(SIG2==0))
				{
					Right(22-i,200);
					Left(13,200);  //  5!  5.
					FR3J();
				}
			}
		}
		Right(23,200);
		Left(1,200);		//房间门口停下，接进下一个房间程序
		Stop();
	}  
}