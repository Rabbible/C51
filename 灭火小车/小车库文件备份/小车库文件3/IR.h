//#include<AT89X52.H>
#include<intrins.h>

#define LeftIR       P1_4   //��ߺ���������ӵ�P14
#define RightIR      P3_6   //�ұߺ���������ӵ�P36
#define LeftLaunch   P1_5   //��ߺ��ⷢ�����ӵ�P15
#define RightLaunch  P3_3   //�ұߺ��ⷢ�����ӵ�P33

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
    for(counter=0;counter<1000;counter++)//�ұ߷���
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
	irDetectRight = RightIR;//�ұ߽���
	IRLaunch('L'); 
	irDetectLeft = LeftIR;//��߽���
}
