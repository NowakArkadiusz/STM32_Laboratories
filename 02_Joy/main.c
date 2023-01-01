#include "Myfun.h"
int main(void)
{
	int x = 4;
	Led_Conf();
	Joy_Conf();
	SysTick_Config(4000000 / 1000);
	while(1)
	{
		if(Joy_Read() == Right)		x--;
		if(Joy_Read() == Left)		x++;
		
		if(x > 7)									x=7;
		if(x < 0)									x=0;
		
		for(int i=0;i<8;i++)
		{
			if(i == x)
				Led_OnOff(x, LedTog);
			else
				Led_OnOff(i, LedOff);
		}
		delay_ms(200);
	}
}
