#ifndef __MMI_WIFI_C__
#define __MMI_WIFI_C__

#include "dqiot_drv_wifi.h"
#include "mmi_sys.h"
#include "mmi_ms.h"
#include "mmi_audio.h"
#include "mmi_fs.h"

static unsigned int wifi_check_times = 0;

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_setting(void)
{
	mmi_dq_ms_set_sys_state(SYS_STATUS_WIFI_MODE);
	mmi_dq_aud_play_with_id(AUD_ID_LOW_BATTERY);
	wifi_net_connect_send();
	wifi_check_times = 0;
	mmi_dq_sys_set_wifi_check();
	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_connected_fail(void)
{
	mmi_dq_fs_set_wifi_setting(0);
	if(SYS_STATUS_WIFI_MODE == mmi_dq_ms_get_sys_state())
		mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);
	else if(SYS_STATUS_ENTER_SLEEP == mmi_dq_ms_get_sys_state())
		mmi_dq_sys_wake_up();
	mmi_dq_aud_play_with_id(AUD_BASE_ID_FAIL);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_connected_suc(void)
{	
	mmi_dq_fs_set_wifi_setting(1);
	if(SYS_STATUS_WIFI_MODE == mmi_dq_ms_get_sys_state())
		mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);
	else if(SYS_STATUS_ENTER_SLEEP == mmi_dq_ms_get_sys_state())
		mmi_dq_sys_wake_up();
	mmi_dq_aud_play_with_id(AUD_BASE_ID_SUCCESS);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_check_connect(void)
{
	wifi_check_times++;
	if(wifi_net_connect_state() == 1)
		mmi_dq_wifi_connected_suc();
	else if(wifi_check_times >= 150)
		mmi_dq_wifi_connected_fail();
	else
		mmi_dq_sys_set_wifi_check();
}




#endif
