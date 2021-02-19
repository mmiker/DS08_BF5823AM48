/*!
    \file  byd_init.h
    \brief byd_init define
*/

/*
    Copyright (C) 2020 BYD

    2020-05-09, V1.0.0, app for byd
*/

#ifndef BYD_INIT_H
#define	BYD_INIT_H

#include "mcu02_clock.h"
#include "delay.h"

#define SYS_CLOCK_SEL  SYS_CLK_12M
//#define SYS_CLOCK_SEL  SYS_CLK_8M
//#define SYS_CLOCK_SEL  SYS_CLK_4M
//#define SYS_CLOCK_SEL  SYS_CLK_1M

#define BYD_CTK_EN     0	//按键检测功能使能
#define TRACEMODE_EN   0	//使用byd工具调试模式使能

#define MIFARE_EN      1

/* function declarations */
void byd_init(void);


#endif