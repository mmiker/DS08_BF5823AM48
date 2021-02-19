/*!
    \file  mcu02_csd.c
    \brief csd driver
*/

/*
    Copyright (C) 2020 BYD

    2020-05-08, V1.0.0, firmware for mcu02
*/

#include "mcu02_csd.h"
#include "mcu02_gpio.h"
#include "mcu02_system.h"

/*!
    \brief      csd_init
    \param[in]	csd_initpara : csd init parameter
    \param[out] none
    \retval     none
*/
void csd_init(csd_parameter_struct csd_initpara)
{
/* csd register config*/    
    CSD_VTH_SET(csd_initpara.vth);		                /* vth select */	
	CSD_DS_SET(csd_initpara.ds);			            /* detect speed select */
	CSD_PRE_CHARGE_SET(csd_initpara.pre_charge);	    /* pre charge select time us*/
	CSD_PRE_DISCHARGE_SET(csd_initpara.pre_discharge);	/* pre discharge select time us*/
	CSD_SW_CLK_SET(csd_initpara.sw_clk_off);		    /* enable or disable sw_clk */
	CSD_PARALLELMODE_SET(csd_initpara.parallel);        /* enable or disable sns parallel */
	CSD_RB_SET(csd_initpara.rb);			            /* rb select */
	CSD_RESO_SET(csd_initpara.reso);			        /* reso select */
	CSD_PRS_DIV_SET(csd_initpara.pre_div);		        /* pre select */
	
	
	CSD_LP_EN_SET(csd_initpara.csd_lowpower);	
	CSD_ENABLE();
	CSD_SCAN_STOP;

/* csd interrupt config*/ 
	INT_CSD_CLR();

	if(csd_initpara.int_status == ENABLE)
	{
	    CSD_IPL_SET(csd_initpara.int_prio);
		CSD_INT_ENABLE();
	}
	else
	{
		CSD_INT_DISABLE();
	}
}

/*!
    \brief      enable csd sensor
    \param[in]	sensor_addr:0~11,16~47
    \param[out] none
    \retval     none
*/
void csd_sensor_enable(uint8_t sensor_addr)
{
    uint32_t sensor_en;

	if(sensor_addr<32)
		sensor_en = ((uint32_t)0x01<<sensor_addr);
	else
	    sensor_en = ((uint32_t)0x01<<(sensor_addr-32));    

	if(sensor_addr>=32)
	{
	    REG_ADDR = SNS_IO_SEL5;REG_DATA |= ((sensor_en)&0xFF);
        REG_ADDR = SNS_IO_SEL6;REG_DATA |= ((sensor_en>>8)&0xFF);
	    
		if(sensor_addr < 36)
			TRISA |= ((sensor_en) & 0x0F);
		else if(sensor_addr < 38)
	    	TRISB |= ((sensor_en >> 4) & 0x03);
		else if(sensor_addr < 44)
		{
			if(sensor_addr==42 || (sensor_addr==43))
		  		TRISC |= ((sensor_en >> 4) & 0xCF);
			else
		  		TRISC |= ((sensor_en >> 6) & 0xCF);
		}
		else
	    	TRISE |= ((sensor_en >> 12) & 0x0F);
	
	}
	else
	{
	    REG_ADDR = SNS_IO_SEL1;REG_DATA |= ((sensor_en)&0xFF);
	    REG_ADDR = SNS_IO_SEL2;REG_DATA |= ((sensor_en>>8)&0x0F);
	    REG_ADDR = SNS_IO_SEL3;REG_DATA |= ((sensor_en>>16)&0xFF);
	    REG_ADDR = SNS_IO_SEL4;REG_DATA |= ((sensor_en>>24)&0xFF);//open SNS

	    TRISB |= ((sensor_en << 2)  & 0xFC);
	    TRISC |= ((sensor_en >> 2)  & 0x30);
	    TRISE |= ((sensor_en >> 4)  & 0xF0);
	    TRISF |= ((sensor_en >> 12) & 0xF0);
	    TRISG |= ((sensor_en >> 20) & 0x0F);
	    TRISH |= ((sensor_en >> 24) & 0xFF);//input
	}
}

/*!
    \brief      disable csd sensor
    \param[in]	sensor_addr:0~11,16~47
    \param[out] none
    \retval     none
*/
void csd_sensor_disable(uint8_t sensor_addr)
{
    uint32_t sensor_en;

	if(sensor_addr<32)
		sensor_en = ((uint32_t)0x01<<sensor_addr);
	else
	    sensor_en = ((uint32_t)0x01<<(sensor_addr-32));    

	if(sensor_addr>=32)
	{
	    REG_ADDR = SNS_IO_SEL5;REG_DATA &= ~((sensor_en)&0xFF);
        REG_ADDR = SNS_IO_SEL6;REG_DATA &= ~((sensor_en>>8)&0xFF);	
	}
	else
	{
	    REG_ADDR = SNS_IO_SEL1;REG_DATA &= ~((sensor_en)&0xFF);
	    REG_ADDR = SNS_IO_SEL2;REG_DATA &= ~((sensor_en>>8)&0x0F);
	    REG_ADDR = SNS_IO_SEL3;REG_DATA &= ~((sensor_en>>16)&0xFF);
	    REG_ADDR = SNS_IO_SEL4;REG_DATA &= ~((sensor_en>>24)&0xFF);
	}
}

/*!
    \brief      disable all csd sensor
    \param[in]	none
    \param[out] none
    \retval     none
*/
void csd_sensor_disable_all(void)
{
    REG_ADDR = SNS_IO_SEL1;REG_DATA = 0;
    REG_ADDR = SNS_IO_SEL2;REG_DATA = 0;
    REG_ADDR = SNS_IO_SEL3;REG_DATA = 0;
    REG_ADDR = SNS_IO_SEL4;REG_DATA = 0;
	REG_ADDR = SNS_IO_SEL5;REG_DATA = 0;
    REG_ADDR = SNS_IO_SEL6;REG_DATA = 0;	
}