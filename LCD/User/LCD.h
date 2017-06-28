#ifndef _LCD_H
#define _LCD_H

#include "stm32f4xx_gpio.h"

#define  _RS_PIN GPIOA, GPIO_Pin_3
#define  _SID_PIN GPIOA, GPIO_Pin_4
#define _SCK_PIN GPIOA, GPIO_Pin_5
#define _CS_PIN GPIOA, GPIO_Pin_6

#define  _RS_H GPIO_SetBits(_RS_PIN);
#define  _RS_L GPIO_ResetBits(_RS_PIN);

#define  _SID_H GPIO_SetBits(_SID_PIN);
#define _SID_L GPIO_ResetBits(_SID_PIN);

#define  _SCK_H GPIO_SetBits(_SCK_PIN);
#define _SCK_L GPIO_ResetBits(_SCK_PIN);

#define _CS_H GPIO_SetBits(_CS_PIN);
#define _CS_L GPIO_ResetBits(_CS_PIN);

void lcdGPIOConfig(void);

static void byteSend(u8 data);
static void cmdSend(u8 data);
static void dataSend(u8 data);
void lcdShowNumber(u8 x_add, float number);
void lcdShowString(u8 x_add, u8 *ptr);
void lcdInit(void);
#endif
