#define uint unsigned int //宏定义uint 为unsigned int类型

sbit P1_2 = P1^2;//定义舵机PWM控制端口
sbit P1_3 = P1^3;//定义舵机PWM控制端口
//***   延时与舵机驱动  ********************
void delay_nus(unsigned int i)  //延时:i>=12 ,i的最小延时单12 us
{ 
  i=i/10;
  while(--i);
}   

void delay_nms(unsigned int n)  //延时n ms
{ 
  n=n+1;
  while(--n)  
  delay_nus(900);         //延时 1ms,同时进行补偿
}

void Forward(uint PulseCount,uint Velocity)//定义向前函数，带脉冲计数参数PulseCount和脉冲宽度参数Velocity
{
    int i;
    for(i=1;i<= PulseCount;i++)//for循环控制运行时间
	{
		P1_3=1;
		delay_nus(1500+ Velocity);
        P1_3=0;
		P1_2=1;
		delay_nus(1460- Velocity);
		P1_2=0;
		delay_nms(20);
	}
}
void Right(uint PulseCount,uint Velocity) //定义右转函数，带脉冲计数参数PulseCount和脉冲宽度参数Velocity
{   
    int i;
    for(i=1;i<= PulseCount;i++)//for循环控制运行时间
	{
		P1_3=1;
		delay_nus(1509-Velocity);
        P1_3=0;
		P1_2=1;
		delay_nus(1500-Velocity);
		P1_2=0;
		delay_nms(20);
	}
}

void Left(uint PulseCount,uint Velocity) //定义右转函数，带脉冲计数参数PulseCount和脉冲宽度参数Velocity
{
    int i;
    for(i=1;i<= PulseCount;i++)//for循环控制运行时间
	{
		P1_3=1;
		delay_nus(1500+Velocity);
        P1_3=0;
		P1_2=1;
		delay_nus(1493+Velocity);
		P1_2=0;
		delay_nms(20);
	}
}

void Backward(uint PulseCount,uint Velocity)//定义向后函数，带脉冲计数参数PulseCount和脉冲宽度参数Velocity
{
    int i;
    for(i=1;i<= PulseCount;i++)//for循环控制运行时间
	{
		P1_3=1;
		delay_nus(1500-Velocity);
        P1_3=0;
		P1_2=1;
		delay_nus(1500+ Velocity);
		P1_2=0;
		delay_nms(20);
	}
}

void R_F(uint PulseCount)//定义向右前方行走调整函数，带脉冲计数参数PulseCount
{
    int i;
    for(i=1;i<= PulseCount;i++)//for循环控制运行时间
	{
		P1_3=1;
		delay_nus(1700);	/* 速度范围需要调控 */
        P1_3=0;
		P1_2=1;
		delay_nus(1280);
		P1_2=0;
		delay_nms(20);
	}
}

void R_F2(uint PulseCount)//程度很大
{
    int i;
    for(i=1;i<= PulseCount;i++)//for循环控制运行时间
	{
		P1_3=1;
		delay_nus(1700);	/* 速度范围需要调控 */
        P1_3=0;
		P1_2=1;
		delay_nus(1200);
		P1_2=0;
		delay_nms(20);
	}
}

void L_F(uint PulseCount)//定义向左前方行走调整函数，带脉冲计数参数PulseCount
{
    int i;
    for(i=1;i<= PulseCount;i++)//for循环控制运行时间
	{
		P1_3=1;
		delay_nus(1740);
        P1_3=0;
		P1_2=1;
		delay_nus(1300);	   /* 速度范围需要调控 */
		P1_2=0;
		delay_nms(20);
	}
}

void Keep()  /*静止*/
{
	{
        P1_3=0;
		P1_2=0;
		delay_nms(20);
	}
}

void Stop()//消除舵机继续行走的惯性 函数
{
	P1_3=1;
	delay_nus(1500);
    P1_3=0;
	P1_2=1;
	delay_nus(1500);
	P1_2=0;
	delay_nms(20);
}

void F_R(uint PulseCount)//定义向前方微右行走调整函数，带脉冲计数参数PulseCount
{
    int i;
    for(i=1;i<= PulseCount;i++)//for循环控制运行时间
	{
		P1_3=1;
		delay_nus(1700);	/* 速度范围需要调控 */
        P1_3=0;
		P1_2=1;
		delay_nus(1290);
		P1_2=0;
		delay_nms(20);
	}
}
//
//void F_L(uint PulseCount)//定义向前方微左行走调整函数，带脉冲计数参数PulseCount
//{
//    int i;
//    for(i=1;i<= PulseCount;i++)//for循环控制运行时间
//	{
//		P1_3=1;
//		delay_nus(1740);
//        P1_3=0;
//		P1_2=1;
//		delay_nus(1300);	   /* 速度范围需要调控 */
//		P1_2=0;
//		delay_nms(20);
//	}
//}

void Left2(uint PulseCount,uint Velocity) //灭火时用
{
    int i;
    for(i=1;i<= PulseCount;i++)//for循环控制运行时间
	{
		P1_3=1;
		delay_nus(1500+Velocity);
        P1_3=0;
		P1_2=1;
		delay_nus(1525+Velocity);
		P1_2=0;
		delay_nms(20);
	}
}

void Right2(uint PulseCount,uint Velocity) //灭火时用
{
    int i;
    for(i=1;i<= PulseCount;i++)//for循环控制运行时间
	{
		P1_3=1;
		delay_nus(1510-Velocity);
        P1_3=0;
		P1_2=1;
		delay_nus(1505-Velocity);
		P1_2=0;
		delay_nms(20);
	}
}

void HR()//定义弧度直角向右函数
{
    int i;
    for(i=1;i<=121;i++)//for循环控制运行时间
	{
		P1_3=1;
		delay_nus(1605);
        P1_3=0;
		P1_2=1;
		delay_nus(1300);
		P1_2=0;
		delay_nms(20);
	}
}

void HL()//定义弧度直角向左函数
{
    int i;
    for(i=1;i<=140;i++)//for循环控制运行时间	146
	{
		P1_3=1;
		delay_nus(1700);
        P1_3=0;
		P1_2=1;
		delay_nus(1401);
		P1_2=0;
		delay_nms(20);
	}
}