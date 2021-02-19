#ifndef __DQIOT_DRV_FP_H__
#define __DQIOT_DRV_FP_H__

#include "mcu02_gpio.h"

#define FP_PWR_PORT	GPIOF
#define FP_PWR_PIN	GPIO_PIN_7

#define FP_INT_PORT	GPIOF
#define FP_INT_PIN	GPIO_PIN_6

/*
parameter: 
	none
return :
	none
*/
void drv_fp_init(void);

#endif//__DQIOT_DRV_FP_H__

