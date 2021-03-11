#ifndef __DQIOT_DRV_FP_H__
#define __DQIOT_DRV_FP_H__

#include "mmi_feature.h"
#ifdef __LOCK_FP_SUPPORT__

#include "dqiot_gpio.h"


/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_fp_gpio_init(void);

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_fp_gpio_deinit(void);

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_fp_poweron(void);


/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_fp_poweroff(void);


#endif
#endif//__DQIOT_DRV_FP_H__

