#include<reg51.h>
#include<zhixian.h>
#define uint unsigned int

void main()
{  	
	uint x=163;
	T0_INIT();
	INT1_INIT();
	trig = 0;
	YLC(x);
	Right(35,200);
}