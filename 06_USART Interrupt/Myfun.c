#include "Myfun.h"
volatile uint32_t tick = 0;
volatile uint16_t lcdnum = 0;
volatile uint16_t lcdpos = 0;
volatile int h, m, s, ms;
void delay_ms(uint32_t ms)
{
	tick = 0;
	while(tick < ms);
}
void Led_Conf(void)
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN | RCC_AHB2ENR_GPIODEN | RCC_AHB2ENR_GPIOEEN;
	GPIOC->MODER &= ~GPIO_MODER_MODER6 & ~GPIO_MODER_MODER7;
	GPIOC->MODER |= GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0;
	GPIOC->MODER &= ~GPIO_MODER_MODER8 & ~GPIO_MODER_MODER9;
	GPIOC->MODER |= GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0;
	
	GPIOE->MODER &= ~GPIO_MODER_MODER4;
	GPIOE->MODER |= GPIO_MODER_MODER4_0;
	
	GPIOD->MODER &= ~GPIO_MODER_MODER3;
	GPIOD->MODER |= GPIO_MODER_MODER3_0;
	
	GPIOE->MODER &= ~GPIO_MODER_MODER5 & ~GPIO_MODER_MODER6;
	GPIOE->MODER |= GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0;
}
void Led_OnOff(uint8_t num, eLed state)
{
	switch(num)
	{
		case 0:
			if(state == LedOff)	GPIOC->ODR &= ~GPIO_ODR_ODR_6;
			else if(state == LedOn)	GPIOC->ODR |= GPIO_ODR_ODR_6;
			else if(state == LedTog)	GPIOC->ODR ^= GPIO_ODR_ODR_6;
			break;
		case 1:
			if(state == LedOff)	GPIOC->ODR &= ~GPIO_ODR_ODR_7;
			else if(state == LedOn)	GPIOC->ODR |= GPIO_ODR_ODR_7;
			else if(state == LedTog)	GPIOC->ODR ^= GPIO_ODR_ODR_7;
			break;
		case 2:
			if(state == LedOff)	GPIOC->ODR &= ~GPIO_ODR_ODR_8;
			else if(state == LedOn)	GPIOC->ODR |= GPIO_ODR_ODR_8;
			else if(state == LedTog)	GPIOC->ODR ^= GPIO_ODR_ODR_8;
			break;
		case 3:
			if(state == LedOff)	GPIOC->ODR &= ~GPIO_ODR_ODR_9;
			else if(state == LedOn)	GPIOC->ODR |= GPIO_ODR_ODR_9;
			else if(state == LedTog)	GPIOC->ODR ^= GPIO_ODR_ODR_9;
			break;
		case 4:
			if(state == LedOff)				GPIOE->ODR &= ~GPIO_ODR_ODR_4;
			else if(state == LedOn)		GPIOE->ODR |= GPIO_ODR_ODR_4;
			else if(state == LedTog)	GPIOE->ODR ^= GPIO_ODR_ODR_4;
			break;
		case 5:
			if(state == LedOff)				GPIOD->ODR &= ~GPIO_ODR_ODR_3;
			else if(state == LedOn)		GPIOD->ODR |= GPIO_ODR_ODR_3;
			else if(state == LedTog)	GPIOD->ODR ^= GPIO_ODR_ODR_3;
			break;
		case 6:
			if(state == LedOff)				GPIOE->ODR &= ~GPIO_ODR_ODR_5;
			else if(state == LedOn)		GPIOE->ODR |= GPIO_ODR_ODR_5;
			else if(state == LedTog)	GPIOE->ODR ^= GPIO_ODR_ODR_5;
			break;
		case 7:
			if(state == LedOff)				GPIOE->ODR &= ~GPIO_ODR_ODR_6;
			else if(state == LedOn)		GPIOE->ODR |= GPIO_ODR_ODR_6;
			else if(state == LedTog)	GPIOE->ODR ^= GPIO_ODR_ODR_6;
			break;
	}
}
void SysTick_Handler(void)
{
	tick++;
	Lcd7seg_WriteNumber();
	Zegarek();
}
void Joy_Conf(void)
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	GPIOE->MODER &= ~GPIO_MODER_MODER0;
	GPIOE->MODER &= ~GPIO_MODER_MODER1;
	GPIOE->MODER &= ~GPIO_MODER_MODER2;
	GPIOE->MODER &= ~GPIO_MODER_MODER3;
	GPIOE->MODER &= ~GPIO_MODER_MODER15;
}
eJoy Joy_Read(void)
{
	eJoy state = JoyNull;
	if((GPIOE->IDR & GPIO_IDR_ID0) == RESET)	state = Right;
	if((GPIOE->IDR & GPIO_IDR_ID1) == RESET)	state = Left;
	if((GPIOE->IDR & GPIO_IDR_ID2) == RESET)	state = Down;
	if((GPIOE->IDR & GPIO_IDR_ID3) == RESET)	state = Up;
	if((GPIOE->IDR & GPIO_IDR_ID15) == RESET)	state = Center;
	return state;
}
void Lcd7seg_Conf(void)
{
	RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN;
	PWR->CR2 |= PWR_CR2_IOSV;
	
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOGEN;
	
	GPIOB->MODER &= ~GPIO_MODER_MODER2;
	GPIOB->MODER |= GPIO_MODER_MODER2_0;
	GPIOB->MODER &= ~GPIO_MODER_MODER3;
	GPIOB->MODER |= GPIO_MODER_MODER3_0;
	GPIOB->MODER &= ~GPIO_MODER_MODER4;
	GPIOB->MODER |= GPIO_MODER_MODER4_0;
	GPIOB->MODER &= ~GPIO_MODER_MODER5;
	GPIOB->MODER |= GPIO_MODER_MODER5_0;
	
	GPIOG->MODER &= ~GPIO_MODER_MODER0;
	GPIOG->MODER |= GPIO_MODER_MODER0_0;
	GPIOG->MODER &= ~GPIO_MODER_MODER1;
	GPIOG->MODER |= GPIO_MODER_MODER1_0;
	GPIOG->MODER &= ~GPIO_MODER_MODER2;
	GPIOG->MODER |= GPIO_MODER_MODER2_0;
	GPIOG->MODER &= ~GPIO_MODER_MODER3;
	GPIOG->MODER |= GPIO_MODER_MODER3_0;
	GPIOG->MODER &= ~GPIO_MODER_MODER4;
	GPIOG->MODER |= GPIO_MODER_MODER4_0;
	GPIOG->MODER &= ~GPIO_MODER_MODER5;
	GPIOG->MODER |= GPIO_MODER_MODER5_0;
	GPIOG->MODER &= ~GPIO_MODER_MODER6;
	GPIOG->MODER |= GPIO_MODER_MODER6_0;
	GPIOG->MODER &= ~GPIO_MODER_MODER9;
	GPIOG->MODER |= GPIO_MODER_MODER9_0;
}
void Lcd7seg_WriteDigit(uint8_t pos, uint8_t num)
{
	GPIOB->ODR &= ~GPIO_ODR_ODR_2;
	GPIOB->ODR &= ~GPIO_ODR_ODR_3;
	GPIOB->ODR &= ~GPIO_ODR_ODR_4;
	GPIOB->ODR &= ~GPIO_ODR_ODR_5;
	
	GPIOG->ODR &= ~GPIO_ODR_ODR_0;
	GPIOG->ODR &= ~GPIO_ODR_ODR_1;
	GPIOG->ODR &= ~GPIO_ODR_ODR_2;
	GPIOG->ODR &= ~GPIO_ODR_ODR_3;
	GPIOG->ODR &= ~GPIO_ODR_ODR_4;
	GPIOG->ODR &= ~GPIO_ODR_ODR_5;
	GPIOG->ODR &= ~GPIO_ODR_ODR_6;
	GPIOG->ODR &= ~GPIO_ODR_ODR_9;
	
	switch(pos)
	{
		case 0:	GPIOB->ODR |= GPIO_ODR_ODR_5;	break;
		case 1:	GPIOB->ODR |= GPIO_ODR_ODR_4;	break;
		case 2:	GPIOB->ODR |= GPIO_ODR_ODR_3;	break;
		case 3:	GPIOB->ODR |= GPIO_ODR_ODR_2;	break;
		default: break;
	}
	
	switch(num)
	{
		case 0:
			GPIOG->ODR |= GPIO_ODR_ODR_0 | GPIO_ODR_ODR_1 | GPIO_ODR_ODR_2 | 
										GPIO_ODR_ODR_3 | GPIO_ODR_ODR_4 | GPIO_ODR_ODR_5;
			break;
		case 1:
			GPIOG->ODR |= GPIO_ODR_ODR_1 | GPIO_ODR_ODR_2;
			break;
		case 2:
			GPIOG->ODR |= GPIO_ODR_ODR_0 | GPIO_ODR_ODR_1 | GPIO_ODR_ODR_3 |
										GPIO_ODR_ODR_4 | GPIO_ODR_ODR_6;
			break;
		case 3:
			GPIOG->ODR |= GPIO_ODR_ODR_0 | GPIO_ODR_ODR_1 | GPIO_ODR_ODR_2 |
										GPIO_ODR_ODR_3 | GPIO_ODR_ODR_6;
			break;
		case 4:
			GPIOG->ODR |= GPIO_ODR_ODR_1 | GPIO_ODR_ODR_2 | GPIO_ODR_ODR_5 |
										GPIO_ODR_ODR_6;
			break;
		case 5:
			GPIOG->ODR |= GPIO_ODR_ODR_0 | GPIO_ODR_ODR_2 | GPIO_ODR_ODR_3 |
										GPIO_ODR_ODR_5 | GPIO_ODR_ODR_6;
			break;
		case 6:
			GPIOG->ODR |= GPIO_ODR_ODR_0 | GPIO_ODR_ODR_2 | GPIO_ODR_ODR_3 |
										GPIO_ODR_ODR_4 | GPIO_ODR_ODR_5 | GPIO_ODR_ODR_6;
			break;
		case 7:
			GPIOG->ODR |= GPIO_ODR_ODR_0 | GPIO_ODR_ODR_1 | GPIO_ODR_ODR_2;
			break;
		case 8:
			GPIOG->ODR |= GPIO_ODR_ODR_0 | GPIO_ODR_ODR_1 | GPIO_ODR_ODR_2 |
										GPIO_ODR_ODR_3 | GPIO_ODR_ODR_4 | GPIO_ODR_ODR_5 |
										GPIO_ODR_ODR_6;
			break;
		case 9:
			GPIOG->ODR |= GPIO_ODR_ODR_0 | GPIO_ODR_ODR_1 | GPIO_ODR_ODR_2 |
										GPIO_ODR_ODR_3 | GPIO_ODR_ODR_5 | GPIO_ODR_ODR_6;
			break;
	}
}
void Lcd7seg_WriteNumber(void)
{
	uint8_t tab[4];
	tab[0] = (lcdnum % 10)/1;
	tab[1] = (lcdnum % 100)/10;
	tab[2] = (lcdnum % 1000)/100;
	tab[3] = (lcdnum % 10000)/1000;
	
	Lcd7seg_WriteDigit(lcdpos, tab[lcdpos]);
	if(lcdpos++ >= 4)
		lcdpos = 0;
}
void Zegarek(void)
{
	ms++;
	if(ms >= 1000)
	{
		ms = 0;
		s++;
	}
	if(s >= 60)
	{
		s = 0;
		m++;
	}
	if(m >= 60)
	{
		m = 0;
		h++;
	}
	if(h >= 24)
	{
		h = 0;
	}
}
void USART_ConfBasic(void)
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	RCC->APB1ENR1 |= RCC_APB1ENR1_USART3EN;
	RCC->CCIPR |= RCC_CCIPR_USART3SEL_0;
	
	GPIOC->MODER &= ~GPIO_MODER_MODER4 & ~GPIO_MODER_MODER5;
	GPIOC->MODER |= GPIO_MODER_MODER4_1 | GPIO_MODER_MODER5_1;
	GPIOC->PUPDR |= GPIO_PUPDR_PUPDR4_0 | GPIO_PUPDR_PUPDR5_0;
	GPIOC->AFR[0] |= 0x00770000;
	
	USART3->BRR = 	4000000/57600;
  USART3->CR1 |= 	USART_CR1_RE | USART_CR1_TE | USART_CR1_UE;
}
void ComSendChar(USART_TypeDef *USARTx, char c)
{
	while(!(USARTx->ISR & USART_ISR_TXE)){;}
		USARTx->TDR = c;
}
void ComPuts(USART_TypeDef* USARTx, const char* str)
{
	while(*str)
		ComSendChar(USARTx, *str++);
}
void USART_Conf_Interrupt(void)
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	RCC->APB1ENR1 |= RCC_APB1ENR1_USART3EN;
	RCC->CCIPR |= RCC_CCIPR_USART3SEL_0;
	
	GPIOC->MODER &= ~GPIO_MODER_MODER4 & ~GPIO_MODER_MODER5;
	GPIOC->MODER |= GPIO_MODER_MODER4_1 | GPIO_MODER_MODER5_1;
	GPIOC->PUPDR |= GPIO_PUPDR_PUPDR4_0 | GPIO_PUPDR_PUPDR5_0;
	GPIOC->AFR[0] |= 0x00770000;
	
	USART3->BRR = 	4000000/57600;
  USART3->CR1 |= 	USART_CR1_RE | USART_CR1_TE | 
									USART_CR1_UE | USART_CR1_RXNEIE;
	NVIC_EnableIRQ(USART3_IRQn);
}
const int ROZMIAR = 24;
volatile int licznik[ROZMIAR];
volatile int znak_zerowy = 65;
void USART3_IRQHandler(void)
{
	if((USART3->ISR & USART_ISR_RXNE) != RESET)
	{
		char c = USART3->RDR;
		for(int i=0;i<ROZMIAR;i++)
		if(c == znak_zerowy+i)
			licznik[i]++;
	}
}
