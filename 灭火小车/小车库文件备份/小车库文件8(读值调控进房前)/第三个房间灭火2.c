#include<reg51.h>    //������Ƭ���Ĵ�����ͷ�ļ�
#include<zhixian.h>
#include<miehuo.h>
#define uint unsigned int //�궨��uint Ϊunsigned int����

void main()
{
	uint i;
 	//��ʼ��
	T0_INIT();
	INT1_INIT();
	trig = 0;
	SIG=1;			//���ȵ����ֹ
	SIG1=1;		//���洫����
	SIG2=1;

   while(1)
   {
   		if((SIG1==0)&&(SIG2==0)) 	//��һ������ǰ����𲢻ؼ�(�������ѭ��)
		ThreeF1J();				 
		else
		{
			Left(5,200);
			if((SIG1==0)&&(SIG2==0))
			{ 	
				Right(5,200);			/* 7 �� */
				ThreeF1J();
			}
			else
			{	//�ڶ�������
				for(i=0;i<18;i++)
				{
					Right(1,200);				/* 7 �� + 19 �� */
				
					if((SIG1==0)&&(SIG2==0)) 	
					{
						Left(10,200);
						ThreeF2J();
					}
				}
				for(i=0;i<25;i++)
				{	//������������
					Right(1,200);
					if((SIG1==0)&&(SIG2==0)) 
					{   
						Right(24-i,200);
						ThreeF3J();
					}
				}
					
				Right(28,200);
				//������һ������
				while(1);
				
				
			}
		}			
	}		
}