#include<reg51.h>    //������Ƭ���Ĵ�����ͷ�ļ�
#include<AD.h>

void main()
{
	Initial_com();
	while(1)
	{
	/********AD-DA����*************/
	ISendByte(PCF8591,0x41);	/*0x41�ǵ�һ��AD����ӿڣ�0x40�ǵڶ���*/ 
	D[0]=IRcvByte(PCF8591);
	ISendByte(PCF8591,0x40);	
	D[1]=IRcvByte(PCF8591);	
	 
	  /********���½�AD��ֵͨ�����ڷ��ͳ�ȥ*************/	
	send_char(D[1]);
	}
}