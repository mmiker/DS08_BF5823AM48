/*!
    \file  mcu02_wdt.h
    \brief wdt define
*/

/*
    Copyright (C) 2020 BYD

    2020-07-16, V1.0.0, firmware for mcu02
*/

#ifndef MCU02_WDT_H
#define	MCU02_WDT_H

#include "mcu02_sfr.h"

#define WDT_ENABLE()        WDT_EN = 0xaa
#define WDT_DISABLE()       WDT_EN = 0x55

#define WDT_INT_ENABLE()	IEN1 |= 0x80   /* enable interrupt */
#define WDT_INT_DISABLE()	IEN1 &= ~0x80  /* disable interrupt */
#define WDT_IPL_SET(x)      IPL1 &= ~0x80;IPL1 |= (x<<7)  /* set interrupt priority */  

/* wdt overflow time */
typedef enum
{
	WDT_TIME_18MS   = 0,
	WDT_TIME_36MS   = 1,
	WDT_TIME_72MS   = 2,
	WDT_TIME_144MS  = 3,
	WDT_TIME_288MS  = 4,
	WDT_TIME_576MS  = 5,
	WDT_TIME_1152MS = 6,
	WDT_TIME_2304MS = 7,
}WDT_TIME_enum;


/* function declarations */
/* wdt init */
void wdt_init(WDT_TIME_enum wdt_time);


#endif