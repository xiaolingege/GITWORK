#include "LCD.h"
#include "stm32f4xx_gpio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include <stdio.h>

void lcdGPIOConfig(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
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
// 		_SCK_H;
		if (data & 0x80)
		{
			_SID_H;
		}
		else
		{
			_SID_L;
		}
		_SCK_H;
		vTaskDelay(1);
		_SCK_L;
		vTaskDelay(1);
		data = data << 1;
	}
}
static void cmdSend(u8  cmd)
{
	_CS_H;
	byteSend(0XF8);
	byteSend(cmd & 0xF0);
	byteSend((cmd & 0x0F) << 4);
	_CS_L;
}
static void dataSend(u8 data)
{
	_CS_H;
	byteSend(0xFA);
	byteSend(data & 0xF0);
	byteSend((data & 0x0F) << 4);
	_CS_L;
}
void lcdShowNumber(u8 x_add, float number)
{
	char arr[5] = {'\0'};
	char *ptr = arr;
	if(number < 0)
	{
		number = 0;
	}
	else
	{
		while(number > 100)
		{
			number -= 100;
		}
	}
	sprintf(arr," %.1f", number);
	cmdSend(x_add);
	if(number < 10)
	{
		dataSend(' ');
	}
	while (*ptr != '\0')
	{
		dataSend(*ptr);
		++ptr;
	}
}

void lcdShowString(u8 x_add, u8 *ptr)
{
	cmdSend(x_add);
	vTaskDelay(1);
	while (*ptr != '\0')
	{
		dataSend(*ptr);
		++ptr;
	}
}

void lcdInit(void)
{
	_CS_L;
	cmdSend(0x30);
		cmdSend(0x0c);
	cmdSend(0x01);
		cmdSend(0x02);
	cmdSend(0x80);
}




