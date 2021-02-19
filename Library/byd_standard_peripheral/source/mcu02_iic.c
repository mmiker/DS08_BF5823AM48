/*!
    \file  mcu02_iic.c
    \brief iic driver
*/

/*
    Copyright (C) 2020 BYD

    2020-07-15, V1.0.0, firmware for mcu02
*/
#include "mcu02_iic.h"


/*!
    \brief      iic port select
    \param[in]  port_select : select PC4/PC5 or PE4/PE5 as iic port
		  \arg      GPIO_PC4_PC5 or GPIO_PE4_PE5
    \param[out] none
    \retval     none
*/
void iic_port_select(uint8_t port_select)
{
    REG_ADDR = PERIPH_IO_SEL1;		
	if(port_select == GPIO_PC4_PC5){		
		REG_DATA &= ~0x10;
	}else if(port_select == GPIO_PE4_PE5){
		REG_DATA |= 0x10;
	}
}

