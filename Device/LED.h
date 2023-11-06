#ifndef __LED_H
#define __LED_H
#include <stdint.h>
#include "stm32f10x.h"

void LED_Init(GPIO_TypeDef* GPIOx, uint16_t pin);
void LED_ON(GPIO_TypeDef* GPIOx, uint16_t pin);
void LED_OFF(GPIO_TypeDef* GPIOx, uint16_t pin);
void LED_Switch(GPIO_TypeDef* GPIOx, uint16_t pin);

#endif
