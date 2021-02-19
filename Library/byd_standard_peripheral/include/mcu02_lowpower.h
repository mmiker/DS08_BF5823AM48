/*!
    \file  mcu02_lowpower.h
    \brief lowpower define
*/

/*
    Copyright (C) 2020 BYD

    2020-08-05, V1.0.0, firmware for mcu02
*/

#ifndef MCU02_LOWPOWER_H
#define	MCU02_LOWPOWER_H

#include "mcu02_sfr.h"


/* function declarations */
void lowpower_idle(void);
void lowpower_wait(void);

#endif