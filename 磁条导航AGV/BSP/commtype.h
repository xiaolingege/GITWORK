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

struct _magSenseHeader
{
	u8 pos1;
	u8 pos2;
	u8 pos3;
	u8 pos4;
	u8 pos5;
};

struct  magtype
{
	u8 pos1 : 1;
	u8 pos2 : 7;
	u8 pos3 : 8;
	u8 pos4 : 1;
	u8 pos5 : 7;
};

typedef union _MAG_UNION
{
	struct magtype rec_seg;
	u8 mag_arr[3];
}MAG_UNION;

#endif

