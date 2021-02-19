/*!
    \file  mcu02_lvdt.h
    \brief lvdt define
*/

/*
    Copyright (C) 2020 BYD

    2020-07-20, V1.0.0, firmware for mcu02
*/

#ifndef MCU02_LVDT_H
#define	MCU02_LVDT_H

#include "mcu02_system.h"

#define INT_VOL_DOWN_FLAG  		0x02
#define INT_VOL_UP_FLAG    		0x01

#define LVDT_INT_DOWN_FLAG_CLR 	INT_POBO_STAT &= ~0x01		/* clear voltage down interrupt flag */
#define LVDT_INT_UP_FLAG_CLR 	INT_POBO_STAT &= ~0x02		/* clear voltage up interrupt flag */

#define LVDT_ENABLE()           REG_ADDR = PD_ANA;REG_DATA &= ~(0x40)/* enable detect voltage*/
#define LVDT_DISABLE()          REG_ADDR = PD_ANA;REG_DATA |= (0x40)/* disable detect voltage*/

#define LVDT_VOL_SET(x) 	    REG_ADDR = SEL_LVDT_VTH;REG_DATA = x;/* set voltage detect value */

#define GET_INT_LVDT_FLAG_STATE(x)  (INT_POBO_STAT & x)

#define LVDT_INT_ENABLE()		IEN2 |= 0x02   /* enable interrupt */
#define LVDT_INT_DISABLE()	    IEN2 &= ~0x02  /* disable interrupt */
#define LVDT_IPL_SET(x)         IPL2 &= ~0x02;IPL2 |= (x<<1)  /* set interrupt priority */ 

/* function declarations */
extern u16 volL; /* 0:电压低;1:电压正常 */
/* lvdt init */
void lvdt_init(uint8_t vth_sel);//电压检测初始化
void lvdt_VolT(void);//电压检测


#endif