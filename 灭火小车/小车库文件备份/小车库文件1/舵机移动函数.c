#include<reg51.h> //������Ƭ���Ĵ����Ķ���ͷ�ļ�
#define uint unsigned int //�궨��uint Ϊunsigned int����
#define uchar unsigned char //�궨��uchar Ϊunsigned char ����
sbit P1_2 = P1^2;//������PWM���ƶ˿�
sbit P1_3 = P1^3;//������PWM���ƶ˿�
#include<BoeBot.h>//�������������ʱ����ͷ�ļ�

void Forward(void)//��ǰ����
{	int i;
    for(i=1;i<=65;i++)
	{
    P1_3=1;
	delay_nus(1700);
    P1_3=0;
	P1_2=1;
	delay_nus(1300);
	P1_2=0;
	delay_nms(20);
	}
}
void Right_Turn(void)//����ת
{
    int i;
    for(i=1;i<=26;i++)//��ת�������ѭ��
	{
		P1_3=1;
		delay_nus(1300);
         P1_3=0;
		P1_2=1;
		delay_nus(1300);
		P1_2=0;
		delay_nms(20);
	}
}
void Left_Turn(void)//����ת
{
    int i;
    for(i=1;i<=26;i++)//��ת�������ѭ��
	{
		P1_3=1;
		delay_nus(1700);
        P1_3=0;
		P1_2=1;
		delay_nus(1700);
		P1_2=0;
		delay_nms(20);
	}
}
void Backward(void)//����
{
    int i;
    for(i=1;i<=65;i++)//�����������ѭ��
	{
		P1_3=1;
		delay_nus(1300);
         P1_3=0;
		P1_2=1;
		delay_nus(1700);
		P1_2=0;
		delay_nms(20);
	}
}

int main(void)//������
{
	{
		if((P2_4state()==0)&&(P2_3state()==0))//�ж�������������״̬�������˷����Ƿ�����ĸ��������ߡ�������������������ϰ�����Ⱥ��ˣ�����ת������ת
		{
			Backward(); //���
			Left_Turn();//����
			Left_Turn();//����
		}
		else if(P1_4state()==0)//������Ҿ��������ϰ������ˣ�������ת
		{
			Backward();//���
			Left_Turn();//����
		} 
        else if(P2_3state()==0)//��������������ϰ��������ת
		{
			Backward();//���
			Right_Turn();//����
		}
		else //���û�������κ��ϰ������ǰֱ��
			Forward();//��ǰ
	}
}
