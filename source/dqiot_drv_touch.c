#ifndef __DQIOT_DRV_TOUCH_C__
#define __DQIOT_DRV_TOUCH_C__

#include "dqiot_drv.h"
#include "byd_ctk.h"
#include "byd_init.h"

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_touch_init(void)
{
#ifdef BYD_CTK_ENABLE
	byd_ctk_init();
#endif
}

/*
parameter: 
	none
return :
	none
*/
uint8_t dqiot_drv_touch_check(void)
{
#ifdef BYD_CTK_ENABLE
	CSD_ENABLE();
	byd_ctk_normal();
	CSD_DISABLE();
#endif
	if(g_bTouchFlag) return 1;

	return 0;
}

/*
parameter: 
	none
return :
	none
*/
uint8_t dqiot_drv_touch_work(void)
{
	u8 i = 0xFF;
#ifdef BYD_CTK_ENABLE
	byd_ctk_normal();
	if(g_bTouchFlag)//tk touch
	{
		i = byd_get_maxkey();
	}

#endif
	return i;
}

/*
parameter: 
	none
return :
	none
*/
uint8_t dqiot_drv_get_touch_flag(void)
{
	return byd_get_touch_flag();
}

/*
parameter: 
	none
return :
	none
*/
uint8_t dqiot_drv_get_touch_value(void)
{
	if(byd_get_touch_flag())
		return byd_get_touch_index();
	else
		return 0xFF;
}

#endif
