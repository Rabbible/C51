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

void Forward(PulseCount,Velocity)//定义向前函数，带脉冲计数参数PulseCount和脉冲宽度参数Velocity
{
    int i;
    for(i=1;i<= PulseCount;i++)//for循环控制运行时间
	{
		P1_3=1;
		delay_nus(1500+ Velocity);
        P1_3=0;
		P1_2=1;
		delay_nus(1518- Velocity);
		P1_2=0;
		delay_nms(20);
	}
}
void Right(PulseCount,Velocity) //定义右转函数，带脉冲计数参数PulseCount和脉冲宽度参数Velocity
{   
    int i;
    for(i=1;i<= PulseCount;i++)//for循环控制运行时间
	{
		P1_3=1;
		delay_nus(1518-Velocity);
        P1_3=0;
		P1_2=1;
		delay_nus(1500-Velocity);
		P1_2=0;
		delay_nms(20);
	}
}
void Left(PulseCount,Velocity) //定义右转函数，带脉冲计数参数PulseCount和脉冲宽度参数Velocity
{
    int i;
    for(i=1;i<= PulseCount;i++)//for循环控制运行时间
	{
		P1_3=1;
		delay_nus(1500+Velocity);
        P1_3=0;
		P1_2=1;
		delay_nus(1482+Velocity);
		P1_2=0;
		delay_nms(20);
	}
}
void Backward(PulseCount,Velocity)//定义向后函数，带脉冲计数参数PulseCount和脉冲宽度参数Velocity
{
    int i;
    for(i=1;i<= PulseCount;i++)//for循环控制运行时间
	{
		P1_3=1;
		delay_nus(1500-Velocity);
        P1_3=0;
		P1_2=1;
		delay_nus(1482+ Velocity);
		P1_2=0;
		delay_nms(20);
	}
}

void R_F(PulseCount)//定义向右前方行走调整函数，带脉冲计数参数PulseCount和脉冲宽度参数Velocity
{
    int i;
    for(i=1;i<= PulseCount;i++)//for循环控制运行时间
	{
		P1_3=1;
		delay_nus(1693);	/* 速度范围需要调控 */
        P1_3=0;
		P1_2=1;
		delay_nus(1300);
		P1_2=0;
		delay_nms(20);
	}
}

void L_F(PulseCount)//定义向左前方行走调整函数，带脉冲计数参数PulseCount和脉冲宽度参数Velocity
{
    int i;
    for(i=1;i<= PulseCount;i++)//for循环控制运行时间
	{
		P1_3=1;
		delay_nus(1700);
        P1_3=0;
		P1_2=1;
		delay_nus(1330);	   /* 速度范围需要调控 */
		P1_2=0;
		delay_nms(20);
	}
}

void Keep(void)  /*静止*/
{
	{
        P1_3=0;
		P1_2=0;
		delay_nms(20);
	}
}