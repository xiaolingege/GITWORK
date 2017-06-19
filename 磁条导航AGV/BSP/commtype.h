#ifndef _COMMTYPE_H
#define _COMMTYPE_H

#define  BOOL unsigned char
#define SPEEDSENDTASKPRIO   1
#define MAGSENSEQUERYPRIO   2
#define SPEEDSENDTASKSTK    500
#define MAGSENSEQUERYSTK    200
#define MAGQUERYMSG	{ 0x52, 0x4D, 0x67, 0x73, 0x77 , 0x5e, 0x69 }

#define COM1_OUT GPIO_Pin_9
#define COM1_IN GPIO_Pin_10

#define COM2_OUT GPIO_Pin_2
#define COM2_IN GPIO_Pin_3

#define COM1 USART1
#define COM2 USART2

#define MAG_SENSE_HEADER {0x52, 0x4D, 0x67, 0x73, 0x77}
#define MAG_RCV_SIZE  (15)


enum _BOOL//自定义BOOL类型
{
	TRUE = 1,
	FALSE = 0
};

enum com85msgmode
{
	MSG_SEND = 0,
	MSG_GET = 1
};

#endif

