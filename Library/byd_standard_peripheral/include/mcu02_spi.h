/*!
    \file  mcu02_spi.h
    \brief spi define
*/

/*
    Copyright (C) 2020 BYD

    2020-05-09, V1.0.0, firmware for mcu02
*/

#ifndef MCU02_SPI_H
#define	MCU02_SPI_H

#include "mcu02_sfr.h"
#include "mcu02_system.h"


/* spi device mode define */
#define	SPI_MASTER		(0x01 << 4)
#define	SPI_SLAVE		(0x00)
/* spi clock define */
#define	SYS_CLK_DIVIDE_2	0x00
#define	SYS_CLK_DIVIDE_4	0x01
#define	SYS_CLK_DIVIDE_6	0x02
#define	SYS_CLK_DIVIDE_8	0x03
#define	SYS_CLK_DIVIDE_10	0x04
#define	SYS_CLK_DIVIDE_12	0x05
#define	SYS_CLK_DIVIDE_14	0x06
#define	SYS_CLK_DIVIDE_16	0x07

/* spi duplex define */
#define	FULL_DUPLEX			(0x00)
#define	HALF_DUPLEX			(0x01 << 4)
/* spi endian define */
#define	LSB_FIRST			(0x01 << 1)
#define	MSB_FIRST			(0x00)
/* spi clock polarity define */
#define	CPOL_HIGH			(0x01 << 3)
#define	CPOL_LOW			(0x00)
/* spi clock phase define */
#define	SPI_CPHA_2Edge		(0x01 << 2)
#define SPI_CPHA_1Edge		(0x00)
/* spi communication mode define */
#define	SPI_HIGH_SPEED		(0x01 << 5)	
/* spi interrupt enable define */
#define	SPI_RX_INT_EN		(0x01 << 7)
#define	SPI_TX_INT_EN 		(0x01 << 5)

/* spi interrupt flag define */
#define	SPI_INT_TX_EMPTY	(0x01)
#define	SPI_RX_OVERFLOW		(0x01 << 1)
#define	SPI_INT_RX_FULL		(0x01 << 2)
/* spi half_duplex direct define */
#define	SPI_HALF_DUPLEX_TX	(0x01 << 3)
#define	SPI_HALF_DUPLEX_RX	(0x00)

/* spi cs define */
#define SPI_CS_N			(0x01)


#define SPI_DEVICE_MODE(x)   SPI1_CFG1 &= ~0x10;SPI1_CFG1 |= (x)
#define SPI_PRESCALE_SET(x)  SPI1_CFG2 &= ~0x07;SPI1_CFG2 |= (x)
#define SPI_DUPLEX_SET(x)    SPI1_CFG2 &= ~0x10;SPI1_CFG2 |= (x)
#define SPI_ENDIAN_SET(x)    SPI1_CFG1 &= ~0x02;SPI1_CFG1 |= (x)
#define SPI_CPOL_SET(x)      SPI1_CFG1 &= ~0x08;SPI1_CFG1 |= (x)
#define SPI_CPHA_SET(x)      SPI1_CFG1 &= ~0x04;SPI1_CFG1 |= (x)

#define SPI_TRANSFER_SET(x)  SPI1_CFG2 &= ~0x08;SPI1_CFG2 |= (x)/* x=SPI_HALF_DUPLEX_TX or SPI_HALF_DUPLEX_RX*/


#define SPI_TX_INT_ENABLE()   SPI1_CFG1 |= SPI_TX_INT_EN
#define SPI_TX_INT_DISABLE()  SPI1_CFG1 &= ~SPI_TX_INT_EN

#define SPI_RX_INT_ENABLE()   SPI1_CFG1 |= SPI_RX_INT_EN
#define SPI_RX_INT_DISABLE()  SPI1_CFG1 &= ~SPI_RX_INT_EN

#define SPI_INT_ENABLE()	 IEN2 |= 0x20   /* enable interrupt */
#define SPI_INT_DISABLE()	 IEN2 &= ~0x20  /* disable interrupt */
#define SPI_IPL_SET(x)       IPL2 &= ~0x20;IPL2 |= (x<<5)  /* set interrupt priority */

#define SPI_ENABLE()	 	 SPI1_CFG1 |= 0x40   /* enable spi */
#define SPI_DISABLE()	 	 SPI1_CFG1 &= ~0x40  /* disable spi */


/* high speed mode enum */
typedef enum
{
	FULL_DUPLEX_MODE,	/* full duplex mode */
	HALF_DUPLEX_TX,		/* half duplex tx mode , not receive */
	HALF_DUPLEX_RX		/* half duplex rx mode , not transmit */
}HIGH_SPEED_MODE_enum;

/* function declarations */

/* spi send and receive a byte */
uint8_t spi_sendbyte(uint8_t dat);

/* spi high speed communication */
void spi_high_speed_comm(uint16_t tx_addr,uint16_t rx_addr,uint16_t comm_num,HIGH_SPEED_MODE_enum high_mode);
/* wait for spi high speed communication complete */
ErrStatus wait_spi_high_comm_end(void);

#endif