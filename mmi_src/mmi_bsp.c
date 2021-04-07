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
	dqiot_drv_init();
	
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
#ifdef __LOCK_FP_SY_SUPPORT__
	FP_Light(FP_NONE_COLOR);
#endif
	dqiot_drv_enter_sleep();
}
#endif
