/*!
    \file  mcu02_lowpower.c
    \brief lowpower driver
*/

/*
    Copyright (C) 2020 BYD

    2020-05-12, V1.0.0, firmware for mcu02
*/
#include "mcu02_lowpower.h"
/*!
    \brief      idle
    \param[in]  none
    \param[out] none
    \retval     none
*/
void lowpower_idle(void)
{
    PCON |= 0x01;
}
/*!
    \brief      wait
    \param[in]  none
    \param[out] none
    \retval     none
*/
void lowpower_wait(void)
{
    SYS_CLK_CFG |= 0x10;
}
