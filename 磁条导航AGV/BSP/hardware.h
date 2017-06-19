#ifndef HARDWARE_H
#define HARDWARE_H
#include "stm32f10x.h"

extern void hardware_init(void);//硬件初始化
extern void change_rs485_mode(u8 msgdir);
extern void NVIC_configuration(void);//中断配置

#endif



