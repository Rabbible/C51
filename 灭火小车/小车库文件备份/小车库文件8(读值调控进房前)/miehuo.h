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
		if((v[i+1]-v[i])>=20) 
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

//�������
void FR1J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{
	Right(1,200);
	YLC(0x02,127);         /* 8 ! */
	L_Chui();
	RTZ(20,'F',3);
	RTZ(15,'F',3);
	//������
	FRHJ();
}

void FR2J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{
	LTZ(15,3);
	LTZ(15,3);
	YLC(0x02,160);
	Right(35,200);
	YLC(0x01,127);
	L_Chui();
	//Left(48,200);
	Forward(20,200);
	RTZ(20,'F',3);
	RTZ(15,'F',3);
	YRC(0x01,155);
	YRC(0x01,155);
	Left(38,200);
	Right(1,200);
	//�ؼ�
	FRHJ();
}

void FR3J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{	Right(2,200);
	ZC(125);
	R_Chui();
	ZC(160);
	Left(36,200);
	//�ؼ�
	FRHJ();
}

void ThreeR1J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{	
	LTZ(20,3);		   //����ƫȻ������ƫ��ֱ��ƫ��
	LTZ(20,3);
	LTZ(15,3);
	LTZ(15,3);
	LTZ(15,2);
	LTZ(15,2);
	LTZ(15,2);
	YLC(0x02,127);         /* 8 ! */
	L_Chui();
	RTZ(20,'F',3);
	RTZ(15,'F',3);
	//������
	ThreeRHJ();
}

void ThreeR2J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{
	LTZ(15,3);
	LTZ(15,3);
	YLC(0x02,160);
	Right(35,200);
	YLC(0x01,127);
	L_Chui();
	//Left(48,200);
	Forward(20,200);
	RTZ(20,'F',3);
	RTZ(15,'F',3);
	YRC(0x01,155);
	YRC(0x01,155);
	Left(38,200);
	Right(1,200);
	//�ؼ�
	ThreeRHJ();
}


void ThreeR3J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{	Right(7,200);
	ZC(125);
	R_Chui();
	ZC(160);
	Left(36,200);
	//�ؼ�
	ThreeRHJ();
}

void TwoR1J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{	Right(1,200);
	YLC(0x02,127);         /* 8 ! */
	L_Chui();
	RTZ(20,'F',3);
	RTZ(15,'F',3);
	//�ؼ�
	TwoRHJ();
}

void TwoR2J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{
	LTZ(15,3);
	LTZ(15,3);
	YLC(0x02,160);
	Right(35,200);
	YLC(0x01,127);
	L_Chui();
	//Left(48,200);
	Forward(20,200);
	RTZ(20,'F',3);
	RTZ(15,'F',3);
	YRC(0x01,155);
	YRC(0x01,155);
	Left(38,200);
	Right(1,200);
	TwoRHJ();
}

void TwoR3J(uint r)		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{	if(r<0x4E&&r>=0x49) Right(9,200);
	else if(r>0x49) Right(6,200);
	else if(r<0x4E) Right(11,200);
	ZC(125);
	R_Chui();
	Right(8,200);
	LTZ(15,3);
	LTZ(15,3);
	ZC(160);
	Left(35,200);
	//�ؼ�
	TwoRHJ();
}

void OR1J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{
	Right(1,200);
	YLC(0x02,127);         /* 8 ! */
	L_Chui();
	RTZ(20,'F',3);
	RTZ(15,'F',3);
	//������
	ORHJ();
}

void OR2J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{
	LTZ(15,3);
	LTZ(15,3);
	YLC(0x02,160);
	Right(35,200);
	YLC(0x01,127);
	L_Chui();
	//Left(48,200);
	Forward(20,200);
	RTZ(20,'F',3);
	RTZ(15,'F',3);
	YRC(0x01,155);
	YRC(0x01,155);
	Left(38,200);
	Right(1,200);
	//�ؼ�
	ORHJ();
}

void OR3J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{	Right(3,200);

	ZC(125);
	R_Chui();
	LTZ(15,3);
	LTZ(15,3);
	ZC(160);
	Left(35,200);
	//�ؼ�
	ORHJ();
}

//�ܷ��亯�������+���+��ͷ+�ؼң�	 �л����ؼҲ����⿨�ڴ˳�����
void FourRoom()
{
	uint i;
	for(i=0;i<15;i++)
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
	for(i=0;i<25;i++)		
	{
		Right(1,200);	// 4!  3.	 
		if((SIG1==0)&&(SIG2==0))
		{	
			Right(25-i,200);
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

	Right(15,200);		 //gai le!
	Left(1,200);		//�����ſ�ͣ�£��ӽ���һ���������
	 
}

void ThreeRoom()
{
	uint i;
	
		for(i=0;i<15;i++)
		{
			Left(1,200);
			if((SIG1==0)&&(SIG2==0))
			{	
				//Left(10-i,200);
				Right(i,200);
				ThreeR1J();
			}
		}
			
		Right(11,200);
		for(i=0;i<23;i++)		
		{
			Right(1,200);	// 4!  3.	 
			if((SIG1==0)&&(SIG2==0))
			{	
				Left(i,200);  //  1!  7.
				ThreeR2J();
				
			}
		}
		Right(5,200);	
			for(i=0;i<26;i++)
			{
				Right(1,200);	 //  2!  4.
				if((SIG1==0)&&(SIG2==0))
				{
					Left(i,200);  //  5!  5.
					ThreeR3J();
				}
			}

		Right(21,200);
		Left(1,200);		//�����ſ�ͣ�£��ӽ���һ���������
		Stop();
	 
}

void TwoRoom(uint r)
{
	uint i;

	for(i=0;i<15;i++)
	{
		Left(1,200);
		if((SIG1==0)&&(SIG2==0))
		{	
			//LefTtt(10-i,200);
			Right(i,200);
			TwoR1J();
		}
	}
		
	Right(18,200);
	for(i=0;i<25;i++)		
	{
		Right(1,200);	// 4!  3.	 
		if((SIG1==0)&&(SIG2==0))
		{	
			Right(25-i,200);
			Right(15,200);	 //  2!  4.
			if((SIG1==0)&&(SIG2==0))
			{
				Left(15,200);  //  5!  5.
				TwoR3J(r);
			}
			else
			{
				Left(43,200);  //  1!  7.
				TwoR2J();
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
			TwoR3J(r);
		}
	}

	Right(15,200);		 //gai le!
	Left(1,200);		//�����ſ�ͣ�£��ӽ���һ���������
	 
}
void ORoom()
{
	uint i;
	for(i=0;i<15;i++)
	{
		Left(1,200);
		if((SIG1==0)&&(SIG2==0))
		{	
			//Left(10-i,200);
			Right(i,200);
			OR1J();
		}
	}
		
	Right(18,200);
	for(i=0;i<25;i++)		
	{
		Right(1,200);	// 4!  3.	 
		if((SIG1==0)&&(SIG2==0))
		{	
			Right(25-i,200);
			Right(15,200);	 //  2!  4.
			if((SIG1==0)&&(SIG2==0))
			{
				Left(15,200);  //  5!  5.
				OR3J();
			}
			else
			{
				Left(43,200);  //  1!  7.
				OR2J();
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
			OR3J();
		}
	}

	Right(15,200);		 //gai le!
	Left(1,200);
}