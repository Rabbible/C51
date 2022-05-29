#include<reg51.h>
#include<AD.h>
#define uint unsigned int //宏定义uint 为unsigned int类型

// ----   求众数	  -----
uint ZS(uint idata F[10])
{	
	uint idata c[10], idata d[10],i,j,q;
	for(i=0;i<9;i++) 	//数组数据从小到大排列
		for(j=0;j<9-i;j++)    
		{
		 	if(F[j]>F[j+1])
			{
			 	q=F[j];
				F[j]=F[j+1];
				F[j+1]=q;
			}
		}

	d[0]=F[0],c[0]=1,j=0;  //求众数
	for(i=0;i<9;i++)
	{
		if(F[i+1]!=F[i])
		{
			j++;
			c[j]=1;
			d[j]=F[i+1];
		}
		else c[j]++;
	}
	for(i=0;i<=j;i++)
	{
	for(q=0;i<=j;q++)
		{
		if(c[i]<c[q])
		break;
		else if(q==j)
		return d[i];
		}
	}	
}

// ----   求绝对值	  -----
int abs(int t)
{
	if(t>0)
	return t;
	else
	return -t;
}

//--   右边红外测距传感器读取十个数据并返回众数值	  --
uint DRZS()				
{	uint i,idata F[10]={0};
	for(i=0;i<10;i++)
	{
		ISendByte(PCF8591,0x40);
		F[i]=IRcvByte(PCF8591);
	}
	return ZS(F);
}

//--   左边红外测距传感器读取十个数据并返回众数值	  --
uint DLZS()				
{	uint i,idata F[10]={0};
	for(i=0;i<10;i++)
	{
		ISendByte(PCF8591,0x41);
		F[i]=IRcvByte(PCF8591);
	}
	return ZS(F);
}

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