#include<chaoshengbo.h>
#include<duoji.h>
#include<AD.h>
#define uint unsigned int //宏定义uint 为unsigned int类型
#define  PCF8591 0x90    //PCF8591 地址

// ----   求众数	  -----
uint ZS(uint idata F[10])
{	
	uint idata c[10],d[10],i,j,q;
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

//---  用右边的红外测距走相对直线（需循环嵌套），小车大偏角状态时无用
void RZ(uint *E,uint a)	   		/* a为基准 */
{  	
 	*E=DRZS();		 		/* 此时E为不断微调更新的读数*/
	if(*E<a)				/* 即使0x01范围偏角也比较大，所以不需用中间范围*/
	{
		 R_F(1);
	}
	else if(*E>a)
	{
		 L_F(1);
	}
	else Forward(1,200);
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

//---  用左边的红外测距走相对直线（需循环嵌套），小车大偏角状态时无用
void LZ(uint *E,uint a)	   		/* a为基准 */
{  	
 	*E=DLZS();		 		/* 此时E为不断微调更新的读数*/
	if(*E<a)				/* 即使0x01范围偏角也比较大，所以不需用中间范围*/
	{
		 L_F(1);
	}
	else if(*E>a)
	{
		 F_R(1);
	}
	else F_R(1);
}


 // 沿右墙走循环函数（感应超过x就跳出,单值比较）
 void YRQ(uint x)				/* x是沿墙走跳出循环的距离,突变（超出量程）也会跳出 */
{
 	uint a=0x35,Exit=0x35;
	while((Exit>x) && (a>x))				/*右边近处没墙,跳出循环*/
	{
		a=DRZS();				 	// 直走一段距离感知小车偏移状态
		Forward(20,200);			/** 太短会判断不正确，太长会走过头 */		 
		Exit=DRZS();					
		if((abs(Exit-a))<0x02)			// 小偏状态比较纠正到平行（直走程序）  ------
		{				  /* 0x02可能要调 */
			a=DRZS();
			while((Exit>x) && (a>x))
			{
				if((abs(Exit-a))>=0x04) break;	  /* 突变（超出量程）跳出 */
				else RZ(&Exit,a);
				//if(E<0x2D) break;	
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
		Forward(20,200);			/** 太短会判断不正确，太长会走过头 */			 
		Exit=DLZS();					
		if((abs(Exit-a))<0x02)			// 小偏状态比较纠正到平行（直走程序）  ------
		{				  /* 0x02可能要调 */
			a=DLZS();
			while((Exit>x)&&(a>x))
			{	if((abs(Exit-a))>=0x04) break;
				else LZ(&Exit,a);
				//if(E<0x2D) break;	
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
//		else //if(abs(b-a)>0x10)   /*距离突变跳出循环*/
//		break;
	}
}

// // 沿左墙走循环函数（右边感应范围,以外沿墙、以内就跳出,双值比较）
// void YLQW(uint x,uint r)				/* x、r依次为小、大值 */
//{
// 	uint a=0x35,Exit=0x35;
//	while((DRZS()<x) || (DRZS()>r))				/*右边近处没墙,跳出循环*/
//	{
//		a=DLZS();				 	// 直走一段距离感知小车偏移状态
//		Forward(20,200);			/** 太短会判断不正确，太长会走过头 */			 
//		Exit=DLZS();					
//		if((abs(Exit-a))<0x02)			// 小偏状态比较纠正到平行（直走程序）  ------
//		{				  /* 0x02可能要调 */
//			a=DLZS();
//			while((DRZS()<x) || (DRZS()>r))
//			{
//				if((abs(Exit-a))>=0x04) break;
//				else LZ(&Exit,a);
//				//if(E<0x2D) break;	
//			}
//			break;
//		}
//		else if((abs(Exit-a))>=0x02/*&&abs(b-a)<0x10*/)		/* 大偏状态,改正后进入下一次循环直走检测平行度 */
//		{
//			if(Exit>x)			/* 用Exit检测到的是远处(左边近处的墙走完了)跳出循环 */	/*左边近处有墙*/
//			{
//				if(Exit>a)
//				{
//				 Right(2,200);	   /* PulseCount需要根据F[9]-F[0]差值调 */
//				}
//				else if(Exit<a)			
//				{
//				 Left(2,200);	   /* PulseCount需要根据F[9]-F[0]差值调 */
//				}
//			}
//		
//		}
////		else //if(abs(b-a)>0x10)   /*距离突变跳出循环*/
////		break;
//	}
//}

// 沿右墙走循环函数（超声波距离控制跳出）
 void YRC(uint x)					/* x是超声波感应到前方墙壁跳出循环的距离(用偏大的值) */
{
 	uint a=0x35,Exit=0x35;
	while(CSB()>x)
	{
		a=DRZS();				 	// 直走一段距离感知小车偏移状态
		Forward(20,200);			/** 太短会判断不正确，太长会走过头 */		 
		Exit=DRZS();					
		if(abs(Exit-a)<0x02)			// 小偏状态比较纠正到平行（直走程序）  ------
		{				  /* 0x02可能要调 */
		a=DRZS();
		while(CSB()>x)
			{
				RZ(&Exit,a);
				//if(E<0x2D) break;	
			}
		}
		else if(abs(Exit-a)>=0x02/*&&abs(b-a)<0x10*/)		/* 大偏状态,改正后进入下一次循环直走检测平行度 */
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
}

void YLC(uint x)  			
{
	uint a=0x35,Exit=0x35;
 	while(CSB()>x)
	{	
		a=DLZS();				 	// 直走一段距离感知小车偏移状态
		Forward(20,200);			/** 太短会判断不正确，太长会走过头 */			 
		Exit=DLZS();					
		if(abs(Exit-a)<0x02)			// 小偏状态比较纠正到平行（直走程序）  ------
		{				  /* 0x02可能要调 */
		a=DLZS();
		while(CSB()>x)
			{
				LZ(&Exit,a);
			}
		}
		else if(abs(Exit-a)>=0x02/*&&abs(b-a)<0x10*/)		/* 大偏状态,改正后进入下一次循环直走检测平行度 */
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
}