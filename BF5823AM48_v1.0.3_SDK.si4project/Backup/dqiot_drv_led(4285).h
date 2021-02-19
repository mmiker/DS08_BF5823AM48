#ifndef __DQIOT_DRV_LED_H__
#define __DQIOT_DRV_LED_H__

#include "dqiot_gpio.h"

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_key_led_gpio_init(void);

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_key_led_on(void);

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_key_led_off(void);

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_rgb_led_gpio_init(void);


#endif
