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
#include "mmi_feature.h"

#define SYS_CLOCK_SEL  SYS_CLK_12M
//#define SYS_CLOCK_SEL  SYS_CLK_8M
//#define SYS_CLOCK_SEL  SYS_CLK_4M
//#define SYS_CLOCK_SEL  SYS_CLK_1M

#ifdef BYD_CTK_ENABLE
#define BYD_CTK_EN     1	//������⹦��ʹ��
#else
#define BYD_CTK_EN     0	//������⹦��ʹ��
#endif
#define TRACEMODE_EN   0	//ʹ��byd���ߵ���ģʽʹ��

#ifdef __LOCK_RFID_CARD_SUPPORT__
#define MIFARE_EN      1
#else
#define MIFARE_EN      0
#endif

/* function declarations */
void byd_init(void);


#endif
