/*!
    \file  delay.c
    \brief delay app
*/

/*
    Copyright (C) 2018 BYD

    2018-09-13, V1.0.0, app for byd
*/

#include "delay.h"
#include "mcu02_wdt.h"
#include "byd_init.h"

#if SYS_CLOCK_SEL==SYS_CLK_12M

#define DELAY_COUNT  858

#elif SYS_CLOCK_SEL==SYS_CLK_8M

#define DELAY_COUNT  570

#elif SYS_CLOCK_SEL==SYS_CLK_4M

#define DELAY_COUNT  284

#else

#define DELAY_COUNT  67

#endif

/*!
    \brief      delay_us
    \param[in]  us
    \param[out] none
    \retval     none
*/
void delay_us(unsigned int us)
{
	for (; us > 0; us--)
	{	
		WDT_CTRL = 0x07;
	}
}
/*!
    \brief      delay_ms
    \param[in]  ms
    \param[out] none
    \retval     none
*/
void delay_ms(unsigned int ms)
{
	unsigned int a = DELAY_COUNT,b = ms;  
	for (b = ms; b > 0; b--)
	{
		for (a = DELAY_COUNT; a > 0; a--)
		{
			WDT_CTRL = 0x07;
		} 
	}
}