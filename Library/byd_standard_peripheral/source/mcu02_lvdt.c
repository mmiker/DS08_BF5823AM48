/*!
    \file  mcu02_lvdt.c
    \brief lvdt driver
*/

/*
    Copyright (C) 2020 BYD

    2020-07-20, V1.0.0, firmware for mcu02
*/

#include "mcu02_lvdt.h"

/*!
    \brief      lvdt init
    \param[in]  vth_sel:
	            		0 : 2.7v
						1 : 3v
						2 :	3.8v
						3 :	4.2v				
    \param[out] none
    \retval     none
*/
void lvdt_init(uint8_t vth_sel)
{	
	LVDT_VOL_SET(vth_sel);
    LVDT_INT_DOWN_FLAG_CLR;//清除中断标志位
	LVDT_INT_UP_FLAG_CLR;
	LVDT_IPL_SET(LOW);
	LVDT_INT_ENABLE();
	LVDT_ENABLE();	
}
