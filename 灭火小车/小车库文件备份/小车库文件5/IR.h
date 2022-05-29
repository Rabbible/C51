//#include<AT89X52.H>
#include<intrins.h>

#define LeftIR       P1_4   //左边红外接收连接到P14
#define RightIR      P3_6   //右边红外接收连接到P36
#define LeftLaunch   P1_5   //左边红外发射连接到P15
#define RightLaunch  P3_3   //右边红外发射连接到P33

int irDetectLeft,irDetectRight;

int IRLaunch(unsigned char IR)
{
 int counter;
 if(IR=='L')
   for(counter=0;counter<1000;counter++)
    {
     LeftLaunch=1;
     _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
     _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
     LeftLaunch=0;
     _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
     _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
    }
  else
    for(counter=0;counter<1000;counter++)//右边发射
    {
      RightLaunch=1;
      _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
      _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
      RightLaunch=0;
      _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
      _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
    }
}

void Launch(void)
{
	IRLaunch('R'); 
	irDetectRight = RightIR;//右边接收
	IRLaunch('L'); 
	irDetectLeft = LeftIR;//左边接收
}
