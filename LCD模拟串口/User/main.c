#include "main.h"	
#include "FreeRTOS.h"
#include "task.h"
#include "timer.h"
#include "queue.h"
#include "LCD.h"
#include "datatype.h"
#include "usart.h"
#include "dma.h"
#include "math.h"

#define _PI (3.1415f)
#define _STEP (0.031415f)

void ledBlinkTask(void *pvParameters);
void lcdShowTask(void *pvParameters);

TaskHandle_t LedBlinkTaskHandle;
TaskHandle_t LcdShowTaskHandle;

static void hardWareInit(void);
int main(void)
{
	hardWareInit();
	xTaskCreate((TaskFunction_t)ledBlinkTask, \
		(const char*)"LedBlinkTask", \
		(u16)_LED_BLINK_TASK_STK, \
		(void*)NULL, \
		(UBaseType_t)_LED_BLINK_TASK_PRIO,\
		&LedBlinkTaskHandle);
	xTaskCreate((TaskFunction_t)lcdShowTask, \
		(const char*)"LcdShowTask", \
		(u16)_LCD_SHOW_TASK_STK, \
		(void*)NULL, \
		(UBaseType_t)_LCD_SHOW_TASK_PRIO, \
		&LcdShowTaskHandle);
	vTaskStartScheduler();
}
/*------硬件初始化--------*/
static void hardWareInit(void)
{
	NVIC_Configuration();
	usartConfig(115200);
	dmaConfig();
	ledGPIOConfig();
	keyGPIOConfig();
	lcdGPIOConfig();
	pwmConfig();
}


void ledBlinkTask(void *pvParameters)
{
	float led1Value = 0;
	u16 led1Set = 0;
	BOOL ledFlag = FALSE;
	pvParameters = (void *)pvParameters;
	while (1)
	{
		TIM_SetCompare1(TIM1, 10000 - led1Value);
		TIM_SetCompare2(TIM1, led1Value);
		calcDuty(&ledFlag, &led1Set, &led1Value);

		vTaskDelay(1);
	}
}

void lcdShowTask(void *pvParameters)
{
	float i = 110.1333;
	u8 j = 0;
	lcdInit();//初始化LCD
	lcdShowString(0x80, "哈工大机器人集团");
	lcdShowString(0x91, "电量：");
	lcdShowString(0x97, "%");
	lcdShowString(0x89, "电压：");
	lcdShowString(0x8F, "V");
	lcdShowString(0x99, "电流：");
	lcdShowString(0x9F, "A");
	pvParameters = (void *)pvParameters;
	while (1)
	{
 		lcdShowNumber(0x94, i);
		lcdShowNumber(0x8C, i);
		lcdShowNumber(0x9C, i);

		j = keyValueGet();
		i += 0.1f*(float)j;
		if (0 == j)
		{
			vTaskDelay(10);
		}
		else
		{
			vTaskDelay(100);
		}
	}
}

static void calcDuty(BOOL *ledFlag, u16 *led1Set, float *led1Value)
{
	if (*ledFlag == TRUE)
	{
		*led1Set += 2;
		if (*led1Set == 10000)
		{
			*ledFlag = FALSE;
		}
	}
	else
	{
		*led1Set -= 2;
		if (*led1Set == 0)
		{
			*ledFlag = TRUE;
		}
	}
	*led1Value = 10000 * sinf((float)*led1Set*3.14f / 10000.0f);
}



