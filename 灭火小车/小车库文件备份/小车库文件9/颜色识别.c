#include<reg51.h>  //����51��Ƭ���Ĵ��������ͷ�ļ�

#define uint unsigned int 
#define uchar unsigned char 

#define true  1 
#define false 0 
	
uchar datah,datal;
uint int_count=0;//�жϼ���
uint int_count_r=0;//��ɫ�˲����жϼ���
uint int_count_b=0;//��ɫ�˲����жϼ���
uint int_count_g=0;//��ɫ�˲����жϼ���
uint t0_count=0;//��ʱ�������
uint t0_count_r=0;//��ɫ�˲����������
uint t0_count_b=0;//��ɫ�˲����������
uint t0_count_g=0;//��ɫ�˲����������

char flag_white_balance = false;//��ƽ�������־
char flag_check_r = false;//��ɫ�˲���������־
char flag_check_b = false;//��ɫ�˲���������־
char flag_check_g = false;//��ɫ�˲���������־

sbit S0=P0^3;
sbit S1=P1^1;
sbit LED=P3^7;
sbit OUT=P2^5;
sbit tes=P2^7;
sbit S2=P0^7;
sbit S3=P2^3;
sbit ss=P2^6;

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
//����һ���ֽ�
void send_char(unsigned char txd)
{
		SBUF = txd;
		while(!TI);			
		TI = 0;					
}
//��ʱ��0��ʼ��
T0_INIT()
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
INT1_INIT()
{
	
	IT1=1;//�������жϲ���
	EX1=1;//�����ⲿ0�ж�
	//EA=1;
}
 
//��ʱ����1����
void delay1ms()
{
   unsigned char i,j;	
	 for(i=0;i<10;i++)
	  for(j=0;j<33;j++)
	   ;		 
 }

//��ʱ������n����
 void delaynms(unsigned int n)
 {
   unsigned int i;
	for(i=0;i<n;i++)
	   delay1ms();
 }

//��ɫ���
void color_check()
{
		T0_INIT();
		INT1_INIT();
	
		//ѡ�������������Ϊ1 ��1
		S0=1;
		S1=1;
		//����LED��
		LED=1;
	
		//ѡͨ��ɫ�˲���
		S2=0;
		S3=0;
		//�������������趨
		flag_white_balance = false;
		flag_check_r = true;
		flag_check_b = false;
		flag_check_g = false;
		int_count=0;//����255
		t0_count=0;//����red�˲���ʱ��ʱ�������
		TH0 = 0x0ff; //��ʱ��ʱ���ֵ,���ʱ��Ϊ0.1ms
		TL0 = 0x0a3;
		ss=1;//P2.6�źŲ��Կ�
		//�����жϺͼ���
		EX1=1;//�ⲿ0�жϿ���
		EA=1;//���жϿ���
		TR0=1;//��ʱ��0������ʱ
		while(t0_count_r!=t0_count);//�ȴ���ɫ�˲���ʱ���׼��
		
		int_count_r = int_count;//ʱ���׼������������ֵ
		datal = int_count_r;
		datah = int_count_r>>8;
		
		send_char(datah);
		send_char(datal);

		//ѡͨ��ɫ�˲���
		S2=0;
		S3=1;
		//�������������趨
		flag_white_balance = false;
		flag_check_r = false;
		flag_check_b = true;
		flag_check_g = false;
		int_count=0;//����255
		t0_count=0;//����red�˲���ʱ��ʱ�������
		TH0 = 0x0ff; //��ʱ��ʱ���ֵ,���ʱ��Ϊ0.1ms
		TL0 = 0x0a3;
		ss=1;//P2.6�źŲ��Կ�
		//�����жϺͼ���
		EX1=1;//�ⲿ0�жϿ���
		//EA=1;//���жϿ���
		TR0=1;//��ʱ��0������ʱ
		while(t0_count_b!=t0_count);//�ȴ���ɫ�˲���ʱ���׼��
		
		int_count_b = int_count;//ʱ���׼������������ֵ
		datal = int_count_b;
		datah = int_count_b>>8;
		
		send_char(datah);
		send_char(datal);
		
		//ѡͨ��ɫ�˲���
		S2=1;
		S3=1;
		//�������������趨
		flag_white_balance = false;
		flag_check_r = false;
		flag_check_b = false;
		flag_check_g = true;
		int_count=0;//����255
		t0_count=0;//����red�˲���ʱ��ʱ�������
		TH0 = 0x0ff; //��ʱ��ʱ���ֵ,���ʱ��Ϊ0.1ms
		TL0 = 0x0a3;
		ss=1;//P2.6�źŲ��Կ�
		//�����жϺͼ���
		EX1=1;//�ⲿ0�жϿ���
		//EA=1;//���жϿ���
		TR0=1;//��ʱ��0������ʱ
		while(t0_count_g!=t0_count);//�ȴ���ɫ�˲���ʱ���׼��
		
		int_count_g = int_count;//ʱ���׼������������ֵ
		datal = int_count_g;
		datah = int_count_g>>8;
		
		send_char(datah);
		send_char(datal);
		
		//�رյ�Դ
		S0=0;
		S1=0;
		//�ر�LED��
		LED = 0;
		//�����ж�
		EA=0;
		//while(1);
		
}
//��ƽ��
void color_white_balance()
{
		T0_INIT();
		INT1_INIT();
		flag_white_balance = true;
		flag_check_r = false;
		flag_check_b = false;
		flag_check_g = false;
		//ѡ�������������Ϊ1 ��1
		S0=1;
		S1=1;
		//����LED��
		LED=1;
	
		//ѡͨ��ɫ�˲���
		S2=0;
		S3=0;
		//�������������趨
		int_count=0;//����255
		t0_count=0;//����red�˲���ʱ��ʱ�������
		TH0 = 0x0ff; //��ʱ��ʱ���ֵ,���ʱ��Ϊ0.1ms
		TL0 = 0x0a3;
		ss=1;//P2.6�źŲ��Կ�
		//�����жϺͼ���
		EX1=1;//�ⲿ0�жϿ���
		EA=1;//���жϿ���
		TR0=1;//��ʱ��0������ʱ
		while(255!=int_count);//����255��
		
		t0_count_r = t0_count;
		datal = t0_count_r;
		datah = t0_count_r>>8;
		
		send_char(datah);
		send_char(datal);
		
		//ѡͨ��ɫ�˲���
		S2=0;
		S3=1;
		//�������������趨
		int_count=0;//����255
		t0_count=0;//����red�˲���ʱ��ʱ�������
		TH0 = 0x0ff; //��ʱ��ʱ���ֵ,���ʱ��Ϊ0.1ms
		TL0 = 0x0a3;
		ss=1;//P2.6�źŲ��Կ�
		//�����жϺͼ���
		EX1=1;//�ⲿ0�жϿ���
		//EA=1;//���жϿ���
		TR0=1;//��ʱ��0������ʱ
		while(255!=int_count);//����255��
		
		t0_count_b = t0_count;
		datal = t0_count_b;
		datah = t0_count_b>>8;
		
		send_char(datah);
		send_char(datal);
		
		//ѡͨ��ɫ�˲���
		S2=1;
		S3=1;
		//�������������趨
		int_count=0;//����255
		t0_count=0;//����red�˲���ʱ��ʱ�������
		TH0 = 0x0ff; //��ʱ��ʱ���ֵ,���ʱ��Ϊ0.1ms
		TL0 = 0x0a3;
		ss=1;//P2.6�źŲ��Կ�
		//�����жϺͼ���
		EX1=1;//�ⲿ0�жϿ���
		//EA=1;//���жϿ���
		TR0=1;//��ʱ��0������ʱ
		while(255!=int_count);//����255��
		
		t0_count_g = t0_count;
		datal = t0_count_g;
		datah = t0_count_g>>8;
		
		send_char(datah);
		send_char(datal);
		
		//�رյ�Դ
		S0=0;
		S1=0;
		//�ر�LED��
		LED = 0;
		//�����ж�
		EA=0;
		//while(1);

}
//�ⲿ�ж�1�жϷ�����
void it_INT1(void) interrupt 2 
{ 
	IE1 = 0; 
	int_count++;//����������
	if(flag_white_balance == true)
	{
			if(255==int_count)
			{
				EX1=0;
				TR0=0;
				ss=0;//P2.6�źŲ��Կ�
			}
	}
	
	tes = ~tes;
	
}
//��ʱ��0�жϷ�����
void it_timer0(void) interrupt 1 
{ 
	TF0 = 0; 

	TH0 = 0x0ff; 
	TL0 = 0x0a3;
	t0_count++;//��ʱ�����������
	if(flag_check_r == true)
	{
			if(t0_count_r==t0_count)//���ƽ���׼ʱ��һ��
			{
				EX1=0;
				TR0=0;
				ss=0;//P2.6�źŲ��Կ�
			}
	}
	if(flag_check_b == true)
	{
			if(t0_count_b==t0_count)//���ƽ���׼ʱ��һ��
			{
				EX1=0;
				TR0=0;
				ss=0;//P2.6�źŲ��Կ�
			}
	}
	if(flag_check_g == true)
	{
			if(t0_count_g==t0_count)//���ƽ���׼ʱ��һ��
			{
				EX1=0;
				TR0=0;
				ss=0;//P2.6�źŲ��Կ�
			}
	}
		
}

//������
void main(void)
{
		init_9600();
		tes=0;
		ss=0;
		delaynms(1000);
		color_white_balance();//��ƽ��
		delaynms(1000);
		while(1)
		{
			color_check();//��ɫ���
			send_char(0xff);
			delaynms(3000);
			//while(1);
		}
}
