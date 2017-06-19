#include "magserv.h"
#include "stm32f10x.h"
#include "rs485communicate.h"
#include "commtype.h"

#define MAGSERVPI   0.05f

static float StationCalc(const u8 * MagSense);
static  BOOL isCheckHead(const u8 * head);
static float mag_center_calc(u32 magsenseBuffer);
static float PIDCalc(float err);

const struct _magSenseHeader magSenseHeader = MAG_SENSE_HEADER;
CAR_MOVE_STATUS CarSpeed;
//static float CarSpeedVx = 0;
//static float CarSpeedVw = 0;

u8 MagRcvDate[MAG_RCV_SIZE] = { 0 };
u8 MagRcvCount = 0;

/*---------------------------------------------------------------------------------------------*/
static float StationCalc(const u8 * MagSense)
{
	static float StationForReturn = 0;
	u32 magDate = 0;
	if (MagRcvCount >= 10)
	{
		if (isCheckHead(MagSense))
		{
			magDate = (MagSense[5] << 16) | (MagSense[6] << 8) | (MagSense[7]);
			MagRcvCount = 0;
			if (0 != magDate)
			{
				StationForReturn = mag_center_calc(magDate);
			}
			else
			{
				CarSpeed.vx = 0;
				StationForReturn = 0;
			}
		}
		MagRcvCount = 0;
	}
	return StationForReturn;
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
static  BOOL isCheckHead(const u8 * head)
{
	u8 hedbuffer[5] = MAG_SENSE_HEADER;
	u8 i = 0;
	for (i = 0; i < 5; i++)
	{
		if (head[i] != hedbuffer[i])
		{
			return FALSE;
		}
	}
	return TRUE;
}

/*---------------------------------------------------------------------------------------------*/
void mag_to_speed(void)
{
	CarSpeed.vw = PIDCalc(StationCalc(MagRcvDate));
	SendSpeedToCtrl(CarSpeed.vx, CarSpeed.vw);
	if (CarSpeed.vx < 0.60f)
	{
		CarSpeed.vx += 0.01f;
	}
}

/*---------------------------------------------------------------------------------------------*/
static float mag_center_calc(u32 magsenseBuffer)
{
	float weight[16];
	float magCenterForReturn = 0;
	float signal[16];
	u8 count = 0;
	u8 i = 0;
	signal[15] = 1 & magsenseBuffer;
	for (i = 0; i < 16; i++)
	{
		weight[i] = (float)i - 7.5f;
	}
	for (i = 8; i < 16; i++)
	{
		signal[i - 1] = 1 & (magsenseBuffer >> (i));
	}
	for (i = 1; i < 8; i++)
	{
		signal[i - 1] = 1 & (magsenseBuffer >> (16 + i));
	}
	for (i = 0; i < 16; i++)
	{
		if (signal[i])
		{
			count++;
		}
		magCenterForReturn += (weight[i] * signal[i]);
	}
	return (magCenterForReturn / (float)count* 10.0f);
}

/*---------------------------------------------------------------------------------------------*/
static float PIDCalc(float err)
{
	float control = 0;
	control = MAGSERVPI * err;
	return  control;
}






