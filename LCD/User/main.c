#include "main.h"	
static void hardWareInit(void);
int main(void)
{
	hardWareInit();
	while (1)
	{
		ledBlink();
		keyValueGet();
	//	One_LED_ON(Key_Value());
	}
}
/*------Ӳ����ʼ��--------*/
static void hardWareInit(void)
{
	ledGPIOInit();
	keyGPIOInit();
}

