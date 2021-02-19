#ifndef __MMI_BSP_C__
#define __MMI_BSP_C__

#include "mmi_fps.h"
#include "mmi_feature.h"
#include "dqiot_drv.h"

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_bsp_init(void)
{
	dqiot_drv_gpio_init();
	
	dqiot_drv_ext_ldo_on();

	dqiot_drv_key_led_on();

	
	dqiot_drv_timer2_init();
	
	dqiot_drv_timer2_start();
	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_bsp_wake_up(void)
{
	dqiot_drv_wake_up();
	
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_bsp_enter_sleep(void)
{
	dqiot_drv_enter_sleep();

}
#endif
