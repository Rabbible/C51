#include <at89x52.h>
#include <string.h>

#define LCM_RW  	P2_1 //定义引脚
#define LCM_RS  	P2_2
#define LCM_E   	P2_0
#define LCM_Data  	P0
#define Busy    	0x80 //用于检测LCM状态字中的Busy标识

void Delay_5Ms(void)//5ms延时
{
    unsigned int TempCyc = 5552;
    while(TempCyc--);
}

void Delay_400Ms(void)//400ms延时
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
    函数名：Read_Status_LCM() 
    功  能： 忙检测函数  
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
      函数名：Write_Data_LCM ( ) 
      功  能： 对LCD 1602写数据 
--------------------------------------------*/
void Write_Data_LCM(unsigned char WDLCM)
{
    Read_Status_LCM(); //检测忙
    
    LCM_RS = 1;
    LCM_RW = 0;
    
    LCM_Data &= 0x0f;
    LCM_Data |= WDLCM&0xf0;
    LCM_E = 1; //若晶振速度太高可以在这后加小的延时
    LCM_E = 1; //延时
    LCM_E = 0;

    WDLCM = WDLCM<<4;
    LCM_Data &= 0x0f;
    LCM_Data |= WDLCM&0xf0;
    LCM_E = 1; 
    LCM_E = 1; //延时
    LCM_E = 0;
}
/*-------------------------------------------
      函数名：Write_Command_ LCM ( ) 
      功  能： 对LCD 1602写指令 
--------------------------------------------*/
void Write_Command_LCM(unsigned char WCLCM,BuysC) //BuysC为0时忽略忙检测
{
    if (BuysC)
        Read_Status_LCM(); //根据需要检测忙
    
    LCM_RS = 0;
    LCM_RW = 0;

    LCM_Data &= 0x0f;
    LCM_Data |= WCLCM&0xf0;//传输高四位 
    LCM_E = 1;
    LCM_E = 1;
    LCM_E = 0;
 
    WCLCM = WCLCM<<4;   //传输低四位
    LCM_Data &= 0x0f;
    LCM_Data |= WCLCM&0xf0;
    LCM_E = 1;
    LCM_E = 1;
    LCM_E = 0;
}
/*-------------------------------------------
      函数名：LCM_Init() 
      功  能： 对LCD 1602初始化 
--------------------------------------------*/
void LCM_Init(void) //LCM初始化
{
    LCM_Data = 0;
    Write_Command_LCM(0x28,0); //三次显示模式设置，不检测忙信号
    Delay_5Ms(); 
    Write_Command_LCM(0x28,0);
    Delay_5Ms(); 
    Write_Command_LCM(0x28,0);
    Delay_5Ms(); 
    Write_Command_LCM(0x28,1); //显示模式设置,开始要求每次检测忙信号
    Write_Command_LCM(0x08,1); //关闭显示
    Write_Command_LCM(0x01,1); //显示清屏
    Write_Command_LCM(0x06,1); //显示光标移动设置
    Write_Command_LCM(0x0C,1); //显示开及光标设置
}
/*-------------------------------------------
      函数名：Set_xy_LCM ()
      功  能：设定显示坐标位置
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
      函数名：Display_List_Char()
      功  能：按指定位置显示一串字符   
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

