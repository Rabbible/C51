#include<reg51.h>
#include<zhixian.h>
#define uint unsigned int //宏定义uint 为unsigned int类型

void main()
{	uint a;
	Initial_com();
	while(1)
	{
		a=DLZS();
		send_char(a);
	}
//	float m;
//	Initial_com();
//	m=DRPJ();
//	send_char(m);

//	uint i;
//	uchar idata G[10]={0x2D};
//	float idata F[10]={0};
//	for(i=0;i<10;i++)
//	{
//		ISendByte(PCF8591,0x40);
//		G[i]=IRcvByte(PCF8591);
//	}
//	NBZ(G,&F);	   //转float
//	return Average(F);

//	YRQ(45.0);
}