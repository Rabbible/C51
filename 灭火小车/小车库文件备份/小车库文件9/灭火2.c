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
	SIG4=1;		//�Ҷ�
 	SIG5=1;

	while(1)	//Ҫ��while�������ŻῪʼ��ȡ
	{

		if((SIG1==0)&&(SIG2==0)) 	//��һ������ǰ����𲢻ؼ�(�������ѭ��)
		OF1J();				 
		else
		{
			Left(8,200);
			if((SIG1==0)&&(SIG2==0))
			{ 	
				Right(9,200);			/* 7 �� */
				OF1J();
			}
			else
			{	//�ڶ�������
				Right(17,200);				/* 7 �� + 19 �� */
				if((SIG1==0)&&(SIG2==0)) 	
				{
					Left(10,200);
					OF2J();
				}
				else
				{	//������������
					Right(25,200);				/* 20 �� */
					if((SIG1==0)&&(SIG2==0))    
					OF3J();
					else //��û��⵽���棬������һ������
					Right(33,200);
					
					while(1);
				}
			}
		}
		while(1) Keep();			
	}	
}