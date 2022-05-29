/*	-----------   回家函数   -------------------------	*/
void FRHJ()		//用此函数前 需调整车头与房间一角的墙 垂直
{
	RTZ(15,'F',3);
	RTZ(15,'F',3);
	YRC(0x01,350);
	ZC(165);
	Right(36,200);
	LTZ(15,3);
	LTZ(15,3);
	LTZ(15,3);
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
	while(1) Keep();
}

void TwoRHJ()	
{
	RTZ(20,'F',3);
	RTZ(15,'F',3);
	YRC(0x01,163);
	Left(35,200);
	RTZ(20,'F',3);
	YRQ(0x2D);
	Forward(10,300);
	LTZ(20,3);
	LTZ(20,3);
	LTZ(20,3);
	YLQ(0x2D);
	Forward(210,200);
	RTZ(20,'R',3);
	RTZ(20,'R',3);
	YRQ(0x2D);
	LTZ(15,3);
	YLC(0x02,140);
	while(1) Keep();
}

void ORHJ()		//用此函数前 需调整车头与房间一角的墙 垂直
{
	RTZ(20,'F',3);
	RTZ(15,'F',3);
	YRC(0x02,163);
	Left(35,200);
	RTZ(20,'F',3);
	RTZ(20,'F',3);
	RTZ(15,'F',3);
	YRQ(0x2D);
	LJ();
	YLC(0x02,145);			 /* 18 ! */
	while(1) Keep();
}

/*	-----------   进房函数   -------------------------	*/

void LJF()  //接弧度转弯、直走感应到与门口齐平的墙后面
{
	RTZ(20,'F',3);			//主要是有校正过程 故采用直角转弯
	RTZ(20,'R',3);
	RTZ(15,'F',3);
	RTZ(15,'F',3);
	Left(36,200);
	Forward(50,300);
	F_R(30);
	Forward(20,300);
	RTZ(15,'R',2);
	RTZ(15,'R',2);
}

void FRJF()
{
	//F_R(20);
	RTZ(30,'F',1);
	RTZ(20,'R',1);
	RTZ(15,'R',1);
	RTZ(15,'F',1);
	Forward(45,300);
	YLQ(0x2E);
	LJ();
	LJF();
}

void ThreeRJF()
{
	RTZ(15,'F',3);
	RTZ(15,'F',3);
	RTZ(15,'F',3);
	YRC(0x01,350);
	ZC(165);
	Right(35,200);
	LTZ(15,3);
	YLQ(0x2E);
	LJ();
	//Forward(2,300);
	LJF();
}

void TwoRJF(uint *r)
{
	YRQ(0x2D);
	F_R(20);
	ZC(157);
	Left(34,200);
	//以下为右进房模块
	YRQ(0x2D);
	Forward(3,300);
	YLC(0x01,165);
	*r=DLZS();
	Right(35,200);
	LTZ(20,3);
	LTZ(20,3);
	LTZ(17,3);
	LTZ(15,2);
	LTZ(15,2);
	LTZ(15,2);
	LTZ(15,2);
	LTZ(15,2);
}

void ORJF()
{
	RTZ(20,'F',3);
	YRC(0x01,159);
	Left(34,200);
	RTZ(20,'F',3);
	YRQ(0x2D);
	Forward(3,300);
	LTZ(20,3);
	YLQ(0x2D);
	LJ();

	//右进房模块少了一个直走
	YRQ(0x2D);
	YLC(0x01,165);
	Right(35,200);
	LTZ(20,3);
	LTZ(20,3);
	LTZ(15,3);
	LTZ(15,2);
	LTZ(15,2);
	LTZ(15,2);
	LTZ(15,2);
	LTZ(15,2);
}
