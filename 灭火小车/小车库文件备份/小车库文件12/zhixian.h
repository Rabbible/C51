#include<chaoshengbo.h>
#include<duoji.h>
#include<AD.h>
#define uint unsigned int //宏定义uint 为unsigned int类型
#define uchar unsigned char
#define  PCF8591 0x90    //PCF8591 地址


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

//---  用右边的红外测距走相对直线（需循环嵌套），小车大偏角状态时无用
void RZ(uint *E,uint a)	   		/* a为基准 */
{  	
 	*E=DRZS();		 		/* 此时E为不断微调更新的读数*/
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
void LZ(uint *E,uint a)	   		/* a为基准 */
{  	
 	*E=DLZS();		 		/* 此时E为不断微调更新的读数*/
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

void RJ()		//大多接沿墙跳出循环后,函数完成后接沿墙走
{
	HR();
	Stop();
	Stop();
	Forward(60,300);
	Stop();
}

void LJ()		//大多接沿墙跳出循环后
{
	HL();
	Stop();
	Stop();
	Forward(50,300);
	Stop();
}

void ZC(int x)		//走直线达到超声波测距跳出循环
{
	while(CSB()>x)
	Forward(2,300);
}

void RC(int x)		//走直线达到超声波测距跳出循环
{
	while(CSB()>x)
	F_R(2);
}

void LTZ(uint x,uchar Q,uint z)  			 	/* x为识别时走的脉冲数 */
{
	uint a,Exit;
	a=DLZS();				 	// 直走一段距离感知小车偏移状态
	if(Q=='F')
	Forward(x,300);			/** 太短会判断不正确，太长会走过头 */
	else if(Q=='R') F_R(x);			 
	Exit=DLZS();
	if((abs(Exit-a))<0x02)			// 小偏状态比较纠正到平行（直走程序）  ------
	{				  /* 0x02可能要调 */
		LZ(&Exit,a);
	}					
	if((abs(Exit-a))>=0x02 /*&& (abs(Exit-a)<0x05)*/)		/* 大偏状态,改正后进入下一次循环直走检测平行度 */
	{

		if(Exit>a)
		{
			Right(z,200);	   /* PulseCount需要根据F[9]-F[0]差值调 */
		}
		else if(Exit<a)			
		{
			Left(z,200);	   /* PulseCount需要根据F[9]-F[0]差值调 */
		}

	}
}

void RTZ(uint x,uchar Q, uint z)	/* x为识别时走的脉冲数,Q为识别时走的是直线或有偏向，Z是大调的脉冲数 */
{
 	uint a,Exit;
	a=DRZS();				 	// 直走一段距离感知小车偏移状态
	if(Q=='F')
	Forward(x,300);			/** 太短会判断不正确，太长会走过头 */
	else if(Q=='R') F_R(x);		 
	Exit=DRZS();
	if((abs(Exit-a))<0x02)			// 小偏状态比较纠正到平行（直走程序）  ------
	{				  /* 0x02可能要调 */
		RZ(&Exit,a);
	}					
	if((abs(Exit-a))>=0x02/*&&abs(Exit-a)<0x05*/)		/* 大偏状态,改正后进入下一次循环直走检测平行度 */
	{
		
		if(Exit>a)
		{
			Left(z,200);	   /* PulseCount需要根据F[9]-F[0]差值调 */
		}
		else if(Exit<a)			
		{
			Right(z,200);	   /* PulseCount需要根据F[9]-F[0]差值调 */
		}
	
	}
}


// 沿右墙走循环函数（感应超过x就跳出,单值比较）
void YRQ(uint x)				/* x是沿墙走跳出循环的距离,突变（超出量程）也会跳出 */
{
 	uint a=0x35,Exit=0x35;
	while((Exit>x) && (a>x))				/*右边近处没墙,跳出循环*/
	{
		a=DRZS();				 	// 直走一段距离感知小车偏移状态
		Forward(15,300);			/** 太短会判断不正确，太长会走过头 */		 
		Exit=DRZS();					
		if((abs(Exit-a))<0x02)			// 小偏状态比较纠正到平行（直走程序）  ------
		{				  /* 0x02可能要调 */
			a=DRZS();
			while((Exit>x) && (a>x))
			{
				if((abs(Exit-a))>0x09) 	break;	  	/* 突变（超出量程）跳出 */
				else RZ(&Exit,a);
				//if(E<45) break;	
			}
			break;
		}
		else if((abs(Exit-a))>=0x02/*&&abs(Exit-a)<0x05*/)		/* 大偏状态,改正后进入下一次循环直走检测平行度 */
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
//		else if(abs(Exit-a)>0x10)	 /*? 为什么出现跳动大 ?*/
//		break;
	}
}

void YLQ(uint x)  			 /* x是沿墙走跳出循环的距离,突变也会跳出 */
{
	uint a=0x35,Exit=0x35;
 	while((Exit>x)&&(a>x))
	{	
		a=DLZS();				 	// 直走一段距离感知小车偏移状态
		F_R(13);			/** 太短会判断不正确，太长会走过头 */			 
		Exit=DLZS();					
		if((abs(Exit-a))<0x02)			// 小偏状态比较纠正到平行（直走程序）
		{				  /* 0x02可能要调 */
			a=DLZS();
			while((Exit>x) && (a>x))
			{	
				if((abs(Exit-a))>0x12) break;		/* 突变（超出量程）跳出 */
				else LZ(&Exit,a);
				//if(E<45) break;	
			}
			break;
		}
		else if((abs(Exit-a))>=0x02 /*&& (abs(Exit-a)<0x05)*/)		/* 大偏状态,改正后进入下一次循环直走检测平行度 */
		{
			if(Exit>x)			/* 用Exit检测到的是远处(左边近处的墙走完了)跳出循环 */	/*左边近处有墙*/
			{
				if(Exit>a)
				{
				 Right(1,200);	   /* PulseCount需要根据F[9]-F[0]差值调 */
				}
				else if(Exit<a)			
				{
				 Left(1,200);	   /* PulseCount需要根据F[9]-F[0]差值调 */
				}
			}
		
		}
//		else //if(abs(b-a)>0x10)   /*距离突变跳出循环*/
//		break;
	}
}

// 沿右墙走循环函数（超声波距离控制跳出）
void YRC(uint x,int B)					/* x是超声波感应到前方墙壁跳出循环的距离(用偏大的值) */
{
 	uint a=0x35,Exit=0x35;
	while(Exit>x)				/*右边近处没墙,跳出循环*/
	{
		if(CSB()<=B) break;
		else
		{
			a=DRZS();				 	// 直走一段距离感知小车偏移状态
			Forward(12,300);			/** 太短会判断不正确，太长会走过头 */		 
			Exit=DRZS();					
			if((abs(Exit-a))<0x02)			// 小偏状态比较纠正到平行（直走程序）  ------
			{				  /* 0x02可能要调 */
				a=DRZS();
				while(Exit>x)
				{
					RZ(&Exit,a);
					if(CSB()<=B) break;
					else continue;	
				}
				break;
			}
			else if((abs(Exit-a))>=0x02/*&&abs(Exit-a)<0x10*/)		/* 大偏状态,改正后进入下一次循环直走检测平行度 */
			{
				if(Exit>x)			/* 用Exit检测到的是远处(右边近处的墙走完了)跳出循环 */	/*右边近处有墙*/
				{
					if(Exit>a)
					{
					 Left(2,200);	   /* PulseCount需要根据F[9]-F[0]差值调 */
					}
					else if(Exit<a)			
					{
					 Right(2,200);	   /* PulseCount需要根据F[9]-F[0]差值调 */
					}
				}
			}
//			else if(abs(Exit-a)>0x10)	 /*? 为什么出现跳动大 ?*/
//			break;
		}
	}
}

void YLC(uint x,int B)  			
{
	uint a=0x35,Exit=0x35;
 	while(Exit>x)
	{	
		if(CSB()<=B) break;
		else
		{
			a=DLZS();				 	// 直走一段距离感知小车偏移状态
			F_R(15);			/** 太短会判断不正确，太长会走过头 */			 
			Exit=DLZS();					
			if((abs(Exit-a))<0x02)			// 小偏状态比较纠正到平行（直走程序）
			{				  /* 0x02可能要调 */
				a=DLZS();
				while(Exit>x)
				{	LZ(&Exit,a);
					if(CSB()<=B) break;	
				}
				break;
			}
			else if((abs(Exit-a))>=0x02/*&&abs(b-a)<0x10*/)		/* 大偏状态,改正后进入下一次循环直走检测平行度 */
			{
				if(Exit>x)			/* 用Exit检测到的是远处(左边近处的墙走完了)跳出循环 */	/*左边近处有墙*/
				{
					if(Exit>a)
					{
					 Right(2,200);	   /* PulseCount需要根据F[9]-F[0]差值调 */
					}
					else if(Exit<a)			
					{
					 Left(2,200);	   /* PulseCount需要根据F[9]-F[0]差值调 */
					}
				}
			
			}
//			else //if(abs(b-a)>0x10)   /*距离突变跳出循环*/
//			break;
		}
	}
}

void YLC2(uint x,int B)  			
{
	uint a=0x35,Exit=0x35;
 	while(Exit>x)
	{	
		if(CSB()<=B) break;
		else
		{
			a=DLZS();				 	// 直走一段距离感知小车偏移状态
			Forward(15,300);			/** 太短会判断不正确，太长会走过头 */			 
			Exit=DLZS();					
			if((abs(Exit-a))<0x02)			// 小偏状态比较纠正到平行（直走程序）
			{				  /* 0x02可能要调 */
				a=DLZS();
				while(Exit>x)
				{	LZ(&Exit,a);
					if(CSB()<=B) break;	
				}
				break;
			}
			else if((abs(Exit-a))>=0x02/*&&abs(b-a)<0x10*/)		/* 大偏状态,改正后进入下一次循环直走检测平行度 */
			{
				if(Exit>x)			/* 用Exit检测到的是远处(左边近处的墙走完了)跳出循环 */	/*左边近处有墙*/
				{
					if(Exit>a)
					{
					 Right(2,200);	   /* PulseCount需要根据F[9]-F[0]差值调 */
					}
					else if(Exit<a)			
					{
					 Left(2,200);	   /* PulseCount需要根据F[9]-F[0]差值调 */
					}
				}
			
			}
//			else //if(abs(b-a)>0x10)   /*距离突变跳出循环*/
//			break;
		}
	}
}