#include "magserv.h"
#include "stm32f10x.h"
#include "rs485communicate.h"
#include "commtype.h"
#include "Log.h"
#define MAGSERVPI   0.05f

static float station_calc(const u8 * MagSense);
static  BOOL is_check_head(const u8 * head);
static float mag_center_calc(u32 magsenseBuffer);
static float PID_calc(float err);
static float speed_vx_plan(float detax, BOOL station_flag, float cur_vx, BOOL block_flag);
static float speed_vw_plan(float detax, float set_vx, int limit_switch);

const struct _magSenseHeader magSenseHeader = MAG_SENSE_HEADER;
CAR_MOVE_STATUS CarSpeed;
//static float CarSpeedVx = 0;
//static float CarSpeedVw = 0;

u8 MagRcvDate[MAG_RCV_SIZE] = { 0 };
u8 MagRcvCount = 0;

/*---------------------------------------------------------------------------------------------*/
static float station_calc(const u8 * MagSense)
{
	static float scStationReturn = 0;
	u32 scMagDate = 0;
	if (MagRcvCount >= 10)
	{
		if (is_check_head(MagSense))
		{
			scMagDate = (MagSense[5] << 16) | (MagSense[6] << 8) | (MagSense[7]);
			MagRcvCount = 0;
			if (0 != scMagDate)
			{
				scStationReturn = mag_center_calc(scMagDate);
			}
			else
			{
				CarSpeed.vx = 0;
				scStationReturn = 0;
			}
		}
		MagRcvCount = 0;
	}
	return scStationReturn;
}

/*---------------------------------------------------------------------------------------------*/
void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		MagRcvDate[MagRcvCount++] = USART_ReceiveData(USART1);
		if (MagRcvDate[0] != magSenseHeader.pos1)
		{
			MagRcvCount = 0;
		}
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}

/*---------------------------------------------------------------------------------------------*/
static  BOOL is_check_head(const u8 * ichHead)
{
	u8 ichHeadBuffer[5] = MAG_SENSE_HEADER;
	u8 i = 0;
	for (i = 0; i < 5; i++)
	{
		if (ichHead[i] != ichHeadBuffer[i])
		{
			return FALSE;
		}
	}
	return TRUE;
}

/*---------------------------------------------------------------------------------------------*/
void mag_to_speed(void)
{
	float mtsDetax = 0;
	mtsDetax = station_calc(MagRcvDate);

	//计算偏差值
	//根据偏差值、站点信息、当前速度与障碍物信息计算vx
	//根据偏差值、线速度值与限位开关信息得到模糊规则的KP、KI、KD并计算vw
	//发送速度到驱动器

	CarSpeed.vx = speed_vx_plan(mtsDetax, 0, 0, 0);
	CarSpeed.vw = speed_vw_plan(mtsDetax, 0, 0);
	CarSpeed.vw = PID_calc(mtsDetax);
	SendSpeedToCtrl(CarSpeed.vx, CarSpeed.vw);
	printf("%.4f\n", CarSpeed.vx);
	if (CarSpeed.vx < 0.60f)
	{
		CarSpeed.vx += 0.01f;
	}
}

/*---------------------------------------------------------------------------------------------*/
static float mag_center_calc(u32 magsenseBuffer)
{
	float mccWeight[16];
	float mccMagCenter = 0;
	float mccSignal[16];
	u8 mccCount = 0;
	u8 mccI = 0;
	mccSignal[15] = 1 & magsenseBuffer;
	for (mccI = 0; mccI < 16; mccI++)
	{
		mccWeight[mccI] = (float)mccI - 7.5f;
	}
	for (mccI = 8; mccI < 16; mccI++)
	{
		mccSignal[mccI - 1] = 1 & (magsenseBuffer >> (mccI));
	}
	for (mccI = 1; mccI < 8; mccI++)
	{
		mccSignal[mccI - 1] = 1 & (magsenseBuffer >> (16 + mccI));
	}
	for (mccI = 0; mccI < 16; mccI++)
	{
		if (mccSignal[mccI])
		{
			mccCount++;
		}
		mccMagCenter += (mccWeight[mccI] * mccSignal[mccI]);
	}
	return (mccMagCenter / (float)mccCount* 10.0f);
}

/*---------------------------------------------------------------------------------------------*/
static float PID_calc(float err)
{
	float PcControl = 0;
	PcControl = MAGSERVPI * err;
	return  PcControl;
}

static float speed_vx_plan(float detax, BOOL station_flag, float cur_vx, BOOL block_flag)
{
	//根据偏差按照模糊规则查找合适的预期速度值
	//和当前速度值进行比较
	//站点信息判断是否更改预期数值
	//障碍物信息判断是否更改预期数值
	return 0;
}

static float speed_vw_plan(float detax, float set_vx, int limit_switch)
{
	//根据预期速度和偏差查询模糊规则
	//根据限位开关信息判断是否更改旋转角速度
	return 0;
}




