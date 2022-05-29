#include<reg51.h>    //������Ƭ���Ĵ�����ͷ�ļ�
#include <I2C.H>
#define  PCF8591 0x90    //PCF8591 ��ַ
#define uint unsigned int //�궨��uint Ϊunsigned int����
#define uchar unsigned char //�궨��uchar Ϊunsigned char ����


// ��������
unsigned char AD_CHANNEL;
unsigned long xdata  LedOut[8];
unsigned int  D[32];
sbit P2_0 = P2^0;
sbit P2_1 = P2^1;
sbit P2_2 = P2^2;
sbit P2_3 = P2^3;
sbit P1_2 = P1^2;//������PWM���ƶ˿�
sbit P1_3 = P1^3;//������PWM���ƶ˿�
int PulseCount; int Velocity;

unsigned char date;

uchar code table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,
                        0xf8,0x80,0x90};


  // �������� 

void display();
void delay(uchar i);
bit DACconversion(unsigned char sla,unsigned char c,  unsigned char Val);
bit ISendByte(unsigned char sla,unsigned char c);
unsigned char IRcvByte(unsigned char sla);
void Initial_com(void);
void delay_nus(unsigned int i);
void delay_nms(unsigned int n);
void Forward(PulseCount,Velocity);
void Right(PulseCount,Velocity);
void Left(PulseCount,Velocity);
void Backward(PulseCount,Velocity);
//******************************************************************/
void main()
{  

	Initial_com();
	while(1)
	{  

	/********����AD-DA����*************/  
	
	    switch(AD_CHANNEL)
		{
			case 0: ISendByte(PCF8591,0x41);
			     D[0]=IRcvByte(PCF8591);  //ADC0 ģ��ת��1      ��������
				 break;  
			
			case 1: ISendByte(PCF8591,0x42);
			     D[1]=IRcvByte(PCF8591);  //ADC1  ģ��ת��2	  ��������
				 break;  
			
			case 2: ISendByte(PCF8591,0x43);
			     D[2]=IRcvByte(PCF8591);  //ADC2	ģ��ת��3	   ����
				 break;  
			
			case 3: ISendByte(PCF8591,0x40);
			     D[3]=IRcvByte(PCF8591);  //ADC3   ģ��ת��4	   �ɵ�0-5v
				 break;  
			
			case 4: DACconversion(PCF8591,0x40, D[4]); //DAC	  ��ģת��
			     break;
		 
		}




//    	D[4]=D[3];  //��ģ������������ź� ͨ����ģת�����
			
	   if(++AD_CHANNEL>4) AD_CHANNEL=0;
	
//	   /********���½�AD��ֵͨ�����ڷ��ͳ�ȥ*************/
//	 delay(200);	
//	 SBUF=D[0];		   	   
//	 delay(200);		  
//	 SBUF=D[1];			   
//	 delay(200);	
//	 SBUF=D[2];
//	 delay(200);
//	 SBUF=D[3];
//	 delay(200);
//	 if(RI)
//	{
//		date=SBUF;    //��Ƭ������
//		SBUF=date;    //��Ƭ������
//		RI=0;
//	}
		if(D[0]>0x25)	/*  D[0]�ұߺ��⴫��������   */
		{
			if(D[0]<0x4B && D[0]>0x30)
				{ 	Right(5,200);
					delay_nms(500);
					Forward(7,200);
					delay_nms(500);
					Left(5,200);
					delay_nms(500);
				}
			else if(D[0]<0x30)
				{ 	Right(10,200);
					delay_nms(1000);
					Forward(7,200);
					delay_nms(500);
					Left(11,200);
					delay_nms(1000);
				}				  
			else if(D[0]>0x56 && D[0]<0x60 ) /*&& D[1]>(D[0]+0x10)*/
					{  	Left(5,200);
						delay_nms(500);
						Forward(7,200);
						delay_nms(500);
						Right(5,200);
						delay_nms(500);
					}
			else if(D[0]>0x56 && D[0]<0x60 ) /*&& D[1]>(D[0]+0x10)*/
					{  	Left(10,200);
						delay_nms(1000);
						Forward(7,200);
						delay_nms(500);
						Right(10,200);
						delay_nms(1000);
					}
			else Forward(1,200);
		}
		
		
//		if( D[1]>0x30 && D[1]<0x51 )	 	/*  D[1]��߱ߺ��⴫��������   */
//		{
//				{ 	Left_Turn();
//					Forward();
//					Right_Turn();
//				}				 
//		}
//		else Forward();
		// ******   ���  ************	 
   }
}


void delay(uchar i)
{
  uchar j,k; 
  for(j=i;j>0;j--)
    for(k=125;k>0;k--);
}

/*******************************************************************
DAC �任, ת������               
*******************************************************************/
bit DACconversion(unsigned char sla,unsigned char c,  unsigned char Val)
{
   Start_I2c();              //��������
   SendByte(sla);            //����������ַ
   if(ack==0)return(0);
   SendByte(c);              //���Ϳ����ֽ�
   if(ack==0)return(0);
   SendByte(Val);            //����DAC����ֵ  
   if(ack==0)return(0);
   Stop_I2c();               //��������
   return(1);
}

/*******************************************************************
ADC�����ֽ�[����]���ݺ���               
*******************************************************************/
bit ISendByte(unsigned char sla,unsigned char c)
{
   Start_I2c();              //��������
   SendByte(sla);            //����������ַ
   if(ack==0)return(0);
   SendByte(c);              //��������
   if(ack==0)return(0);
   Stop_I2c();               //��������
   return(1);
}

/*******************************************************************
ADC���ֽ����ݺ���               
*******************************************************************/
unsigned char IRcvByte(unsigned char sla)
{  unsigned char c;

   Start_I2c();          //��������
   SendByte(sla+1);      //����������ַ
   if(ack==0)return(0);
   c=RcvByte();          //��ȡ����0

   Ack_I2c(1);           //���ͷǾʹ�λ
   Stop_I2c();           //��������
   return(c);
}


//*****���ڳ�ʼ������***********

//******************************
void Initial_com(void)
{
 EA=1;        //�����ж�
 ES=1;        //�������ж�
 ET1=1;        //����ʱ��T1���ж�
 TMOD=0x20;   //��ʱ��T1���ڷ�ʽ2�жϲ���������
 PCON=0x00;   //SMOD=0
 SCON=0x50;   // ��ʽ1 �ɶ�ʱ������
 TH1=0xfd;    //����������Ϊ9600
 TL1=0xfd;
 TR1=1;       //����ʱ��T1���п���λ

}

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
//***************************************************************************//
