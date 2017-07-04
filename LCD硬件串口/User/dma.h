#ifndef _DMA_H
#define _DMA_H
#include "datatype.h"
#define _DMA_USART_SIZE (1024)

extern BOOL IsDmaSendEnd;
extern volatile u8 UsartRcvMsg[_DMA_USART_SIZE];
extern volatile u8 UsartSendMsg[_DMA_USART_SIZE];
void dmaConfig(void);

void NVIC_Configuration(void);
#endif // !_DMA_H
