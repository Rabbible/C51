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
   		YRQ(0x2E);
   		TwoFJF();
   		if((SIG1==0)&&(SIG2==0)) 	//��һ������ǰ����𲢻ؼ�(�������ѭ��)
		ThreeF1J();				 
		else
		{
			Left(7,200);
			if((SIG1==0)&&(SIG2==0))
			{ 	
				Right(6,200);			/* 7 �� */
				TwoF1J();
			}
			else
			{	
				while(1)
				{
					//�ڶ�������
					for(i=0;i<30;i++)
					{
						
						Right(1,200);				/* 7 �� + 19 �� */
						if((SIG1==0)&&(SIG2==0)) 	
						{
							Left(15,200);
							TwoF2J();
						}
						
					}
					for(i=0;i<16;i++)
					{	
	
						//������������
						Right(1,200);
						if((SIG1==0)&&(SIG2==0)) 
						{   
							Right(13-i,200);
							Left(1,200);
							TwoF3J();
						}
						
					}
						
					Right(28,200);
					//������һ������
					while(1) Keep();
				}
			}
			break;
		}
		break;			
	}
		
}