/*!
    \file  main.h
    \brief main define
*/

/*
    Copyright (C) 2020 BYD

    2020-07-22, V1.0.0, firmware for mcu02
*/

#ifndef MAIN_H
#define	MAIN_H

#include <absacc.h>
#include "byd_init.h"
#include "byd_ctk.h"
#include "byd_sm4.h"
#include "byd_adc.h"
#include "byd_led.h"
#include "byd_spi_flash.h"
#include "byd_mifare.h"
#include "iso14443.h"
#include "byd_idle.h"
#include "byd_eeprom.h"
#include "bydmcu_libopt.h"

/* variable declarations */


#define SYS_CLOCK_SEL  SYS_CLK_12M
//#define SYS_CLOCK_SEL  SYS_CLK_8M
//#define SYS_CLOCK_SEL  SYS_CLK_4M
//#define SYS_CLOCK_SEL  SYS_CLK_1M

#endif
