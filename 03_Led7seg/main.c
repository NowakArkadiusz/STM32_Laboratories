#include "Myfun.h"
extern uint16_t lcdnum;
int main()
{
	SysTick_Config(4000000/1000);
	Led_Conf();
	Joy_Conf();
	Lcd7seg_Conf();
	while(1)
	{
		for(int i=0;i<10000;i++)
		{
			lcdnum = i;
			delay_ms(5);
		}
	}
}
