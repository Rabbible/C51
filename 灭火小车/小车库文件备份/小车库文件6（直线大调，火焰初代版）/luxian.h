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

void JF()  //�ӻ���ת�䡢ֱ�߸�Ӧ�����ſ���ƽ��ǽ����
{
	RTZ(30);			//��Ҫ����У������ �ʲ���ֱ��ת��
	RTZ(20);
	RTZ(15);
	//Forward(80,200);
	Left(36,200);
	Forward(110,200);
	RTZ(15);
	RTZ(20);
}


void FRJF()
{
	//F_R(20);
	RTZ(15);
	RTZ(15);
	RTZ2(15);
	RTZ2(15);
	RTZ(30);
	RTZ(30);
	YLQ3(0x2E);
	LJ();
//	HL();
//	Stop();
//	Stop();
//	RWQ();
	JF();
}

void ThreeRJF()
{
	YRQ(0x2D);
	ZC(165);
	Right(36,200);
	YLQ(0x2E);
	LJ();
	JF();
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
