#include "intrins.h"
#define uint unsigned int 
#define uchar unsigned char 

#define true  1 
#define false 0 

sbit trig=P1^4;//�����˿�
sbit echo=P1^5;//�źŽ��ն˿�
sbit tes = P1^0;//���Զ˿�

uchar time_h,time_l;//ʱ��ֵ
uchar distance_h,distance_l;//����ֵ
uint time,distance;//ʱ����ֵ��������ֵ
uint d;
uchar d0,d1,d2,d3;

//���ڳ�ʼ��
void init_9600(void)
{
		TMOD = 0x20;			
		TH1 = 0xFD;		
		TL1 = 0xFD;
		SCON = 0x50;			
		PCON &= 0xef;		
		TR1 = 1;				
	
		IE = 0x0;		

}

//��ʱ��0��ʼ��
void T0_INIT(void)
{
	TMOD &= 0xF0; /* Timer 0 mode 1 with software gate */ 
	TMOD |= 0x01; /* GATE0=0; C/T0#=0; M10=0; M00=1; */ 
	TH0 = 0x00; /* init values */ 
	TL0 = 0x00; 
	ET0=1; /* enable timer0 interrupt */ 
	//EA=1; /* enable interrupts */ 
	//TR0=1; /* timer0 run */
}
//�ⲿ�ж�1��ʼ��
void INT1_INIT(void)
{
	IT1=1;//�������жϲ���
	EX1=1;//�����ⲿ1�ж�
	//EA=1;
}
 //�ⲿ�ж�1�жϷ�����
void it_INT1(void) interrupt 2 
{ 
	IE1 = 0; 
}

//��ʱ��0�жϷ�����
void it_timer0(void) interrupt 1 
{ 
	TF0 = 0; 
}

int CSB()		  //�ô˺���ǰһ��Ҫ�����������ȳ�ʼ����
{		
	TH0 = 0x00; 
	TL0 = 0x00; 
	trig = 1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	trig = 0;

	while(0 == echo);
	TR0=1;
	while(1 == echo);
	TR0=0;
	time_h = TH0;
	time_l = TL0;
	//send_char(time_h);
	//send_char(time_l);
	time = time_h*256+time_l;
	distance =(int)(time*0.17);

	return distance;
}