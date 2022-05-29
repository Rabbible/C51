#include<stdio.h>
uint ZS(void)
{

	unsigned int i,j,q;
	unsigned int D[5],c[5],d[5];
	//for(i=0;i<5;i++)
	//scanf("%d",&D[i]);
	for(i=0;i<4;i++) 	//数组数据从小到大排列
		for(j=0;j<4-i;j++)    
		{
		 	if(D[j]>D[j+1])
			{
			 	q=D[j];
				D[j]=D[j+1];
				D[j+1]=q;
			}
		}

	d[0]=D[0],c[0]=1,j=0;  //求众数
	for(i=0;i<4;i++)
	{
		if(D[i+1]!=D[i])
		{
			j++;
			c[j]=1;
			d[j]=D[i+1];
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