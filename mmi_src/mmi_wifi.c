#ifndef __MMI_WIFI_C__
#define __MMI_WIFI_C__

#include "mmi_feature.h"
#include "dqiot_drv_wifi.h"
#include "mmi_sys.h"
#include "mmi_ms.h"
#include "mmi_audio.h"
#include "mmi_fs.h"
#include "delay.h"

static unsigned int wifi_check_times = 0;


/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_wakeup(void)
{
	wifi_wake_up();
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_sleep(void)
{
	wifi_sleep_mode();
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_wifi_setting(void)
{
	unsigned char ret = 1;
	wifi_wake_up();
	delay_ms(250);
	if(wifi_net_connect_send() == 0)
	{
		delay_ms(250);
		ret = wifi_net_connect_send();
	}
	if(ret == 1)
	{
		wifi_check_times = 1;
		mmi_dq_sys_set_wifi_check(0);
	}
	return ret;
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
	static unsigned char wifi_check_connect_flag = 0;
	wifi_check_times++;
	if(wifi_net_connect_state() == 1)
	{
		wifi_check_connect_flag++;
		if(wifi_check_connect_flag>=2)
		{
			mmi_dq_wifi_connected_suc();
			wifi_check_connect_flag = 0;
			wifi_check_times = 0;
			return;
		}
	}
	else
	{
		wifi_check_connect_flag = 0;
	}
	
	if(wifi_check_times > 600)
	{
		mmi_dq_wifi_connected_fail();
		wifi_check_times = 0;
	}
	else
		mmi_dq_sys_set_wifi_check(0);
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_wifi_open_ask(void)
{
	unsigned char ret = 1;
	if(wifi_check_times > 0)
		return 0;
	mmi_dq_wifi_wakeup();
	delay_ms(250);
	if(wifi_open_ask() == 0)
	{
		delay_ms(250);
		ret =  wifi_open_ask();
	}
	if(ret == 1)
	{
		wifi_check_times = 1;
		mmi_dq_sys_set_wifi_check(1);
	}
	return ret;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_check_open(void)
{
	unsigned char state = wifi_open_reply_get();
	wifi_check_times++;
	if(state == 1)
	{
		if(SYS_STATUS_ENTER_SLEEP == mmi_dq_ms_get_sys_state())
			mmi_dq_sys_wake_up();
		mmi_dq_sys_door_open(SYS_OPEN_BY_WIFI);
		wifi_check_times = 0;
	}
	else if(state == 2 || wifi_check_times > 300)
	{
		if(SYS_STATUS_ENTER_SLEEP == mmi_dq_ms_get_sys_state())
			mmi_dq_sys_wake_up();
		mmi_dq_aud_play_with_id(AUD_BASE_ID_FAIL);
		wifi_check_times = 0;
	}
	else
		mmi_dq_sys_set_wifi_check(1);

}


/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_add_password(void)
{
	mmi_dq_wifi_wakeup();

	delay_ms(150);
	wifi_add_password();
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_del_password(void)
{
	mmi_dq_wifi_wakeup();

	delay_ms(150);

	wifi_del_password();
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_add_fp(void)
{
	mmi_dq_wifi_wakeup();

	delay_ms(150);

	wifi_add_fp();
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_del_fp(void)
{
	mmi_dq_wifi_wakeup();

	delay_ms(150);

	wifi_del_fp();
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_open_by_password(void)
{
	mmi_dq_wifi_wakeup();

	delay_ms(100);

	wifi_open_by_password();
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_open_by_fp(void)
{
	mmi_dq_wifi_wakeup();

	delay_ms(150);

	wifi_open_by_fp();
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_open_by_rfid(void)
{
	mmi_dq_wifi_wakeup();

	delay_ms(150);

	wifi_open_by_rfid();
}


/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_open_by_key(void)
{
	mmi_dq_wifi_wakeup();

	delay_ms(150);

	wifi_open_by_key();
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_open_by_wifi(void)
{

	wifi_open_by_wifi();
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_door_close(void)
{

	wifi_door_close();
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_via_alarm(void)
{
	mmi_dq_wifi_wakeup();

	delay_ms(150);

	wifi_via_alarm();
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_pw_alarm(void)
{
	mmi_dq_wifi_wakeup();

	delay_ms(150);

	wifi_pw_alarm();
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_fp_alarm(void)
{
	mmi_dq_wifi_wakeup();

	delay_ms(150);

	wifi_fp_alarm();
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_rfid_alarm(void)
{
	mmi_dq_wifi_wakeup();

	delay_ms(150);

	wifi_rf_alarm();
}


/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_lowpower_alarm(void)
{
	static uint8_t wifi_lowpower_flag = 0;
	if(wifi_lowpower_flag == 0)
	{
		wifi_lowpower_flag = 1;
		mmi_dq_wifi_wakeup();

		delay_ms(150);
	
		wifi_lowpower_alarm();
	}
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_wifi_get_running_flag(void)
{
	if(wifi_check_times>0)
		return 1;
	return 0;
}

#endif
