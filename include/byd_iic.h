/*!
    \file  byd_iic.h
    \brief iic define
*/

/*
    Copyright (C) 2020 BYD

    2020-07-15, V1.0.0, app for byd
*/

#ifndef BYD_IIC_H
#define	BYD_IIC_H

#include "mcu02_iic.h"

#define IIC_RD_SCL_LOCK_EN   0 //主机读操作时是否拉低时钟线 0 不拉低 1 拉低

/* variable declarations */


/* function declarations */
void iic_config(void);
void iic_isr_func(void);


#endif