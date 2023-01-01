#include "Myfun.h"
extern volatile int licznik[];
extern volatile int znak_zerowy;
extern const int ROZMIAR;
int main(void)
{
	SysTick_Config(4000000/1000);
	Led_Conf();
	USART_Conf_Interrupt();
	char buf[100];
	while(1)
	{
		for(int i=0;i<ROZMIAR;i++)
		{
			sprintf(buf, "Odebralem %d liter %c\r\n", licznik[i], znak_zerowy+i);
			ComPuts(USART3, buf);
		}
		ComPuts(USART3, "\r\n");
		delay_ms(1000);
	}
}
