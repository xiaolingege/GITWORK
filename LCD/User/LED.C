/***********************************************************************
文件名称：LED.C
功    能：led  IO初始化
编写时间：2013.4.25
编 写 人：
注    意：
***********************************************************************/
#include "main.h"

static u32 LedBlinkTime = 0xffffff;

void ledBlinkTimeSet(u32 val)
{
	LedBlinkTime = val;
}

void ledGPIOInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	/* Enable the GPIO_LED Clock */
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOE, ENABLE); 						 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

/***********************************************************************
函数名称：LED_Blink(void)
功    能：完成LED闪烁
输入参数：
输出参数：
编写时间：2013.4.25
编 写 人：
注    意：
***********************************************************************/
void ledBlink(void)
{
	/*****熄灭四个led灯******/
	_LED1_OFF;
	_LED2_OFF;
	_LED3_OFF;
	_LED4_OFF;
	ledDelay(LedBlinkTime);
	/*****点亮四个led灯******/
	_LED1_ON;
	_LED2_ON;
	_LED3_ON;
	_LED4_ON;
	ledDelay(LedBlinkTime);
}
/***********************************************************************
函数名称：One_LED_ON(unsigned char led_num)
功    能：实现点亮一个LED灯
输入参数：
输出参数：
编写时间：2013.4.25
编 写 人：
注    意：
***********************************************************************/
void oneLedON(unsigned char led_num)
{	
	/*****熄灭四个led灯******/
	_LED1_OFF;
	_LED2_OFF;
	_LED3_OFF;
	_LED4_OFF;
	switch(led_num)
	{
		case KEY1:
		{
			_LED1_ON;
			break;
		}
		case KEY2:
		{
			_LED2_ON;
			break;		
		}
		case KEY3:
		{
			_LED3_ON;
			break;		
		}
		case KEY4:
		{
			_LED4_ON;
			break;		
		}
		default:
		{
			break;	
		}
	}		
}

static ledDelay(uint32_t nCount)
{ 
  while(nCount > 0)
  { 
  	  nCount --;   
  }
}
