#include <reg51.H>
#include<duoji.h>
#include<fan.h>
#define uint unsigned int //�궨��uint Ϊunsigned int����
#define uchar unsigned char //�궨��uchar Ϊunsigned char ����

void main()
{
	 SIG=1;			//���õ����ֹ
	 SIG1=1;
	 SIG2=1;
	while(1)
	{
		if((SIG1==0)&&(SIG2==0))//���һ��洫������ⶼ��⵽����		
		 {
		 	SIG =0;  		 //���ÿ��ƶ˿�Ϊ�͵�ƽ�������ת����
		 	Left(25,200);
		 }
		else
		SIG=1;			    
	}

}
