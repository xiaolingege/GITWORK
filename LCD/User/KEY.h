/***********************************************************************
�ļ����ƣ�KEY.h
��    �ܣ���������
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺
***********************************************************************/

#ifndef _KEY_H_
#define _KEY_H_

/***********����Ϊ���������жϺ궨��*****************************/
#define KEY1   			!GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12)
#define KEY2			!GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_13)
#define KEY3			!GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14)
#define KEY4 			!GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15)

/***********����Ϊ������ֵ�궨��*****************************/
#define KEY1_VALUE       1
#define KEY2_VALUE       2
#define KEY3_VALUE       3
#define KEY4_VALUE       4

void Key_Configuration(void);
unsigned char Key_Value(void);
static void Key_Delay(uint32_t nCount);

#endif
