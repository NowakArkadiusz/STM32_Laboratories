#include "Myfun.h"
#include "HD44780.h"
extern volatile int h, m, s, ms;
int main(void)
{
	SysTick_Config(4000000/1000);
	Led_Conf();
	Joy_Conf();
	LCD_Init();
	while(1)
	{
		LCD_Clear();
		Lcd_WriteTime(h, m, s, ms);
		delay_ms(100);
	}
}
