/*!
    \file  byd_iic.c
    \brief iic app
*/

/*
    Copyright (C) 2020 BYD

    2020-07-15, V1.0.0, app for byd
*/

#include "byd_iic.h"
#include "byd_init.h"

uint8_t xdata iic_tx_data[5] = {0,0,0,0,0};
uint8_t xdata iic_rx_data[5] = {0x11,0x22,0x33,0x44,0x55};
uint8_t xdata iic_cnt = 0;

/*!
    \brief      iic config
    \param[in]  none
    \param[out] none
    \retval     none
*/
void iic_config(void)
{	
	iic_port_select(GPIO_PE4_PE5);
	SET_PE4_PU_ON;//开启上拉
	SET_PE5_PU_ON;//开启上拉
	SET_PE4_IO_IN;
	SET_PE5_IO_IN;

	IIC_ADDR_SET(iic_slaveaddr);
	IICSTAT = 0;
	IICCON |= IIC_SCLEN;

#if IIC_RD_SCL_LOCK_EN
	IIC_RD_SCL_SET(SCL_LOCK_RD_ENABLE);
#else
	IIC_RD_SCL_SET(SCL_LOCK_RD_DISABLE);
#endif

	IIC_WR_SCL_SET(SCL_LOCK_WR_DISABLE);
	IIC_SR_SET(IIC_400K);

	IIC_AFIL_MODE_SET(IIC_ANALOG_FILTER_ENABLE);
	IIC_DFIL_MODE_SET(IIC_DIGITAL_FILTER_DISABLE);

	INT_IIC_CLR();
	IIC_IPL_SET(HIGH);
	IIC_INT_ENABLE();
	
	IIC_ENABLE();	
}

/*!
    \brief      iic interrupt function example
    \param[in]  none
    \param[out] none
    \retval     none
*/
void iic_isr_func(void)
{
	uint8_t dat;
	
	if(!IIC_AD){

		iic_cnt = 0;

		if(IIC_RW){
#if IIC_RD_SCL_LOCK_EN
			IICBUF = iic_rx_data[iic_cnt];/* master read the first data when iic_config_para.scl_lock_rd_en = SCL_LOCK_RD_ENABLE */
#else
			iic_cnt = 1;
			IICBUFFER = iic_rx_data[iic_cnt];/* master read the second data when iic_config_para.scl_lock_rd_en = SCL_LOCK_RD_DISABLE,
											the first date write to IICBUFFER before interrupt occur */
#endif
			iic_cnt++;
		}else{
			dat = IICBUF;					/* master write the slave address */ 
		}
	}else{
		if(IIC_RW){
#if IIC_RD_SCL_LOCK_EN
				IICBUF = iic_rx_data[iic_cnt];	/* master read the remain data when iic_config_para.scl_lock_rd_en = SCL_LOCK_RD_ENABLE */
#else
				IICBUFFER = iic_rx_data[iic_cnt];/* master read the remain data when iic_config_para.scl_lock_rd_en = SCL_LOCK_RD_DISABLE */
#endif
			iic_cnt++;
		}else{
			iic_tx_data[iic_cnt] = IICBUF;	/* master write data to slave device */
			iic_cnt++;
#if IIC_RD_SCL_LOCK_EN==0
			   IICBUFFER = iic_rx_data[0]; /* first data must ready befor master read when scl_lock_rd_en = SCL_LOCK_RD_DISABLE */
#endif
		}
	}
	IICCON |= IIC_SCLEN;					/* release scl */

	if(IIC_WCOL){					/* iic write conflict */
		IICSTAT &= ~0x02;
	}
	if(IIC_RECOV){					/* iic read conflict */
		IICSTAT &= ~0x01;
		dat = IICBUF;
	}
}

