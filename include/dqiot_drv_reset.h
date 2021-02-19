#ifndef __DQIOT_DRV_RESET_H__
#define __DQIOT_DRV_RESET_H__

#include "dqiot_gpio.h"

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_reset_gpio_init(void);

/*
parameter: 
	none
return :
	none
*/
uint8_t dqiot_drv_get_reset_pin(void);


#endif//__DQIOT_DRV_RESET_H__

