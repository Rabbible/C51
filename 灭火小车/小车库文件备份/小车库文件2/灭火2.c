#include<reg51.h>    //������Ƭ���Ĵ�����ͷ�ļ�
#include<zhixian.h>
#include<miehuo.h>
#define uint unsigned int //�궨��uint Ϊunsigned int����

void main()
{ 
	if((SIG1==0)&&(SIG2==0)) 	//��һ������ǰ����𲢻ؼ�(�������ѭ��)
	OF1J();					
	while(1);
//	Right(11,200);				/* 19 �� */
//	if((SIG1==0)&&(SIG2==0)) 	
//	2F2J();					
//
//	Right(11,200);				/* 20 �� */
//	if((SIG1==0)&&(SIG2==0)) 	
//	3F3J();					
//	
//	Right(33,200);
//	YRC(x);			/* 15 ! */
//	Left(33,200);	//��������෴��
//	YRQ(0x28);
//	Forward(48,200); /* 16 !ȷ�� */
//	Right(33,200);
//	//���ڶ�������

}