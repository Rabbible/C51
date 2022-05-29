#include<fan.h>
#include<luxian.h>

//在左边的蜡烛附近吹灭火焰 ，总转头 180°
void L_Chui()
{	
	uint i;
	int idata v[30]={127};
	for(i=0;i<29;i++)				 //检测墙角>45°便退出开风扇
	{
		v[i+1]=CSB();
		if((v[i+1]-v[i])>=20) 
		{
			SIG=0;
			break;
		}
		else Left(5,60);
	}
	SIG=0;
	delay_nms(2000);
	Left2(40,60);	//120，50 /230,40 --45°  //转一下停三秒，保证能吹灭
	delay_nms(2000);
	Left2(40,60);	
	delay_nms(3000);
	Left2(40,60);	
	delay_nms(5000);
	SIG=1;
	Left(37,200);
}

void R_Chui()
{
	uint i;
	int idata v[30]={125};
	for(i=0;i<29;i++)				 //检测墙角>45°便退出开风扇
	{
		v[i+1]=CSB();
		if((v[i+1]-v[i])>=20) 
		{
			SIG=0;
			break;
		}
		else Right2(5,70);
	}
	SIG=0;
	delay_nms(1000);
	Right2(30,90);	
	delay_nms(2000);
	Right2(30,90);	
	delay_nms(2000);										   
	Right2(30,90);	
	delay_nms(4000);
	SIG=1;
	Right(39,200);
}

void FourJ_Chui()
{
	SIG=0;
	delay_nms(2000);
	Right2(30,90);	
	delay_nms(2000);
	Right2(30,90);	
	delay_nms(2000);										   
	Right2(30,90);	
	delay_nms(2000);

	Left2(40,60);	//120，50 /230,40 --45°  //转一下停三秒，保证能吹灭
	delay_nms(2000);
	Left2(40,60);	
	delay_nms(3000);
	Left2(40,60);	
	delay_nms(3000);
	SIG=1;
}

void FJ(uint c)					 //四角检测+灭火(没检测到会回到检测前位置,不影响初始位置)
{	uint i;						 //c 是差量，能调节转的角度
	for(i=0;i<32-c;i++)		//90du
	{
		Left(1,200);	 //  2!  4.
		if((SIG1==0)&&(SIG2==0))
		{
			Left(32-i-c,200);  //  5!  5.
			Stop();
			FourJ_Chui();
			Left(33,200);

			Forward(50,300);  //防止蜡烛让程序跳出走直线
			FRHJ(4);		  //卡死在里面
		}
	}
	Right(32-c,200);
}
void OneJ()		  //检测到一角附近火焰的
{	uint i;

	Left(30,200);
	FJ(26);
	Right(30,200);

	for(i=0;i<2;i++)
	LTZ(20,'F',3);

	YLC(0x02,127);         /* 8 ! */
	L_Chui();
	RTZ(20,'F',3);
	RTZ(15,'F',3);

}

void TwoJ()
{
	LTZ(15,'F',3);
	LTZ(15,'F',3);
	YLC(0x02,160);
	Right(35,200);
	YLC(0x01,127);
	L_Chui();
	Forward(20,200);
	RTZ(20,'F',3);
	RTZ(15,'F',3);
	YRC(0x01,155);
	YRC(0x01,155);
	Left(38,200);
	Right(1,200);
}
void ThreeJ(uint x)
{
	Right(3,200);
	F_R(x);
	ZC(125);
	R_Chui();
	LTZ(15,'F',3);
	LTZ(15,'F',3);
	ZC(160);
	Left(35,200);
}

//角落灭火
void FR1J()		/* 接对应的角度火焰感应 */
{
	OneJ();
	FRHJ(1);
}

void FR2J()		/* 接对应的角度火焰感应 */
{
	TwoJ();
	//回家
	FRHJ(1);
}

void FR3J()		/* 接对应的角度火焰感应 */
{	
	ThreeJ(30);
	//回家
	FRHJ(1);
}

void ThreeR1J()		/* 接对应的角度火焰感应 */
{	uint i;
	Left(30,200);
	FJ(26);
	Right(30,200);
	
	for(i=0;i<2;i++)
	LTZ(20,'F',3);		   //向左偏然后向右偏（直线偏左）
	for(i=0;i<5;i++)
	LTZ(15,'F',2);
	YLC(0x02,127);         /* 8 ! */
	L_Chui();
	for(i=0;i<4;i++)
	RTZ(20,'F',3);
	RTZ(15,'F',2);
	//灭火完成
	ThreeRHJ();
}

void ThreeR2J()		/* 接对应的角度火焰感应 */
{
	TwoJ();
	//回家
	ThreeRHJ();
}


void ThreeR3J()		/* 接对应的角度火焰感应 */
{	
	Right(6,200);
	ThreeJ(30);
	//回家
	ThreeRHJ();
}

void TwoR1J()		/* 接对应的角度火焰感应 */
{	
	OneJ();
	//回家
	TwoRHJ();
}

void TwoR2J()		/* 接对应的角度火焰感应 */
{
	TwoJ();
	TwoRHJ();
}

void TwoR3J()		/* 接对应的角度火焰感应 */
{
	ThreeJ(50);
	//回家
	TwoRHJ();
}

void OR1J()		/* 接对应的角度火焰感应 */
{	
	OneJ();
	//灭火完成
	ORHJ();
}

void OR2J()		/* 接对应的角度火焰感应 */
{
	TwoJ();
	//回家
	ORHJ();
}

void OR3J()		/* 接对应的角度火焰感应 */
{	
	ThreeJ(15);
	//回家
	ORHJ();
}

//总房间函数（检测+灭火+调头+回家）	 有火焰会回家并故意卡在此程序里
void FourRoom()
{
	uint i;
	for(i=0;i<15;i++)	  //1角
	{
		Left(1,200);
		if((SIG1==0)&&(SIG2==0))
		{	
			Right(i,200);
			FR1J();
		}
	}
	FJ(15);
	Right(18,200);
	for(i=0;i<25;i++)		
	{
		Right(1,200);	// 4!  3.	 
		if((SIG1==0)&&(SIG2==0))
		{	
			Right(25-i,200);
			Right(15,200);	 //  2!  4.
			if((SIG1==0)&&(SIG2==0))
			{
				Left(15,200);  //  5!  5.
				FR3J();
			}
			else
			{
				Left(43,200);  //  1!  7.
				FR2J();
			}
		}
		else continue;
	}
	Right(3,200);
	for(i=0;i<23;i++)
	{
		Right(1,200);	 //  2!  4.
		if((SIG1==0)&&(SIG2==0))
		{
			Left(i,200);  //  5!  5.
			FR3J();
		}
	}
	Right(9,200);
	Left(1,200);
	 
}

void ThreeRoom()
{
	uint i;
	
		for(i=0;i<15;i++)
		{
			Left(1,200);
			if((SIG1==0)&&(SIG2==0))
			{	
				//Left(10-i,200);
				Right(i,200);
				ThreeR1J();
			}
		}
			
		Right(11,200);
		for(i=0;i<23;i++)		
		{
			Right(1,200);	// 4!  3.	 
			if((SIG1==0)&&(SIG2==0))
			{	
				Left(i,200);  //  1!  7.
				ThreeR2J();
				
			}
		}
		Right(5,200);	
			for(i=0;i<26;i++)
			{
				Right(1,200);	 //  2!  4.
				if((SIG1==0)&&(SIG2==0))
				{
					Left(i,200);  //  5!  5.
					ThreeR3J();
				}
			}

		Right(21,200);
		Left(1,200);		//房间门口停下，接进下一个房间程序
	 
}

void TwoRoom()
{
	uint i;

	for(i=0;i<15;i++)
	{
		Left(1,200);
		if((SIG1==0)&&(SIG2==0))
		{	
			//LefTt(10-i,200);
			Right(i,200);
			TwoR1J();
		}
	}
		
	Right(18,200);
	for(i=0;i<25;i++)		
	{
		Right(1,200);	// 4!  3.	 
		if((SIG1==0)&&(SIG2==0))
		{	
			Right(25-i,200);
			Right(15,200);	 //  2!  4.
			if((SIG1==0)&&(SIG2==0))
			{
				Left(15,200);  //  5!  5.
				TwoR3J();
			}
			else
			{
				Left(43,200);  //  1!  7.
				TwoR2J();
			}
		}
		else continue;
	}
	Right(3,200);
	for(i=0;i<23;i++)
	{
		Right(1,200);	 //  2!  4.
		if((SIG1==0)&&(SIG2==0))
		{
			Left(i,200);  //  5!  5.
			TwoR3J();
		}
	}

	Right(17,200);		 //gai le!
	Left(1,200);		//房间门口停下，接进下一个房间程序
	 
}

void ORoom()
{
	uint i;
	for(i=0;i<15;i++)
	{
		Left(1,200);
		if((SIG1==0)&&(SIG2==0))
		{	
			//Left(10-i,200);
			Right(i,200);
			OR1J();
		}
	}
		
	Right(18,200);
	for(i=0;i<25;i++)		
	{
		Right(1,200);	// 4!  3.	 
		if((SIG1==0)&&(SIG2==0))
		{	
			Right(25-i,200);
			Right(15,200);	 //  2!  4.
			if((SIG1==0)&&(SIG2==0))
			{
				Left(15,200);  //  5!  5.
				OR3J();
			}
			else
			{
				Left(43,200);  //  1!  7.
				OR2J();
			}
		}
		else continue;
	}
	Right(3,200);
	for(i=0;i<23;i++)
	{
		Right(1,200);	 //  2!  4.
		if((SIG1==0)&&(SIG2==0))
		{
			Left(i,200);  //  5!  5.
			OR3J();
		}
	}

	Right(15,200);		 //gai le!
	Left(1,200);
}