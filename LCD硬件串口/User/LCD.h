#ifndef _LCD_H
#define _LCD_H

#include "stm32f4xx_gpio.h"

#define  _RS_PIN GPIOA, GPIO_Pin_3
#define  _SID_PIN GPIOA, GPIO_Pin_4
#define _SCK_PIN GPIOA, GPIO_Pin_5
#define _CS_PIN GPIOB, GPIO_Pin_6

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
enum LCD_POS
{
	X1_Y1 = 0x80,
	X1_Y2,
	X1_Y3,
	X1_Y4,
	X1_Y5,
	X1_Y6,
	X1_Y7,
	X1_Y8,
	X3_Y1,
	X3_Y2,
	X3_Y3,
	X3_Y4,
	X3_Y5,
	X3_Y6,
	X3_Y7,
	X3_Y8,
	X2_Y1,
	X2_Y2,
	X2_Y3,
	X2_Y4,
	X2_Y5,
	X2_Y6,
	X2_Y7,
	X2_Y8,
	X4_Y1,
	X4_Y2,
	X4_Y3,
	X4_Y4,
	X4_Y5,
	X4_Y6,
	X4_Y7,
	X4_Y8,
};

#endif
