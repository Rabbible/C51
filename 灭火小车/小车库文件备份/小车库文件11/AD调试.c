#include<reg51.h>
#include<AD.h>
#define uint unsigned int //�궨��uint Ϊunsigned int����

// ----   ������	  -----
uint ZS(uint idata F[10])
{	
	uint idata c[10], idata d[10],i,j,q;
	for(i=0;i<9;i++) 	//�������ݴ�С��������
		for(j=0;j<9-i;j++)    
		{
		 	if(F[j]>F[j+1])
			{
			 	q=F[j];
				F[j]=F[j+1];
				F[j+1]=q;
			}
		}

	d[0]=F[0],c[0]=1,j=0;  //������
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

// ----   �����ֵ	  -----
int abs(int t)
{
	if(t>0)
	return t;
	else
	return -t;
}

//--   �ұߺ����ഫ������ȡʮ�����ݲ���������ֵ	  --
uint DRZS()				
{	uint i,idata F[10]={0};
	for(i=0;i<10;i++)
	{
		ISendByte(PCF8591,0x40);
		F[i]=IRcvByte(PCF8591);
	}
	return ZS(F);
}

//--   ��ߺ����ഫ������ȡʮ�����ݲ���������ֵ	  --
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
//	NBZ(G,&F);	   //תfloat
//	return Average(F);

//	YRQ(45.0);
}