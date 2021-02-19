/*!
    \file  mcu02_wdt.c
    \brief wdt driver
*/

/*
    Copyright (C) 2020 BYD

    2020-05-09, V1.0.0, firmware for mcu02
*/

#include "mcu02_wdt.h"
#include "mcu02_system.h"


/*!
    \brief      wdt_init
    \param[in]  wdt_time:WDT_TIME_xMS						
    \param[out] none
    \retval     none
*/
void wdt_init(WDT_TIME_enum wdt_time)
{	
	WDT_CTRL = wdt_time;	
}
