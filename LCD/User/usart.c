#include "usart.h"
#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"
#include "dma.h"
#include "datatype.h"

BOOL IsDmaRcvEnd = TRUE;
u16 UsartSendDataLen = 0;

void usartConfig(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;//定义GPIO_InitTypeDef类型的结构体成员GPIO_InitStructure

	USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStruct;
	//使能需要用到的GPIO管脚时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOD, ENABLE);
	//使能USART1 时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	///复位串口1
	USART_DeInit(USART1);

	USART_StructInit(&USART_InitStructure);//载入默认USART参数
	USART_ClockStructInit(&USART_ClockInitStruct);//载入默认USART参数        
												  //配置串口1的管脚 PA8 USART1_EN PA9 USART1_TX PA10 USART1_RX    
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    //复用
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);        //管脚PA9复用为USART1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

	USART_ClockInit(USART1, &USART_ClockInitStruct);

	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);

	USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
	// 	USART_ITConfig(USART1, USART_IT_TC, ENABLE);// 

	// 	//采用DMA方式发送  
	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
	//采用DMA方式接收  
	USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);

	USART_Cmd(USART1, ENABLE);
	USART_ClearITPendingBit(USART1, USART_IT_TC);//清除中断TC位	
}

void USART1_IRQHandler(void)
{

	unsigned char temp = 0;
	if (USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
	{
		temp = USART1->SR;
		temp = USART1->DR; 												//清USART_IT_IDLE标志 
		IsDmaRcvEnd = TRUE;	   											//DMA接收标志

		DMA_Cmd(DMA2_Stream5, DISABLE); 							  	//读取数据长度先关闭DMA 
		UsartSendDataLen = _DMA_USART_SIZE - DMA_GetCurrDataCounter(DMA2_Stream5);//获取DMA接收的数据长度，

		DMA_SetCurrDataCounter(DMA2_Stream5, _DMA_USART_SIZE);		//设置传输数据长度    
		DMA_Cmd(DMA2_Stream5, ENABLE);
	}
	if (USART_GetITStatus(USART1, USART_IT_TC) != RESET)					//串口发送中断
	{
		USART_ClearITPendingBit(USART1, USART_IT_TC);
		IsDmaSendEnd = TRUE;										//允许再次发送
	}
}

void Rs232DmaSend(unsigned char *send_buff, unsigned int length)
{

	unsigned int counter_232 = 0;
	while (IsDmaSendEnd != TRUE)					//等待上次的DMA传输完成
	{
		counter_232++;
		if (counter_232 >= 0xffff)
		{
			break;
		}
	}
	IsDmaRcvEnd = FALSE;
	DMA2_Stream7->M0AR = (u32)send_buff;
	DMA_SetCurrDataCounter(DMA2_Stream7, length);  	//设置传输长度
	DMA_Cmd(DMA2_Stream7, ENABLE);					//启动DMA传输
}

