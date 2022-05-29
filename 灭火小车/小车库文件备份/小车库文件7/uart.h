/*----------------------------------------------------------------
                     8051�����ж���������
--------------------------------------------------------------*/
#include <AT89X52.h>
#include <stdio.h>
#define XTAL 11059200
#define baudrate 9600

#define OLEN 8	      //���з��ͻ�������С
unsigned char ostart;  //���ͻ�������ʼ����
unsigned char oend;      //���ͻ�������������
char idata outbuf[OLEN]; //���ͻ������洢����

#define ILEN 8	        //���н��ջ�������С
unsigned char istart;   //���ջ�������ʼ����
unsigned char iend;     //���ջ�������������
char idata inbuf[ILEN]; //���ջ���洢����

bit bdata sendfull;    //���ͻ���������־
bit bdata sendactive;  //������Ч��־
/*�����жϷ������*/
static void com_isr(void) interrupt 4 using 1        //�����ж�
{ 
   //-------------���������ж�--------------
  char c;
  if(RI)			     //�����ж�
  { 				     
    c=SBUF;	    //���ַ�
    RI=0;	    //������ж������־
    if(istart+ILEN!=iend)
    { 
      inbuf[iend++&(ILEN-1)]=c;   //��������������
    }
  }

  //-------------���������ж�--------------
  if(TI)
  { 
    TI=0;	 //�巢���жϱ�־
    if(ostart!=oend)
    {  
       SBUF=outbuf[ostart++&(OLEN-1)];//���ͻ����������ַ�
       sendfull=0;		      //���û���������־λ
     }
     else
     { 
        sendactive=0; 	          //���÷�����Ч
     }
   }
}   

//PUTBUF: д�ַ���SBUF���ͻ�����
void putbuf(char c)
{ 
    if(!sendfull)	 //��������������ͷ���
    {
      if(!sendactive)   
      { 
          sendactive=1; //ֱ�ӷ���һ���ַ�
          SBUF=c;       //д��SBUF����������
      }
      else 
      { 
        ES=0;	      //��ʱ���пڹر��ж�
        outbuf[oend++&(OLEN-1)]=c;  //���ͻ����������ַ�
        if(((oend^ostart)&(OLEN-1))==0)  
         { sendfull=1;}    //���û���������־
         ES=1;	      //�򿪴��п��ж�
      }
    }
}

//putchar:�жϿ���putchar����
//�滻��׼�⺯��putchar����
//printf����ʹ��putchar���һ���ַ�
char putchar (char c)
{ 
  if (c=='\n')	         //�����µ���
    {
      while(sendfull);   //�ȴ����ͻ�������
      putbuf(0x0D);      //��������LFǰ����CR
    }
  while(sendfull); 
  putbuf(c);
  return(c);
}

//_getkey:�жϿ���_getkey����
//�滻��׼�⺯��_getkey����
//getchar��gets����ʹ��_getkey
char _getkey(void)
{ 
  char c;
  while(iend==istart)      //�жϽ��ջ�������ʼ�����Ƿ���ڽ��ջ�������������
  {;}
  ES=0;
  c=inbuf[istart++&(ILEN-1)];
  ES=1;
  return(c);
}

/* ��ʼ�����пں�UART�����ʺ���*/
void com_initialize(void)
{ 
  istart=0;
  iend=0;
  ostart=0;
  oend=0;
  sendactive=0;
  sendfull=0;

  TMOD |=0x20;   //���ö�ʱ��T/C1�����ڷ�ʽ2,��ʱ1�������Զ�����ģʽ
  SCON=0x50;     //���ô��пڹ�����ʽ1��SCON��ʽ |M0|M1|M2|REN|TB8|RB8|TI|RI
  TH1=0xfd;      //������9600
  TL1=0xfd;
  TR1=1;         //������ʱ��
  ES=1;	        //�����п��ж�
}    

void uart_Init()
{ 
  com_initialize();
  EA=1;	        //CPU�����ж�
}

  
