#include "Myfun.h"
int main(void)
{
	SysTick_Config(4000000/1000);
	Led_Conf();
	Joy_Conf();
	USART_ConfBasic();
	int licznik = 0;
	while(1)
	{
		if((USART3->ISR & USART_ISR_RXNE) != RESET)
		{
			char data = USART3->RDR;
			if(data == 'A')
			{
				licznik ++;
				char buf[100];
				sprintf(buf, "Odebralem %d literek A \r\n", licznik);
				ComPuts(USART3, buf);
			}
		}
	}
}
