#include<reg51.h>    //������Ƭ���Ĵ�����ͷ�ļ�
#include<duoji.h>
#include<chaoshengbo.h>

void main()
{  
	init_9600();   /*�������Ķ���*/
	T0_INIT();
	INT1_INIT();
	trig = 0;
	
	while(1)
	{  				 
	if (CSB()<=122)		   /* ������ */
	Right(1,200);			
	else Forward(1,200);	 /*  ��ת90��  */		 
   	}

	

}