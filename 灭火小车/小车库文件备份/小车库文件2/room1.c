#include<reg51.h> //������Ƭ���Ĵ����Ķ���ͷ�ļ�
#define uint unsigned int //�궨��uint Ϊunsigned int����
#define uchar unsigned char //�궨��uchar Ϊunsigned char ����
sbit P1_2 = P1^2;//������PWM���ƶ˿�
sbit P1_3 = P1^3;//������PWM���ƶ˿�
//��ʱn΢��
void delay_nus(unsigned int i)  
{ 
  	i=i/10;
  	while(--i);
}   
//��ʱn����
void delay_nms(unsigned int n)  
{ 
  	n=n+1;
  	while(--n)  
  	delay_nus(900);         
}   

//������
void main(void)
{
    uint a,b,c,d,e,f; 
    while(1)
	{
//ǰ��
		for(a=0;a<100;a++)
		{
//��ֹ��׼ʱ��t=1500us�����ڻ�С��1500us��ʹ��Ӧ�˿ڵĳ�������ת����
			P1_3=1;
			delay_nus(1700);
			P1_3=0;
							 
			P1_2=1;
			delay_nus(1300);
			P1_2=0;
			delay_nms(25);
				
		}
//��ת
        for(b=0;b<100;b++)
		{
//��ֹ��׼ʱ��t=1500us�����ڻ�С��1500us��ʹ��Ӧ�˿ڵĳ�������ת����
            P1_3=1;
			delay_nus(1500);
			P1_3=0;
							 
			P1_2=1;
			delay_nus(1300);
			P1_2=0;
			delay_nms(10);
		}
//ǰ��
		for(c=0;c<100;c++)
		{
//��ֹ��׼ʱ��t=1500us�����ڻ�С��1500us��ʹ��Ӧ�˿ڵĳ�������ת����
			P1_3=1;
			delay_nus(1700);
			P1_3=0;
							 
			P1_2=1;
			delay_nus(1300);
			P1_2=0;
			delay_nms(25);
				
		}
//��ת	
		for(d=0;d<100;d++)
		{
//��ֹ��׼ʱ��t=1500us�����ڻ�С��1500us��ʹ��Ӧ�˿ڵĳ�������ת����
            P1_3=1;
			delay_nus(1700);
			P1_3=0;
							 
			P1_2=1;
			delay_nus(1500);
			P1_2=0;
			delay_nms(10);
		}
//ǰ��
		for(e=0;e<100;e++)
		{
//��ֹ��׼ʱ��t=1500us�����ڻ�С��1500us��ʹ��Ӧ�˿ڵĳ�������ת����
			P1_3=1;
			delay_nus(1700);
			P1_3=0;
							 
			P1_2=1;
			delay_nus(1300);
			P1_2=0;
			delay_nms(25);
				
		}
//��ת	
		for(f=0;f<100;f++)
		{
//��ֹ��׼ʱ��t=1500us�����ڻ�С��1500us��ʹ��Ӧ�˿ڵĳ�������ת����
            P1_3=1;
			delay_nus(1700);
			P1_3=0;
							 
			P1_2=1;
			delay_nus(1500);
			P1_2=0;
			delay_nms(10);
		}			
	}
}	  	 