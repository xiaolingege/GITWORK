#include "main.h"	
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "LCD.h"

#define _LED_BLINK_FRE 2
#define _LED_ON 1
#define _LED_OFF 0

#define _LED_BLINK_TASK_PRIO 30
#define _LCD_SHOW_TASK_PRIO 2

#define _LED_BLINK_TASK_STK 100
#define _LCD_SHOW_TASK_STK 100

void ledBlinkTask(void *pvParameters);
void lcdShowTask(void *pvParameters);

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
	xTaskCreate((TaskFunction_t)lcdShowTask, \
						(const char*)"KeyCheckTask", \
						(u16)_LCD_SHOW_TASK_STK,\
						(void*)NULL,\
						(UBaseType_t)_LCD_SHOW_TASK_PRIO,
						 &KeyCheckTaskHandle);
	vTaskStartScheduler();
}
/*------Ó²¼þ³õÊ¼»¯--------*/
static void hardWareInit(void)
{
	ledGPIOInit();
	keyGPIOInit();
	lcdGPIOInit();
}

void ledBlinkTask(void *pvParameters)
{
	pvParameters = (void *)pvParameters;
	while(1)
	{
		ledBlink(_LED_ON);
		vTaskDelay(3000/_LED_BLINK_FRE);
		ledBlink(_LED_OFF);
		vTaskDelay(3000/_LED_BLINK_FRE);
	}
}

void lcdShowTask(void *pvParameters)
{
	lcdInit();
	pvParameters = (void *)pvParameters;
	while(1)
	{
		lcdShowString(0x80, "haha");
		lcdShowNumber(0x90, 50.1);
		keyValueGet();
		vTaskDelay(100);
	}
}

