/*	-----------   回家函数   -------------------------	*/
void OFHJ()		//用此函数前 需调整车头与房间一角的墙 垂直
{
	YRC(0x01,265);			/* 15 ! */
	HL();
	YRQ(0x2F);
	LJ();
	YLC(0x02,130);			 /* 18 ! */
	while(1) Keep();
}

void FFHJ()		//用此函数前 需调整车头与房间一角的墙 垂直
{
	YRC(0x01,350);
	ZC(165);
	Right(36,200);
	YLQ(0x2F);
	Forward(5,200);
	RJ();
	Forward(25,200);
	YRQ(0x2F);
	YLC(0x02,130);
	while(1) Keep();
}

void ThreeFHJ()	
{
	YRQ(0x2D);
	RJ();
	YLQ(0x2D);
	Forward(250,200);
	YRQ(0x2D);
	YLC(0x02,130);
	while(1);
}

void TwoFHJ()	
{
	YRC(0x02,265);
	LJ();
	YLQ(0x2D);

	Forward(270,200);
	YRQ(0x2D);
	YLC(0x02,140);
	while(1);
}

/*	-----------   进房函数   -------------------------	*/
void FFJF()
{
	RTZ();
	RTZ();
	RTZ();
	RTZ();
	YLQ(0x2E);
	LJ();
	LJ();
}

void ThreeFJF()
{
	YRQ(0x2F);
	ZC(165);
	Right(36,200);
	YLQ(0x2F);
	LJ();
	LJ();
}

void TwoFJF()
{
	LJ();
	YLC(0x2D,165);
	Right(33,200);
	LTZ();
	LTZ();
	LTZ();
	Forward(10,200);
	//Forward(60,200);
	
}