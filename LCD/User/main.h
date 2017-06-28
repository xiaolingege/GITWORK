/***********************************************************************
文件名称：main.h
功    能：
编写时间：
编 写 人：
注    意：
***********************************************************************/
#ifndef _MAIN_H_
#define _MAIN_H_

#include "stm32f4xx.h"
#include "LED.H"
#include "KEY.h"

#define _LED_BLINK_FRE 1
#define _LED_ON 1
#define _LED_OFF 0

#define _LED_BLINK_TASK_PRIO 3
#define _LCD_SHOW_TASK_PRIO 4

#define _LED_BLINK_TASK_STK 100
#define _LCD_SHOW_TASK_STK 100

#endif

