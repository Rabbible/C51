/*	-----------   �ؼҺ���   -------------------------	*/
void ORHJ()		//�ô˺���ǰ �������ͷ�뷿��һ�ǵ�ǽ ��ֱ
{
	YRC(0x01,265);			/* 15 ! */
	HL();
	YRQ(0x2F);
	LJ();
	YLC(0x02,130);			 /* 18 ! */
	while(1) Keep();
}

void FRHJ()		//�ô˺���ǰ �������ͷ�뷿��һ�ǵ�ǽ ��ֱ
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


/*	-----------   ��������   -------------------------	*/

void LJF()  //�ӻ���ת�䡢ֱ�߸�Ӧ�����ſ���ƽ��ǽ����
{
	RTZ(20);			//��Ҫ����У������ �ʲ���ֱ��ת��
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
