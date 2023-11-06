#include "stm32f10x.h"
#include "Key.h"
#include "Delay.h"
#include <stdlib.h>

void Key_Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	// 下拉输入模式
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

int toggled(void) {
	
	// PB15 高电平 按下按键
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15) == 1) {
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15) == 1){
			// 等待按键释放
		}
		Delay_ms(20);
		return 1;
	}
	return 0;
}
