/*!
    \file  mcu02_led.c
    \brief led driver
*/

/*
    Copyright (C) 2020 BYD

    2020-07-22, V1.0.0, firmware for mcu02
*/

#include "mcu02_led.h"


/*!
    \brief      led matrix
    \param[in]  com:0~7
	\param[in]  seg:0~0xff
    \param[out] none
    \retval     none
*/
void led_arr_data(uint8_t com,uint8_t seg)
{
	 XBYTE[0x1000+com] = seg;
}

