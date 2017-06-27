#ifndef _KEY_H_
#define _KEY_H_

/***********以下为按键按下判断宏定义*****************************/
#define _KEY1   		!GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12)
#define _KEY2			!GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_13)
#define _KEY3			!GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14)
#define _KEY4 			!GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15)

/***********以下为按键键值宏定义*****************************/
#define _KEY1_VALUE       1
#define _KEY2_VALUE       2
#define _KEY3_VALUE       3
#define _KEY4_VALUE       4

enum _KEY_VAL
{
	KEY1 = 1,
	KEY2 = 2,
	KEY3 = 3,
	KEY4 = 4
};

void keyGPIOInit(void);
unsigned char keyValueGet(void);
static void keyDelay(uint32_t nCount);

#endif
