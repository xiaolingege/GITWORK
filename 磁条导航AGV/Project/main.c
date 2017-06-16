#include "hardware.h"
#include "rs485communicate.h"
#include "magserv.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "commtype.h"
#include "rs485config.h"

void speed_send_task(void *pvParameters);
void mag_sense_query_task(void *pvParameter);

TaskHandle_t    SpeedSendTaskHandle;//速度发送任务句柄
TaskHandle_t    MagSenseQueryHandle;//磁传感器查询句柄

/*---------------------------------------------------------------------------------------------*/
int main(void)
{
	hardware_init();
	NVIC_configuration();
	/*创建速度发送任务*/
	xTaskCreate((TaskFunction_t)speed_send_task,
		(const char*)"SpeedSendTask",
		(u16)SPEEDSENDTASKSTK,
		(void*)NULL,
		(UBaseType_t)SPEEDSENDTASKPRIO,
		(TaskHandle_t *)&SpeedSendTaskHandle);

	/*创建磁传感器查询任务*/
	xTaskCreate((TaskFunction_t)mag_sense_query_task,
		(const char*)"MagSenseQuery",
		(u16)MAGSENSEQUERYSTK,
		(void*)NULL,
		(UBaseType_t)MAGSENSEQUERYPRIO,
		(TaskHandle_t *)&MagSenseQueryHandle);
	vTaskStartScheduler();
}

/*---------------------------------------------------------------------------------------------*/
//速度控制任务
void speed_send_task(void *pvParameters)
{
	pvParameters = (void *)pvParameters;
	while (1)
	{
		mag_to_speed();
		vTaskDelay(50);
	}
}
//磁传感器查询任务

/*---------------------------------------------------------------------------------------------*/
void mag_sense_query_task(void *pvParameters)
{
	static u8 TxBufferToQueryMagsense[7] = MAGQUERYMSG;  //磁导航传感器查询内容
	pvParameters = (void *)pvParameters;
	while (1)
	{
		usart_out(USART1, TxBufferToQueryMagsense, 7);
		vTaskDelay(200);
	}
}

