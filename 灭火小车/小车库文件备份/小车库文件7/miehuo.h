#include<fan.h>
#include<luxian.h>

//����ߵ����򸽽�������� ����תͷ 180��
void L_Chui()
{	
	uint i;
	int idata v[30]={127};
	for(i=0;i<29;i++)				 //���ǽ��>45����˳�������
	{
		v[i+1]=CSB();
		if((v[i+1]-v[i])>=19) 
		{
			SIG=0;
			break;
		}
		else Left(5,60);
	}
	SIG=0;
	delay_nms(2000);
//	if((SIG1==0)&&(SIG2==0))
//	{
		Left2(40,50);	//120��50 /230,40 --45��  //תһ��ͣ���룬��֤�ܴ���
		delay_nms(2000);
		Left2(40,50);	
		delay_nms(3000);
		Left2(40,50);	
		delay_nms(5000);
		SIG=1;
//	}
//	else 
//	{
//		Left(22,200);
//		SIG=1;
//	}
	Left(39,200);
}

void R_Chui()
{
	uint i;
	int idata v[30]={125};
	for(i=0;i<29;i++)				 //���ǽ��>45����˳�������
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
	Right2(30,70);	
	delay_nms(2000);
	Right2(30,70);	
	delay_nms(2000);										   
	Right2(30,70);	
	delay_nms(4000);
	SIG=1;
	Right(41,200);
}

//��һ������ǰ����𲢻ؼ�(�������ѭ��)
void OR1J()
{
	YLC(0x02,135);         /* 8 ! */
	L_Chui();
	//������
	Left(36,200);	/* 9 ! */
	//�ؼ�
	ORHJ();
}

void OR2J()
{
	YLC(0x02,155);			 /* >8 ! */
	Right(33,200);		 /* 90���һ��� */
	YLC(0x02,127);			 /* 8 ! */
	L_Chui();  //������
	Left(50,200);		 /* 2 ! */
	YRC(0x02,121);
	Left(33,200);
	//�ؼ�
	ORHJ();
}

void OR3J()
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
	//������
	Left(10,200);
	Backward(85,200);
	Right(32,200);
	//�ؼ�
	ORHJ();
}


void FR1J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{
	YLC(0x02,127);         /* 8 ! */
	L_Chui();
	RTZ(20);
	RTZ(15);
	//������
	FRHJ();
}

void FR2J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{
	LTZ(15);
	LTZ(15);
	YLC(0x02,160);
	Right(35,200);
	YLC(0x01,127);
	L_Chui();
	//Left(48,200);
	Forward(20,200);
	RTZ(20);
	RTZ(15);
	YRC(0x01,155);
	YRC(0x01,155);
	Left(38,200);
	Right(1,200);
	//�ؼ�
	FRHJ();
}

void FR3J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{	
	YLC(0x01,125);
	R_Chui();
	ZC(160);
	Left(36,200);
	//�ؼ�
	FRHJ();
}

void ThreeR1J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{
	YLC(0x02,135);         /* 8 ! */
	L_Chui();
	//������
	Left(36,200);	/* 9 ! */
	ThreeRHJ();
}

void ThreeR2J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{
	YLC(0x02,155);			 /* >8 ! */
	Right(33,200);		 /* 90���һ��� */
	YLC(0x02,127);			 /* 8 ! */
	L_Chui();  //������
	Left(50,200);		 /* 2 ! */
	YRC(0x02,121);
	Left(55,200);
	ThreeRHJ();
}


void ThreeR3J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
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
	//������
	Left(11,200);
	Backward(150,200);
	Right(33,200);
	ThreeRHJ();
}

void TwoR1J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{
	YLC(0x02,135);         /* 8 ! */
	L_Chui();
	//������
	Left(36,200);	/* 9 ! */
	TwoRHJ();
}

void TwoR2J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{
	YLC(0x02,155);			 /* >8 ! */
	Right(33,200);		 /* 90���һ��� */
	YLC(0x02,127);			 /* 8 ! */
	L_Chui();  //������
	Left(50,200);		 /* 2 ! */
	YRC(0x02,121);
	Left(33,200);
	TwoRHJ();
}


void TwoR3J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{
	Forward(100,200);
	RTZ(20);
	RTZ(20);
	RTZ(20);
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
	//������
	Left(11,200);
	Backward(270,200);
	Right(35,200);
	TwoRHJ();
}


//�ܷ��亯�������+���+��ͷ+�ؼң�	 �л����ؼҲ����⿨�ڴ˳�����
void FourRoom()
{
	uint i;
	if((SIG1==0)&&(SIG2==0)) 	//��һ������ǰ����𲢻ؼ�(�������ѭ��)
	{
		for(i=0;i<11;i++)	   // 3!    1.
		{
			Left(1,200);
			if((SIG1==0)&&(SIG2==0))
			{	
				//Left(10-i,200);
				Right(i,200);
				FR1J();
			}
		}
		Right(11,200);	// 1!   2.
		FR2J();
	}

	else
	{	
		for(i=0;i<11;i++)
		{
			Left(1,200);
			if((SIG1==0)&&(SIG2==0))
			{	
				//Leftt(10-i,200);
				Right(i,200);
				FR1J();
			}
		}
			
		Right(18,200);
		for(i=0;i<23;i++)		
		{
			Right(1,200);	// 4!  3.	 
			if((SIG1==0)&&(SIG2==0))
			{	
				Right(23-i,200);
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

		Right(14,200);		 //gai le!
		Left(1,200);		//�����ſ�ͣ�£��ӽ���һ���������
		Stop();
	}  
}

void ThreeRoom()
{
	uint i;
	if((SIG1==0)&&(SIG2==0)) 	//��һ������ǰ����𲢻ؼ�(�������ѭ��)
	{	  
		for(i=0;i<11;i++)	   // 3!    1.
		{
			Left(1,200);
			if((SIG1==0)&&(SIG2==0))
			{	
				//Left(10-i,200);
				Right(i,200);
				FR1J();
			}
		}
		Right(11,200);	// 1!   2.
		FR2J();
	}

	else
	{	

		for(i=0;i<11;i++)
		{
			Left(1,200);
			if((SIG1==0)&&(SIG2==0))
			{	
				//Left(10-i,200);
				Right(i,200);
				FR1J();
			}
		}
			
		Right(11,200);
		for(i=0;i<28;i++)		
		{
			Right(1,200);	// 4!  3.	 
			if((SIG1==0)&&(SIG2==0))
			{	
				Left(i,200);  //  1!  7.
				FR2J();
				
			}
		}
//		Right(5,200);	
//			for(i=0;i<26;i++)
//			{
//				Right(1,200);	 //  2!  4.
//				if((SIG1==0)&&(SIG2==0))
//				{
//					Left(i,200);  //  5!  5.
//					FR3J();
//				}
//			}

//		Right(13,200);
//		Left(1,200);		//�����ſ�ͣ�£��ӽ���һ���������
		Stop();
	} 
}