/*!
    \file  mcu02_pwm.h
    \brief pwm define
*/

/*
    Copyright (C) 2020 BYD

    2020-05-08, V1.0.0, firmware for mcu02
*/

#ifndef MCU02_PWM_H
#define	MCU02_PWM_H

#include "mcu02_sfr.h"
#include "mcu02_system.h"


/* pwm3 channel define */
#define	PWM3_CH_PA0		(0x80)/*!< PWM3 on PA0*/

/* pwm2 channel define */
#define	PWM2_CH_PH7		(0x40)/*!< PWM2 on PH7*/

/* pwm1 channel define */
#define	PWM1_CH_PC3		(0x20)/*!< PWM1 on PC3*/
#define	PWM1_CH_PB7		(0x10)/*!< PWM1 on PB7*/
#define	PWM1_CH_PB5		(0x08)/*!< PWM1 on PB5*/

/* pwm0 channel define */
#define	PWM0_CH_PC2		(0x04)/*!< PWM0 on PC2*/
#define	PWM0_CH_PB6		(0x02)/*!< PWM0 on PB6*/
#define	PWM0_CH_PB4		(0x01)/*!< PWM0 on PB4*/

//x = PWM0_CH_PC2,PWM0_CH_PB6,PWM0_CH_PB4,PWM1_CH_PB5,PWM1_CH_PB7,PWM1_CH_PC3,PWM2_CH_PH7,PWM3_CH_PA0 
#define PWM_CH_ENABLE(x)  REG_ADDR = PWM_IO_SEL;REG_DATA |= x  
#define PWM_CH_DISABLE(x) REG_ADDR = PWM_IO_SEL;REG_DATA &= ~x
 
/* function declarations */

/* pwm0 duty and width config */
void pwm0_duty_width_config(uint16_t cnt_h,uint16_t cnt_l);
/* pwm1 duty and width config */
void pwm1_duty_width_config(uint16_t cnt_h,uint16_t cnt_l);
/* pwm2 duty and width config */
void pwm2_duty_width_config(uint16_t cnt_h,uint16_t cnt_l);
/* pwm3 duty and width config */
void pwm3_duty_width_config(uint16_t cnt_h,uint16_t cnt_l);

#endif