/*!
    \file  byd_led.h
    \brief led define
*/

/*
    Copyright (C) 2020 BYD

    2020-07-22, V1.0.0, app for byd
*/

#ifndef BYD_LED_H
#define	BYD_LED_H

#include "mcu02_led.h"


#define LED_SCAN_INT_EN         	0//1：中断方式扫描 0：循环扫描

void led_init(void);
void led_work(void);
#endif