#ifndef __DQIOT_DRV_RESET_C__
#define __DQIOT_DRV_RESET_C__

#include "dqiot_drv.h"
#include "dqiot_drv_reset.h"
#include "delay.h"

/*
parameter: 
	none
return :
	none
*/
void drv_reset_gpio_init(void)
{
	gpio_init(MOTOR_PWREN_PORT,MOTOR_PWREN_PIN,GPIO_MODE_IPU);
	return;
}


#endif

