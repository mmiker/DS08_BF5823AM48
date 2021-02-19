/*!
    \file  mcu02_clock.h
    \brief clock define
*/

/*
    Copyright (C) 2020 BYD

    2020-05-11, V1.0.0, firmware for mcu02
*/

#ifndef	MCU02_CLOCK_H
#define	MCU02_CLOCK_H

#include "mcu02_sfr.h"

/* system clock define */
#define	SYS_CLK_1M			7	/*!< system select as 1Mhz */
#define	SYS_CLK_4M			6	/*!< system select as 4Mhz */
#define	SYS_CLK_8M			5	/*!< system select as 8Mhz */
#define	SYS_CLK_12M			4	/*!< system select as 12Mhz */

#define SYS_CLK_ON          SYS_CLK_CFG &= ~(0x01)
#define SYS_CLK_OFF         SYS_CLK_CFG |= 0x01

/* variable declarations */


/* function declarations */
/* system clock select */
void clock_config(uint8_t sys_clock_sel);
uint8_t get_clock_freq(void);

#endif