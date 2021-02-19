/*!
    \file  mcu02_exint.h
    \brief sfr define
*/

/*
    Copyright (C) 2020 BYD

    2020-09-08, V1.0.0, firmware for mcu02
*/
#ifndef MCU02_EXINT_H
#define MCU02_EXINT_H

#include "mcu02_system.h"
#include "mcu02_gpio.h"

/* set int0 definitions */
#define INT0_0_PH0_CONFIG(x) {SET_PH0_IO_IN;REG_ADDR = PERIPH_IO_SEL2;REG_DATA &= ~(0x01);REG_DATA |= (0x01&(x<<0));}/*function 1:int; 0:io*/ 
#define INT0_1_PH1_CONFIG(x) {SET_PH1_IO_IN;REG_ADDR = PERIPH_IO_SEL2;REG_DATA &= ~(0x02);REG_DATA |= (0x02&(x<<1));}/*function 1:int; 0:io*/  
#define INT0_2_PH2_CONFIG(x) {SET_PH2_IO_IN;REG_ADDR = PERIPH_IO_SEL2;REG_DATA &= ~(0x04);REG_DATA |= (0x04&(x<<2));}/*function 1:int; 0:io*/  
#define INT0_3_PH3_CONFIG(x) {SET_PH3_IO_IN;REG_ADDR = PERIPH_IO_SEL2;REG_DATA &= ~(0x08);REG_DATA |= (0x08&(x<<3));}/*function 1:int; 0:io*/  
#define INT0_4_PH4_CONFIG(x) {SET_PH4_IO_IN;REG_ADDR = PERIPH_IO_SEL2;REG_DATA &= ~(0x10);REG_DATA |= (0x10&(x<<4));}/*function 1:int; 0:io*/  
#define INT0_5_PH5_CONFIG(x) {SET_PH5_IO_IN;REG_ADDR = PERIPH_IO_SEL2;REG_DATA &= ~(0x20);REG_DATA |= (0x20&(x<<5));}/*function 1:int; 0:io*/  
#define INT0_6_PH6_CONFIG(x) {SET_PH6_IO_IN;REG_ADDR = PERIPH_IO_SEL2;REG_DATA &= ~(0x40);REG_DATA |= (0x40&(x<<6));}/*function 1:int; 0:io*/  
#define INT0_7_PH7_CONFIG(x) {SET_PH7_IO_IN;REG_ADDR = PERIPH_IO_SEL2;REG_DATA &= ~(0x80);REG_DATA |= (0x80&(x<<7));}/*function 1:int; 0:io*/ 
#define INT0_8_PB0_CONFIG(x) {SET_PB0_IO_IN;REG_ADDR = PERIPH_IO_SEL1;REG_DATA &= ~(0x01);REG_DATA |= (0x01&(x<<0));}/*function 1:int; 0:io*/  

/* set int0 interrupt */
#define INT0_ENABLE()    IEN0 |= 0x01   /* enable interrupt */
#define INT0_DISABLE()	 IEN0 &= ~0x01  /* disable interrupt */

/* set int0 interrupt priority */
#define INT0_IPL_SET(x) 	IPL0 &= ~0x01;IPL0 |= (x)/*1 :high priority; 0:low priority*/

/* set int0 trigge mode */
#define INT0_0_7_TRIGGER_SET(x) {REG_ADDR = EXT_INT_CON2;REG_DATA &= ~(0x03);REG_DATA |= (x);}/* set int0_0~7 trigge mode: 0 EXTI_TRIG_BOTH;  1 EXTI_TRIG_FALLING; 2 EXTI_TRIG_RISING*/
#define INT0_8_TRIGGER_SET(x)   {REG_ADDR = EXT_INT_CON1;REG_DATA &= ~(0x03);REG_DATA |= (x);}/* set int0_8 trigge mode: 0 EXTI_TRIG_BOTH;  1 EXTI_TRIG_FALLING; 2 EXTI_TRIG_RISING*/

/* get int0 flag status definitions */
#define GET_INT0_8_FLAG_STATE()      	 (INT_PE_STAT & (0x01 << 5))
#define GET_INT0_0_7_FLAG_STATE(x)       (EXINT_STAT & (0x01 << x) )

/* clear int0 flag status definitions */
#define INT0_0_7_FLAG_CLR(x)    EXINT_STAT  &= ~(0x01<<x)
#define INT0_8_FLAG_CLR()       INT_PE_STAT &= ~0x20

/* set int1 definitions */
#define INT1_PB1_CONFIG(x) {SET_PB1_IO_IN;REG_ADDR = PERIPH_IO_SEL1;REG_DATA &= ~(0x02);REG_DATA |= (0x02&(x<<1));}/*function 1:int; 0:io*/ 
/* set int1 interrupt */
#define INT1_ENABLE()       IEN0 |= 0x04   /* enable interrupt */
#define INT1_DISABLE()	    IEN0 &= ~0x04  /* disable interrupt */
/* set int1 interrupt priority */
#define INT1_IPL_SET(x) 	IPL0 &= ~0x04;IPL0 |= (x<<2)/*1 :high priority; 0:low priority*/
/* set int1 trigge mode */
#define INT1_TRIGGER_SET(x) {REG_ADDR = EXT_INT_CON1;REG_DATA &= ~(0x0C);REG_DATA |= (x<<2);}/* 0 EXTI_TRIG_BOTH;  1 EXTI_TRIG_FALLING; 2 EXTI_TRIG_RISING*/
/* get int1 flag status definitions */
#define GET_INT1_FLAG()     (TCON&0x08)


/* set int2 definitions */
#define INT2_PB2_CONFIG(x) {SET_PB2_IO_IN;REG_ADDR = PERIPH_IO_SEL1;REG_DATA &= ~(0x04);REG_DATA |= (0x04&(x<<2));}/*function 1:int; 0:io*/ 
/* set int2 interrupt */
#define INT2_ENABLE()       IEN1 |= 0x04   /* enable interrupt */
#define INT2_DISABLE()	    IEN1 &= ~0x04  /* disable interrupt */
/* set int2 interrupt priority */
#define INT2_IPL_SET(x) 	IPL1 &= ~0x04;IPL1 |= (x<<2)/*1 :high priority; 0:low priority*/
/* set int2 trigge mode */
#define INT2_TRIGGER_SET(x) {REG_ADDR = EXT_INT_CON1;REG_DATA &= ~(0x30);REG_DATA |= (x<<4);}/* 0 EXTI_TRIG_BOTH;  1 EXTI_TRIG_FALLING; 2 EXTI_TRIG_RISING*/

/* set int3 definitions */
#define INT3_PB3_CONFIG(x) {SET_PB3_IO_IN;REG_ADDR = PERIPH_IO_SEL1;REG_DATA &= ~(0x08);REG_DATA |= (0x08&(x<<3));}/*function 1:int; 0:io*/ 
/* set int3 interrupt */
#define INT3_ENABLE()       IEN2 |= 0x40   /* enable interrupt */
#define INT3_DISABLE()	    IEN2 &= ~0x40  /* disable interrupt */
/* set int3 interrupt priority */
#define INT3_IPL_SET(x) 	IPL2 &= ~0x40;IPL2 |= (x<<6)/*1 :high priority; 0:low priority*/
/* set int3 trigge mode */
#define INT3_TRIGGER_SET(x) {REG_ADDR = EXT_INT_CON1;REG_DATA &= ~(0xC0);REG_DATA |= (x<<6);}/* 0 EXTI_TRIG_BOTH;  1 EXTI_TRIG_FALLING; 2 EXTI_TRIG_RISING*/

/* set int4 definitions */
#define INT4_07_PE4_CONFIG(x) {SET_PE4_IO_IN;REG_ADDR = PERIPH_IO_SEL3;REG_DATA &= ~(0x80);REG_DATA |= (0x80&(x<<7));}/*function 1:int; 0:io*/  
#define INT4_08_PE5_CONFIG(x) {SET_PE5_IO_IN;REG_ADDR = PERIPH_IO_SEL4;REG_DATA &= ~(0x01);REG_DATA |= (0x01&(x));}   /*function 1:int; 0:io*/
#define INT4_09_PE6_CONFIG(x) {SET_PE6_IO_IN;REG_ADDR = PERIPH_IO_SEL4;REG_DATA &= ~(0x02);REG_DATA |= (0x02&(x<<1));}/*function 1:int; 0:io*/
#define INT4_10_PE7_CONFIG(x) {SET_PE7_IO_IN;REG_ADDR = PERIPH_IO_SEL4;REG_DATA &= ~(0x04);REG_DATA |= (0x04&(x<<2));}/*function 1:int; 0:io*/
#define INT4_15_PF4_CONFIG(x) {SET_PF4_IO_IN;REG_ADDR = PERIPH_IO_SEL4;REG_DATA &= ~(0x80);REG_DATA |= (0x80&(x<<7));}/*function 1:int; 0:io*/
#define INT4_16_PF5_CONFIG(x) {SET_PF5_IO_IN;REG_ADDR = PERIPH_IO_SEL5;REG_DATA &= ~(0x01);REG_DATA |= (0x01&(x));}   /*function 1:int; 0:io*/
#define INT4_17_PF6_CONFIG(x) {SET_PF6_IO_IN;REG_ADDR = PERIPH_IO_SEL5;REG_DATA &= ~(0x02);REG_DATA |= (0x02&(x<<1));}/*function 1:int; 0:io*/
#define INT4_18_PF7_CONFIG(x) {SET_PF7_IO_IN;REG_ADDR = PERIPH_IO_SEL5;REG_DATA &= ~(0x04);REG_DATA |= (0x04&(x<<2));}/*function 1:int; 0:io*/
#define INT4_19_PG0_CONFIG(x) {SET_PG0_IO_IN;REG_ADDR = PERIPH_IO_SEL5;REG_DATA &= ~(0x08);REG_DATA |= (0x08&(x<<3));}/*function 1:int; 0:io*/
#define INT4_20_PG1_CONFIG(x) {SET_PG1_IO_IN;REG_ADDR = PERIPH_IO_SEL5;REG_DATA &= ~(0x10);REG_DATA |= (0x10&(x<<4));}/*function 1:int; 0:io*/
#define INT4_21_PG2_CONFIG(x) {SET_PG2_IO_IN;REG_ADDR = PERIPH_IO_SEL5;REG_DATA &= ~(0x20);REG_DATA |= (0x20&(x<<5));}/*function 1:int; 0:io*/
#define INT4_22_PG3_CONFIG(x) {SET_PG3_IO_IN;REG_ADDR = PERIPH_IO_SEL5;REG_DATA &= ~(0x40);REG_DATA |= (0x40&(x<<6));}/*function 1:int; 0:io*/

/* set int4 interrupt */
#define INT4_ENABLE()       IEN2 |= 0x80   /* enable interrupt */
#define INT4_DISABLE()	    IEN2 &= ~0x80  /* disable interrupt */
/* set int4 interrupt priority */
#define INT4_IPL_SET(x) 	IPL2 &= ~0x80;IPL2 |= (x<<7)/*1 :high priority; 0:low priority*/
/* set int4 trigge mode */
#define INT4_TRIGGER_SET(x) {REG_ADDR = EXT_INT_CON2;REG_DATA &= ~(0x04);REG_DATA |= (x<<2);}/* 0 EXTI4_TRIG_FALLING; 1 EXTI4_TRIG_RISING*/

#define EXTI4_TRIG_FALLING  0
#define EXTI4_TRIG_RISING   1

/* exti port  definitions */
typedef enum
{
	EXTI_INT0_0 = 0,		/* exti on PH0 */     
	EXTI_INT0_1 ,			/* exti on PH1 */     
	EXTI_INT0_2 ,	 		/* exti on PH2 */     
	EXTI_INT0_3 ,	 		/* exti on PH3 */     
	EXTI_INT0_4 ,	 		/* exti on PH4 */     
	EXTI_INT0_5 ,	 		/* exti on PH5 */     
	EXTI_INT0_6 ,	 		/* exti on PH6 */     
	EXTI_INT0_7 ,	 		/* exti on PH7 */     
	EXTI_INT0_8 ,	 		/* exti on PB0 */     
	EXTI_INT1   ,	 		/* exti on PB1 */     
	EXTI_INT2   ,	 		/* exti on PB2 */     
	EXTI_INT3   ,	 		/* exti on PB3 */     
	NONE_0 ,	 			/* none */     
	NONE_1 ,	 			/* none */     
	NONE_2 ,	 			/* none */     
	NONE_3 ,	 			/* none */     
	NONE_4 ,	 			/* none */     
	NONE_5 ,	 			/* none */     
	NONE_6 ,	 			/* none */     
	EXTI_INT4_7 ,	 		/* exti on PE4 */     
	EXTI_INT4_8 ,	 		/* exti on PE5 */     
	EXTI_INT4_9 ,	 		/* exti on PE6 */     
	EXTI_INT4_10,	 		/* exti on PE7 */     
	NONE_11,	 			/* none */     
	NONE_12,	 			/* none */     
	NONE_13,	 			/* none */     
	NONE_14,	 			/* none */     
	EXTI_INT4_15,	 		/* exti on PF4 */     
	EXTI_INT4_16,	 		/* exti on PF5 */     
	EXTI_INT4_17,	 		/* exti on PF6 */     
	EXTI_INT4_18,	 		/* exti on PF7 */     
	EXTI_INT4_19,	 		/* exti on PG0 */     
	EXTI_INT4_20,	 		/* exti on PG1 */     
	EXTI_INT4_21,	 		/* exti on PG2 */     
	EXTI_INT4_22,	 		/* exti on PG3 */    
}EXTI_PORT_enum;

typedef enum
{
    INT0_0_PH0_FLAG = 0,
	INT0_1_PH1_FLAG,
	INT0_2_PH2_FLAG,
	INT0_3_PH3_FLAG,
	INT0_4_PH4_FLAG,
	INT0_5_PH5_FLAG,
	INT0_6_PH6_FLAG,
	INT0_7_PH7_FLAG

}EXTI0_7_FLAG_enum;


/* exti0~3 trigger mode */
typedef enum
{
	EXTI_TRIG_BOTH = 0   , 		/* rising and falling trigger */
	EXTI_TRIG_FALLING = 1, 		/* falling trigger */
	EXTI_TRIG_RISING = 2  		/* rising edge trigger */
}EXTI_TRIG_enum;

/* function declarations */
/* exti init */
void exti_init(EXTI_PORT_enum int_port,EXTI_TRIG_enum trigger,ControlStatus status,IntPrioStatus prio);


#endif