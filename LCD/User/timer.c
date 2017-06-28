#include "timer.h"
#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"

void pwmConfig(void)
{
	u16 arr, ccr1, ccr2;
	TIM_TimeBaseInitTypeDef Tim_Init;
	TIM_OCInitTypeDef TIM_OCInit;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	arr = SystemCoreClock/10000;
	ccr1 = arr;
	ccr2 = arr;
	Tim_Init.TIM_Period = arr;
	Tim_Init.TIM_Prescaler = 0;
	Tim_Init.TIM_ClockDivision = TIM_CKD_DIV1;
	Tim_Init.TIM_CounterMode = TIM_CounterMode_Up;
	Tim_Init.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &Tim_Init);
	
	TIM_OCInit.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInit.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInit.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInit.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInit.TIM_Pulse = ccr1;
	TIM_OCInit.TIM_OCNPolarity = TIM_OCNPolarity_Low;
	TIM_OCInit.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInit.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	
	TIM_OC1Init(TIM1, &TIM_OCInit);
	
	TIM_OCInit.TIM_Pulse = ccr2;
	TIM_OC2Init(TIM1, &TIM_OCInit);
	TIM_Cmd(TIM1, ENABLE);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	

}
