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
	Left2(40,60);	//120��50 /230,40 --45��  //תһ��ͣ���룬��֤�ܴ���
	delay_nms(2000);
	Left2(40,60);	
	delay_nms(3000);
	Left2(40,60);	
	delay_nms(5000);
	SIG=1;
	Left(37,200);
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
	Right2(30,90);	
	delay_nms(2000);
	Right2(30,90);	
	delay_nms(2000);										   
	Right2(30,90);	
	delay_nms(4000);
	SIG=1;
	Right(39,200);
}

void FourJ_Chui()
{
	SIG=0;
	delay_nms(2000);
	Right2(30,90);	
	delay_nms(2000);
	Right2(30,90);	
	delay_nms(2000);										   
	Right2(30,90);	
	delay_nms(2000);

	Left2(40,60);	//120��50 /230,40 --45��  //תһ��ͣ���룬��֤�ܴ���
	delay_nms(2000);
	Left2(40,60);	
	delay_nms(3000);
	Left2(40,60);	
	delay_nms(3000);
	SIG=1;
}

void FJ(uint c)					 //�ĽǼ��+���(û��⵽��ص����ǰλ��,��Ӱ���ʼλ��)
{	uint i;						 //c �ǲ������ܵ���ת�ĽǶ�
	for(i=0;i<32-c;i++)		//90du
	{
		Left(1,200);	 //  2!  4.
		if((SIG1==0)&&(SIG2==0))
		{
			Left(32-i-c,200);  //  5!  5.
			Stop();
			FourJ_Chui();
			Left(33,200);

			Forward(50,300);  //��ֹ�����ó���������ֱ��
			FRHJ(4);		  //����������
		}
	}
	Right(32-c,200);
}
void OneJ()		  //��⵽һ�Ǹ��������
{	uint i;

	Left(30,200);
	FJ(26);
	Right(30,200);

	for(i=0;i<2;i++)
	LTZ(20,'F',3);

	YLC(0x02,127);         /* 8 ! */
	L_Chui();
	RTZ(20,'F',3);
	RTZ(15,'F',3);

}

void TwoJ()
{
	LTZ(15,'F',3);
	LTZ(15,'F',3);
	YLC(0x02,160);
	Right(35,200);
	YLC(0x01,127);
	L_Chui();
	Forward(20,200);
	RTZ(20,'F',3);
	RTZ(15,'F',3);
	YRC(0x01,155);
	YRC(0x01,155);
	Left(38,200);
	Right(1,200);
}
void ThreeJ(uint x)
{
	Right(3,200);
	F_R(x);
	ZC(125);
	R_Chui();
	LTZ(15,'F',3);
	LTZ(15,'F',3);
	ZC(160);
	Left(35,200);
}

//�������
void FR1J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{
	OneJ();
	FRHJ(1);
}

void FR2J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{
	TwoJ();
	//�ؼ�
	FRHJ(1);
}

void FR3J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{	
	ThreeJ(30);
	//�ؼ�
	FRHJ(1);
}

void ThreeR1J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{	uint i;
	Left(30,200);
	FJ(26);
	Right(30,200);
	
	for(i=0;i<2;i++)
	LTZ(20,'F',3);		   //����ƫȻ������ƫ��ֱ��ƫ��
	for(i=0;i<5;i++)
	LTZ(15,'F',2);
	YLC(0x02,127);         /* 8 ! */
	L_Chui();
	for(i=0;i<4;i++)
	RTZ(20,'F',3);
	RTZ(15,'F',2);
	//������
	ThreeRHJ();
}

void ThreeR2J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{
	TwoJ();
	//�ؼ�
	ThreeRHJ();
}


void ThreeR3J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{	
	Right(6,200);
	ThreeJ(30);
	//�ؼ�
	ThreeRHJ();
}

void TwoR1J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{	
	OneJ();
	//�ؼ�
	TwoRHJ();
}

void TwoR2J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{
	TwoJ();
	TwoRHJ();
}

void TwoR3J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{
	ThreeJ(50);
	//�ؼ�
	TwoRHJ();
}

void OR1J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{	
	OneJ();
	//������
	ORHJ();
}

void OR2J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{
	TwoJ();
	//�ؼ�
	ORHJ();
}

void OR3J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{	
	ThreeJ(15);
	//�ؼ�
	ORHJ();
}

//�ܷ��亯�������+���+��ͷ+�ؼң�	 �л����ؼҲ����⿨�ڴ˳�����
void FourRoom()
{
	uint i;
	for(i=0;i<15;i++)	  //1��
	{
		Left(1,200);
		if((SIG1==0)&&(SIG2==0))
		{	
			Right(i,200);
			FR1J();
		}
	}
	FJ(15);
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
	Right(9,200);
	Left(1,200);
	 
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
	 
}

void TwoRoom()
{
	uint i;

	for(i=0;i<15;i++)
	{
		Left(1,200);
		if((SIG1==0)&&(SIG2==0))
		{	
			//LefTt(10-i,200);
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
				TwoR3J();
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
			TwoR3J();
		}
	}

	Right(17,200);		 //gai le!
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