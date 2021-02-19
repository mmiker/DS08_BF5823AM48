/*!
    \file  mcu02_timer.h
    \brief timer define
*/

/*
    Copyright (C) 2020 BYD

    2020-07-16, V1.0.0, firmware for mcu02
*/
#ifndef MCU02_TIMER_H
#define	MCU02_TIMER_H

#include "mcu02_sfr.h"

#define TIMER0_ENABLE()  TCON |= 0x10
#define TIMER1_ENABLE()  TCON |= 0x40
#define TIMER2_ENABLE()  TIMER2_CFG |= 0x01
#define TIMER3_ENABLE()  TIMER3_CFG |= 0x01

#define TIMER0_DISABLE()  TCON &= ~0x10
#define TIMER1_DISABLE()  TCON &= ~0x40
#define TIMER2_DISABLE()  TIMER2_CFG &= ~0x01
#define TIMER3_DISABLE()  TIMER3_CFG &= ~0x01

#define GET_TIMER0_MODE() (TMOD & 0x03)
#define GET_TIMER1_MODE() ((TMOD & 0x30)>>4)


/* timer0/timer1 mode define */
#define	TIMER_13BIT				0	/* 8bit timer with 5-bit prescale */
#define	TIMER_16BIT				1	/* 16bit timer */
#define	TIMER_8BIT_AUTORELOAD	2	/* 8bit timer with auto-reload */
#define	TIMER_8BIT				3	/* 8bit timer */

#define TIME_SELECT       		0x00 /*timer mode*/
#define COUNT_SELECT      		0x04 /*count mode*/

/*timer0*/
#define TIMER0_MODE_SET(x)      TMOD &= ~0x03;TMOD |= x
#define TIMER0_CT_MODE_SET(x)   TMOD &= ~0x04;TMOD |= x
#define TIMER0_COUNT_13BIT(x)   {x = 8192-x;TH0 = x>>5;TL0 = x&0x1f;}
#define TIMER0_COUNT_16BIT(x)   {x = 65536-x;TH0 = x>>8;TL0 = x;}
#define TIMER0_COUNT_8BIT(x)    {x = 256-x;TH0 = x;TL0 = x;}			

#define TIMER0_INT_ENABLE()		IEN0 |= 0x02   /* enable interrupt */
#define TIMER0_INT_DISABLE()	IEN0 &= ~0x02  /* disable interrupt */
#define TIMER0_IPL_SET(x)       IPL0 &= ~0x02;IPL0 |= (x<<1)  /* set interrupt priority */        

/*timer1*/
#define TIMER1_MODE_SET(x)      TMOD &= ~0x30;TMOD |= (x<<4)
#define TIMER1_CT_MODE_SET(x)   TMOD &= ~0x40;TMOD |= (x<<6)
#define TIMER1_COUNT_13BIT(x)   {x = 8192-x;TH1 = x>>5;TL1 = x & 0x1f;}		
#define TIMER1_COUNT_16BIT(x)   {x = 65536-x;TH1 = x>>8;TL1 = x;}
#define TIMER1_COUNT_8BIT(x)    {x = 256-x;TH1 = x;TL1 = x;}

#define TIMER1_INT_ENABLE()		IEN0 |= 0x08   /* enable interrupt */
#define TIMER1_INT_DISABLE()	IEN0 &= ~0x08  /* disable interrupt */
#define TIMER1_IPL_SET(x)       IPL0 &= ~0x08;IPL0 |= (x<<3)  /* set interrupt priority */  


/* timer2 clock define */
#define	TIMER2_CLOCK_RC					0	/* select rc as timer2 clock */
#define	TIMER2_CLOCK_XTAL				1	/* select xtal as timer2 clock */

/* timer2 prescale select */
#define	TIMER2_PRESCALE_65536			1	/* select timer2 clock prescale as 65536 */
#define	TIMER2_PRESCALE_1				0	/* select timer2 no clock prescale */

/* timer3 clock define */
#define	TIMER3_CLOCK_DIVIDE_12			0	/* select timer3 24M clock divide by 12 */
#define	TIMER3_CLOCK_DIVIDE_4			1	/* select timer3 24M clock divide by 4 */


/*timer2*/
#define TIMER2_CLOCK_SELECT(x)  TIMER2_CFG &= ~0x04;TIMER2_CFG |= (x<<2)
#define TIMER2_AUTO_RELOAD(x)   TIMER2_CFG &= ~0x02;TIMER2_CFG |= (x<<1)
#define TIMER2_PRESCALE(x)      TIMER2_CFG &= ~0x08;TIMER2_CFG |= (x<<3)       
#define TIMER2_COUNT_SET(x)     TIMER2_SET_H = x>>8;TIMER2_SET_L = x

#define TIMER2_INT_ENABLE()		IEN1 |= 0x80   /* enable interrupt */
#define TIMER2_INT_DISABLE()	IEN1 &= ~0x80  /* disable interrupt */
#define TIMER2_IPL_SET(x)       IPL1 &= ~0x80;IPL1 |= (x<<7)  /* set interrupt priority */        

/*timer3*/
#define TIMER3_CLOCK_DIVIDE(x)  TIMER3_CFG &= ~0x04;TIMER3_CFG |= (x<<2)
#define TIMER3_AUTO_RELOAD(x)   TIMER3_CFG &= ~0x02;TIMER3_CFG |= (x<<1)
#define TIMER3_COUNT_SET(x)     TIMER3_SET_H = x>>8;TIMER3_SET_L = x

#define TIMER3_INT_ENABLE()		IEN2 |= 0x10   /* enable interrupt */
#define TIMER3_INT_DISABLE()	IEN2 &= ~0x10  /* disable interrupt */
#define TIMER3_IPL_SET(x)       IPL2 &= ~0x10;IPL2 |= (x<<4)  /* set interrupt priority */

/* timer enum */
typedef enum
{
	TIMER0 = 0,
	TIMER1,
	TIMER2,
	TIMER3
}TIMER_enum;

/* variable declarations */
extern uint8_t data TH0_reload,TL0_reload;
extern uint8_t data TH1_reload,TL1_reload;

/* function declarations */

/* timer0/timer1 init */
void timer0_1_init(TIMER_enum timer_port);



#endif
