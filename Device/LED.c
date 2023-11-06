#include <stdlib.h>
#include <stdint.h>
#include "stm32f10x.h"
#include "LED.h"

#define SPEED GPIO_Speed_50MHz

void LED_Init(GPIO_TypeDef* GPIOx, uint16_t pin) {
	
	// 开启时钟
	if (GPIOx == GPIOA) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	} else if (GPIOx == GPIOB) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	} else if (GPIOx == GPIOC) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	}

	GPIO_InitTypeDef GPIO_InitStructure;
	// 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = pin;
	GPIO_InitStructure.GPIO_Speed = SPEED;
	GPIO_Init(GPIOx, &GPIO_InitStructure);
}

// 低电平点亮小灯
void LED_ON(GPIO_TypeDef* GPIOx, uint16_t pin) {
	GPIO_ResetBits(GPIOx, pin);
}

// 关闭小灯
void LED_OFF(GPIO_TypeDef* GPIOx, uint16_t pin) {
	GPIO_SetBits(GPIOx, pin);
}

// 切换状态
void LED_Switch(GPIO_TypeDef* GPIOx, uint16_t pin) {
	if (GPIO_ReadOutputDataBit(GPIOx, pin) == 1) {
		GPIO_ResetBits(GPIOx, pin);
	} else {
		GPIO_SetBits(GPIOx, pin);
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
	}
}
