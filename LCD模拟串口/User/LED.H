/***********************************************************************
�ļ����ƣ�LED.h
��    �ܣ�led  IO��ʼ��
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺
***********************************************************************/

#ifndef _LED_H_
#define _LED_H_

#define _LED1			GPIOE , GPIO_Pin_8
#define _LED2			GPIOE , GPIO_Pin_9
#define _LED3			GPIOE , GPIO_Pin_10
#define _LED4			GPIOE , GPIO_Pin_11

#define _LED1_ON 		GPIO_ResetBits(GPIOE , GPIO_Pin_8)
#define _LED2_ON 		GPIO_ResetBits(GPIOE , GPIO_Pin_9)
#define _LED3_ON 		GPIO_ResetBits(GPIOE , GPIO_Pin_10)
#define _LED4_ON 		GPIO_ResetBits(GPIOE , GPIO_Pin_11)

#define _LED1_OFF 		GPIO_SetBits(GPIOE , GPIO_Pin_8)
#define _LED2_OFF 		GPIO_SetBits(GPIOE , GPIO_Pin_9)
#define _LED3_OFF 		GPIO_SetBits(GPIOE , GPIO_Pin_10)
#define _LED4_OFF 		GPIO_SetBits(GPIOE , GPIO_Pin_11)

void ledBlinkTimeSet(u32 val);
void ledGPIOConfig(void);
void ledBlink(u8 led_flag);
void oneLedON(unsigned char led_num);
static ledDelay(uint32_t nCount);

#endif
