/*!
    \file  byd_sm4.h
    \brief sm4 define
*/

/*
    Copyright (C) 2020 BYD

    2020-03-31, V1.0.0, app for byd
*/

#ifndef BYD_SM4_H
#define	BYD_SM4_H

#include "mcu02_sm4.h"

#define SM4_INT_EN             1   /* 1:interrupt; 0:inquiry */

extern volatile bit g_bSm4IntFlag;

void byd_sm4_init(void);
void byd_sm4_work(uint8_t mode,uint8_t *pbuf);

#endif