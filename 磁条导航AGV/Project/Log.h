#ifndef _LOG_H_
#define _LOG_H_

#include "stdio.h"
#include "stm32f10x.h"

#define LOG_USART USART3 //根据实际情况设置串口号

#define LOG_INFO(...) do{\
	printf("[Info] "); \
	PRINT(__VA_ARGS__); } \
while (0)\

#define LOG_ERROR(...) do{\
	printf("[Error] "); \
	PRINT(__VA_ARGS__); } \
while (0)\

#define PRINT(...) do{\
	printf("[%s] ", __FUNCTION__);  \
	printf(__VA_ARGS__); \
	printf("\r\n"); \
} while (0)\

void LOG_HEX(const u8 *data, u16 len);

#endif


