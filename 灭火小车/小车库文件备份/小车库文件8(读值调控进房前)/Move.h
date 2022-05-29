struct
{
	char *dir;
	int pulseLeft;
	int pulseRight;
	int counter;
}Forward={"Forward",1700,1300},
 Backward={"Backward",1300,1700,65},
 LeftTurn={"Turn Left",1300,1300,26},
 RightTurn={"Turn Right",1700,1700,26};

void For_Ward(void)
{
   	P1_3=1;
	delay_nus(Forward.pulseLeft);
    P1_3=0;
	P1_2=1;
	delay_nus(Forward.pulseRight);
	P1_2=0;
	delay_nms(20);
}
void Left_Turn(void)
{
    int i;
    for(i=1;i<= LeftTurn.counter;i++)
	{
		P1_3=1;
		delay_nus(LeftTurn.pulseLeft);
         P1_3=0;
		P1_2=1;
		delay_nus(LeftTurn.pulseRight);
		P1_2=0;
		delay_nms(20);
	}
}
void Right_Turn(void)
{
   	int i;
    for(i=1;i<=RightTurn.counter;i++)
	{
		P1_3=1;
		delay_nus(RightTurn.pulseLeft);
        P1_3=0;
		P1_2=1;
		delay_nus(RightTurn.pulseRight);
		P1_2=0;
		delay_nms(20);
	}
}
void Back_Ward(void)
{
    int i;
    for(i=1;i<= Backward.counter;i++)
	{
		P1_3=1;
		delay_nus(Backward.pulseLeft);
         P1_3=0;
		P1_2=1;
		delay_nus(Backward.pulseRight);
		P1_2=0;
		delay_nms(20);
	}
}