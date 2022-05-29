/*	-----------   回家函数   -------------------------	*/
void ORHJ()		//用此函数前 需调整车头与房间一角的墙 垂直
{
	YRC(0x01,265);			/* 15 ! */
	HL();
	YRQ(0x2F);
	LJ();
	YLC(0x02,130);			 /* 18 ! */
	while(1) Keep();
}

void FRHJ()		//用此函数前 需调整车头与房间一角的墙 垂直
{
	RTZ(15);
	RTZ(15);
	YRC(0x01,350);
	ZC(155);
	Right(36,200);
	LTZ(15);
	LTZ(15);
	LTZ(15);
	YLQ(0x2D);
	Forward(5,200);
	RJ();
	Forward(25,200);
	YRQ(0x2F);
	YLC(0x02,130);
	while(1) Keep();
}

void ThreeRHJ()	
{
	YRQ(0x2D);
	RJ();
	YLQ(0x2D);
	Forward(250,200);
	YRQ(0x2D);
	YLC(0x02,130);
	while(1);
}

void TwoRHJ()	
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

void LJF()  //接弧度转弯、直走感应到与门口齐平的墙后面
{
	RTZ(20);			//主要是有校正过程 故采用直角转弯
	RTZ2(15);
	RTZ(20);
	Left(36,200);
	Forward(40,300);
	F_R(30);
	Forward(30,300);
	RTZ(15);
	RTZ(15);
}


void FRJF()
{
	//F_R(20);
	RTZ(30);
	RTZ2(15);
	RTZ(15);
	RTZ(15);
	Forward(45,300);
	YLQ(0x2E);
	LJ();
	LJF();
}

void ThreeRJF()
{
	YRQ(0x2D);
	ZC(165);
	Right(35,200);
	LTZ(15);
	YLQ(0x2E);
	LJ();
	LJF();
}

void TwoRJF()
{
	LJ();
	YLC(0x2D,165);
	Right(33,200);
	LTZ(20);
	LTZ(20);
	LTZ(20);
	Forward(10,200);
	//Forward(60,200);
	
}
