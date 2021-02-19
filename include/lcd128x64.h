#ifndef LCD128x62_H
#define LCD128x62_H

#include "mcu02_sfr.h"
#include "mcu02_gpio.h"
#include "mcu02_spi.h"


#define X_WIDTH 128
#define Y_WIDTH 64

#define	LCD_CMD_DATA_PORT	GPIOB
#define	LCD_CMD_DATA_PIN	GPIO_PIN_7

#define	LCD_RST_PORT		GPIOB
#define	LCD_RST_PIN			GPIO_PIN_6

#define	SPI1_CS_H()			(SPI1_CFG1 |= 0x01)
#define	SPI1_CS_L()			(SPI1_CFG1 &= ~0x01)

extern uint8_t idata timer_10ms;
extern uint8_t xdata spi_tx_data[1024];
extern uint8_t xdata spi_rx_data[1024];
extern code uint8_t F8X16_up[];
extern code uint8_t F8X16_down[];
extern uint8_t xdata lcd_data_up[128];
extern uint8_t xdata lcd_data_down[128];


void lcd_init(void);
void Draw_LQLogo(void);
#endif