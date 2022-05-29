#define uint unsigned int //�궨��uint Ϊunsigned int����

sbit P1_2 = P1^2;//������PWM���ƶ˿�
sbit P1_3 = P1^3;//������PWM���ƶ˿�
//***   ��ʱ��������  ********************
void delay_nus(unsigned int i)  //��ʱ:i>=12 ,i����С��ʱ��12 us
{ 
  i=i/10;
  while(--i);
}   

void delay_nms(unsigned int n)  //��ʱn ms
{ 
  n=n+1;
  while(--n)  
  delay_nus(900);         //��ʱ 1ms,ͬʱ���в���
}

void Forward(uint PulseCount,uint Velocity)//������ǰ�������������������PulseCount�������Ȳ���Velocity
{
    int i;
    for(i=1;i<= PulseCount;i++)//forѭ����������ʱ��
	{
		P1_3=1;
		delay_nus(1500+ Velocity);
        P1_3=0;
		P1_2=1;
		delay_nus(1460- Velocity);
		P1_2=0;
		delay_nms(20);
	}
}
void Right(uint PulseCount,uint Velocity) //������ת�������������������PulseCount�������Ȳ���Velocity
{   
    int i;
    for(i=1;i<= PulseCount;i++)//forѭ����������ʱ��
	{
		P1_3=1;
		delay_nus(1509-Velocity);
        P1_3=0;
		P1_2=1;
		delay_nus(1500-Velocity);
		P1_2=0;
		delay_nms(20);
	}
}

void Left(uint PulseCount,uint Velocity) //������ת�������������������PulseCount�������Ȳ���Velocity
{
    int i;
    for(i=1;i<= PulseCount;i++)//forѭ����������ʱ��
	{
		P1_3=1;
		delay_nus(1500+Velocity);
        P1_3=0;
		P1_2=1;
		delay_nus(1493+Velocity);
		P1_2=0;
		delay_nms(20);
	}
}

void Backward(uint PulseCount,uint Velocity)//������������������������PulseCount�������Ȳ���Velocity
{
    int i;
    for(i=1;i<= PulseCount;i++)//forѭ����������ʱ��
	{
		P1_3=1;
		delay_nus(1500-Velocity);
        P1_3=0;
		P1_2=1;
		delay_nus(1500+ Velocity);
		P1_2=0;
		delay_nms(20);
	}
}

void R_F(uint PulseCount)//��������ǰ�����ߵ����������������������PulseCount
{
    int i;
    for(i=1;i<= PulseCount;i++)//forѭ����������ʱ��
	{
		P1_3=1;
		delay_nus(1700);	/* �ٶȷ�Χ��Ҫ���� */
        P1_3=0;
		P1_2=1;
		delay_nus(1280);
		P1_2=0;
		delay_nms(20);
	}
}

void R_F2(uint PulseCount)//�̶Ⱥܴ�
{
    int i;
    for(i=1;i<= PulseCount;i++)//forѭ����������ʱ��
	{
		P1_3=1;
		delay_nus(1700);	/* �ٶȷ�Χ��Ҫ���� */
        P1_3=0;
		P1_2=1;
		delay_nus(1200);
		P1_2=0;
		delay_nms(20);
	}
}

void L_F(uint PulseCount)//��������ǰ�����ߵ����������������������PulseCount
{
    int i;
    for(i=1;i<= PulseCount;i++)//forѭ����������ʱ��
	{
		P1_3=1;
		delay_nus(1740);
        P1_3=0;
		P1_2=1;
		delay_nus(1300);	   /* �ٶȷ�Χ��Ҫ���� */
		P1_2=0;
		delay_nms(20);
	}
}

void Keep()  /*��ֹ*/
{
	{
        P1_3=0;
		P1_2=0;
		delay_nms(20);
	}
}

void Stop()//��������������ߵĹ��� ����
{
	P1_3=1;
	delay_nus(1500);
    P1_3=0;
	P1_2=1;
	delay_nus(1500);
	P1_2=0;
	delay_nms(20);
}

void F_R(uint PulseCount)//������ǰ��΢�����ߵ����������������������PulseCount
{
    int i;
    for(i=1;i<= PulseCount;i++)//forѭ����������ʱ��
	{
		P1_3=1;
		delay_nus(1700);	/* �ٶȷ�Χ��Ҫ���� */
        P1_3=0;
		P1_2=1;
		delay_nus(1290);
		P1_2=0;
		delay_nms(20);
	}
}
//
//void F_L(uint PulseCount)//������ǰ��΢�����ߵ����������������������PulseCount
//{
//    int i;
//    for(i=1;i<= PulseCount;i++)//forѭ����������ʱ��
//	{
//		P1_3=1;
//		delay_nus(1740);
//        P1_3=0;
//		P1_2=1;
//		delay_nus(1300);	   /* �ٶȷ�Χ��Ҫ���� */
//		P1_2=0;
//		delay_nms(20);
//	}
//}

void Left2(uint PulseCount,uint Velocity) //���ʱ��
{
    int i;
    for(i=1;i<= PulseCount;i++)//forѭ����������ʱ��
	{
		P1_3=1;
		delay_nus(1500+Velocity);
        P1_3=0;
		P1_2=1;
		delay_nus(1525+Velocity);
		P1_2=0;
		delay_nms(20);
	}
}

void Right2(uint PulseCount,uint Velocity) //���ʱ��
{
    int i;
    for(i=1;i<= PulseCount;i++)//forѭ����������ʱ��
	{
		P1_3=1;
		delay_nus(1510-Velocity);
        P1_3=0;
		P1_2=1;
		delay_nus(1505-Velocity);
		P1_2=0;
		delay_nms(20);
	}
}

void HR()//���廡��ֱ�����Һ���
{
    int i;
    for(i=1;i<=121;i++)//forѭ����������ʱ��
	{
		P1_3=1;
		delay_nus(1605);
        P1_3=0;
		P1_2=1;
		delay_nus(1300);
		P1_2=0;
		delay_nms(20);
	}
}

void HL()//���廡��ֱ��������
{
    int i;
    for(i=1;i<=140;i++)//forѭ����������ʱ��	146
	{
		P1_3=1;
		delay_nus(1700);
        P1_3=0;
		P1_2=1;
		delay_nus(1401);
		P1_2=0;
		delay_nms(20);
	}
}