#include<REGX51.H>
sbit SIG1=P1^4; //定义信号接收引脚
sbit SIG2=P1^5; //定义信号接收引脚

void main()
{
	SIG1=1;
	SIG2=1;
	while(1)
	{
		if(SIG1==1)//QTI传感器1检测到黑色边界
		{
			//当QTI传感器1检测到黑色边界时对应的的操作
		    }
			else if(SIG1==0) //QTI传感器1检测到白色边界
{
//当QTI传感器1检测到白色边界时对应的的操作
}

if(SIG2==1)//QTI传感器2检测到黑色边界
		{
			//当QTI传感器2检测到黑色边界时对应的的操作
		    }
			else if(SIG2==0) //QTI传感器2检测到白色边界
{
//当QTI传感器2检测到白色边界时对应的的操作
}

	  }
}
