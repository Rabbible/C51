#include<reg51.h>    //������Ƭ���Ĵ�����ͷ�ļ�
#include<zhixian.h>
#include<miehuo.h>
#define uint unsigned int //�궨��uint Ϊunsigned int����

void main()
{ 	//��ʼ��
	T0_INIT();
	INT1_INIT();
	trig = 0;
	SIG=1;			//���ȵ����ֹ
	SIG1=1;		//���洫����
	SIG2=1;

   while(1)
   {
   		if((SIG1==0)&&(SIG2==0)) 	//��һ������ǰ����𲢻ؼ�(�������ѭ��)
		TF1J();				 
		else
		{
			Left(5,200);
			if((SIG1==0)&&(SIG2==0))
			{ 	
				Right(5,200);			/* 7 �� */
				TF1J();
			}
			else
			{	//�ڶ�������
				Right(11,200);				/* 7 �� + 19 �� */
				if((SIG1==0)&&(SIG2==0)) 	
				{
					Left(10,200);
					TF2J();
				}
				else
				{	//������������
					Right(25,200);				/* 20 �� */
					if((SIG1==0)&&(SIG2==0))    
					TF3J();
					else //��û��⵽���棬������һ������
					Right(33,200);
					//������һ������
					while(1);
				}
			}
		}
	
		while(1) Keep();			
	}		
}