void ZL()
{	uint i;
	RTZ(20,'F',3);
	RTZ(15,'F',3);
	YRC(0x01,155);
	Left(35,200);
	RTZ(20,'R',3);
	YRQ(0x2D);
	Forward(10,300);
	for(i=0;i<3;i++)
	LTZ(20,'R',3);
	YLQ(0x2D);
}

void HJL()
{
	F_R(30);
	Forward(100,300);
	RTZ(20,'F',3);
	RTZ(20,'F',3);
	YRQ(0x2D);
	LTZ(15,'R',3);
	YLC(0x02,140);
}

/*	-----------   回家函数   -------------------------	*/
void FRHJ(uint flag)		//用此函数前 需调整车头与房间一角的墙 垂直
{	if(flag==1)
	RTZ(15,'F',3);		 //四角不会执行此行
	YRC(0x01,350);
	ZC(165);
	Right(36,200);
	LTZ(20,'R',3);
	LTZ(20,'F',3);
	LTZ(15,'F',3);
	YLQ(0x2D);
	F_R(5);
	RJ();
	F_R(25);
	YRQ(0x2D);
	YLC(0x02,140);
	while(1) Keep();
}

void ThreeRHJ()	
{
	RTZ(20,'R',3);
	YRQ(0x2D);
	Forward(5,300);
	RJ();
	LTZ(17,'F',3);
	LTZ(15,'F',3);
	YLQ(0x2D);
	HJL();
	while(1) Keep();
}

void TwoRHJ()	
{
	ZL();
	HJL();
	while(1) Keep();
}

void ORHJ()		//用此函数前 需调整车头与房间一角的墙 垂直
{	uint i;
	RTZ(20,'F',3);
	YRC(0x01,163);
	Left(35,200);
	for(i=0;i<2;i++)
	RTZ(20,'R',3);
	RTZ(15,'F',3);
	YRQ(0x2D);
	LJ();
	for(i=0;i<3;i++)
	LTZ(20,'F',3);
	YLC(0x02,145);			 /* 18 ! */
	while(1) Keep();
}

/*	-----------   进房函数   -------------------------	*/
void Enter(uint r2)
{	uint i;
	Forward(50,300);
	F_R(30);
	Forward(20,300);
	if(r2>0x66) 
	{	
		for(i=0;i<3;i++)
		RTZ(20,'R',1);
		F_R(10);
	}
	else if((r2<0x66)&&(r2>=0x43))
	{
		for(i=0;i<2;i++)
		RTZ(20,'R',1);
	}  
	else if(r2<0x43) RTZ(20,'R',2);
}

void Enter2(uint r3)
{	uint i;
	for(i=0;i<2;i++)
	LTZ(20,'R',3);
	LTZ(16,'R',2);
	for(i=0;i<2;i++)
	LTZ(15,'R',2);
	if((r3<=0x50)&&(r3>=0x40)) 	 //中间
	{	
		for(i=0;i<3;i++)
		LTZ(15,'F',2);
		RTZ(20,'R',2);		
	}
	else if(r3>0x50)   //靠墙近
	{	
		for(i=0;i<3;i++)
		LTZ(15,'F',2);
		for(i=0;i<2;i++)
		LTZ(15,'R',2);
		if(r3>0x90)
		LTZ(15,'F',2);		
	}
	else if(r3<0x40)   //离房间门近
	{	
		for(i=0;i<2;i++)
		LTZ(15,'F',2);		
		LTZ(20,'R',2);
		if(r3<0x2E)
		LTZ(15,'F',2);		
	}
}

void LJF(uint flag)  //接弧度转弯、直走感应到与门口齐平的墙后面
{	
	uint r2;
	RTZ(20,'F',3);			//主要是有校正过程 故采用直角转弯
	RTZ(20,'F',3);
	if(flag==4)
	RTZ(18,'R',3);
	if(flag==3)
	Forward(3,300);
	r2=DRZS();
	Left(37,200);
	Enter(r2);
	
}

void FRJF()
{
	RTZ(30,'R',1);
	RTZ(20,'R',1);
	RTZ(15,'R',1);
	RTZ(15,'F',1);
	Forward(45,300);
	YLQ(0x2E);
	LJ();
	LJF(4);
}

void ThreeRJF()
{
	uint i;
	for(i=0;i<3;i++)
	RTZ(15,'R',3);
	YRC(0x01,350);
	ZC(165);
	Right(35,200);
	LTZ(15,'R',3);
	YLQ(0x2E);
	LJ();
	LJF(3);
}

void TwoRJF()
{	
	uint r3;
	YRQ(0x2D);
	F_R(20);
	ZC(157);
	Left(34,200);
	//以下为右进房模块
	YRQ(0x2D);
	Forward(3,300);
	YLC(0x01,175);
	r3=DLZS();
	Right(35,200);
	Enter2(r3);
}

void ORJF()
{	uint i,r4;
	ZL();
	LJ();
	//右进房模块少了一个直走
	for(i=0;i<2;i++)
	RTZ(20,'R',3);
	YRQ(0x2D);
	for(i=0;i<2;i++)
	LTZ(20,'R',3);
	YLC(0x01,175);
	r4=DLZS();
	Right(35,200);
	Enter2(r4);
}
