#define uint unsigned int //�궨��uint Ϊunsigned int����
/*	-----------   �ؼҺ���   -------------------------	*/
void FRHJ()		//�ô˺���ǰ �������ͷ�뷿��һ�ǵ�ǽ ��ֱ
{
	RTZ(15,'F',3);
	RTZ(15,'F',3);
	YRC(0x01,350);
	ZC(165);
	Right(36,200);
	LTZ(20,3);
	LTZ(20,3);
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

void ORHJ()		//�ô˺���ǰ �������ͷ�뷿��һ�ǵ�ǽ ��ֱ
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

/*	-----------   ��������   -------------------------	*/

void LJF()  //�ӻ���ת�䡢ֱ�߸�Ӧ�����ſ���ƽ��ǽ����
{	
	uint i,r2=0;
	RTZ(20,'F',3);			//��Ҫ����У������ �ʲ���ֱ��ת��
	RTZ(20,'R',3);
	for(i=0;i<2;i++)
	RTZ(15,'F',3);
	r2=DRZS();
	Left(36,200);
	Forward(50,300);
	F_R(30);
	Forward(20,300);
	if(r2>0x63) 
	{	for(i=0;i<2;i++)
		RTZ(20,'R',2);
	}
	else if((r2<0x62)&&(r2>=0x43))
	{	for(i=0;i<2;i++)
		RTZ(15,'R',2);
	}  
	else if(r2<0x43) RTZ(15,'R',2);
	
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
{	uint i;
	//int asd;
	for(i=0;i<3;i++)
	RTZ(15,'F',3);
	YRC(0x01,350);
	ZC(165);
	Right(35,200);
	LTZ(15,3);
	YLQ(0x2E);
	LJ();
	
	RTZ(20,'F',3);			//��Ҫ����У������ �ʲ���ֱ��ת��
	RTZ(20,'R',3);
	for(i=0;i<2;i++)
	RTZ(15,'F',3);
	//asd=DRZS();
	Left(35,200);
	Forward(50,300);
	F_R(30);
	Forward(20,300);
//	if(asd>0x63) LTZ(18,2);
//	else if((asd<0x62)&&(asd>=0x43))
//	{
//		LTZ(18,2);
//		LTZ(15,2);
//	}  
//	else Keep();
	
}

void TwoRJF(uint *r)
{	uint i;
	YRQ(0x2D);
	F_R(20);
	ZC(157);
	Left(34,200);
	//����Ϊ�ҽ���ģ��
	YRQ(0x2D);
	Forward(3,300);
	YLC(0x01,165);
	*r=DLZS();
	Right(35,200);
	for(i=0;i<2;i++)
	LTZ(20,3);
	LTZ(17,3);
	for(i=0;i<5;i++)
	LTZ(15,2);
}

void ORJF()
{	uint i;
	RTZ(20,'F',3);
	YRC(0x01,159);
	Left(34,200);
	RTZ(20,'F',3);
	YRQ(0x2D);
	Forward(3,300);
	LTZ(20,3);
	YLQ(0x2D);
	LJ();

	//�ҽ���ģ������һ��ֱ��
	YRQ(0x2D);
	YLC(0x01,165);
	Right(35,200);
	for(i=0;i<2;i++)
	LTZ(20,3);
	for(i=0;i<6;i++)
	LTZ(15,2);
}
