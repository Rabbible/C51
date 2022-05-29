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

void Forward(PulseCount,Velocity)//������ǰ�������������������PulseCount�������Ȳ���Velocity
{
    int i;
    for(i=1;i<= PulseCount;i++)//forѭ����������ʱ��
	{
		P1_3=1;
		delay_nus(1500+ Velocity);
        P1_3=0;
		P1_2=1;
		delay_nus(1518- Velocity);
		P1_2=0;
		delay_nms(20);
	}
}
void Right(PulseCount,Velocity) //������ת�������������������PulseCount�������Ȳ���Velocity
{   
    int i;
    for(i=1;i<= PulseCount;i++)//forѭ����������ʱ��
	{
		P1_3=1;
		delay_nus(1518-Velocity);
        P1_3=0;
		P1_2=1;
		delay_nus(1500-Velocity);
		P1_2=0;
		delay_nms(20);
	}
}
void Left(PulseCount,Velocity) //������ת�������������������PulseCount�������Ȳ���Velocity
{
    int i;
    for(i=1;i<= PulseCount;i++)//forѭ����������ʱ��
	{
		P1_3=1;
		delay_nus(1500+Velocity);
        P1_3=0;
		P1_2=1;
		delay_nus(1482+Velocity);
		P1_2=0;
		delay_nms(20);
	}
}
void Backward(PulseCount,Velocity)//������������������������PulseCount�������Ȳ���Velocity
{
    int i;
    for(i=1;i<= PulseCount;i++)//forѭ����������ʱ��
	{
		P1_3=1;
		delay_nus(1500-Velocity);
        P1_3=0;
		P1_2=1;
		delay_nus(1482+ Velocity);
		P1_2=0;
		delay_nms(20);
	}
}

void R_F(PulseCount)//��������ǰ�����ߵ����������������������PulseCount�������Ȳ���Velocity
{
    int i;
    for(i=1;i<= PulseCount;i++)//forѭ����������ʱ��
	{
		P1_3=1;
		delay_nus(1693);	/* �ٶȷ�Χ��Ҫ���� */
        P1_3=0;
		P1_2=1;
		delay_nus(1300);
		P1_2=0;
		delay_nms(20);
	}
}

void L_F(PulseCount)//��������ǰ�����ߵ����������������������PulseCount�������Ȳ���Velocity
{
    int i;
    for(i=1;i<= PulseCount;i++)//forѭ����������ʱ��
	{
		P1_3=1;
		delay_nus(1700);
        P1_3=0;
		P1_2=1;
		delay_nus(1330);	   /* �ٶȷ�Χ��Ҫ���� */
		P1_2=0;
		delay_nms(20);
	}
}

void Keep(void)  /*��ֹ*/
{
	{
        P1_3=0;
		P1_2=0;
		delay_nms(20);
	}
}