/*!
    \file  mcu02_pwm.c
    \brief pwm driver
*/

/*
    Copyright (C) 2020 BYD

    2020-05-08, V1.0.0, firmware for mcu02
*/
#include "mcu02_pwm.h"


/*!
    \brief      pwm0 duty and width config
    \param[in]  cnt_h: pwm high level cnt
				cnt_l: pwm low level cnt
				pwm_duty = (cnt_h+cnt_l)/sys_clk
				pwm_width = cnt_h/(cnt_h+cnt_l)
    \param[out] none
    \retval     none
*/
void pwm0_duty_width_config(uint16_t cnt_h,uint16_t cnt_l)
{
	PWM0_L_L = (uint8_t)cnt_l;
	PWM0_L_H = (uint8_t)(cnt_l >> 8);
	PWM0_H_L = (uint8_t)cnt_h;
	PWM0_H_H = (uint8_t)(cnt_h >> 8);
}

/*!
    \brief      pwm1 duty and width config
    \param[in]  cnt_h: pwm high level cnt
				cnt_l: pwm low level cnt
				pwm_duty = (cnt_h+cnt_l)/sys_clk
				pwm_width = cnt_h/(cnt_h+cnt_l)
    \param[out] none
    \retval     none
*/
void pwm1_duty_width_config(uint16_t cnt_h,uint16_t cnt_l)
{
	PWM1_L_L = (uint8_t)cnt_l;
	PWM1_L_H = (uint8_t)(cnt_l >> 8);
	PWM1_H_L = (uint8_t)cnt_h;
	PWM1_H_H = (uint8_t)(cnt_h >> 8);
}

/*!
    \brief      pwm2 duty and width config
    \param[in]  cnt_h: pwm high level cnt
				cnt_l: pwm low level cnt
				pwm_duty = (cnt_h+cnt_l)/sys_clk
				pwm_width = cnt_h/(cnt_h+cnt_l)
    \param[out] none
    \retval     none
*/
void pwm2_duty_width_config(uint16_t cnt_h,uint16_t cnt_l)
{
	PWM2_L_L = (uint8_t)cnt_l;
	PWM2_L_H = (uint8_t)(cnt_l >> 8);
	PWM2_H_L = (uint8_t)cnt_h;
	PWM2_H_H = (uint8_t)(cnt_h >> 8);
}

/*!
    \brief      pwm3 duty and width config
    \param[in]  cnt_h: pwm high level cnt
				cnt_l: pwm low level cnt
				pwm_duty = (cnt_h+cnt_l)/sys_clk
				pwm_width = cnt_h/(cnt_h+cnt_l)
    \param[out] none
    \retval     none
*/
void pwm3_duty_width_config(uint16_t cnt_h,uint16_t cnt_l)
{
	PWM3_L_L = (uint8_t)cnt_l;
	PWM3_L_H = (uint8_t)(cnt_l >> 8);
	PWM3_H_L = (uint8_t)cnt_h;
	PWM3_H_H = (uint8_t)(cnt_h >> 8);
}
