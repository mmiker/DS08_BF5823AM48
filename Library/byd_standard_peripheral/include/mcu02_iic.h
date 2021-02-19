/*!
    \file  mcu02_iic.h
    \brief iic define
*/

/*
    Copyright (C) 2020 BYD

    2020-07-15, V1.0.0, firmware for mcu02
*/
#ifndef MCU02_IIC_H
#define	MCU02_IIC_H

#include "mcu02_sfr.h"
#include "mcu02_system.h"

/* iic flag define */
#define	IIC_SCLEN				(0x01 << 2)

#define	SCL_LOCK_RD_ENABLE		0x01
#define	SCL_LOCK_RD_DISABLE		0x00
#define	SCL_LOCK_WR_ENABLE		0x01
#define	SCL_LOCK_WR_DISABLE		0x00

/* iic port select define */
#define	GPIO_PC4_PC5			0x00		/* select PC4/PC5 as iic function */
#define	GPIO_PE4_PE5			(0x01 << 4)	/* select PE4/PE5 as iic function */

#define IIC_100K                0x01                  
#define IIC_400K                0x00

#define	IIC_ENABLE()			IICCON |= 0x01
#define	IIC_DISABLE()			IICCON &= 0xfe
#define	IIC_RESET()				IICCON |= 0x20

#define IIC_ADDR_SET(x)         IICADD = x
#define IIC_RD_SCL_SET(x)       IICCON &= ~0x10; IICCON |= (x<<4)
#define IIC_WR_SCL_SET(x)       IICCON &= ~0x08; IICCON |= (x<<3)
#define IIC_SR_SET(x)           IICCON &= ~0x02; IICCON |= (x<<1)

/* iic filter mode */
#define IIC_ANALOG_FILTER_ENABLE    0x01
#define IIC_ANALOG_FILTER_DISABLE   0x00

#define IIC_DIGITAL_FILTER_ENABLE   0x01
#define IIC_DIGITAL_FILTER_DISABLE  0x00

#define IIC_AFIL_MODE_SET(x)        REG_ADDR = IIC_FIL_MODE;REG_DATA &= (~0x02);REG_DATA |= (x<<1)//Ä£ÄâÂË²¨
#define IIC_DFIL_MODE_SET(x)        REG_ADDR = IIC_FIL_MODE;REG_DATA &= (~0x01);REG_DATA |= (x)//Êý×ÖÂË²¨

#define IIC_INT_ENABLE()		IEN1 |= 0x08   /* enable interrupt */
#define IIC_INT_DISABLE()		IEN1 &= ~0x08  /* disable interrupt */
#define IIC_IPL_SET(x)       	IPL1 &= ~0x08;IPL1 |= (x<<3) /* set interrupt priority LOW */


/* function declarations */

/* iic port select */
void iic_port_select(uint8_t port_select);


#endif