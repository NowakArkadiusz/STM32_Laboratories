#include "Myfun.h"
#include "HD44780.h"
extern uint16_t tab2[];
int main(void)
{
	SysTick_Config(4000000/1000);
	Led_Conf();
	ADC_Conf_Dma_2Channels();
	LCD_Init();
	while(1)
	{
		LCD_Clear();
		char buf[16];
		sprintf(buf, "ADC= %d", tab2[0]);
		LCD_WriteText(buf);
		LCD_GoTo(0,1);
		sprintf(buf, "TEMP= %d", tab2[1]);
		LCD_WriteText(buf);
		
		Led_OnOff(0, LedTog);
		delay_ms(100);
	}
}
