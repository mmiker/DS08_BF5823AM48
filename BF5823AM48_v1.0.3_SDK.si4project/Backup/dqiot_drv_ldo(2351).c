#ifndef __DQIOT_DRV_LDO_C__
#define __DQIOT_DRV_LDO_C__

#include "dqiot_drv.h"
#include "dqiot_drv_ldo.h"

/*
parameter: 
	none
return :
	none
*/
void drv_ext_ldo_init(void)
{
	gpio_init(EXT_LDO_PORT,EXT_LDO_PIN,GPIO_MODE_OUT);
	gpio_bit_reset(EXT_LDO_PORT,EXT_LDO_PIN);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void drv_ext_ldo_on(void)
{
	gpio_bit_set(EXT_LDO_PORT,EXT_LDO_PIN);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void drv_ext_ldo_off(void)
{
	gpio_bit_reset(EXT_LDO_PORT,EXT_LDO_PIN);
	return;
}



#endif
