#ifndef _MYFUN
#define _MYFUN
#include <stm32l4xx.h>
#include <stm32l496xx.h>
typedef enum{LedOff = 0, LedOn = 1, LedTog = 2}eLed;
typedef enum{JoyNull = 0, Up = 1, Down = 2, Left = 3, Right = 4, Center = 5}eJoy;

void delay_ms(uint32_t ms);
void Led_Conf(void);
void Led_OnOff(uint8_t num, eLed state);
void Joy_Conf(void);
eJoy Joy_Read(void);
void Lcd7seg_Conf(void);
void Lcd7seg_WriteDigit(uint8_t pos, uint8_t num);
void Lcd7seg_WriteNumber(void);

#endif
