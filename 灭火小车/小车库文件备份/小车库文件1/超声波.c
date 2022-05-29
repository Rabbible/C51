#include<reg51.h>    //包含单片机寄存器的头文件
#include<duoji.h>
#include<chaoshengbo.h>

void main()
{  
	init_9600();   /*超声波的定义*/
	T0_INIT();
	INT1_INIT();
	trig = 0;
	
	while(1)
	{  				 
	if (CSB()<=122)		   /* 超声波 */
	Right(1,200);			
	else Forward(1,200);	 /*  右转90°  */		 
   	}

	

}