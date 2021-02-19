/*!
    \file  mcu02_gpio.h
    \brief gpio define
*/

/*
    Copyright (C) 2020 BYD

    2020-07-10, V1.0.0, firmware for mcu02
*/

#ifndef MCU02_GPIO_H
#define	MCU02_GPIO_H

#include "mcu02_sfr.h"


/**********************PA口**********************/

#define SET_PA0_IO_IN REG_ADDR = PWM_IO_SEL;REG_DATA &= ~0x80;\
					  REG_ADDR = SNS_IO_SEL5;REG_DATA &= ~0x01;\
					  REG_ADDR = ADC_IO_SEL1;REG_DATA &= ~0x02;\
					  TRISA |= 0x01

#define SET_PA1_IO_IN REG_ADDR = SNS_IO_SEL5;REG_DATA &= ~0x02;\
					  REG_ADDR = ADC_IO_SEL1;REG_DATA &= ~0x04;\
					  TRISA |= 0x02

#define SET_PA2_IO_IN REG_ADDR = SNS_IO_SEL5;REG_DATA &= ~0x04;\
					  REG_ADDR = ADC_IO_SEL1;REG_DATA &= ~0x08;\
					  TRISA |= 0x04

#define SET_PA3_IO_IN REG_ADDR = SNS_IO_SEL5;REG_DATA &= ~0x08;\
					  REG_ADDR = ADC_IO_SEL1;REG_DATA &= ~0x10;\
					  TRISA |= 0x08

#define SET_PA0_IO_OUT REG_ADDR = PWM_IO_SEL;REG_DATA &= ~0x80;\
					   REG_ADDR = SNS_IO_SEL5;REG_DATA &= ~0x01;\
					   REG_ADDR = ADC_IO_SEL1;REG_DATA &= ~0x02;\
					   TRISA &= ~0x01

#define SET_PA1_IO_OUT REG_ADDR = SNS_IO_SEL5;REG_DATA &= ~0x02;\
					   REG_ADDR = ADC_IO_SEL1;REG_DATA &= ~0x04;\
					   TRISA &= ~0x02

#define SET_PA2_IO_OUT REG_ADDR = SNS_IO_SEL5;REG_DATA &= ~0x04;\
					   REG_ADDR = ADC_IO_SEL1;REG_DATA &= ~0x08;\
					   TRISA &= ~0x04

#define SET_PA3_IO_OUT REG_ADDR = SNS_IO_SEL5;REG_DATA &= ~0x08;\
					   REG_ADDR = ADC_IO_SEL1;REG_DATA &= ~0x10;\
					   TRISA &= ~0x08

#define SET_PA0_L DATAA &= ~0x01
#define SET_PA1_L DATAA &= ~0x02
#define SET_PA2_L DATAA &= ~0x04
#define SET_PA3_L DATAA &= ~0x08

#define SET_PA0_H DATAA |= 0x01
#define SET_PA1_H DATAA |= 0x02
#define SET_PA2_H DATAA |= 0x04
#define SET_PA3_H DATAA |= 0x08

#define GET_PA0 (DATAA&0x01)
#define GET_PA1 (DATAA&0x02)
#define GET_PA2 (DATAA&0x04)
#define GET_PA3 (DATAA&0x08)

#define SET_PA0_PU_ON REG_ADDR = PU_PA;REG_DATA |= 0x01
#define SET_PA1_PU_ON REG_ADDR = PU_PA;REG_DATA |= 0x02
#define SET_PA2_PU_ON REG_ADDR = PU_PA;REG_DATA |= 0x04
#define SET_PA3_PU_ON REG_ADDR = PU_PA;REG_DATA |= 0x08

#define SET_PA0_PU_OFF REG_ADDR = PU_PA;REG_DATA &= ~0x01
#define SET_PA1_PU_OFF REG_ADDR = PU_PA;REG_DATA &= ~0x02
#define SET_PA2_PU_OFF REG_ADDR = PU_PA;REG_DATA &= ~0x04
#define SET_PA3_PU_OFF REG_ADDR = PU_PA;REG_DATA &= ~0x08

/**********************PA口**********************/

/**********************PB口**********************/

#define SET_PB0_IO_IN  REG_ADDR = SNS_IO_SEL5;REG_DATA &= ~0x10;\
					   REG_ADDR = ADC_IO_SEL1;REG_DATA &= ~0x20;\
					   TRISB |= 0x01

#define SET_PB1_IO_IN  REG_ADDR = SNS_IO_SEL5;REG_DATA &= ~0x20;\
					   REG_ADDR = ADC_IO_SEL1;REG_DATA &= ~0x40;\
					   TRISB |= 0x02

#define SET_PB2_IO_IN  REG_ADDR = SNS_IO_SEL1;REG_DATA &= ~0x01;\
                       REG_ADDR = ADC_IO_SEL1;REG_DATA &= ~0x80;\
					   TRISB |= 0x04

#define SET_PB3_IO_IN  REG_ADDR = SNS_IO_SEL1;REG_DATA &= ~0x02;\
					   REG_ADDR = ADC_IO_SEL2;REG_DATA &= ~0x01;\
					   TRISB |= 0x08

#define SET_PB4_IO_IN  REG_ADDR = PWM_IO_SEL;REG_DATA &= ~0x01;\
					   REG_ADDR = SNS_IO_SEL1;REG_DATA &= ~0x04;\
					   REG_ADDR = ADC_IO_SEL2;REG_DATA &= ~0x02;\
					   TRISB |= 0x10

#define SET_PB5_IO_IN  REG_ADDR = PWM_IO_SEL;REG_DATA &= ~0x08;\
					   REG_ADDR = SNS_IO_SEL1;REG_DATA &= ~0x08;\
					   REG_ADDR = ADC_IO_SEL2;REG_DATA &= ~0x04;\
					   TRISB |= 0x20

#define SET_PB6_IO_IN  REG_ADDR = PWM_IO_SEL;REG_DATA &= ~0x02;\
					   REG_ADDR = SNS_IO_SEL1;REG_DATA &= ~0x10;\
					   REG_ADDR = ADC_IO_SEL2;REG_DATA &= ~0x08;\
					   TRISB |= 0x40

#define SET_PB7_IO_IN  REG_ADDR = PWM_IO_SEL;REG_DATA &= ~0x10;\
					   REG_ADDR = SNS_IO_SEL1;REG_DATA &= ~0x20;\
					   REG_ADDR = ADC_IO_SEL2;REG_DATA &= ~0x10;\
					   TRISB |= 0x80

#define SET_PB0_IO_OUT REG_ADDR = SNS_IO_SEL5;REG_DATA &= ~0x10;\
					   REG_ADDR = ADC_IO_SEL1;REG_DATA &= ~0x20;\
					   TRISB &= ~0x01

#define SET_PB1_IO_OUT REG_ADDR = SNS_IO_SEL5;REG_DATA &= ~0x20;\
					   REG_ADDR = ADC_IO_SEL1;REG_DATA &= ~0x40;\
					   TRISB &= ~0x02

#define SET_PB2_IO_OUT REG_ADDR = SNS_IO_SEL1;REG_DATA &= ~0x01;\
                       REG_ADDR = ADC_IO_SEL1;REG_DATA &= ~0x80;\
                       TRISB &= ~0x04

#define SET_PB3_IO_OUT REG_ADDR = SNS_IO_SEL1;REG_DATA &= ~0x02;\
					   REG_ADDR = ADC_IO_SEL2;REG_DATA &= ~0x01;\
					   TRISB &= ~0x08

#define SET_PB4_IO_OUT REG_ADDR = PWM_IO_SEL;REG_DATA &= ~0x01;\
                       REG_ADDR = SNS_IO_SEL1;REG_DATA &= ~0x04;\
					   REG_ADDR = ADC_IO_SEL2;REG_DATA &= ~0x02;\
					   TRISB &= ~0x10

#define SET_PB5_IO_OUT REG_ADDR = PWM_IO_SEL;REG_DATA &= ~0x08;\
                       REG_ADDR = SNS_IO_SEL1;REG_DATA &= ~0x08;\
					   REG_ADDR = ADC_IO_SEL2;REG_DATA &= ~0x04;\
					   TRISB &= ~0x20

#define SET_PB6_IO_OUT REG_ADDR = PWM_IO_SEL;REG_DATA &= ~0x02;\
                       REG_ADDR = SNS_IO_SEL1;REG_DATA &= ~0x10;\
					   REG_ADDR = ADC_IO_SEL2;REG_DATA &= ~0x08;\
					   TRISB &= ~0x40

#define SET_PB7_IO_OUT REG_ADDR = PWM_IO_SEL;REG_DATA &= ~0x10;\
                       REG_ADDR = SNS_IO_SEL1;REG_DATA &= ~0x20;\
					   REG_ADDR = ADC_IO_SEL2;REG_DATA &= ~0x10;\
					   TRISB &= ~0x80

#define SET_PB0_L DATAB &= ~0x01
#define SET_PB1_L DATAB &= ~0x02
#define SET_PB2_L DATAB &= ~0x04
#define SET_PB3_L DATAB &= ~0x08
#define SET_PB4_L DATAB &= ~0x10
#define SET_PB5_L DATAB &= ~0x20
#define SET_PB6_L DATAB &= ~0x40
#define SET_PB7_L DATAB &= ~0x80

#define SET_PB0_H DATAB |= 0x01
#define SET_PB1_H DATAB |= 0x02
#define SET_PB2_H DATAB |= 0x04
#define SET_PB3_H DATAB |= 0x08
#define SET_PB4_H DATAB |= 0x10
#define SET_PB5_H DATAB |= 0x20
#define SET_PB6_H DATAB |= 0x40
#define SET_PB7_H DATAB |= 0x80

#define GET_PB0 (DATAB&0x01)
#define GET_PB1 (DATAB&0x02)
#define GET_PB2 (DATAB&0x04)
#define GET_PB3 (DATAB&0x08)
#define GET_PB4 (DATAB&0x10)
#define GET_PB5 (DATAB&0x20)
#define GET_PB6 (DATAB&0x40)
#define GET_PB7 (DATAB&0x80)

#define SET_PB0_PU_ON REG_ADDR = PU_PB;REG_DATA |= 0x01
#define SET_PB1_PU_ON REG_ADDR = PU_PB;REG_DATA |= 0x02
#define SET_PB2_PU_ON REG_ADDR = PU_PB;REG_DATA |= 0x04
#define SET_PB3_PU_ON REG_ADDR = PU_PB;REG_DATA |= 0x08
#define SET_PB4_PU_ON REG_ADDR = PU_PB;REG_DATA |= 0x10
#define SET_PB5_PU_ON REG_ADDR = PU_PB;REG_DATA |= 0x20
#define SET_PB6_PU_ON REG_ADDR = PU_PB;REG_DATA |= 0x40
#define SET_PB7_PU_ON REG_ADDR = PU_PB;REG_DATA |= 0x80

#define SET_PB0_PU_OFF REG_ADDR = PU_PB;REG_DATA &= ~0x01
#define SET_PB1_PU_OFF REG_ADDR = PU_PB;REG_DATA &= ~0x02
#define SET_PB2_PU_OFF REG_ADDR = PU_PB;REG_DATA &= ~0x04
#define SET_PB3_PU_OFF REG_ADDR = PU_PB;REG_DATA &= ~0x08
#define SET_PB4_PU_OFF REG_ADDR = PU_PB;REG_DATA &= ~0x10
#define SET_PB5_PU_OFF REG_ADDR = PU_PB;REG_DATA &= ~0x20
#define SET_PB6_PU_OFF REG_ADDR = PU_PB;REG_DATA &= ~0x40
#define SET_PB7_PU_OFF REG_ADDR = PU_PB;REG_DATA &= ~0x80

/**********************PB口**********************/

/**********************PC口**********************/

#define SET_PC0_IO_IN  REG_ADDR = SNS_IO_SEL5;REG_DATA &= ~0x40;\
					   REG_ADDR = ADC_IO_SEL2;REG_DATA &= ~0x20;\
					   TRISC |= 0x01

#define SET_PC1_IO_IN  REG_ADDR = SNS_IO_SEL5;REG_DATA &= ~0x80;\
					   REG_ADDR = ADC_IO_SEL2;REG_DATA &= ~0x40;\
					   TRISC |= 0x02

#define SET_PC2_IO_IN  REG_ADDR = PWM_IO_SEL;REG_DATA &= ~0x04;\
                       REG_ADDR = SNS_IO_SEL6;REG_DATA &= ~0x01;\
					   REG_ADDR = ADC_IO_SEL2;REG_DATA &= ~0x80;\
					   TRISC |= 0x04

#define SET_PC3_IO_IN  REG_ADDR = PWM_IO_SEL;REG_DATA &= ~0x20;\
                       REG_ADDR = SNS_IO_SEL6;REG_DATA &= ~0x02;\
					   REG_ADDR = ADC_IO_SEL3;REG_DATA &= ~0x01;\
                       TRISC |= 0x08

#define SET_PC4_IO_IN  REG_ADDR = SNS_IO_SEL1;REG_DATA &= ~0x40;\
                       REG_ADDR = ADC_IO_SEL3;REG_DATA &= ~0x02;\
					   TRISC |= 0x10
#define SET_PC5_IO_IN  REG_ADDR = SNS_IO_SEL1;REG_DATA &= ~0x80;\
                       REG_ADDR = ADC_IO_SEL3;REG_DATA &= ~0x04;\
                       TRISC |= 0x20

#define SET_PC6_IO_IN  REG_ADDR = SNS_IO_SEL6;REG_DATA &= ~0x04;\
					   REG_ADDR = ADC_IO_SEL3;REG_DATA &= ~0x08;\
					   TRISC |= 0x40

#define SET_PC7_IO_IN  REG_ADDR = SNS_IO_SEL6;REG_DATA &= ~0x08;\
					   REG_ADDR = ADC_IO_SEL3;REG_DATA &= ~0x10;\
					   TRISC |= 0x80

#define SET_PC0_IO_OUT REG_ADDR = SNS_IO_SEL5;REG_DATA &= ~0x40;\
					   REG_ADDR = ADC_IO_SEL2;REG_DATA &= ~0x20;\
					   TRISC &= ~0x01

#define SET_PC1_IO_OUT REG_ADDR = SNS_IO_SEL5;REG_DATA &= ~0x80;\
					   REG_ADDR = ADC_IO_SEL2;REG_DATA &= ~0x40;\
					   TRISC &= ~0x02

#define SET_PC2_IO_OUT REG_ADDR = PWM_IO_SEL;REG_DATA &= ~0x04;\
                       REG_ADDR = SNS_IO_SEL6;REG_DATA &= ~0x01;\
					   REG_ADDR = ADC_IO_SEL2;REG_DATA &= ~0x80;\
					   TRISC &= ~0x04

#define SET_PC3_IO_OUT REG_ADDR = PWM_IO_SEL;REG_DATA &= ~0x20;\
                       REG_ADDR = SNS_IO_SEL6;REG_DATA &= ~0x02;\
					   REG_ADDR = ADC_IO_SEL3;REG_DATA &= ~0x01;\
					   TRISC &= ~0x08

#define SET_PC4_IO_OUT REG_ADDR = SNS_IO_SEL1;REG_DATA &= ~0x40;\
                       REG_ADDR = ADC_IO_SEL3;REG_DATA &= ~0x02;\
                       TRISC &= ~0x10

#define SET_PC5_IO_OUT REG_ADDR = SNS_IO_SEL1;REG_DATA &= ~0x80;\
                       REG_ADDR = ADC_IO_SEL3;REG_DATA &= ~0x04;\
                       TRISC &= ~0x20

#define SET_PC6_IO_OUT REG_ADDR = SNS_IO_SEL6;REG_DATA &= ~0x04;\
					   REG_ADDR = ADC_IO_SEL3;REG_DATA &= ~0x08;\
					   TRISC &= ~0x40

#define SET_PC7_IO_OUT REG_ADDR = SNS_IO_SEL6;REG_DATA &= ~0x08;\
					   REG_ADDR = ADC_IO_SEL3;REG_DATA &= ~0x10;\
					   TRISC &= ~0x80

#define SET_PC0_L DATAC &= ~0x01
#define SET_PC1_L DATAC &= ~0x02
#define SET_PC2_L DATAC &= ~0x04
#define SET_PC3_L DATAC &= ~0x08
#define SET_PC4_L DATAC &= ~0x10
#define SET_PC5_L DATAC &= ~0x20
#define SET_PC6_L DATAC &= ~0x40
#define SET_PC7_L DATAC &= ~0x80

#define SET_PC0_H DATAC |= 0x01
#define SET_PC1_H DATAC |= 0x02
#define SET_PC2_H DATAC |= 0x04
#define SET_PC3_H DATAC |= 0x08
#define SET_PC4_H DATAC |= 0x10
#define SET_PC5_H DATAC |= 0x20
#define SET_PC6_H DATAC |= 0x40
#define SET_PC7_H DATAC |= 0x80

#define GET_PC0 (DATAC&0x01)
#define GET_PC1 (DATAC&0x02)
#define GET_PC2 (DATAC&0x04)
#define GET_PC3 (DATAC&0x08)
#define GET_PC4 (DATAC&0x10)
#define GET_PC5 (DATAC&0x20)
#define GET_PC6 (DATAC&0x40)
#define GET_PC7 (DATAC&0x80)

#define SET_PC0_PU_ON REG_ADDR = PU_PC;REG_DATA |= 0x01
#define SET_PC1_PU_ON REG_ADDR = PU_PC;REG_DATA |= 0x02
#define SET_PC2_PU_ON REG_ADDR = PU_PC;REG_DATA |= 0x04
#define SET_PC3_PU_ON REG_ADDR = PU_PC;REG_DATA |= 0x08
#define SET_PC4_PU_ON REG_ADDR = PU_PC;REG_DATA |= 0x10
#define SET_PC5_PU_ON REG_ADDR = PU_PC;REG_DATA |= 0x20
#define SET_PC6_PU_ON REG_ADDR = PU_PC;REG_DATA |= 0x40
#define SET_PC7_PU_ON REG_ADDR = PU_PC;REG_DATA |= 0x80

#define SET_PC0_PU_OFF REG_ADDR = PU_PC;REG_DATA &= ~0x01
#define SET_PC1_PU_OFF REG_ADDR = PU_PC;REG_DATA &= ~0x02
#define SET_PC2_PU_OFF REG_ADDR = PU_PC;REG_DATA &= ~0x04
#define SET_PC3_PU_OFF REG_ADDR = PU_PC;REG_DATA &= ~0x08
#define SET_PC4_PU_OFF REG_ADDR = PU_PC;REG_DATA &= ~0x10
#define SET_PC5_PU_OFF REG_ADDR = PU_PC;REG_DATA &= ~0x20
#define SET_PC6_PU_OFF REG_ADDR = PU_PC;REG_DATA &= ~0x40
#define SET_PC7_PU_OFF REG_ADDR = PU_PC;REG_DATA &= ~0x80


#define SET_PC4_OD_ON REG_ADDR = ODRAIN_EN;REG_DATA |= 0x01
#define SET_PC5_OD_ON REG_ADDR = ODRAIN_EN;REG_DATA |= 0x02

#define SET_PC4_OD_OFF REG_ADDR = ODRAIN_EN;REG_DATA &= ~0x01
#define SET_PC5_OD_OFF REG_ADDR = ODRAIN_EN;REG_DATA &= ~0x02

/**********************PC口**********************/



/**********************PE口*********************/

#define SET_PE0_IO_IN  REG_ADDR = SNS_IO_SEL6;REG_DATA &= ~0x10;\
					   REG_ADDR = ADC_IO_SEL3;REG_DATA &= ~0x20;\
					   TRISE |= 0x01

#define SET_PE1_IO_IN  REG_ADDR = SNS_IO_SEL6;REG_DATA &= ~0x20;\
					   REG_ADDR = ADC_IO_SEL3;REG_DATA &= ~0x40;\
					   TRISE |= 0x02

#define SET_PE2_IO_IN  REG_ADDR = SNS_IO_SEL6;REG_DATA &= ~0x40;\
					   REG_ADDR = ADC_IO_SEL3;REG_DATA &= ~0x80;\
					   TRISE |= 0x04

#define SET_PE3_IO_IN  REG_ADDR = SNS_IO_SEL6;REG_DATA &= ~0x80;\
					   REG_ADDR = ADC_IO_SEL4;REG_DATA &= ~0x01;\
					   TRISE |= 0x08

#define SET_PE4_IO_IN  REG_ADDR = SNS_IO_SEL2;REG_DATA &= ~0x01;\
                       REG_ADDR = ADC_IO_SEL4;REG_DATA &= ~0x02;\
					   TRISE |= 0x10

#define SET_PE5_IO_IN  REG_ADDR = SNS_IO_SEL2;REG_DATA &= ~0x02;\
					   REG_ADDR = ADC_IO_SEL4;REG_DATA &= ~0x04;\
					   TRISE |= 0x20

#define SET_PE6_IO_IN  REG_ADDR = SNS_IO_SEL2;REG_DATA &= ~0x04;\
                       REG_ADDR = ADC_IO_SEL4;REG_DATA &= ~0x08;\
                       TRISE |= 0x40

#define SET_PE7_IO_IN  REG_ADDR = SNS_IO_SEL2;REG_DATA &= ~0x08;\
                       REG_ADDR = ADC_IO_SEL4;REG_DATA &= ~0x10;\
                       TRISE |= 0x80

#define SET_PE0_IO_OUT REG_ADDR = SNS_IO_SEL6;REG_DATA &= ~0x10;\
					   REG_ADDR = ADC_IO_SEL3;REG_DATA &= ~0x20;\
					   TRISE &= ~0x01

#define SET_PE1_IO_OUT REG_ADDR = SNS_IO_SEL6;REG_DATA &= ~0x20;\
					   REG_ADDR = ADC_IO_SEL3;REG_DATA &= ~0x40;\
					   TRISE &= ~0x02

#define SET_PE2_IO_OUT REG_ADDR = SNS_IO_SEL6;REG_DATA &= ~0x40;\
					   REG_ADDR = ADC_IO_SEL3;REG_DATA &= ~0x80;\
					   TRISE &= ~0x04

#define SET_PE3_IO_OUT REG_ADDR = SNS_IO_SEL6;REG_DATA &= ~0x80;\
					   REG_ADDR = ADC_IO_SEL4;REG_DATA &= ~0x01;\
					   TRISE &= ~0x08

#define SET_PE4_IO_OUT REG_ADDR = SNS_IO_SEL2;REG_DATA &= ~0x01;\
					   REG_ADDR = ADC_IO_SEL4;REG_DATA &= ~0x02;\
					   TRISE &= ~0x10

#define SET_PE5_IO_OUT REG_ADDR = SNS_IO_SEL2;REG_DATA &= ~0x02;\
                       REG_ADDR = ADC_IO_SEL4;REG_DATA &= ~0x04;\
					   TRISE &= ~0x20

#define SET_PE6_IO_OUT REG_ADDR = SNS_IO_SEL2;REG_DATA &= ~0x04;\
                       REG_ADDR = ADC_IO_SEL4;REG_DATA &= ~0x08;\
					   TRISE &= ~0x40

#define SET_PE7_IO_OUT REG_ADDR = SNS_IO_SEL2;REG_DATA &= ~0x08;\
                       REG_ADDR = ADC_IO_SEL4;REG_DATA &= ~0x10;\
					   TRISE &= ~0x80

#define SET_PE0_L DATAE &= ~0x01
#define SET_PE1_L DATAE &= ~0x02
#define SET_PE2_L DATAE &= ~0x04
#define SET_PE3_L DATAE &= ~0x08
#define SET_PE4_L DATAE &= ~0x10
#define SET_PE5_L DATAE &= ~0x20
#define SET_PE6_L DATAE &= ~0x40
#define SET_PE7_L DATAE &= ~0x80

#define SET_PE0_H DATAE |= 0x01
#define SET_PE1_H DATAE |= 0x02
#define SET_PE2_H DATAE |= 0x04
#define SET_PE3_H DATAE |= 0x08
#define SET_PE4_H DATAE |= 0x10
#define SET_PE5_H DATAE |= 0x20
#define SET_PE6_H DATAE |= 0x40
#define SET_PE7_H DATAE |= 0x80

#define GET_PE0 (DATAE&0x01)
#define GET_PE1 (DATAE&0x02)
#define GET_PE2 (DATAE&0x04)
#define GET_PE3 (DATAE&0x08)
#define GET_PE4 (DATAE&0x10)
#define GET_PE5 (DATAE&0x20)
#define GET_PE6 (DATAE&0x40)
#define GET_PE7 (DATAE&0x80)

#define SET_PE0_PU_ON REG_ADDR = PU_PE;REG_DATA |= 0x01
#define SET_PE1_PU_ON REG_ADDR = PU_PE;REG_DATA |= 0x02
#define SET_PE2_PU_ON REG_ADDR = PU_PE;REG_DATA |= 0x04
#define SET_PE3_PU_ON REG_ADDR = PU_PE;REG_DATA |= 0x08
#define SET_PE4_PU_ON REG_ADDR = PU_PE;REG_DATA |= 0x10
#define SET_PE5_PU_ON REG_ADDR = PU_PE;REG_DATA |= 0x20
#define SET_PE6_PU_ON REG_ADDR = PU_PE;REG_DATA |= 0x40
#define SET_PE7_PU_ON REG_ADDR = PU_PE;REG_DATA |= 0x80

#define SET_PE0_PU_OFF REG_ADDR = PU_PE;REG_DATA &= ~0x01
#define SET_PE1_PU_OFF REG_ADDR = PU_PE;REG_DATA &= ~0x02
#define SET_PE2_PU_OFF REG_ADDR = PU_PE;REG_DATA &= ~0x04
#define SET_PE3_PU_OFF REG_ADDR = PU_PE;REG_DATA &= ~0x08
#define SET_PE4_PU_OFF REG_ADDR = PU_PE;REG_DATA &= ~0x10
#define SET_PE5_PU_OFF REG_ADDR = PU_PE;REG_DATA &= ~0x20
#define SET_PE6_PU_OFF REG_ADDR = PU_PE;REG_DATA &= ~0x40
#define SET_PE7_PU_OFF REG_ADDR = PU_PE;REG_DATA &= ~0x80

#define SET_PE4_OD_ON REG_ADDR  = ODRAIN_EN;REG_DATA |= 0x04
#define SET_PE5_OD_ON REG_ADDR  = ODRAIN_EN;REG_DATA |= 0x08

#define SET_PE4_OD_OFF REG_ADDR = ODRAIN_EN;REG_DATA &= ~0x04
#define SET_PE5_OD_OFF REG_ADDR = ODRAIN_EN;REG_DATA &= ~0x08

/**********************PE口**********************/

/**********************PF口*********************/

#define SET_PF0_IO_IN TRISF |= 0x01
#define SET_PF1_IO_IN TRISF |= 0x02
#define SET_PF2_IO_IN TRISF |= 0x04
#define SET_PF3_IO_IN TRISF |= 0x08

#define SET_PF4_IO_IN REG_ADDR = SNS_IO_SEL3;REG_DATA &= ~0x01;\
                      REG_ADDR = ADC_IO_SEL4;REG_DATA &= ~0x20;\
			          TRISF |= 0x10

#define SET_PF5_IO_IN REG_ADDR = SNS_IO_SEL3;REG_DATA &= ~0x02;\
                      REG_ADDR = ADC_IO_SEL4;REG_DATA &= ~0x40;\
                      TRISF |= 0x20

#define SET_PF6_IO_IN REG_ADDR = SNS_IO_SEL3;REG_DATA &= ~0x04;\
                      REG_ADDR = ADC_IO_SEL4;REG_DATA &= ~0x80;\
                      TRISF |= 0x40

#define SET_PF7_IO_IN REG_ADDR = SNS_IO_SEL3;REG_DATA &= ~0x08;\
					  REG_ADDR = ADC_IO_SEL5;REG_DATA &= ~0x01;\
					  TRISF |= 0x80

#define SET_PF0_IO_OUT TRISF &= ~0x01
#define SET_PF1_IO_OUT TRISF &= ~0x02
#define SET_PF2_IO_OUT TRISF &= ~0x04
#define SET_PF3_IO_OUT TRISF &= ~0x08

#define SET_PF4_IO_OUT REG_ADDR = SNS_IO_SEL3;REG_DATA &= ~0x01;\
                       REG_ADDR = ADC_IO_SEL4;REG_DATA &= ~0x20;\
                       TRISF &= ~0x10

#define SET_PF5_IO_OUT REG_ADDR = SNS_IO_SEL3;REG_DATA &= ~0x02;\
                       REG_ADDR = ADC_IO_SEL4;REG_DATA &= ~0x40;\
                       TRISF &= ~0x20
#define SET_PF6_IO_OUT REG_ADDR = SNS_IO_SEL3;REG_DATA &= ~0x04;\
                       REG_ADDR = ADC_IO_SEL4;REG_DATA &= ~0x40;\
					   TRISF &= ~0x40
#define SET_PF7_IO_OUT REG_ADDR = SNS_IO_SEL3;REG_DATA &= ~0x08;\
                       REG_ADDR = ADC_IO_SEL5;REG_DATA &= ~0x01;\
					   TRISF &= ~0x80

#define SET_PF0_L DATAF &= ~0x01
#define SET_PF1_L DATAF &= ~0x02
#define SET_PF2_L DATAF &= ~0x04
#define SET_PF3_L DATAF &= ~0x08
#define SET_PF4_L DATAF &= ~0x10
#define SET_PF5_L DATAF &= ~0x20
#define SET_PF6_L DATAF &= ~0x40
#define SET_PF7_L DATAF &= ~0x80

#define SET_PF0_H DATAF |= 0x01
#define SET_PF1_H DATAF |= 0x02
#define SET_PF2_H DATAF |= 0x04
#define SET_PF3_H DATAF |= 0x08
#define SET_PF4_H DATAF |= 0x10
#define SET_PF5_H DATAF |= 0x20
#define SET_PF6_H DATAF |= 0x40
#define SET_PF7_H DATAF |= 0x80

#define GET_PF0 (DATAF&0x01)
#define GET_PF1 (DATAF&0x02)
#define GET_PF2 (DATAF&0x04)
#define GET_PF3 (DATAF&0x08)
#define GET_PF4 (DATAF&0x10)
#define GET_PF5 (DATAF&0x20)
#define GET_PF6 (DATAF&0x40)
#define GET_PF7 (DATAF&0x80)

#define SET_PF0_PU_ON REG_ADDR = PU_PF;REG_DATA |= 0x01
#define SET_PF1_PU_ON REG_ADDR = PU_PF;REG_DATA |= 0x02
#define SET_PF2_PU_ON REG_ADDR = PU_PF;REG_DATA |= 0x04
#define SET_PF3_PU_ON REG_ADDR = PU_PF;REG_DATA |= 0x08
#define SET_PF4_PU_ON REG_ADDR = PU_PF;REG_DATA |= 0x10
#define SET_PF5_PU_ON REG_ADDR = PU_PF;REG_DATA |= 0x20
#define SET_PF6_PU_ON REG_ADDR = PU_PF;REG_DATA |= 0x40
#define SET_PF7_PU_ON REG_ADDR = PU_PF;REG_DATA |= 0x80

#define SET_PF0_PU_OFF REG_ADDR = PU_PF;REG_DATA &= ~0x01
#define SET_PF1_PU_OFF REG_ADDR = PU_PF;REG_DATA &= ~0x02
#define SET_PF2_PU_OFF REG_ADDR = PU_PF;REG_DATA &= ~0x04
#define SET_PF3_PU_OFF REG_ADDR = PU_PF;REG_DATA &= ~0x08
#define SET_PF4_PU_OFF REG_ADDR = PU_PF;REG_DATA &= ~0x10
#define SET_PF5_PU_OFF REG_ADDR = PU_PF;REG_DATA &= ~0x20
#define SET_PF6_PU_OFF REG_ADDR = PU_PF;REG_DATA &= ~0x40
#define SET_PF7_PU_OFF REG_ADDR = PU_PF;REG_DATA &= ~0x80

/**********************PF口**********************/

#define TRUN_PF0 {if(GET_PF0 != 0){SET_PF0_L;}else{SET_PF0_H;}}

/**********************PG口*********************/

#define SET_PG0_IO_IN REG_ADDR = SNS_IO_SEL3;REG_DATA &= ~0x10;\
                      REG_ADDR = ADC_IO_SEL5;REG_DATA &= ~0x02;\
					  TRISG |= 0x01

#define SET_PG1_IO_IN REG_ADDR = SNS_IO_SEL3;REG_DATA &= ~0x20;\
                      REG_ADDR = ADC_IO_SEL5;REG_DATA &= ~0x04;\
					  TRISG |= 0x02

#define SET_PG2_IO_IN REG_ADDR = SNS_IO_SEL3;REG_DATA &= ~0x40;\
                      REG_ADDR = ADC_IO_SEL5;REG_DATA &= ~0x08;\
					  TRISG |= 0x04

#define SET_PG3_IO_IN REG_ADDR = SNS_IO_SEL3;REG_DATA &= ~0x80;\
                      REG_ADDR = ADC_IO_SEL5;REG_DATA &= ~0x10;\
					  TRISG |= 0x08

#define SET_PG0_IO_OUT REG_ADDR = SNS_IO_SEL3;REG_DATA &= ~0x10;\
                       REG_ADDR = ADC_IO_SEL5;REG_DATA &= ~0x02;\
					   TRISG &= ~0x01

#define SET_PG1_IO_OUT REG_ADDR = SNS_IO_SEL3;REG_DATA &= ~0x20;\
                       REG_ADDR = ADC_IO_SEL5;REG_DATA &= ~0x04;\
					   TRISG &= ~0x02

#define SET_PG2_IO_OUT REG_ADDR = SNS_IO_SEL3;REG_DATA &= ~0x40;\
                       REG_ADDR = ADC_IO_SEL5;REG_DATA &= ~0x08;\
					   TRISG &= ~0x04

#define SET_PG3_IO_OUT REG_ADDR = SNS_IO_SEL3;REG_DATA &= ~0x80;\
                       REG_ADDR = ADC_IO_SEL5;REG_DATA &= ~0x10;\
					   TRISG &= ~0x08

#define SET_PG0_L DATAG &= ~0x01
#define SET_PG1_L DATAG &= ~0x02
#define SET_PG2_L DATAG &= ~0x04
#define SET_PG3_L DATAG &= ~0x08

#define SET_PG0_H DATAG |= 0x01
#define SET_PG1_H DATAG |= 0x02
#define SET_PG2_H DATAG |= 0x04
#define SET_PG3_H DATAG |= 0x08

#define GET_PG0 (DATAG&0x01)
#define GET_PG1 (DATAG&0x02)
#define GET_PG2 (DATAG&0x04)
#define GET_PG3 (DATAG&0x08)

#define SET_PG0_PU_ON REG_ADDR = PU_PG;REG_DATA |= 0x01
#define SET_PG1_PU_ON REG_ADDR = PU_PG;REG_DATA |= 0x02
#define SET_PG2_PU_ON REG_ADDR = PU_PG;REG_DATA |= 0x04
#define SET_PG3_PU_ON REG_ADDR = PU_PG;REG_DATA |= 0x08

#define SET_PG0_PU_OFF REG_ADDR = PU_PG;REG_DATA &= ~0x01
#define SET_PG1_PU_OFF REG_ADDR = PU_PG;REG_DATA &= ~0x02
#define SET_PG2_PU_OFF REG_ADDR = PU_PG;REG_DATA &= ~0x04
#define SET_PG3_PU_OFF REG_ADDR = PU_PG;REG_DATA &= ~0x08

/**********************PG口**********************/

/**********************PH口*********************/

#define SET_PH0_IO_IN REG_ADDR = SNS_IO_SEL4;REG_DATA &= ~0x01;\
					  REG_ADDR = ADC_IO_SEL0;REG_DATA &= ~0x01;\
					  TRISH |= 0x01

#define SET_PH1_IO_IN REG_ADDR = SNS_IO_SEL4;REG_DATA &= ~0x02;\
					  REG_ADDR = ADC_IO_SEL0;REG_DATA &= ~0x02;\
					  TRISH |= 0x02

#define SET_PH2_IO_IN REG_ADDR = SNS_IO_SEL4;REG_DATA &= ~0x04;\
					  REG_ADDR = ADC_IO_SEL0;REG_DATA &= ~0x04;\
					  TRISH |= 0x04

#define SET_PH3_IO_IN REG_ADDR = SNS_IO_SEL4;REG_DATA &= ~0x08;\
					  REG_ADDR = ADC_IO_SEL0;REG_DATA &= ~0x08;\
					  TRISH |= 0x08

#define SET_PH4_IO_IN REG_ADDR = SNS_IO_SEL4;REG_DATA &= ~0x10;\
					  REG_ADDR = ADC_IO_SEL0;REG_DATA &= ~0x10;\
					  TRISH |= 0x10

#define SET_PH5_IO_IN REG_ADDR = SNS_IO_SEL4;REG_DATA &= ~0x20;\
					  REG_ADDR = ADC_IO_SEL0;REG_DATA &= ~0x20;\
					  TRISH |= 0x20

#define SET_PH6_IO_IN REG_ADDR = SNS_IO_SEL4;REG_DATA &= ~0x40;\
					  REG_ADDR = ADC_IO_SEL0;REG_DATA &= ~0x40;\
					  TRISH |= 0x40

#define SET_PH7_IO_IN REG_ADDR = PWM_IO_SEL;REG_DATA &= ~0x40;\
                      REG_ADDR = SNS_IO_SEL4;REG_DATA &= ~0x80;\
					  REG_ADDR = ADC_IO_SEL1;REG_DATA &= ~0x01;\
					  TRISH |= 0x80


#define SET_PH0_IO_OUT REG_ADDR = SNS_IO_SEL4;REG_DATA &= ~0x01;\
					   REG_ADDR = ADC_IO_SEL0;REG_DATA &= ~0x01;\
					   TRISH &= ~0x01

#define SET_PH1_IO_OUT REG_ADDR = SNS_IO_SEL4;REG_DATA &= ~0x02;\
					   REG_ADDR = ADC_IO_SEL0;REG_DATA &= ~0x02;\
					   TRISH &= ~0x02

#define SET_PH2_IO_OUT REG_ADDR = SNS_IO_SEL4;REG_DATA &= ~0x04;\
					   REG_ADDR = ADC_IO_SEL0;REG_DATA &= ~0x04;\
					   TRISH &= ~0x04

#define SET_PH3_IO_OUT REG_ADDR = SNS_IO_SEL4;REG_DATA &= ~0x08;\
					   REG_ADDR = ADC_IO_SEL0;REG_DATA &= ~0x08;\
					   TRISH &= ~0x08

#define SET_PH4_IO_OUT REG_ADDR = SNS_IO_SEL4;REG_DATA &= ~0x10;\
					   REG_ADDR = ADC_IO_SEL0;REG_DATA &= ~0x10;\
					   TRISH &= ~0x10

#define SET_PH5_IO_OUT REG_ADDR = SNS_IO_SEL4;REG_DATA &= ~0x20;\
					   REG_ADDR = ADC_IO_SEL0;REG_DATA &= ~0x20;\
					   TRISH &= ~0x20

#define SET_PH6_IO_OUT REG_ADDR = SNS_IO_SEL4;REG_DATA &= ~0x40;\
					   REG_ADDR = ADC_IO_SEL0;REG_DATA &= ~0x40;\
					   TRISH &= ~0x40

#define SET_PH7_IO_OUT REG_ADDR = PWM_IO_SEL;REG_DATA &= ~0x40;\
                       REG_ADDR = SNS_IO_SEL4;REG_DATA &= ~0x80;\
					   REG_ADDR = ADC_IO_SEL1;REG_DATA &= ~0x01;\
					   TRISH &= ~0x80

#define SET_PH0_L DATAH &= ~0x01
#define SET_PH1_L DATAH &= ~0x02
#define SET_PH2_L DATAH &= ~0x04
#define SET_PH3_L DATAH &= ~0x08
#define SET_PH4_L DATAH &= ~0x10
#define SET_PH5_L DATAH &= ~0x20
#define SET_PH6_L DATAH &= ~0x40
#define SET_PH7_L DATAH &= ~0x80

#define SET_PH0_H DATAH |= 0x01
#define SET_PH1_H DATAH |= 0x02
#define SET_PH2_H DATAH |= 0x04
#define SET_PH3_H DATAH |= 0x08
#define SET_PH4_H DATAH |= 0x10
#define SET_PH5_H DATAH |= 0x20
#define SET_PH6_H DATAH |= 0x40
#define SET_PH7_H DATAH |= 0x80

#define GET_PH0 (DATAH&0x01)
#define GET_PH1 (DATAH&0x02)
#define GET_PH2 (DATAH&0x04)
#define GET_PH3 (DATAH&0x08)
#define GET_PH4 (DATAH&0x10)
#define GET_PH5 (DATAH&0x20)
#define GET_PH6 (DATAH&0x40)
#define GET_PH7 (DATAH&0x80)

#define SET_PH0_PU_ON REG_ADDR = PU_PH;REG_DATA |= 0x01
#define SET_PH1_PU_ON REG_ADDR = PU_PH;REG_DATA |= 0x02
#define SET_PH2_PU_ON REG_ADDR = PU_PH;REG_DATA |= 0x04
#define SET_PH3_PU_ON REG_ADDR = PU_PH;REG_DATA |= 0x08
#define SET_PH4_PU_ON REG_ADDR = PU_PH;REG_DATA |= 0x10
#define SET_PH5_PU_ON REG_ADDR = PU_PH;REG_DATA |= 0x20
#define SET_PH6_PU_ON REG_ADDR = PU_PH;REG_DATA |= 0x40
#define SET_PH7_PU_ON REG_ADDR = PU_PH;REG_DATA |= 0x80

#define SET_PH0_PU_OFF REG_ADDR = PU_PH;REG_DATA &= ~0x01
#define SET_PH1_PU_OFF REG_ADDR = PU_PH;REG_DATA &= ~0x02
#define SET_PH2_PU_OFF REG_ADDR = PU_PH;REG_DATA &= ~0x04
#define SET_PH3_PU_OFF REG_ADDR = PU_PH;REG_DATA &= ~0x08
#define SET_PH4_PU_OFF REG_ADDR = PU_PH;REG_DATA &= ~0x10
#define SET_PH5_PU_OFF REG_ADDR = PU_PH;REG_DATA &= ~0x20
#define SET_PH6_PU_OFF REG_ADDR = PU_PH;REG_DATA &= ~0x40
#define SET_PH7_PU_OFF REG_ADDR = PU_PH;REG_DATA &= ~0x80

/**********************PH口**********************/


/* gpio mode definitions */
typedef enum
{
	GPIO_MODE_IN_FLOATING,			/*!< floating input mode */
	GPIO_MODE_IPU,					/*!< pull-up input mode */
	GPIO_MODE_OUT,					/*!< GPIO output */
	GPIO_MODE_OUT_OD,				/*!< GPIO output with open-drain,only PC4/PC5/PE4/PE5*/
}GPIO_MODE_enum;

/* gpio port definitions */
typedef enum
{
	GPIOA,
	GPIOB,
	GPIOC,
	GPIOE,
	GPIOF,
	GPIOG,
	GPIOH
}GPIO_PORT_enum;

/* gpio pin definitions */
#define	GPIO_PIN_0			0x01
#define	GPIO_PIN_1			0x02
#define	GPIO_PIN_2			0x04
#define	GPIO_PIN_3			0x08
#define	GPIO_PIN_4			0x10
#define	GPIO_PIN_5			0x20
#define	GPIO_PIN_6			0x40
#define	GPIO_PIN_7			0x80
#define	GPIO_PIN_ALL		0xFF

#define GPIOA_BIT_SET(x)  	DATAA |= (x)
#define GPIOB_BIT_SET(x)  	DATAB |= (x)
#define GPIOC_BIT_SET(x)  	DATAC |= (x)
#define GPIOE_BIT_SET(x)  	DATAE |= (x)
#define GPIOF_BIT_SET(x)  	DATAF |= (x)
#define GPIOG_BIT_SET(x)  	DATAG |= (x)
#define GPIOH_BIT_SET(x)  	DATAH |= (x)

#define GPIOA_BIT_RESET(x)  DATAA &= ~(x)
#define GPIOB_BIT_RESET(x)  DATAB &= ~(x)
#define GPIOC_BIT_RESET(x)  DATAC &= ~(x)
#define GPIOE_BIT_RESET(x)  DATAE &= ~(x)
#define GPIOF_BIT_RESET(x)  DATAF &= ~(x)
#define GPIOG_BIT_RESET(x)  DATAG &= ~(x)
#define GPIOH_BIT_RESET(x)  DATAH &= ~(x)


#define SET_GPIOA_DATA(x)  DATAA = x
#define SET_GPIOB_DATA(x)  DATAB = x
#define SET_GPIOC_DATA(x)  DATAC = x
#define SET_GPIOE_DATA(x)  DATAE = x
#define SET_GPIOF_DATA(x)  DATAF = x
#define SET_GPIOG_DATA(x)  DATAG = x
#define SET_GPIOH_DATA(x)  DATAH = x

#define GET_GPIOA_DATA()  DATAA
#define GET_GPIOB_DATA()  DATAB
#define GET_GPIOC_DATA()  DATAC
#define GET_GPIOE_DATA()  DATAE
#define GET_GPIOF_DATA()  DATAF
#define GET_GPIOG_DATA()  DATAG
#define GET_GPIOH_DATA()  DATAH

#define GET_GPIOA_BIT(x)  (DATAA & x)
#define GET_GPIOB_BIT(x)  (DATAB & x)
#define GET_GPIOC_BIT(x)  (DATAC & x)
#define GET_GPIOE_BIT(x)  (DATAE & x)
#define GET_GPIOF_BIT(x)  (DATAF & x)
#define GET_GPIOG_BIT(x)  (DATAG & x)
#define GET_GPIOH_BIT(x)  (DATAH & x)

/* function declarations */
/* gpio init */
void gpio_init(GPIO_PORT_enum gpio_port,uint8_t gpio_pin,GPIO_MODE_enum gpio_mode);
/* gpio bit set */
void gpio_bit_set(GPIO_PORT_enum gpio_port,uint8_t gpio_pin);
/* gpio bit reset */
void gpio_bit_reset(GPIO_PORT_enum gpio_port,uint8_t gpio_pin);

uint8_t gpio_bit_get(GPIO_PORT_enum gpio_port,uint8_t gpio_pin);
#endif
