//#include<AT89X52.h>

int P1_5state(void)//获取P1_5的状态,右胡须
{
	return (P1&0x20)?1:0;
}
int P2_3state(void)//获取P2_3的状态,左胡须
{
	return (P2&0x08)?1:0;
}

/*int main(void)
{
		uart_Init();
		printf("Program Run!\n");
	
		while(1)
		{
			if((P1_5state()==0)&&(P2_3state()==0))//两边均检查到,后退再左拐
			{
                printf("first %c and then %c\n", Backward.dir,LeftTurn.dir);
				Back_Ward();
				Left_Turn();
				Left_Turn();
			}
			else if(P1_5state()==0)//右边检查到
			{
                printf("first %c and then %c\n",Backward.dir,LeftTurn.dir);
				Back_Ward();
				Left_Turn();
			}
			else if(P2_3state()==0)//左边检查到
			{
                printf("first %c and then %c\n",Backward.dir,RightTurn.dir);
				Back_Ward();
				Right_Turn();
			}
			else
			{
                printf("Direction: %c\n",Forward.dir);
    			For_Ward();
			} 
		}
}*/
