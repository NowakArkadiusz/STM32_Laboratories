#include <stm32l4xx.h>
#include <stm32l496xx.h>
volatile uint32_t tick = 0;
uint32_t time = 120;
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
	
	GPIOD->MODER &= ~GPIO_MODER_MODER3;
	GPIOD->MODER |= GPIO_MODER_MODER3_0;
	
	GPIOE->MODER &= ~GPIO_MODER_MODER4 & ~GPIO_MODER_MODER5 & ~GPIO_MODER_MODER6;
	GPIOE->MODER |= GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0;
}
int main()
{
	SysTick_Config(4000000 / 1000);
	Led_Conf();
	while(1)
	{
		GPIOC->ODR |= GPIO_ODR_ODR_6;
		delay_ms(time);
		GPIOC->ODR &= ~GPIO_ODR_ODR_6;
		delay_ms(time);
	}
}
void SysTick_Handler(void)
{
	tick++;
}
