#ifndef __MMI_SYS_C__
#define __MMI_SYS_C__

#include "mmi_feature.h"
#include "mmi_sys.h"
#include "mmi_audio.h"
#include "mmi_rst.h"
#include "mmi_queue.h"
#include "dqiot_drv.h"
#include "mmi_ms.h"
#include "mmi_fs.h"
#include "mmi_bsp.h"
#include "mmi_motor.h"
#include "mmi_wifi.h"
#include "mmi_decode.h"
// #include <stdio.h>

#ifdef __LOCK_VIRTUAL_PASSWORD__
#include "mmi_rtc.h"
#define MMI_MAX_ERROR_TIMES 5
#define MMI_ERROR_LOCK_TIME 60
// #define MMI_TIMER_BASE_TIME 4
#define MMI_TIMER_ENTER_SLEEP 10000
#define MMI_TIMER_ENTER_SLEEP_COUNT (MMI_TIMER_ENTER_SLEEP / MMI_TIMER_BASE_TIME)
#define MMI_TIMER_ENTER_SLEEP_DELAY 20000
#define MMI_TIMER_ENTER_SLEEP_DELAY_COUNT (MMI_TIMER_ENTER_SLEEP_DELAY / MMI_TIMER_BASE_TIME)
static uint32_t g_last_error_time = 0;
static unsigned char g_multiple_error_times = 0;
static uint8_t lock_easy_open_mode = 0;
static uint8_t lock_inside_lock = 0;
//static unsigned int g_enter_sleep_set_time = MMI_TIMER_ENTER_SLEEP_COUNT;
#endif //__LOCK_VIRTUAL_PASSWORD__

// extern void printfS(char *show, char *status);
// extern void printfV(char *show, int value);

static unsigned char g_sys_door_open_flag = 0;

static unsigned int g_timer2_sleep_count = 0;
static unsigned int g_timer2_count = 0;
static unsigned int g_timer2_set_count = 0;
static unsigned char g_timer2_flag = 0;

static unsigned char g_wifi_check_flag = 0;
static unsigned char g_wifi_check_count = 0;
static unsigned char g_wifi_check_type = 0;

/* RFID */
static unsigned char g_rfid_flag = 0;

#define LOCK_MAX_EEROR_TIMES 5
static unsigned char g_lock_error_flag = 0;
static unsigned int g_lock_error_count = 0;

timer2_delay_pro g_timer2_delay_pro = 0;

#define MMI_TIMER_BASE_TIME 100
#define MMI_TIMER_ENTER_SLEEP 10000
#define MMI_TIMER_ENTER_SLEEP_COUNT (MMI_TIMER_ENTER_SLEEP / MMI_TIMER_BASE_TIME)
#define MMI_TIMER_ENTER_SLEEP_DELAY 20000
#define MMI_TIMER_ENTER_SLEEP_DEALY_COUNT (MMI_TIMER_ENTER_SLEEP_DELAY / MMI_TIMER_BASE_TIME)
#define MMI_TIMER_DOOR_OPEN 6000
#define MMI_TIMER_DOOR_OPEN_COUNT (MMI_TIMER_DOOR_OPEN / MMI_TIMER_BASE_TIME)
#define MMI_TIMER_MOTOR 300
#define MMI_TIMER_MOTOR_COUNT (MMI_TIMER_MOTOR / MMI_TIMER_BASE_TIME)
#define MMI_TIMER_WIFI_CHECK 1000
#define MMI_TIMER_WIFI_CHECK_COUNT (MMI_TIMER_WIFI_CHECK / MMI_TIMER_BASE_TIME)
#define MMI_WIFI_SETTING_DELAY 60000
#define MMI_WIFI_SETTING_DELAY_COUNT (MMI_WIFI_SETTING_DELAY / MMI_TIMER_BASE_TIME)
#define MMI_LOCK_ERROR_DELAY 60000
#define MMI_LOCK_ERROR_DELAY_COUNT (MMI_LOCK_ERROR_DELAY / MMI_TIMER_BASE_TIME)
/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_init(void)
{
	mmi_InitQueue();
	mmi_ms_pwd_init_var();
	mmi_dq_fs_init();
}
/*
parameter: 
	none
return :
	none
*/
// #ifndef __LOCK_VIRTUAL_PASSWORD__
void mmi_dq_sys_show_message_with_id(unsigned char text_id, unsigned long time_msec)
{
	unsigned char audio_id = 0;

	time_msec = 0;

#ifdef __LOCK_AUDIO_SUPPORT__
	audio_id = mmi_dq_aud_get_audio_id(text_id);
	mmi_dq_aud_play_with_id(audio_id);
#endif
	return;
}
// #endif

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_lock_add_admin_suc(void)
{
	mmi_dq_fs_set_admin_status(1);

	mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);
}

/*
function: system enter sleep
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_enter_sleep(void)
{
	mmi_dq_bsp_enter_sleep();

	g_timer2_flag = 0;
	g_sys_door_open_flag = 0;

	mmi_dq_ms_set_sys_state(SYS_STATUS_ENTER_SLEEP);
}

/*
function: system wake up
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_wake_up(void)
{

	mmi_dq_bsp_wake_up();
	if (mmi_dq_sys_check_vbat() == 0)
	{
#ifdef __LOCK_WIFI_SUPPORT__
		mmi_dq_wifi_wakeup();
#endif
#ifdef __LOCK_FP_SUPPORT__
		mmi_dq_fp_init(); //握手、点灯
#endif
		mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);
	}
}

/*
function: 
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_door_open_cb(void)
{
#ifdef __LOCK_MOTOR_SUPPORT__
	mmi_dq_motor_stop();
#endif
#ifdef __LOCK_AUDIO_SUPPORT__
	mmi_dq_aud_play_with_id(AUD_ID_DOOR_OPEN);
#endif
	mmi_dq_sys_set_delay_event(MMI_TIMER_DOOR_OPEN_COUNT, mmi_dq_sys_door_close);
}

/*
function: 
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_door_open(sys_open_type type)
{
#ifdef __LOCK_BUS_SUPPORT__
	if ((mmi_dq_fs_get_business_flag() == 1) && ((type & SYS_OPEN_BY_110) == 0) && (SYS_OPEN_BY_WIFI != type))
	{
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_IS_BUSINESS);
#endif
#ifdef __LOCK_WIFI_SUPPORT__
		switch (type)
		{
		case SYS_OPEN_BY_PASSWORD:
			mmi_dq_wifi_pw_alarm();
			break;
		case SYS_OPEN_BY_FP:
			mmi_dq_wifi_fp_alarm();
			break;
		case SYS_OPEN_BY_RFID:
			mmi_dq_wifi_rfid_alarm();
			break;
		}
#endif
		return;
	}
#endif
	g_lock_error_flag = 0;
	if ((mmi_dq_fs_get_open_mode() == SYS_OPEN_MODE_DBL) && (SYS_OPEN_BY_WIFI != type) && ((type & SYS_OPEN_BY_110) == 0))
	{
		if ((g_sys_door_open_flag & (~type)) != 0)
		{
			g_sys_door_open_flag = 0;
		}
		else
		{
			g_sys_door_open_flag |= type;
#ifdef __LOCK_AUDIO_SUPPORT__
			mmi_dq_aud_play_with_id(AUD_ID_SYS_DBL_OPEN_MODE);
#endif
			return;
		}
	}

	mmi_dq_ms_set_sys_state(SYS_STATUS_DOOR_OPEN);

#ifdef __LOCK_MOTOR_SUPPORT__
	mmi_dq_motor_turn_right();
#endif
	//mmi_dq_wifi_open_door();
	mmi_dq_sys_set_delay_event(MMI_TIMER_MOTOR_COUNT, mmi_dq_sys_door_open_cb);

#ifdef __LOCK_WIFI_SUPPORT__
	switch (type)
	{
#ifdef __LOCK_110_SUPPORT__
	case SYS_OPEN_BY_110_PASSWORD:
		mmi_dq_wifi_send_pwd_110(get_index);
		// printfV("get_index",(int)get_index);
		break;
	case SYS_OPEN_BY_110_FP:
		mmi_dq_wifi_send_fp_110(get_index);
		// printfV("get_index",(int)get_index);
		break;
#endif
	case SYS_OPEN_BY_PASSWORD:
		mmi_dq_wifi_open_by_password(get_index);
		// printfV("get_index",(int)get_index);
		break;
#ifdef __LOCK_FP_SUPPORT__
	case SYS_OPEN_BY_FP:
		mmi_dq_wifi_open_by_fp(get_index);
		// printfV("get_index",(int)get_index);
		break;
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
	case SYS_OPEN_BY_RFID:
		mmi_dq_wifi_open_by_rfid(get_index);
		// printfV("get_index",(int)get_index);
		break;
#endif
	case SYS_OPEN_BY_WIFI:
		mmi_dq_wifi_open_by_wifi();
		break;
	}

	if (pv_add_switch == 0)
		;
	else if (pv_add_switch == 1)
		mmi_dq_wifi_take_photos(); //拍照
	else if (pv_add_switch == 2)
		mmi_dq_wifi_take_videos(); //录像
	else if (pv_add_switch == 3)
	{
		mmi_dq_wifi_take_photos(); //拍照
		mmi_dq_wifi_take_videos(); //录像
	}

#endif
}

/*
function: 
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_door_open_fail(sys_open_type type)
{
	g_lock_error_count = 0;
	g_lock_error_flag++;
	switch (type)
	{
	case SYS_OPEN_BY_PASSWORD:
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_PWD_WRONG_TRY);
#endif
#ifdef __LOCK_WIFI_SUPPORT__
		if (g_lock_error_flag >= LOCK_MAX_EEROR_TIMES)
			mmi_dq_wifi_pw_alarm();
#endif
		break;
#ifdef __LOCK_FP_SUPPORT__
	case SYS_OPEN_BY_FP:
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_FP_WRONG_TRY);
#endif
#ifdef __LOCK_WIFI_SUPPORT__
		if (g_lock_error_flag >= LOCK_MAX_EEROR_TIMES)
			mmi_dq_wifi_fp_alarm();
#endif
		break;
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
	case SYS_OPEN_BY_RFID:
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_RFCARD_WRONG_TRY);
#endif
#ifdef __LOCK_WIFI_SUPPORT__
		if (g_lock_error_flag >= LOCK_MAX_EEROR_TIMES)
			mmi_dq_wifi_rfid_alarm();
#endif
		break;
#endif
	}
}

/*
function: 
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_sys_door_state_check(void)
{
	if (g_lock_error_flag >= LOCK_MAX_EEROR_TIMES)
		return 1;
	return 0;
}

/*
function: 
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_door_close_cb(void)
{
#ifdef __LOCK_MOTOR_SUPPORT__
	mmi_dq_motor_stop();
#endif
#ifdef __LOCK_AUDIO_SUPPORT__
	mmi_dq_aud_play_with_id(AUD_ID_DOOR_CLOSE);
#endif
	mmi_dq_ms_set_sys_state(SYS_STATUS_WAIT_FOR_ENTER_SLEEP);
}

/*
function: 
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_door_close(void)
{
#ifdef __LOCK_MOTOR_SUPPORT__
	mmi_dq_motor_turn_back();
#endif
	//mmi_dq_wifi_close_door();
	mmi_dq_sys_set_delay_event(MMI_TIMER_MOTOR_COUNT, mmi_dq_sys_door_close_cb);
}

/*
function: 
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_aud_end(void)
{
	mmi_dq_ms_set_msg_que(QUE_EVENT_AUDIO_END, QUE_PRO_LOW, 0);
}

/*
function: 
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_time_out_handle(void)
{
	SYS_BASE_STATUS state = mmi_dq_ms_get_sys_state();

	if ((state >= SYS_STATUS_ADD_PWD && state < SYS_STATUS_ADD_ADMIN_PWD) || (state == SYS_STATUS_SYS_MENU) || (state == SYS_STATUS_CHG_ADMIN_PWD))
	{
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_TIME_OUT);
#endif
		mmi_dq_ms_set_sys_state(SYS_STATUS_WAIT_FOR_ENTER_SLEEP);
	}
#ifdef __LOCK_FP_SUPPORT__
	else if (state == SYS_STATUS_ADD_ADMIN_FP1 || state == SYS_STATUS_ADD_ADMIN_FP2)
	{
		if (mmi_dq_fs_get_admin_status() == 0)
			g_timer2_sleep_count = 0;
		else
		{
#ifdef __LOCK_AUDIO_SUPPORT__
			mmi_dq_aud_play_with_id(AUD_ID_TIME_OUT);
#endif
			mmi_dq_ms_set_sys_state(SYS_STATUS_WAIT_FOR_ENTER_SLEEP);
		}
	}
#endif
	else if (state == SYS_STATUS_ADD_ADMIN_PWD)
	{
		g_timer2_sleep_count = 0;
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_ADD_ADMIN_PWD_FIRST);
#endif
	}
	else
		mmi_dq_ms_set_sys_state(SYS_STATUS_WAIT_FOR_ENTER_SLEEP);
}

/*
function: 
parameter: 
	none
return :
	none
*/
void System_timer_event_handler(void)
{
	SYS_BASE_STATUS state = mmi_dq_ms_get_sys_state();

	g_rfid_flag = 1; /* RFID */

	if (g_timer2_flag == 1)
	{
		g_timer2_count++;
		if (g_timer2_count >= g_timer2_set_count)
		{
			g_timer2_flag = 2;
			g_timer2_count = 0;
			//mmi_dq_ms_set_msg_que(QUE_EVENT_TIMER_END,QUE_PRO_LOW,0);
		}
	}

	if (g_wifi_check_flag == 1)
	{
		g_wifi_check_count++;
		if (g_wifi_check_count >= MMI_TIMER_WIFI_CHECK_COUNT)
		{
			g_wifi_check_flag = 2;
			g_wifi_check_count = 0;
		}
	}

	if (g_lock_error_flag > 0)
	{
		g_lock_error_count++;
		if (g_lock_error_count >= MMI_LOCK_ERROR_DELAY_COUNT)
			g_lock_error_flag = 0;
	}

	if ((mmi_dq_rst_timer_event() != 0) && (SYS_STATUS_ENTER_SLEEP != state && SYS_STATUS_WAIT_FOR_ENTER_SLEEP != state) && (g_timer2_flag != 1) && (mmi_dq_ms_get_run_flag() == 0)
#ifdef __LOCK_WIFI_SUPPORT__
		&& (mmi_dq_wifi_get_running_flag() == 0)
#endif
	)
	{
		unsigned char flag = 0;
		g_timer2_sleep_count++;
		if (state == SYS_STATUS_ADD_PWD || state == SYS_STATUS_DEL_PWD || state == SYS_STATUS_ADD_ADMIN_PWD
#ifdef __LOCK_FP_SUPPORT__
			|| state == SYS_STATUS_ADD_ADMIN_FP1 || state == SYS_STATUS_ADD_ADMIN_FP2 || state == SYS_STATUS_ADD_FP || state == SYS_STATUS_DEL_FP
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
			|| state == SYS_STATUS_ADD_RFID || state == SYS_STATUS_DEL_RFID
#endif
		)
		{
			if (g_timer2_sleep_count > MMI_TIMER_ENTER_SLEEP_DEALY_COUNT)
			{
				flag = 1;
			}
		}
		else if (g_timer2_sleep_count > MMI_TIMER_ENTER_SLEEP_COUNT)
		{
			flag = 1;
		}

		if (flag)
		{
			mmi_dq_sys_time_out_handle();
		}
	}
	else
		g_timer2_sleep_count = 0;
}

/*
function: 
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_sys_get_rfid_flag(void)
{
	if (g_rfid_flag == 1)
	{
		g_rfid_flag = 0;
		return 1;
	}
	return 0;
}

/*
function: 
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_sys_get_wifi_check_flag(void)
{
	if (g_wifi_check_flag == 2)
	{
		g_wifi_check_flag = 0;
		return 1;
	}
	return 0;
}

/*
function: 
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_set_wifi_check(unsigned char type)
{
	g_wifi_check_count = 0;
	g_wifi_check_flag = 1;
	g_wifi_check_type = type;
}

/*
function: 
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_sys_get_wifi_check_type(void)
{
	return g_wifi_check_type;
}

/*
function: 
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_sleep_timer_reset(void)
{
	g_timer2_sleep_count = 0;
	return;
}

/*
function: 
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_sys_get_timer2_flag(void)
{
	if (g_timer2_flag == 2)
	{
		g_timer2_flag = 0;
		return 1;
	}
	return 0;
}

/*
function: 
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_set_delay_event(unsigned int count, timer2_delay_pro pro)
{
	if (count != 0)
	{
		g_timer2_count = 0;
		g_timer2_set_count = count;
		g_timer2_delay_pro = pro;
		g_timer2_flag = 1;
	}
	else
		pro();
}

/*
function: 
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_delay_event_pro(void)
{
	if (g_timer2_delay_pro != 0)
		g_timer2_delay_pro();
}

/*
function: 
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_sys_check_vbat(void)
{
	unsigned char state = adc_VolT();
	if (state > 0)
	{
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_LOW_BATTERY);
#endif
#ifdef __LOCK_WIFI_SUPPORT__
		mmi_dq_wifi_lowpower_alarm();
#endif
		if (state == 2)
		{
			mmi_dq_ms_set_sys_state(SYS_STATUS_LOW_POWER);
			return 1;
		}
	}

	return 0;
}

/**
  * @brief  远程开门
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_sys_wifi_open(void)
{
#ifdef __LOCK_WIFI_SUPPORT__
	if (mmi_dq_wifi_open_ask() == 0)
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_SET_FAIL);
#else
		;
#endif
#endif
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_add_admin_pwd(void)
{
#ifdef __LOCK_AUDIO_SUPPORT__
	mmi_dq_aud_play_with_id(AUD_ID_ADD_ADMIN_PWD_FIRST);
#endif
	mmi_ms_pwd_init_var();
	mmi_dq_ms_set_sys_state(SYS_STATUS_ADD_ADMIN_PWD);
	return;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//*******************************************************************************************************************************************************************************************
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
//				menu part
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//*******************************************************************************************************************************************************************************************
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_add_pwd(void)
{
	if (mmi_dq_fs_get_pwd_unuse_index() == 0xFF)
	{
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_PWD_FULL);
#endif
		mmi_dq_sys_show_cur_menu_list();
	}
	else
	{
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_INPUT_68_PWD);
#endif
		mmi_ms_pwd_init_var();
		mmi_dq_ms_set_sys_state(SYS_STATUS_ADD_PWD);
	}
	return;
}

void mmi_dq_sys_add_pwd_con(void)
{
#ifdef __LOCK_AUDIO_SUPPORT__
	mmi_dq_aud_play_with_id(AUD_ID_CONTINUE_ADD_PWD);
#endif
	mmi_dq_ms_set_sys_state(SYS_STATUS_ADD_PWD_CON);
	return;
}

#ifdef __LOCK_110_SUPPORT__
/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_add_110_pwd(void)
{
	mmi_dq_wifi_wakeup();
	if (mmi_dq_wifi_check() == 1)
	{
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_WIFI_UNFINDE);
#endif
		mmi_dq_sys_show_cur_menu_list();
		return;
	}
#ifdef __LOCK_AUDIO_SUPPORT__
	mmi_dq_aud_play_with_id(AUD_ID_INPUT_68_PWD);
#endif
	mmi_ms_pwd_init_var();
	mmi_dq_ms_set_sys_state(SYS_STATUS_ADD_110_PWD);
	return;
}
#endif
/*
parameter: 
	none
return :
	none
*/
static void mmi_dq_sys_chg_pwd(void)
{
	//mmi_dq_ms_set_sys_state(SYS_STATUS_CHG_PWD);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_del_pwd(void)
{
#ifdef __LOCK_AUDIO_SUPPORT__
	mmi_dq_aud_play_with_id(AUD_ID_INPUT_DEL_NUM);
#endif
	mmi_ms_pwd_init_var();
	mmi_dq_ms_set_sys_state(SYS_STATUS_DEL_PWD);
	return;
}

void mmi_dq_sys_del_pwd_con(void)
{
#ifdef __LOCK_AUDIO_SUPPORT__
	mmi_dq_aud_play_with_id(AUD_ID_DEL_CONFIRM);
#endif
	mmi_dq_ms_set_sys_state(SYS_STATUS_DEL_PWD_CON);
	return;
}

/*
parameter: 
	none
return :
	none
*/
static void mmi_dq_sys_clear_pwd(void)
{
#ifdef __LOCK_AUDIO_SUPPORT__
	mmi_dq_aud_play_with_id(AUD_ID_CLR_PWD_CONFIRM);
#endif
	mmi_dq_ms_set_sys_state(SYS_STATUS_CLR_PWD);
	return;
}

#if defined(__LOCK_FP_SUPPORT__)
/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_add_fp(void)
{
	if (mmi_dq_fs_get_fp_unuse_index() == 0xFF)
	{
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_FP_FULL);
#endif
		mmi_dq_sys_show_cur_menu_list();
	}
	else
	{
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_PRESS_FP);
#endif
		mmi_dq_fp_light(FP_BLUE);
		mmi_ms_opt_time_init();
		mmi_dq_ms_set_sys_state(SYS_STATUS_ADD_FP);
	}
	return;
}

void mmi_dq_sys_add_fp_con(void)
{
#ifdef __LOCK_AUDIO_SUPPORT__
	mmi_dq_aud_play_with_id(AUD_ID_CONTINUE_ADD_PWD);
#endif
	mmi_dq_ms_set_sys_state(SYS_STATUS_ADD_FP_CON);
	return;
}

#ifdef __LOCK_110_SUPPORT__
/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_add_110_fp(void)
{
	mmi_dq_wifi_wakeup();
	if (mmi_dq_wifi_check() == 1)
	{
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_WIFI_UNFINDE);
#endif
		mmi_dq_sys_show_cur_menu_list();
		return;
	}
#ifdef __LOCK_AUDIO_SUPPORT__
	mmi_dq_aud_play_with_id(AUD_ID_PRESS_FP);
#endif
	mmi_dq_fp_light(FP_BLUE);
	mmi_ms_opt_time_init();
	mmi_dq_ms_set_sys_state(SYS_STATUS_ADD_110_FP);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_del_110_fp(void)
{
	mmi_dq_wifi_wakeup();
	if (mmi_dq_wifi_check() == 1)
	{
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_WIFI_UNFINDE);
#endif
		mmi_dq_sys_show_cur_menu_list();
		return;
	}
#ifdef __LOCK_AUDIO_SUPPORT__
	mmi_dq_aud_play_with_id(AUD_ID_PRESS_FP);
#endif
	mmi_dq_fp_light(FP_BLUE);
	mmi_ms_opt_time_init();
	mmi_dq_ms_set_sys_state(SYS_STATUS_DEL_110_FP);
	return;
}

#endif

/*
parameter: 
	none
return :
	none
*/
static void mmi_dq_sys_chg_fp(void)
{
	//mmi_dq_ms_set_sys_state(SYS_STATUS_CHG_FP);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_del_fp(void)
{
#ifdef __LOCK_AUDIO_SUPPORT__
	mmi_dq_aud_play_with_id(AUD_ID_INPUT_DEL_FP_NUM);
#endif
	mmi_dq_fp_light(FP_BLUE);
	mmi_ms_opt_time_init();
	mmi_dq_ms_set_sys_state(SYS_STATUS_DEL_FP);
	return;
}

void mmi_dq_sys_del_fp_con(void)
{
#ifdef __LOCK_AUDIO_SUPPORT__
	mmi_dq_aud_play_with_id(AUD_ID_DEL_CONFIRM);
#endif
	mmi_dq_ms_set_sys_state(SYS_STATUS_DEL_FP_CON);
	return;
}

/*
parameter: 
	none
return :
	none
*/
static void mmi_dq_sys_clear_fp(void)
{
#ifdef __LOCK_AUDIO_SUPPORT__
	mmi_dq_aud_play_with_id(AUD_ID_CLR_FP_CONFIRM);
#endif
	mmi_dq_ms_set_sys_state(SYS_STATUS_CLR_FP);
	return;
}
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_add_rf(void)
{

	if (mmi_dq_fs_get_rfid_unuse_index() == 0xFF)
	{
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_RFCARD_FULL);
#endif
		mmi_dq_sys_show_cur_menu_list();
	}
	else
	{
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_PRESS_RFCARD);
#endif
		mmi_ms_opt_time_init();
		mmi_dq_ms_set_sys_state(SYS_STATUS_ADD_RFID);
	}
	return;
}

void mmi_dq_sys_add_rf_con(void)
{
#ifdef __LOCK_AUDIO_SUPPORT__
	mmi_dq_aud_play_with_id(AUD_ID_CONTINUE_ADD_PWD);
#endif
	mmi_dq_ms_set_sys_state(SYS_STATUS_ADD_RFID_CON);
	return;
}

/*
parameter: 
	none
return :
	none
*/
static void mmi_dq_sys_chg_rf(void)
{
	//mmi_dq_ms_set_sys_state(SYS_STATUS_CHG_RFID);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_del_rf(void)
{
#ifdef __LOCK_AUDIO_SUPPORT__
	mmi_dq_aud_play_with_id(AUD_ID_INPUT_DEL_RFCARD_NUM);
#endif
	mmi_ms_opt_time_init();
	mmi_dq_ms_set_sys_state(SYS_STATUS_DEL_RFID);
	return;
}

void mmi_dq_sys_del_rf_con(void)
{
#ifdef __LOCK_AUDIO_SUPPORT__
	mmi_dq_aud_play_with_id(AUD_ID_DEL_CONFIRM);
#endif
	mmi_dq_ms_set_sys_state(SYS_STATUS_DEL_RFID_CON);
	return;
}

/*
parameter: 
	none
return :
	none
*/
static void mmi_dq_sys_clear_rf(void)
{
#ifdef __LOCK_AUDIO_SUPPORT__
	mmi_dq_aud_play_with_id(AUD_ID_CLR_RFCARD_CONFIRM);
#endif
	mmi_dq_ms_set_sys_state(SYS_STATUS_CLR_RFID);
	return;
}
#endif

#ifdef __LOCK_DECODE_SUPPORT__
/**
  * @brief  add 8key from decode
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void mmi_dq_sys_add_decode(void)
{
	if (mmi_dq_fs_get_decode_unuse_index() == 0xFF)
	{
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_ADD_FAIL_RETRY);
#endif
		mmi_dq_sys_show_cur_menu_list();
	}
	else
	{
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_INPUT_68_PWD);
#endif
		mmi_ms_opt_time_init();
		mmi_dq_ms_set_sys_state(SYS_STATUS_ADD_DECODE_RANDOM);
	}
	return;
}
#endif

/*
parameter: 
	none
return :
	none
*/
static void mmi_dq_sys_open_pro_sound(void)
{
	mmi_dq_sys_set_menu_father_id(STR_ID_SETTING);

	if (mmi_dq_fs_set_pro_sound(1) == RET_SUCESS)
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_OPEN_PRO_AUDIO_SUCESS)
#endif
			;
	else
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_OPEN_PRO_AUDIO_FAIL)
#endif
			;

	mmi_dq_sys_show_cur_menu_list();
	return;
}

/*
parameter: 
	none
return :
	none
*/
static void mmi_dq_sys_close_pro_sound(void)
{
	mmi_dq_sys_set_menu_father_id(STR_ID_SETTING);

	if (mmi_dq_fs_set_pro_sound(0) == RET_SUCESS)
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_CLOSE_PRO_AUDIO_SUCESS)
#endif
			;
	else
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_CLOSE_PRO_AUDIO_FAIL)
#endif
			;

	mmi_dq_sys_show_cur_menu_list();
	return;
}

/*
parameter: 
	none
return :
	none
*/
static void mmi_dq_sys_sin_open_mode(void)
{
	mmi_dq_sys_set_menu_father_id(STR_ID_SETTING);

	if (mmi_dq_fs_set_open_mode(SYS_OPEN_MODE_SIN) == RET_SUCESS)
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_SIN_OPEN_MODE_SUCESS)
#endif
			;
	else
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_SIN_OPEN_MODE_FAIL)
#endif
			;

	mmi_dq_sys_show_cur_menu_list();
	return;
}

/*
parameter: 
	none
return :
	none
*/
static void mmi_dq_sys_dbl_open_mode(void)
{
	mmi_dq_sys_set_menu_father_id(STR_ID_SETTING);

	if (mmi_dq_fs_set_open_mode(SYS_OPEN_MODE_DBL) == RET_SUCESS)
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_DBL_OPEN_MODE_SUCESS)
#endif
			;
	else
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_DBL_OPEN_MODE_FAIL)
#endif
			;

	mmi_dq_sys_show_cur_menu_list();
	return;
}

#if defined(__LOCK_FP_SUPPORT__)
/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_chg_admin_fp_No1(void)
{
#ifdef __LOCK_AUDIO_SUPPORT__
	mmi_dq_aud_play_with_id(AUD_ID_NEW_ADMIN_FP);
#endif
	mmi_dq_fp_light(FP_BLUE);
	mmi_ms_opt_time_init();
	mmi_dq_ms_set_sys_state(SYS_STATUS_ADD_ADMIN_FP1);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_chg_admin_fp_No2(void)
{
#ifdef __LOCK_AUDIO_SUPPORT__
	mmi_dq_aud_play_with_id(AUD_ID_NEW_ADMIN_FP);
#endif
	mmi_dq_fp_light(FP_BLUE);
	mmi_ms_opt_time_init();
	mmi_dq_ms_set_sys_state(SYS_STATUS_ADD_ADMIN_FP2);
	return;
}
#endif

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_chg_admin_pwd(void)
{
#ifdef __LOCK_AUDIO_SUPPORT__
	mmi_dq_aud_play_with_id(AUD_ID_INPUT_NEW_ADMIN_PWD);
#endif
	mmi_ms_pwd_init_var();
	mmi_dq_ms_set_sys_state(SYS_STATUS_CHG_ADMIN_PWD);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_restore_lock(void)
{
	unsigned char retval = 0;
	mmi_dq_ms_set_sys_state(SYS_STATUS_RESTORE_LOCK);

	if (RET_SUCESS != mmi_dq_fs_clr_set())
		retval = 1;
	if (RET_SUCESS != mmi_dq_fs_clr_pwd())
		retval = 1;
#ifdef __LOCK_FP_SUPPORT__
	if (RET_SUCESS != mmi_dq_fs_clr_fp())
		retval = 1;
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
	if (RET_SUCESS != mmi_dq_fs_clr_rfid())
		retval = 1;
#endif

	if (retval == 0)
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_RESTORE_SUCESS)
#endif
			;
	else
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_RESTORE_FAIL)
#endif
			;

	mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);
	return;
}

/*
parameter: 
	none
return :
	none
*/
static void mmi_dq_sys_restore_lock_con(void)
{
#ifdef __LOCK_AUDIO_SUPPORT__
	mmi_dq_aud_play_with_id(AUD_ID_RESTORE_LOCK_CONTINUE_CONFIRM);
#endif
	mmi_dq_ms_set_sys_state(SYS_STATUS_RESTORE_LOCK_CON);
}

#ifdef __LOCK_WIFI_SUPPORT__

/**
  * @brief  智能能配网
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
static void mmi_dq_sys_wifi_setting(void)
{
	if (0 == mmi_dq_wifi_setting())
	{
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_SET_FAIL);
#endif
		mmi_dq_sys_show_cur_menu_list();
	}
	else
	{
		mmi_dq_ms_set_sys_state(SYS_STATUS_WIFI_MODE);
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_WIFI_CONNECTING);
#endif
	}
}

/**
  * @brief  AirKiss配网
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
static void mmi_dq_sys_wifi_airkiss_setting(void)
{
	if (0 == mmi_dq_wifi_arikiss_con())
	{
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_SET_FAIL);
#endif
		mmi_dq_sys_show_cur_menu_list();
	}
	else
	{
		mmi_dq_ms_set_sys_state(SYS_STATUS_WIFI_MODE);
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_WIFI_CONNECTING);
#endif
	}
}

/**
  * @brief  二维码配网
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
static void mmi_dq_sys_wifi_code_setting(void)
{
	if (0 == mmi_dq_wifi_code_con())
	{
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_SET_FAIL);
#endif
		mmi_dq_sys_show_cur_menu_list();
	}
	else
	{
		mmi_dq_ms_set_sys_state(SYS_STATUS_WIFI_MODE);
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_WIFI_CONNECTING);
#endif
	}
}
#endif

#ifdef __LOCK_DECODE_SUPPORT__
static void mmi_dq_sys_sync_start_time(void)
{
}
#endif

typedef struct sys_menu_t
{
	unsigned char menu_father_id;
	unsigned char menu_sub_id;
	void (*sys_menu_node_function)(void);
} sys_menu_t;

typedef struct sys_menu_list
{
	unsigned char id;
	unsigned char menu_id;
} sys_menu_list;

const sys_menu_t sys_menu_tree[] =
	{
		{STR_ID_SYSTEM, STR_ID_PASSWORD, 0},
#if defined(__LOCK_FP_SUPPORT__)
		{STR_ID_SYSTEM, STR_ID_FINGERPRINT, 0},
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
		{STR_ID_SYSTEM, STR_ID_RF_CARD, 0},
#endif
		{STR_ID_SYSTEM, STR_ID_ADMIN, 0},
		{STR_ID_SYSTEM, STR_ID_SETTING, 0},
		{STR_ID_SYSTEM, STR_ID_RESTORE, mmi_dq_sys_restore_lock_con},
#ifdef __LOCK_WIFI_SUPPORT__
		{STR_ID_SYSTEM, STR_ID_WIFI, mmi_dq_sys_wifi_setting},
		{STR_ID_SYSTEM, STR_ID_WIFI, mmi_dq_sys_wifi_airkiss_setting},
#ifdef __LOCK_DECODE_SUPPORT__
		{STR_ID_SYSTEM, STR_ID_DECODE, mmi_dq_sys_add_decode},
#endif

#endif
#ifdef __LOCK_110_SUPPORT__
		{STR_ID_SYSTEM, STR_ID_110, 0},

		{STR_ID_110, STR_ID_PASSWORD_110, mmi_dq_sys_add_110_pwd},
#if defined(__LOCK_FP_SUPPORT__)
		{STR_ID_110, STR_ID_FINGERPRINT_110, 0},
#endif
#endif

		{STR_ID_SYSTEM2, STR_ID_ADMIN, 0},
		{STR_ID_SYSTEM2, STR_ID_SETTING, 0},
		{STR_ID_SYSTEM2, STR_ID_RESTORE, mmi_dq_sys_restore_lock_con},

		//PWD
		{STR_ID_PASSWORD, STR_ID_ADD_PWD, mmi_dq_sys_add_pwd},
		//{STR_ID_PASSWORD,STR_ID_CHG_PWD,mmi_dq_sys_chg_pwd},
		{STR_ID_PASSWORD, STR_ID_DEL_PWD, mmi_dq_sys_del_pwd},
		{STR_ID_PASSWORD, STR_ID_CLR_PWD, mmi_dq_sys_clear_pwd},
//FP
#if defined(__LOCK_FP_SUPPORT__)
		{STR_ID_FINGERPRINT, STR_ID_ADD_FP, mmi_dq_sys_add_fp},
		//{STR_ID_FINGERPRINT,STR_ID_CHG_FP,mmi_dq_sys_chg_fp},
		{STR_ID_FINGERPRINT, STR_ID_DEL_FP, mmi_dq_sys_del_fp},
		{STR_ID_FINGERPRINT, STR_ID_CLR_FP, mmi_dq_sys_clear_fp},
#ifdef __LOCK_110_SUPPORT__
		{STR_ID_FINGERPRINT_110, STR_ID_ADD_FP, mmi_dq_sys_add_110_fp},
		{STR_ID_FINGERPRINT_110, STR_ID_DEL_FP, mmi_dq_sys_del_110_fp},
#endif
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
		//RF
		{STR_ID_RF_CARD, STR_ID_ADD_RFCARD, mmi_dq_sys_add_rf},
		//{STR_ID_RF_CARD,STR_ID_CHG_RFCARD,mmi_dq_sys_chg_rf},
		{STR_ID_RF_CARD, STR_ID_DEL_RFCARD, mmi_dq_sys_del_rf},
		{STR_ID_RF_CARD, STR_ID_CLR_RFCARD, mmi_dq_sys_clear_rf},
#endif
		//admin
		{STR_ID_ADMIN, STR_ID_CHG_ADMIN_PWD, mmi_dq_sys_chg_admin_pwd},
#if defined(__LOCK_FP_SUPPORT__)
		{STR_ID_ADMIN, STR_ID_CHG_ADMIN_FP, 0},
		{STR_ID_CHG_ADMIN_FP, STR_ID_NO1_ADMIN_FP, mmi_dq_sys_chg_admin_fp_No1},
		{STR_ID_CHG_ADMIN_FP, STR_ID_NO2_ADMIN_FP, mmi_dq_sys_chg_admin_fp_No2},
#endif
		//setting
		{STR_ID_SETTING, STR_ID_PRO_AUDIO, 0},
		{STR_ID_SETTING, STR_ID_OPEN_MODE, 0},

		{STR_ID_PRO_AUDIO, STR_ID_OPEN_PRO_AUDIO, mmi_dq_sys_open_pro_sound},
		{STR_ID_PRO_AUDIO, STR_ID_CLOSE_PRO_AUDIO, mmi_dq_sys_close_pro_sound},
		{STR_ID_OPEN_MODE, STR_ID_SIN_OPEN_MODE, mmi_dq_sys_sin_open_mode},
		{STR_ID_OPEN_MODE, STR_ID_DBL_OPEN_MODE, mmi_dq_sys_dbl_open_mode},
};

static unsigned char g_dq_menu_father_id;
static sys_menu_list g_dq_menu_list_id[10];
static unsigned char g_dq_menu_count;

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_set_menu_father_id(unsigned char father_id)
{
	g_dq_menu_father_id = father_id;
	return;
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_sys_get_menu_count(void)
{
	return g_dq_menu_count;
}

/*
parameter: 
	none
return :
	none
*/
static void mmi_dq_sys_get_menu_list(unsigned char father_id)
{
	unsigned char i = 0, j = 0;
	unsigned char menu_tree_size = sizeof(sys_menu_tree) / sizeof(sys_menu_t);

	g_dq_menu_father_id = father_id;

	memset(&g_dq_menu_list_id, 0x00, sizeof(g_dq_menu_list_id));
	g_dq_menu_count = 0;

	for (i = 0; i < menu_tree_size; i++)
	{
		if (sys_menu_tree[i].menu_father_id == g_dq_menu_father_id)
		{
			g_dq_menu_list_id[j].id = i;
			g_dq_menu_list_id[j].menu_id = sys_menu_tree[i].menu_sub_id;
			j++;
			g_dq_menu_count++;
		}
	}
	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_show_cur_menu_list(void)
{
	mmi_dq_sys_get_menu_list(g_dq_menu_father_id);

#ifdef __LOCK_AUDIO_SUPPORT__
	mmi_dq_aud_play_with_id(mmi_dq_aud_get_audio_id(g_dq_menu_father_id));
#endif
#ifdef __LOCK_FP_SUPPORT__
	mmi_dq_fp_light(FP_NONE_COLOR);
#endif
	mmi_dq_ms_set_sys_state(SYS_STATUS_SYS_MENU);
	return;
}

/*
parameter: 
	none
return :
	current machine status
*/
void mmi_dq_sys_get_pre_menu_list(void)
{
	if (g_dq_menu_father_id == STR_ID_SYSTEM)
	{
		mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);
	}
	else
	{
		unsigned char i = 0;
		unsigned char menu_tree_size = sizeof(sys_menu_tree) / sizeof(sys_menu_t);

		for (i = 0; i < menu_tree_size; i++)
		{
			if (sys_menu_tree[i].menu_sub_id == g_dq_menu_father_id)
			{
				g_dq_menu_father_id = sys_menu_tree[i].menu_father_id;
				break;
			}
		}
		mmi_dq_sys_get_menu_list(g_dq_menu_father_id);
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(mmi_dq_aud_get_audio_id(g_dq_menu_father_id));
#endif
	}
	return;
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_sys_exe_menu_fun(unsigned char menu_id)
{
	unsigned char i = 0;
	unsigned char menu_tree_size = sizeof(sys_menu_tree) / sizeof(sys_menu_t);
	if (menu_id >= g_dq_menu_count)
		return RET_FAIL;
	i = g_dq_menu_list_id[menu_id].id;
	if (sys_menu_tree[i].sys_menu_node_function != 0)
	{
		sys_menu_tree[i].sys_menu_node_function();
	}
	else
	{
		mmi_dq_sys_get_menu_list(g_dq_menu_list_id[menu_id].menu_id);

#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(mmi_dq_aud_get_audio_id(g_dq_menu_father_id));
#endif
	}

	return RET_SUCESS;
}

/************************************************************************************
 * 							     	 Own function							        *
 ************************************************************************************/
#if 0 //def __LOCK_VIRTUAL_PASSWORD__
void mmi_dq_sys_show_message_with_id(unsigned char tile_id, unsigned char bmp_id, unsigned char text_id, uint32_t time_msec, BASE_STATUS_MACHINE status)
{
	unsigned char i = 0;
#ifdef __LOCK_OLED_SUPPORT__
	mmi_dq_oled_show_input_dialog(tile_id, bmp_id, text_id);
#endif

#ifdef __NBDQIOT_PROJECT_B06_SUPPORT__
	if (text_id == STR_ID_OPEN_DOOR)
	{
		//power_off();
		lock_inside_lock = 0;
		lock_easy_open_mode = 0;
		mmi_dq_aud_play_with_id(AUD_ID_DOOR_OPEN, 0);
		// mmi_dq_entry_sleep_delay_time();
		mmi_dq_show_msg_timer_start(10000);
		timer_ms_status = status;
		mmi_dq_ms_set_machine_status(BASE_STATUS_M_LOCK_OPEN);
		mmi_dq_moto_lock_open();
	}
	else
	{
#ifdef __LOCK_AUDIO_SUPPORT__
		for (i = 0; msg_aud_list[i].msg_id < STR_ID_MAX_COUNT; i++)
		{
			if (msg_aud_list[i].msg_id == text_id)
			{
				break;
			}
		}
		if (msg_aud_list[i].aud_id != 0xFF)
		{
			mmi_dq_aud_play_with_id(msg_aud_list[i].aud_id, 0);
		}
#endif
		if (time_msec > 0)
		{
			mmi_dq_show_msg_timer_start(time_msec);
			timer_ms_status = status;
			mmi_dq_ms_set_machine_status(BASE_STATUS_M_INVALID);
		}
		else
			mmi_dq_ms_set_machine_status(status);
	}
#else

#ifdef __LOCK_AUDIO_SUPPORT__
	for (i = 0; msg_aud_list[i].msg_id < STR_ID_MAX_COUNT; i++)
	{
		if (msg_aud_list[i].msg_id == text_id)
		{
			break;
		}
	}
	if (msg_aud_list[i].aud_id != 0xFF)
	{
//		mmi_dq_aud_play_with_id(msg_aud_list[i].aud_id, 0);
	}
#endif

//	if (time_msec > 0)
//	{
//		mmi_dq_show_msg_timer_start(time_msec);
//		timer_ms_status = status;
//		mmi_dq_ms_set_machine_status(BASE_STATUS_M_INVALID);
//	}
//	else
//		mmi_dq_ms_set_machine_status(status);

	if (text_id == STR_ID_OPEN_DOOR)
	{
		mmi_dq_moto_lock_open();
	}
#endif
	return;
}
#endif
#ifdef __LOCK_VIRTUAL_PASSWORD__
uint8_t mmi_dq_sys_lock_error(void)
{
	uint32_t time = mmi_dq_rtc_get_sys_sec_info();
	if (time - g_last_error_time > MMI_ERROR_LOCK_TIME)
	{
		g_multiple_error_times = 1;
		g_last_error_time = time;
	}
	else
	{
		g_last_error_time = time;
		g_multiple_error_times++;
		if (g_multiple_error_times >= MMI_MAX_ERROR_TIMES)
		{
			//multiple error
#ifdef __LOCK_APP_COMM_SUPPORT__
			if (mmi_dq_fs_app_init_sucess() == 1)
			{
				dq_otp_add_alarm_log(DQ_ALART_LOG_MULTIPLE_ERROR);
			}
#endif
			return 1;
		}
	}
	return 0;
}

void mmi_dq_sys_lock_correct(void)
{
	g_last_error_time = 0;
	g_multiple_error_times = 0;
}

void mmi_dq_entry_sleep_delay_time(void)
{
	//	g_enter_sleep_set_time = MMI_TIMER_ENTER_SLEEP_DELAY_COUNT;
}

void mmi_dq_show_msg_timer_start(uint32_t time_msec)
{
	uint32_t time_ms = MMI_TIMER_BASE_TIME;
	uint32_t time_ticks;

	//	g_show_msg_time_voval_count = time_msec/MMI_TIMER_BASE_TIME;
	//	g_show_msg_time_count = 0;
	//	time_ticks = nrf_drv_timer_ms_to_ticks(&TIMER2_MMI_TIMER, time_ms);
	//	nrf_drv_timer_extended_compare(&TIMER2_MMI_TIMER, NRF_TIMER_CC_CHANNEL1, time_ticks, NRF_TIMER_SHORT_COMPARE1_CLEAR_MASK, true);
	//	nrf_drv_timer_enable(&TIMER2_MMI_TIMER);
	return;
}

#endif //__LOCK_VIRTUAL_PASSWORD__
/************************************************************************************
 * 							     	 End function							        *
 ************************************************************************************/

#endif //__MMI_SYS_C__
