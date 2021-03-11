#ifndef __DQIOT_DRV_MOTOR_H__
#define __DQIOT_DRV_MOTOR_H__
#include "mmi_feature.h"
#ifdef __LOCK_MOTOR_SUPPORT__
#include "dqiot_gpio.h"
/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_motor_gpio_init(void);

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_motor_gpio_deinit(void);

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_motor_init(void);

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_motor_turn_right(void);

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_motor_turn_back(void);

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_motor_stop(void);
#endif
#endif//__DQIOT_DRV_MOTOR_H__

