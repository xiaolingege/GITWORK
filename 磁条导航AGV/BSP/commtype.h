#ifndef _COMMTYPE_H
#define _COMMTYPE_H

#define  BOOL unsigned char
#define SPEEDSENDTASKPRIO   1
#define MAGSENSEQUERYPRIO   2
#define SPEEDSENDTASKSTK    500
#define MAGSENSEQUERYSTK    200
#define MAGQUERYMSG	{ 0x52, 0x4D, 0x67, 0x73, 0x77 , 0x5e, 0x69 }

enum _BOOL//自定义BOOL类型
{
	TRUE = 1,
	FALSE = 0
};


#endif

