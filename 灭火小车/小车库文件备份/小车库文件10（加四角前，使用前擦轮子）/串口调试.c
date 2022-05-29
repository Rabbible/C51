#include<uart.h>//包含头文件uart.h
int main(void)
{
	int i;//定义变量i
	uart_Init();//串口初始化
	i = 36*29;//i=7乘11
	printf("What's 36 X 29 ?\n");//打印What's 7 X 11?
	printf("The fucking answer is : %d\n\n",i);//打印i的结果
	while(1);//程序等待
}