#ifndef _USART_H
#define _USART_H
#include "stm32f4xx.h"

void usartConfig(u32 bound);
void Rs232DmaSend(unsigned char *send_buff, unsigned int length);
#endif // !_USART_H
