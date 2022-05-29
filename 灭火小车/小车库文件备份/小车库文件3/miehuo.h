#include<fan.h>
#include<luxian.h>

//在左边的蜡烛附近吹灭火焰，后面接转头90°回去
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
	delay_nms(4000);
	if((SIG1==0)&&(SIG2==0))
	{
		Left2(40,50);	//120，50 /230,40 --45°  //转一下停三秒，保证能吹灭
		delay_nms(5000);
		Left2(40,50);	
		delay_nms(4000);
		Left2(40,50);	
		delay_nms(4000);
		SIG=1;
	}
	else 
	{
		Left(23,200);
		SIG=1;
	}
}

//第一个角落前进灭火并回家(最后是死循环)
void OF1J()
{
	YLC(0x02,135);         /* 8 ! */
	L_Chui();
	//灭火完成
	Left(36,200);	/* 9 ! */
	//回家
	OFHJ();
}

void OF2J()
{
	YLC(0x02,155);			 /* >8 ! */
	Right(33,200);		 /* 90°大一点点 */
	YLC(0x02,127);			 /* 8 ! */
	L_Chui();  //灭火完成
	Left(50,200);		 /* 2 ! */
	YRC(0x02,121);
	Left(33,200);
	//回家
	OFHJ();
}

void OF3J()
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
	OFHJ();
}


void FF1J()		/* 接对应的角度火焰感应 */
{
	YLC(0x02,127);         /* 8 ! */
	L_Chui();
	//灭火完成
	Left(36,200);	/* 9 ! */
	FFHJ();
}

void FF2J()		/* 接对应的角度火焰感应 */
{
	YLC(0x02,173);
	Right(33,200);
	ZC(127);
	L_Chui();
	Left(38,200);
	YRC(0x02,155);
	Left(32,200);
	//回家
	FFHJ();
}

void FF3J()		/* 接对应的角度火焰感应 */
{
	Forward(65,200);
	SIG=0;
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
	FFHJ();
}

void ThreeF1J()		/* 接对应的角度火焰感应 */
{
	YLC(0x02,135);         /* 8 ! */
	L_Chui();
	//灭火完成
	Left(36,200);	/* 9 ! */
	ThreeFHJ();
}

void ThreeF2J()		/* 接对应的角度火焰感应 */
{
	YLC(0x02,155);			 /* >8 ! */
	Right(33,200);		 /* 90°大一点点 */
	YLC(0x02,127);			 /* 8 ! */
	L_Chui();  //灭火完成
	Left(50,200);		 /* 2 ! */
	YRC(0x02,121);
	Left(55,200);
	ThreeFHJ();
}


void ThreeF3J()		/* 接对应的角度火焰感应 */
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
	ThreeFHJ();
}

void TwoF1J()		/* 接对应的角度火焰感应 */
{
	YLC(0x02,135);         /* 8 ! */
	L_Chui();
	//灭火完成
	Left(36,200);	/* 9 ! */
	TwoFHJ();
}

void TwoF2J()		/* 接对应的角度火焰感应 */
{
	YLC(0x02,155);			 /* >8 ! */
	Right(33,200);		 /* 90°大一点点 */
	YLC(0x02,127);			 /* 8 ! */
	L_Chui();  //灭火完成
	Left(50,200);		 /* 2 ! */
	YRC(0x02,121);
	Left(33,200);
	TwoFHJ();
}


void TwoF3J()		/* 接对应的角度火焰感应 */
{
	Forward(40,200);
	F_R(50);
	RTZ();
	RTZ();
	RTZ();
	RTZ();
	RTZ();
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
	TwoFHJ();
}