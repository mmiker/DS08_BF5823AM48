/*!
    \file  mcu02_clock.c
    \brief clock driver
*/

/*
    Copyright (C) 2018 BYD

    2020-03-31, V1.0.0, firmware for mcu02
*/

#include "mcu02_clock.h"

/*!
    \brief      sys clock select
    \param[in]  sys_clock_sel: system clock select Mhz
						SYS_CLK_1M:	system 1Mhz
						SYS_CLK_4M:	system 4Mhz
						SYS_CLK_8M:	system 8Mhz
						SYS_CLK_12M: system 12Mhz
    \param[out] none
    \retval     none
*/
void clock_config(uint8_t sys_clock_sel)
{
	SYS_CLK_CFG &= ~(0x0e);
	SYS_CLK_CFG |= (0x0E&(sys_clock_sel<<1));
	SYS_CLK_ON;	
} 
/*!
    \brief      get sys clock
    \param[in]  none
    \param[out] none
    \retval     none
*/
uint8_t get_clock_freq(void)
{
   	uint8_t sys_clock;

	sys_clock = (SYS_CLK_CFG & 0x0e)>>1;

	if(SYS_CLK_12M == sys_clock)
	{
	   return SYS_CLK_12M;
	}
	else if(SYS_CLK_8M == sys_clock)
	{
		return SYS_CLK_8M;
	}
	else if(SYS_CLK_4M == sys_clock)
	{
		return SYS_CLK_4M;
	}
	else
	{
		return SYS_CLK_1M;
	}
}
