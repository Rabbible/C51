//风扇、灰度要在主函数先定义初始状态！
//	 SIG=1;			//风扇电机静止
//	 SIG1=1;		//火焰传感器
//	 SIG2=1;
//	 SIG4=1;		//灰度
// 	 SIG5=1;
sbit SIG = P1^0; //定义信号控制引脚
sbit SIG1 = P0^0; //定义信号1接收引脚
sbit SIG2 = P0^1; //定义信号2接收引脚
sbit SIG4=P1^4; //定义信号接收引脚
sbit SIG5=P1^5; //定义信号接收引脚
