#ifndef _SPI_H
#define _SPI_H
#include "stm32f4xx.h"
#include "stm32f4xx_spi.h"

#define LCD_SPI SPI3
#define LCD_PORT_CSN GPIOB
#define LCD_PIN_CSN	GPIO_Pin_6
void spiGPIOConfig(void);


#endif // !_SPI_H
