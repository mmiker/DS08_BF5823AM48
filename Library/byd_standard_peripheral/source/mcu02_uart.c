/*!
    \file  mcu02_uart.c
    \brief uart driver
*/

/*
    Copyright (C) 2020 BYD

    2020-07-15, V1.0.0, firmware for mcu02
*/

#include "mcu02_uart.h"

/*!
    \brief      uart0 and uart1 init
    \param[in]  uart_port: UART0 or UART1
				baudrate : UART_BAUDRATE_xx
    \param[out] none
    \retval     none
*/
void uart_baudrate_config(UART_PORT_enum uart_port,uint32_t baudrate)
{
   	uint16_t tmp;

	tmp = (uint16_t)((UART_BUS_CLK >> 4) / baudrate);

	if(uart_port == UART0){
			
		UART0_BDL = (uint8_t)tmp;
		UART0_CON2 |= ((tmp >> 8) & 0x03);		

	}else{
		
		UART1_BDL = (uint8_t)tmp;
		UART1_CON2 |= ((tmp >> 8) & 0x03);		
	}
}

/*!
    \brief      uart send byte
    \param[in]  uart_port: UART0/UART1
				dat :send data
    \param[out] none
    \retval     none
*/
void uart_tx_byte(UART_PORT_enum uart_port,uint8_t dat)
{
	if(uart_port == UART0){
		UART0_BUF = dat;
		while((UART0_STATE & TX_EMPTY_FLAG) == 0x00);
		CLR_UART0_TX_STATE();
	}else if(uart_port == UART1){
		UART1_BUF = dat;
		while((UART1_STATE & TX_EMPTY_FLAG) == 0x00);
		CLR_UART1_TX_STATE();
	}
}

/*!
    \brief      uart receive byte
    \param[in]  uart_port: UART0/UART1
    \param[out] none
    \retval     receive data
*/
uint8_t uart_rx_byte(UART_PORT_enum uart_port)
{
	uint8_t dat;
	if(uart_port == UART0){
		while((UART0_STATE & RX_FULL_FLAG) == 0x00);
		dat = UART0_BUF;
		// CLR_UART0_RX_STATE();
	}else if(uart_port == UART1){
		while((UART1_STATE & RX_FULL_FLAG) == 0x00);
		dat = UART1_BUF;
		CLR_UART1_RX_STATE();
	}
	return dat;
}		
		
		