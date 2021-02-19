/*!
    \file  mcu02_uart.h
    \brief uart define
*/

/*
    Copyright (C) 2020 BYD

    2020-07-15, V1.0.0, firmware for mcu02
*/

#ifndef	MCU02_UART_H
#define	MCU02_UART_H

#include "mcu02_sfr.h"

#define	UART_BUS_CLK	  (uint32_t)24000000

#define UART0_PC4_PC5     0x00
#define UART0_PE4_PE5     0x01
#define UART0_PF4_PF5     0x02

#define UART1_PC6_PC7     0x00
#define UART1_PH4_PH5     0x01

#define UART0_PORT_SET(x) {REG_ADDR = PERIPH_IO_SEL1;REG_DATA &= ~(0x60);REG_DATA |= (0x60&(x<<5));}
#define UART1_PORT_SET(x) {REG_ADDR = PERIPH_IO_SEL1;REG_DATA &= ~(0x80);REG_DATA |= (0x80&(x<<7));}

/* uart baudrate define */
#define	UART_BAUDRATE_4800			(uint32_t)4800
#define	UART_BAUDRATE_9600			(uint32_t)9600
#define	UART_BAUDRATE_19200			(uint32_t)19200
#define	UART_BAUDRATE_38400			(uint32_t)38400
#define	UART_BAUDRATE_57600			(uint32_t)57600
#define	UART_BAUDRATE_115200		(uint32_t)115200
#define	UART_BAUDRATE_125000		(uint32_t)125000
#define	UART_BAUDRATE_150000		(uint32_t)150000
#define	UART_BAUDRATE_187500		(uint32_t)187500
#define	UART_BAUDRATE_250000		(uint32_t)250000
#define	UART_BAUDRATE_300000		(uint32_t)300000
#define	UART_BAUDRATE_375000		(uint32_t)375000
#define	UART_BAUDRATE_500000		(uint32_t)500000
#define	UART_BAUDRATE_750000		(uint32_t)750000
#define	UART_BAUDRATE_1500000		(uint32_t)1500000

/* stop bit width define */
#define	STOP_WIDTH_1BIT				0x00
#define	STOP_WIDTH_2BIT				0x01

/* data mode define */
#define	DATA_MODE_8BIT				0x00
#define	DATA_MODE_9BIT				0x01

/* parity select define */
#define	ODD_PARITY					0x01
#define	EVEN_PARITY					0x00

/* uart port define */
typedef enum
{
	UART0,
	UART1
}UART_PORT_enum;

/* uart interrupt flag define */
#define	TX_EMPTY_FLAG			0x10		/* tx buffer empty flag */
#define	RX_FULL_FLAG			0x08		/* rx buffer full flag */
#define	RX_OVERFLOW_FLAG		0x04		/* rx buffer overflow flag */
#define	FRAME_ERROR_FLAG		0x02		/* frame error flag */
#define	PARITY_ERROR_FLAG		0x01		/* parity error flag */


#define TX_SEND_INT_EN          0x08
#define RX_RECEIVE_INT_EN       0x04

/*uart0*/
#define UART0_MULTI_MODE(x)     UART0_CON1 &= ~0x10;UART0_CON1 |= (x<<4)
#define UART0_STOP_MODE(x)      UART0_CON1 &= ~0x08;UART0_CON1 |= (x<<3)
#define UART0_DATA_MODE(x)      UART0_CON1 &= ~0x04;UART0_CON1 |= (x<<2)
#define UART0_PARITY_SET(x)     UART0_CON1 &= ~0x02;UART0_CON1 |= (x<<1)
#define UART0_PARITY_SEL(x)     UART0_CON1 &= ~0x01;UART0_CON1 |= (x)

#define UART0_ENABLE()		    UART0_CON1 |= 0x40
#define UART0_DISABLE()			UART0_CON1 &= ~0x40

#define UART0_RX_ENABLE()		UART0_CON1 |= 0x20
#define UART0_RX_DISABLE()	    UART0_CON1 &= ~(0x20)

#define GET_UART0_TX_STATE()    (UART0_STATE & TX_EMPTY_FLAG)
#define GET_UART0_RX_STATE()    (UART0_STATE & RX_FULL_FLAG)
#define GET_UART0_RFW_STATE()   (UART0_STATE & RX_OVERFLOW_FLAG)
#define GET_UART0_PERR_STATE()  (UART0_STATE & PARITY_ERROR_FLAG)
#define GET_UART0_FERR_STATE()  (UART0_STATE & FRAME_ERROR_FLAG)

#define CLR_UART0_TX_STATE()    UART0_STATE &= ~TX_EMPTY_FLAG
#define CLR_UART0_RX_STATE()    UART0_STATE &= ~RX_FULL_FLAG
#define CLR_UART0_RFW_STATE()   UART0_STATE &= ~RX_OVERFLOW_FLAG
#define CLR_UART0_PERR_STATE()  UART0_STATE &= ~PARITY_ERROR_FLAG
#define CLR_UART0_FERR_STATE()  UART0_STATE &= ~FRAME_ERROR_FLAG

#define UART0_TX_INT_ENABLE()   UART0_CON2 |= TX_SEND_INT_EN
#define UART0_TX_INT_DISABLE()  UART0_CON2 &= ~TX_SEND_INT_EN

#define UART0_RX_INT_ENABLE()   UART0_CON2 |= RX_RECEIVE_INT_EN
#define UART0_RX_INT_DISABLE()  UART0_CON2 &= ~RX_RECEIVE_INT_EN

#define UART0_INT_ENABLE()		IEN2 |= 0x04   /* enable interrupt */
#define UART0_INT_DISABLE()		IEN2 &= ~0x04  /* disable interrupt */
#define UART0_IPL_SET(x)        IPL2 &= ~0x04;IPL2 |= (x<<2)  /* set interrupt priority */


/*uart1*/
#define UART1_MULTI_MODE(x)     UART1_CON1 &= ~0x10;UART1_CON1 |= (x<<4)
#define UART1_STOP_MODE(x)      UART1_CON1 &= ~0x08;UART1_CON1 |= (x<<3)
#define UART1_DATA_MODE(x)      UART1_CON1 &= ~0x04;UART1_CON1 |= (x<<2)
#define UART1_PARITY_SET(x)     UART1_CON1 &= ~0x02;UART1_CON1 |= (x<<1)
#define UART1_PARITY_SEL(x)     UART1_CON1 &= ~0x01;UART1_CON1 |= (x)

#define UART1_ENABLE()		    UART1_CON1 |= 0x40
#define UART1_DISABLE()			UART1_CON1 &= ~0x40

#define UART1_RX_ENABLE()		UART1_CON1 |= 0x20
#define UART1_RX_DISABLE()	    UART1_CON1 &= ~(0x20)

#define GET_UART1_TX_STATE()    (UART1_STATE & TX_EMPTY_FLAG)
#define GET_UART1_RX_STATE()    (UART1_STATE & RX_FULL_FLAG)
#define GET_UART1_RFW_STATE()   (UART1_STATE & RX_OVERFLOW_FLAG)
#define GET_UART1_PERR_STATE()  (UART1_STATE & PARITY_ERROR_FLAG)
#define GET_UART1_FERR_STATE()  (UART1_STATE & FRAME_ERROR_FLAG)

#define CLR_UART1_TX_STATE()    UART1_STATE &= ~TX_EMPTY_FLAG
#define CLR_UART1_RX_STATE()    UART1_STATE &= ~RX_FULL_FLAG
#define CLR_UART1_RFW_STATE()   UART1_STATE &= ~RX_OVERFLOW_FLAG 
#define CLR_UART1_PERR_STATE()  UART1_STATE &= ~PARITY_ERROR_FLAG
#define CLR_UART1_FERR_STATE()  UART1_STATE &= ~FRAME_ERROR_FLAG

#define UART1_TX_INT_ENABLE()   UART1_CON2 |= TX_SEND_INT_EN
#define UART1_TX_INT_DISABLE()  UART1_CON2 &= ~TX_SEND_INT_EN

#define UART1_RX_INT_ENABLE()   UART1_CON2 |= RX_RECEIVE_INT_EN
#define UART1_RX_INT_DISABLE()  UART1_CON2 &= ~RX_RECEIVE_INT_EN

#define UART1_INT_ENABLE()		IEN2 |= 0x08   /* enable interrupt */
#define UART1_INT_DISABLE()		IEN2 &= ~0x08  /* disable interrupt */
#define UART1_IPL_SET(x)        IPL2 &= ~0x08;IPL2 |= (x<<3)  /* set interrupt priority */



/* function declarations */
/* uart_baudrate_config */
void uart_baudrate_config(UART_PORT_enum uart_port,uint32_t baudrate);

/* uart send byte */
void uart_tx_byte(UART_PORT_enum uart_port,uint8_t dat);
/* uart receive byte */
uint8_t uart_rx_byte(UART_PORT_enum uart_port);

#endif