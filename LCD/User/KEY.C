/***********************************************************************
文件名称：KEY.C
功    能：按键配置
编写时间：2013.4.25
编 写 人：
注    意：
***********************************************************************/
#include "main.h"

#define _KEY_GET_DELAY 0x18l

void keyGPIOInit(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	/********************按键输入***************************/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

/***********************************************************************
函数名称：Key_Value(void)
功    能：返回按键的值
输入参数：
输出参数：按键的值,,无键按下返回0
编写时间：2013.4.25
编 写 人：
注    意：key1 ：1,
		  key2 ：2,
		  key3 ：3,
		  key4 ：4,
		  无键按下时返回 0
***********************************************************************/
unsigned char keyValueGet(void)
{
	if (_KEY1)//KEY1按下
	{
		keyDelay(_KEY_GET_DELAY);//延时消抖
		if (_KEY1)
		{
			ledBlinkTimeSet(0x1ffffff);
			return _KEY1_VALUE;
		}
	}
	else
		if (_KEY2)//KEY2按下
		{
			keyDelay(_KEY_GET_DELAY);//延时消抖
			if (_KEY2)
			{
				ledBlinkTimeSet(0x2ffffff);

				return _KEY2_VALUE;
			}
		}
		else
			if (_KEY3)//KEY3按下
			{
				keyDelay(_KEY_GET_DELAY);//延时消抖
				if (_KEY3)
				{
					ledBlinkTimeSet(0x3ffffff);

					return _KEY3_VALUE;
				}
			}
			else
				if (_KEY4)//KEY4按下
				{
					keyDelay(_KEY_GET_DELAY);//延时消抖
					if (_KEY4)
					{
						ledBlinkTimeSet(0x4ffffff);

						return _KEY4_VALUE;
					}
				}
				else	//无键按下
				{
					return 0;
				}
	return 0;
}

/***********************************************************************
函数名称：Key_Delay(uint32_t nCount)
功    能：按键消抖延时
输入参数：
输出参数：
编写时间：2013.4.25
编 写 人：
注    意：
***********************************************************************/
static void keyDelay(uint32_t nCount)
{
	while (nCount > 0)
	{
		nCount--;
	}
}
