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

	while(1)	//Ҫ��while�������ŻῪʼ��ȡ
	{
		FFJF();
		//���ĸ�����
		if((SIG1==0)&&(SIG2==0)) 	//��һ������ǰ����𲢻ؼ�(�������ѭ��)
		{
			Left(7,200);   // 3!    1.
			if((SIG1==0)&&(SIG2==0))
			{
				Right(7,200); // 1!  2.
				FF1J();	 
			}
			else 
			{
				Right(7,200);	// 1!   2.
				FF2J();
			}
		}

		else
		{
			Right(15,200);	// 4!  3.	 
			if((SIG1==0)&&(SIG2==0))
			{
				Right(23,200);	 //  2!  4.
				if((SIG1==0)&&(SIG2==0))
				{
					Left(6,200);  //  5!  5.
					FF3J();
				}
				else
				{
					Left(39,200);  //  1!  7.
					FF2J();
				}
			}
			else
			{
				Right(23,200);	 //  2!  4.
				if((SIG1==0)&&(SIG2==0))
				{
					Left(6,200);  //  5!  5.
					FF3J();
				}
				else
				{
					Right(30,200);  
					//ȥ��һ������
					ThreeFJF();
					while(1) Keep();
				}
			}
		}
		while(1) Keep();			
	}	
}