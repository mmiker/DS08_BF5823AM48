#ifndef __DQIOT_DRV_RESET_C__
#define __DQIOT_DRV_RESET_C__

#include "dqiot_drv.h"

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_reset_gpio_init(void)
{
	gpio_init(RESET_PORT,RESET_PIN,GPIO_MODE_IPU);
	return;
}

/*
parameter: 
	none
return :
	none
*/
uint8_t dqiot_drv_get_reset_pin(void)
{
	return gpio_bit_get(RESET_PORT, RESET_PIN);
}

#endif

