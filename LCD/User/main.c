#include "main.h"	
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"

#define _LED_BLINK_FRE 1
#define _LED_ON 1
#define _LED_OFF 0

#define _LED_BLINK_TASK_PRIO 1
#define _KEY_CHECK_TASK_PRIO 2

#define _LED_BLINK_TASK_STK 100
#define _KEY_CHECK_TASK_STK 100

void ledBlinkTask(void *pvParameters);
void keyCheckTask(void *pvParameters);


TaskHandle_t LedBlinkTaskHandle;
TaskHandle_t KeyCheckTaskHandle;


static void hardWareInit(void);
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	hardWareInit();
	xTaskCreate((TaskFunction_t)ledBlinkTask, \
							(const char*)"LedBlinkTask", \
							(u16)_LED_BLINK_TASK_STK,\
							(void*)NULL,\
							(UBaseType_t)_LED_BLINK_TASK_PRIO,
							 &LedBlinkTaskHandle);
	xTaskCreate((TaskFunction_t)keyCheckTask, \
						(const char*)"KeyCheckTask", \
						(u16)_KEY_CHECK_TASK_STK,\
						(void*)NULL,\
						(UBaseType_t)_KEY_CHECK_TASK_PRIO,
						 &KeyCheckTaskHandle);
	vTaskStartScheduler();
	while (1)
	{
		
	//	keyValueGet();
	//	One_LED_ON(Key_Value());
	}
}
/*------Ó²¼þ³õÊ¼»¯--------*/
static void hardWareInit(void)
{
	ledGPIOInit();
	keyGPIOInit();

}

void ledBlinkTask(void *pvParameters)
{
	pvParameters = (void *)pvParameters;
	while(1)
	{
		ledBlink(_LED_ON);
		vTaskDelay(1000/_LED_BLINK_FRE);
		ledBlink(_LED_OFF);
		vTaskDelay(1000/_LED_BLINK_FRE);
	}
}

void keyCheckTask(void *pvParameters)
{
	pvParameters = (void *)pvParameters;
	while(1)
	{
		keyValueGet();
		vTaskDelay(10);
	}
}

