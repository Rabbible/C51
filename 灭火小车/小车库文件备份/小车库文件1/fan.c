#include <REGX51.H>
#include< BoeBot.h>//�������������ʱ����ͷ�ļ�
#define uint unsigned int //�궨��uint Ϊunsigned int����
#define uchar unsigned char //�궨��uchar Ϊunsigned char ����
sbit SIG = P1^0; //�����źſ�������
sbit SIG1 = P0^0; //�����ź�1��������
sbit SIG2 = P0^1; //�����ź�2��������
sbit P12 = P1^2;//������PWM���ƶ˿�
sbit P13 = P1^3;//������PWM���ƶ˿�

void Right_Turn(void)//����ת
{
    int i;
    for(i=1;i<=55;i++)//��ת�������ѭ��
	{
		P13=1;
		delay_nus(1450);
         P13=0;
		P12=1;
		delay_nus(1450);
		P12=0;
		delay_nms(20);
	}
}
void Left_Turn(void)//����ת
{
    int i;
    for(i=1;i<=25;i++)//��ת�������ѭ��
	{
		P13=1;
		delay_nus(1550);
        P13=0;
		P12=1;
		delay_nus(1550);
		P12=0;
		delay_nms(20);
	}
}

void main()
{
	 SIG=1;//���õ����ֹ
	 SIG1=1;
	 SIG2=1;
	while(1)
	{
		if((SIG1==0)&&(SIG2==0))//���һ��洫������ⶼ��⵽����		
		 {
		 	SIG =0;  
		 	Left_Turn();
		 	Right_Turn();
		 }
		else
		SIG=1;	//���ÿ��ƶ˿�Ϊ�͵�ƽ�������ת����		    
	}

}
