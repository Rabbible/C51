#include<duoji.h>
#include<AD.h>
#define uint unsigned int //宏定义uint 为unsigned int类型
#define uchar unsigned char
#define  PCF8591 0x90    //PCF8591 地址

// ----   求绝对值	  -----
int abs(int t)
{
	if(t>0)
	return t;
	else
	return -t;
}

float Average(uchar idata G[10])
{
	uint i;
	float idata F[10];
	for(i=0;i<10;i++)
	{
	 	F[i]=(float)G[i];	   //十六进制数组转换成float数组
	}
	for(i=0;i<9;i++)			//去突变值，剩下的求平均
	{
		if(abs(F[i+1]-F[i])>5)
		{
			if(F[i+1]>F[i])
			F[i+1]=F[i];
		}
		else F[i+1]=(F[i+1]+F[i])/2.000;
	}
	return F[9];
}

//--   右边红外测距传感器读取十个数据并返回众数值	  --
float DRPJ()				
{	uint i;
	uchar idata G[10]={0x2D};
	for(i=0;i<10;i++)
	{
		ISendByte(PCF8591,0x40);
		G[i]=IRcvByte(PCF8591);
	}
	return Average(G);
}

//--   左边红外测距传感器读取十个数据并返回众数值	  --
float DLPJ()				
{	uint i;
	uchar idata G[10]={0x2D};
	for(i=0;i<10;i++)
	{
		ISendByte(PCF8591,0x41);
		G[i]=IRcvByte(PCF8591);
	}
	return Average(G);
}

//---  用右边的红外测距走相对直线（需循环嵌套），小车大偏角状态时无用
void RZ(float *E,float a)	   		/* a为基准 */
{  	
 	*E=DRPJ();		 		/* 此时E为不断微调更新的读数*/
	if(*E<a)				/* 即使0x01范围偏角也比较大，所以不需用中间范围*/
	{
		 R_F(2);
	}
	else if(*E>a)
	{
		 L_F(2);
	}
	else Forward(2,300);
}

//---  用左边的红外测距走相对直线（需循环嵌套），小车大偏角状态时无用
void LZ(float *E,float a)	   		/* a为基准 */
{  	
 	*E=DLPJ();		 		/* 此时E为不断微调更新的读数*/
	if(*E<a)				/* 即使0x01范围偏角也比较大，所以不需用中间范围*/
	{
		 L_F(2);
	}
	else if(*E>a)
	{
		 R_F(2);
	}
	else Forward(2,300);
}

// 沿右墙走循环函数（感应超过x就跳出,单值比较）
void YRQ(float x)				/* x是沿墙走跳出循环的距离,突变（超出量程）也会跳出 */
{
 	float a=53.0,Exit=53.0;
	while((Exit>x) && (a>x))				/*右边近处没墙,跳出循环*/
	{
		a=DRPJ();				 	// 直走一段距离感知小车偏移状态
		Forward(15,300);			/** 太短会判断不正确，太长会走过头 */		 
		Exit=DRPJ();					
		if((abs(Exit-a))<=1.0)			// 小偏状态比较纠正到平行（直走程序）  ------
		{				  /* 0x02可能要调 */
			a=DRPJ();
			while((Exit>x) && (a>x))
			{
				if((abs(Exit-a))>9) 	break;	  	/* 突变（超出量程）跳出 */
				else RZ(&Exit,a);	
			}
			break;
		}
		else if((abs(Exit-a))>1.0/*&&abs(Exit-a)<0x05*/)		/* 大偏状态,改正后进入下一次循环直走检测平行度 */
		{
			if(Exit>x)			/* 用Exit检测到的是远处(右边近处的墙走完了)跳出循环 */	/*右边近处有墙*/
			{
				if(Exit>a)
				{
					Left(1,200);	   /* PulseCount需要根据F[9]-F[0]差值调 */
				}
				else if(Exit<a)			
				{
					Right(1,200);	   /* PulseCount需要根据F[9]-F[0]差值调 */
				}
			}
			  
		}
	}
}