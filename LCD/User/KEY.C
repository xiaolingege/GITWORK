#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#define _KEY_GET_DELAY 0x0fl

void keyGPIOConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

unsigned char keyValueGet(void)
{
	if (_KEY1)//KEY1按下
	{
		vTaskDelay(100);
		if (_KEY1)
		{
			return _KEY1_VALUE;
		}
	}
	else
		if (_KEY2)//KEY2按下
		{
			vTaskDelay(100);
			if (_KEY2)
			{
				return _KEY2_VALUE;
			}
		}
		else
			if (_KEY3)//KEY3按下
			{
				vTaskDelay(100);
				if (_KEY3)
				{
					return _KEY3_VALUE;
				}
			}
			else
				if (_KEY4)//KEY4按下
				{
					vTaskDelay(100);
					if (_KEY4)
					{
						return _KEY4_VALUE;
					}
				}
				else	//无键按下
				{
					return 0;
				}
	return 0;
}

