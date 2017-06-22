#include "Log.h"

void LOG_HEX(const u8 *data, u16 len)
{
	u16 i = 0; 
	printf("[HEX] ");
	for(; i < len; ++i) 
	{
		printf("%x ", data[i]);
	} 
	printf("\r\n");
}

int fputc(int ch, FILE *f)
{
// 	USART_ClearFlag(LOG_USART, USART_FLAG_TC);
	USART_SendData(LOG_USART, ch);
	while(USART_GetFlagStatus(LOG_USART, USART_FLAG_TC) == RESET);
	return(ch);
}




