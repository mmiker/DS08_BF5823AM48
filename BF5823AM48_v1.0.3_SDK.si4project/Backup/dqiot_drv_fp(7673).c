#ifndef __DQIOT_DRV_FP_C__
#define __DQIOT_DRV_FP_C__

#include "dqiot_drv.h"
#include "dqiot_drv_fp.h"
#include "delay.h"

/*
parameter: 
	none
return :
	none
*/
void drv_fp_init(void)
{
	gpio_init(FP_PWR_PORT,FP_PWR_PIN,GPIO_MODE_OUT);
	gpio_bit_reset(FP_PWR_PORT,FP_PWR_PIN);

	gpio_init(FP_INT_PORT,FP_INT_PIN,GPIO_MODE_IN_FLOATING);

	return;
}

#endif//__DQIOT_DRV_FP_C__

