#include <at89x52.h>
#include <string.h>

#define LCM_RW  	P2_1 //��������
#define LCM_RS  	P2_2
#define LCM_E   	P2_0
#define LCM_Data  	P0
#define Busy    	0x80 //���ڼ��LCM״̬���е�Busy��ʶ

void Delay_5Ms(void)//5ms��ʱ
{
    unsigned int TempCyc = 5552;
    while(TempCyc--);
}

void Delay_400Ms(void)//400ms��ʱ
{
    unsigned char TempCycA = 5;
    unsigned int TempCycB;
    while(TempCycA--)
    {
       TempCycB=7269;
       while(TempCycB--);
    };
}

/*=====================================
    ��������Read_Status_LCM() 
    ��  �ܣ� æ��⺯��  
======================================*/
void Read_Status_LCM(void)
{
  unsigned char read=0;

  LCM_RW = 1;
  LCM_RS = 0;
  LCM_E = 1;
  LCM_Data = 0xff;
  do
  {
   read = LCM_Data;
  }
while(read & Busy);

  LCM_E = 0;
}
/*-------------------------------------------
      ��������Write_Data_LCM ( ) 
      ��  �ܣ� ��LCD 1602д���� 
--------------------------------------------*/
void Write_Data_LCM(unsigned char WDLCM)
{
    Read_Status_LCM(); //���æ
    
    LCM_RS = 1;
    LCM_RW = 0;
    
    LCM_Data &= 0x0f;
    LCM_Data |= WDLCM&0xf0;
    LCM_E = 1; //�������ٶ�̫�߿���������С����ʱ
    LCM_E = 1; //��ʱ
    LCM_E = 0;

    WDLCM = WDLCM<<4;
    LCM_Data &= 0x0f;
    LCM_Data |= WDLCM&0xf0;
    LCM_E = 1; 
    LCM_E = 1; //��ʱ
    LCM_E = 0;
}
/*-------------------------------------------
      ��������Write_Command_ LCM ( ) 
      ��  �ܣ� ��LCD 1602дָ�� 
--------------------------------------------*/
void Write_Command_LCM(unsigned char WCLCM,BuysC) //BuysCΪ0ʱ����æ���
{
    if (BuysC)
        Read_Status_LCM(); //������Ҫ���æ
    
    LCM_RS = 0;
    LCM_RW = 0;

    LCM_Data &= 0x0f;
    LCM_Data |= WCLCM&0xf0;//�������λ 
    LCM_E = 1;
    LCM_E = 1;
    LCM_E = 0;
 
    WCLCM = WCLCM<<4;   //�������λ
    LCM_Data &= 0x0f;
    LCM_Data |= WCLCM&0xf0;
    LCM_E = 1;
    LCM_E = 1;
    LCM_E = 0;
}
/*-------------------------------------------
      ��������LCM_Init() 
      ��  �ܣ� ��LCD 1602��ʼ�� 
--------------------------------------------*/
void LCM_Init(void) //LCM��ʼ��
{
    LCM_Data = 0;
    Write_Command_LCM(0x28,0); //������ʾģʽ���ã������æ�ź�
    Delay_5Ms(); 
    Write_Command_LCM(0x28,0);
    Delay_5Ms(); 
    Write_Command_LCM(0x28,0);
    Delay_5Ms(); 
    Write_Command_LCM(0x28,1); //��ʾģʽ����,��ʼҪ��ÿ�μ��æ�ź�
    Write_Command_LCM(0x08,1); //�ر���ʾ
    Write_Command_LCM(0x01,1); //��ʾ����
    Write_Command_LCM(0x06,1); //��ʾ����ƶ�����
    Write_Command_LCM(0x0C,1); //��ʾ�����������
}
/*-------------------------------------------
      ��������Set_xy_LCM ()
      ��  �ܣ��趨��ʾ����λ��
--------------------------------------------*/
void Set_xy_LCM(unsigned char x, unsigned char y)
{
    unsigned char address;
    if( x == 0 )
       address = 0x80+y;
    else
       address = 0xc0+y;
    Write_Command_LCM(address,1);
}
/*-------------------------------------------
      ��������Display_List_Char()
      ��  �ܣ���ָ��λ����ʾһ���ַ�   
--------------------------------------------*/
void Display_List_Char(unsigned char x, unsigned char y, unsigned char *s)
{
    unsigned char length,j;
	length=strlen(s);
	Set_xy_LCM(x,y);
    /*while(*s)
     {
        LCM_Data = *s;
        Write_Data_LCM(*s);
        s++;
      }*/
	
	for(j=0;j<length;j++)
	{
		LCM_Data = *s;
        Write_Data_LCM(*s);
        s++;
	}
}

