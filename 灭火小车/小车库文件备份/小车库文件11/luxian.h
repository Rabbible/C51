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

/*	-----------   �ؼҺ���   -------------------------	*/
void FRHJ(uint flag)		//�ô˺���ǰ �������ͷ�뷿��һ�ǵ�ǽ ��ֱ
{	if(flag==1)
	RTZ(15,'F',3);		 //�Ľǲ���ִ�д���
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

void ORHJ()		//�ô˺���ǰ �������ͷ�뷿��һ�ǵ�ǽ ��ֱ
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

/*	-----------   ��������   -------------------------	*/
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
	if((r3<=0x50)&&(r3>=0x40)) 	 //�м�
	{	
		for(i=0;i<3;i++)
		LTZ(15,'F',2);
		RTZ(20,'R',2);		
	}
	else if(r3>0x50)   //��ǽ��
	{	
		for(i=0;i<3;i++)
		LTZ(15,'F',2);
		for(i=0;i<2;i++)
		LTZ(15,'R',2);
		if(r3>0x90)
		LTZ(15,'F',2);		
	}
	else if(r3<0x40)   //�뷿���Ž�
	{	
		for(i=0;i<2;i++)
		LTZ(15,'F',2);		
		LTZ(20,'R',2);
		if(r3<0x2E)
		LTZ(15,'F',2);		
	}
}

void LJF(uint flag)  //�ӻ���ת�䡢ֱ�߸�Ӧ�����ſ���ƽ��ǽ����
{	
	uint r2;
	RTZ(20,'F',3);			//��Ҫ����У������ �ʲ���ֱ��ת��
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
	//����Ϊ�ҽ���ģ��
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
	//�ҽ���ģ������һ��ֱ��
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
