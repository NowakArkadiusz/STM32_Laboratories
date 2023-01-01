#include "Myfun.h"
volatile uint32_t tick = 0;
void delay_ms(uint32_t ms)
{
	tick=0;
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
