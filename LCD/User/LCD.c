#include "LCD.h"
#include "stm32f4xx_gpio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"


void lcdGPIOInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	/* Enable the GPIO_LED Clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
static void byteSend(u8 data)
{
	u8 i = 0;
	for (i = 0; i < 8; i++)
	{
		_SCK_H;
		if (data & 0x80)
		{
			_SID_H;
		}
		else
		{
			_SID_L;
		}
		vTaskDelay(2);
		_SCK_L;
		data = data << 1;
		vTaskDelay(2);
	}
}
void cmdSend(u8  data)
{
	byteSend(99);
}




