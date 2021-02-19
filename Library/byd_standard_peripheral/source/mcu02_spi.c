/*!
    \file  mcu02_spi.c
    \brief spi driver
*/

/*
    Copyright (C) 2020 BYD

    2020-05-10, V1.0.0, firmware for mcu02
*/

#include "mcu02_spi.h"

/*!
    \brief      spi high speed communication
    \param[in]  tx_addr: spi transmit data addr 
				rx_addr: spi save receive data addr
				comm_num: spi communication byte number	
    \param[out] none
    \retval     none
*/
void spi_high_speed_comm(uint16_t tx_addr,uint16_t rx_addr,uint16_t comm_num,HIGH_SPEED_MODE_enum high_mode)
{
	uint8_t tx_addr_buff = (tx_addr >> 4);
	uint8_t rx_addr_buff = (rx_addr >> 4);
	
    REG_ADDR = SPI1_TX_START_ADDR;
	REG_DATA = tx_addr_buff;

	REG_ADDR = SPI1_RX_START_ADDR;
	REG_DATA = rx_addr_buff;

	REG_ADDR = SPI1_NUM_L;
	REG_DATA = (uint8_t)comm_num;

	REG_ADDR = SPI_NUM_H;
	REG_DATA = ((comm_num >> 8) & 0x0f);

	if(FULL_DUPLEX_MODE==high_mode)
	{
		SPI1_CFG2 &= ~HALF_DUPLEX;
	}
	else if(HALF_DUPLEX_TX==high_mode)
	{
		SPI1_CFG2 |= HALF_DUPLEX;
		SPI1_CFG2 |= SPI_HALF_DUPLEX_TX;
	}
	else if(HALF_DUPLEX_RX==high_mode)
	{
		SPI1_CFG2 |= HALF_DUPLEX;
		SPI1_CFG2 &= ~SPI_HALF_DUPLEX_TX;
	}
	SPI1_CFG1 &= ~SPI_CS_N;
	SPI1_CFG2 |= SPI_HIGH_SPEED;

}

/*!
    \brief      wait spi high speed communication complete
    \param[in]  none
    \param[out] none
    \retval     SUCCESS or ERROR
*/
ErrStatus wait_spi_high_comm_end(void)
{	
	while(SPI1_CFG2 & SPI_HIGH_SPEED);
	while((SPI1_STATE & SPI_INT_TX_EMPTY) == 0x00);
	SPI1_CFG1 |= SPI_CS_N;
	SPI1_CFG2 &= ~HALF_DUPLEX;
	return SUCCESS;
}

/*!
    \brief      spi send and receive a byte
    \param[in]  dat: send data
    \param[out] none
    \retval     receive data
*/
uint8_t spi_sendbyte(uint8_t dat)
{	
	while((SPI1_STATE & SPI_INT_TX_EMPTY) == 0x00);
	SPI1_SPID = dat;
	while((SPI1_STATE & SPI_INT_RX_FULL) == 0x00);
	dat = SPI1_SPID;
	SPI1_STATE &= ~SPI_INT_RX_FULL;
	return dat;
}


