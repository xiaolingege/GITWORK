#include "usart.h"
#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"
#include "dma.h"
#include "datatype.h"

BOOL IsDmaRcvEnd = TRUE;
u16 UsartSendDataLen = 0;

void usartConfig(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;//����GPIO_InitTypeDef���͵Ľṹ���ԱGPIO_InitStructure

	USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStruct;
	//ʹ����Ҫ�õ���GPIO�ܽ�ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOD, ENABLE);
	//ʹ��USART1 ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	///��λ����1
	USART_DeInit(USART1);

	USART_StructInit(&USART_InitStructure);//����Ĭ��USART����
	USART_ClockStructInit(&USART_ClockInitStruct);//����Ĭ��USART����        
												  //���ô���1�Ĺܽ� PA8 USART1_EN PA9 USART1_TX PA10 USART1_RX    
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    //����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //�������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);        //�ܽ�PA9����ΪUSART1
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

	// 	//����DMA��ʽ����  
	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
	//����DMA��ʽ����  
	USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);

	USART_Cmd(USART1, ENABLE);
	USART_ClearITPendingBit(USART1, USART_IT_TC);//����ж�TCλ	
}

void USART1_IRQHandler(void)
{

	unsigned char temp = 0;
	if (USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
	{
		temp = USART1->SR;
		temp = USART1->DR; 												//��USART_IT_IDLE��־ 
		IsDmaRcvEnd = TRUE;	   											//DMA���ձ�־

		DMA_Cmd(DMA2_Stream5, DISABLE); 							  	//��ȡ���ݳ����ȹر�DMA 
		UsartSendDataLen = _DMA_USART_SIZE - DMA_GetCurrDataCounter(DMA2_Stream5);//��ȡDMA���յ����ݳ��ȣ�

		DMA_SetCurrDataCounter(DMA2_Stream5, _DMA_USART_SIZE);		//���ô������ݳ���    
		DMA_Cmd(DMA2_Stream5, ENABLE);
	}
	if (USART_GetITStatus(USART1, USART_IT_TC) != RESET)					//���ڷ����ж�
	{
		USART_ClearITPendingBit(USART1, USART_IT_TC);
		IsDmaSendEnd = TRUE;										//�����ٴη���
	}
}

void Rs232DmaSend(unsigned char *send_buff, unsigned int length)
{

	unsigned int counter_232 = 0;
	while (IsDmaSendEnd != TRUE)					//�ȴ��ϴε�DMA�������
	{
		counter_232++;
		if (counter_232 >= 0xffff)
		{
			break;
		}
	}
	IsDmaRcvEnd = FALSE;
	DMA2_Stream7->M0AR = (u32)send_buff;
	DMA_SetCurrDataCounter(DMA2_Stream7, length);  	//���ô��䳤��
	DMA_Cmd(DMA2_Stream7, ENABLE);					//����DMA����
}

