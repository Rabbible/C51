#include<fan.h>
#include<luxian.h>

//����ߵ����򸽽�������棬�����תͷ90���ȥ
void L_Chui()
{	
	uint i;
	int idata v[50]={127};
	for(i=0;i<49;i++)				 //���ǽ��>45����˳�������
	{
		v[i+1]=CSB();
		if((v[i+1]-v[i])>=30) 
		{
			SIG=0;
			break;
		}
		else Left(5,60);
	}
	SIG=0;
	delay_nms(4000);
	if((SIG1==0)&&(SIG2==0))
	{
		Left2(40,50);	//120��50 /230,40 --45��  //תһ��ͣ���룬��֤�ܴ���
		delay_nms(5000);
		Left2(40,50);	
		delay_nms(4000);
		Left2(40,50);	
		delay_nms(4000);
		SIG=1;
	}
	else 
	{
		Left(23,200);
		SIG=1;
	}
}

//��һ������ǰ����𲢻ؼ�(�������ѭ��)
void OF1J()
{
	YLC(0x02,135);         /* 8 ! */
	L_Chui();
	//������
	Left(36,200);	/* 9 ! */
	//�ؼ�
	OFHJ();
}

void OF2J()
{
	YLC(0x02,155);			 /* >8 ! */
	Right(33,200);		 /* 90���һ��� */
	YLC(0x02,127);			 /* 8 ! */
	L_Chui();  //������
	Left(50,200);		 /* 2 ! */
	YRC(0x02,121);
	Left(33,200);
	//�ؼ�
	OFHJ();
}

void OF3J()
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
	OFHJ();
}


void FF1J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{
	YLC(0x02,127);         /* 8 ! */
	L_Chui();
	//������
	Left(36,200);	/* 9 ! */
	FFHJ();
}

void FF2J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{
	YLC(0x02,173);
	Right(33,200);
	ZC(127);
	L_Chui();
	Left(38,200);
	YRC(0x02,155);
	Left(32,200);
	//�ؼ�
	FFHJ();
}

void FF3J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{
	Forward(65,200);
	SIG=0;
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
	FFHJ();
}

void ThreeF1J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{
	YLC(0x02,135);         /* 8 ! */
	L_Chui();
	//������
	Left(36,200);	/* 9 ! */
	ThreeFHJ();
}

void ThreeF2J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{
	YLC(0x02,155);			 /* >8 ! */
	Right(33,200);		 /* 90���һ��� */
	YLC(0x02,127);			 /* 8 ! */
	L_Chui();  //������
	Left(50,200);		 /* 2 ! */
	YRC(0x02,121);
	Left(55,200);
	ThreeFHJ();
}


void ThreeF3J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
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
	ThreeFHJ();
}

void TwoF1J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{
	YLC(0x02,135);         /* 8 ! */
	L_Chui();
	//������
	Left(36,200);	/* 9 ! */
	TwoFHJ();
}

void TwoF2J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{
	YLC(0x02,155);			 /* >8 ! */
	Right(33,200);		 /* 90���һ��� */
	YLC(0x02,127);			 /* 8 ! */
	L_Chui();  //������
	Left(50,200);		 /* 2 ! */
	YRC(0x02,121);
	Left(33,200);
	TwoFHJ();
}


void TwoF3J()		/* �Ӷ�Ӧ�ĽǶȻ����Ӧ */
{
	Forward(40,200);
	F_R(50);
	RTZ();
	RTZ();
	RTZ();
	RTZ();
	RTZ();
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
	TwoFHJ();
}