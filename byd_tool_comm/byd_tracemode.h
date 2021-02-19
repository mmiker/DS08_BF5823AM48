/*!
    \file  byd_tracemode.h
    \brief tracemode define
*/

/*
    Copyright (C) 2020 BYD

    2020-05-18, V1.0.0, api for byd
*/

#ifndef BYD_TRACEMODE_H
#define	BYD_TRACEMODE_H

#include "mcu02_sfr.h"

#define IIC_RD_SCL_SEL  0//0：读拉低；1 ：读不拉低通信方式

void byd_tracemode_init(uint8_t iic_slaveaddr,uint8_t iic_port);
void byd_tracemode_read(void);
void byd_tracemode_write(void);
void byd_tracemode_isr(void);

#endif