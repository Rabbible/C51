#include<reg51.h> //������Ƭ���Ĵ����Ķ���ͷ�ļ�
#define uint unsigned int //�궨��uint Ϊunsigned int����
#define uchar unsigned char //�궨��uchar Ϊunsigned char ����
sbit P1_2 = P1^2;//������PWM���ƶ˿�
sbit P1_3 = P1^3;//������PWM���ƶ˿�

#include<BoeBot.h>//�������������ʱ����ͷ�ļ�
int PulseCount; int Velocity;
void Forward(PulseCount,Velocity)//������ǰ�������������������PulseCount�������Ȳ���Velocity
{
    int i;
    for(i=1;i<= PulseCount;i++)//forѭ����������ʱ��
	{
		P1_3=1;
		delay_nus(1500+ Velocity);
        P1_3=0;
		P1_2=1;
		delay_nus(1500- Velocity);
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
		delay_nus(1500-Velocity);
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
		delay_nus(1500+Velocity);
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
		delay_nus(1500+ Velocity);
		P1_2=0;
		delay_nms(20);
	}
}
int main(void)//������
{ 

	Forward(65,200);//��ǰ
	Left(26,200);//��ת
	Right(26,200);//��ת
	Backward(65,200);//���
	while(1);//����ȴ�
}
