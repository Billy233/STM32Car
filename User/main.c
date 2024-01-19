#include "stm32f10x.h"
#include "LED.h"
#include "Serial.h"
#include "oled.h"

//test stm32Car
int main(void) {
	
	LED_Init(GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
	LED_OFF(GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);

	Serial_Init();
	//作业1，2是13-50行代码
	OLED_Init();
	OLED_ColorTurn(0);
	OLED_DisplayTurn(1);
	
	// 发数据包开灯
	uint8_t cmdPacket[3] = {0x20, 0x50, 0xAB};
	
	while(1) {
		if (getRxFlag() == 1) {
			uint8_t *p = getRxPacket();
			if (pivot == 3) {
				for (int i = 0; i < 3; i++) {
					if (p[i] != cmdPacket[i]) {
						OLED_Clear();
						OLED_ShowString(1, 1, "ERROR", 16, 1);
						OLED_Refresh();
						break;
					}
					if (i == 2) {
						LED_Switch(GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
						if (GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_12) == RESET) {
							OLED_Clear();
							OLED_ShowString(1, 1, "LED on", 16, 1);
							OLED_Refresh();
						} else {
							OLED_Clear();
							OLED_ShowString(1, 1, "LED off", 16, 1);
							OLED_Refresh();
						}
					}
				}
			} else {
				OLED_Clear();
				OLED_ShowString(1, 1, "ERROR", 16, 1);
				OLED_Refresh();
			}
		}
	}

//作业3在这
	// 接受并返回数据包
	while(1) {
		if (getRxFlag() == 1) {
			Serial_SendPacket(getRxPacket());
		}
	}
	
}
