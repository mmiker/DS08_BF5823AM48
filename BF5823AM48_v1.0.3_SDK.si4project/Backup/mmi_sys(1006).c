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

static unsigned char g_sys_door_open_flag = 0;

static unsigned int g_timer2_sleep_count = 0;
static unsigned int g_timer2_count = 0;
static unsigned int g_timer2_set_count = 0;
static unsigned char g_timer2_flag = 0;

static unsigned char g_wifi_check_flag = 0;
static unsigned char g_wifi_check_count = 0;
static unsigned char g_wifi_check_type = 0;

#define LOCK_MAX_EEROR_TIMES 5
static unsigned char g_lock_error_flag = 0;
static unsigned int g_lock_error_count = 0;

timer2_delay_pro g_timer2_delay_pro = 0;


#define MMI_TIMER_BASE_TIME		100
#define MMI_TIMER_ENTER_SLEEP	10000
#define MMI_TIMER_ENTER_SLEEP_COUNT	(MMI_TIMER_ENTER_SLEEP/MMI_TIMER_BASE_TIME)
#define MMI_TIMER_ENTER_SLEEP_DELAY	20000
#define MMI_TIMER_ENTER_SLEEP_DEALY_COUNT	(MMI_TIMER_ENTER_SLEEP_DELAY/MMI_TIMER_BASE_TIME)
#define MMI_TIMER_DOOR_OPEN 	6000
#define MMI_TIMER_DOOR_OPEN_COUNT	(MMI_TIMER_DOOR_OPEN/MMI_TIMER_BASE_TIME)
#define MMI_TIMER_MOTOR 	 	300
#define MMI_TIMER_MOTOR_COUNT	(MMI_TIMER_MOTOR/MMI_TIMER_BASE_TIME)
#define MMI_WIFI_SETTING_DELAY  60000
#define MMI_WIFI_SETTING_DELAY_COUNT (MMI_WIFI_SETTING_DELAY/MMI_TIMER_BASE_TIME)
#define MMI_LOCK_ERROR_DELAY	60000
#define MMI_LOCK_ERROR_DELAY_COUNT (MMI_LOCK_ERROR_DELAY/MMI_TIMER_BASE_TIME)
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
void mmi_dq_sys_show_message_with_id(unsigned char text_id,unsigned long time_msec)
{
	unsigned char audio_id = 0;
	
	time_msec = 0;
	
#ifdef __LOCK_AUDIO_SUPPORT__
	audio_id = mmi_dq_aud_get_audio_id(text_id);

	mmi_dq_aud_play_with_id(audio_id);

#endif
	return;
}

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
	if(mmi_dq_sys_check_vbat() == 0) 
	{
	    mmi_dq_wifi_wakeup();
#ifdef __LOCK_FP_SUPPORT__
		mmi_dq_fp_init(); //ÎÕÊÖ¡¢µãµÆ
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
	mmi_dq_motor_stop();
	mmi_dq_aud_play_with_id(AUD_ID_DOOR_OPEN);
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
	g_lock_error_flag = 0;
	if(mmi_dq_fs_get_open_mode() == SYS_OPEN_MODE_DBL && SYS_OPEN_BY_WIFI != type)
	{
		if(g_sys_door_open_flag & (~ type) != 0)
		{
			g_sys_door_open_flag = 0;
		}
		else
		{
			g_sys_door_open_flag &= type;
			return;
		}
	}

	mmi_dq_ms_set_sys_state(SYS_STATUS_DOOR_OPEN);

	mmi_dq_motor_turn_right();
	//mmi_dq_wifi_open_door();
	mmi_dq_sys_set_delay_event(MMI_TIMER_MOTOR_COUNT, mmi_dq_sys_door_open_cb);
	
	switch(type)
	{
		case SYS_OPEN_BY_PASSWORD:
			mmi_dq_wifi_open_by_password();
			break;
		case SYS_OPEN_BY_FP:
			mmi_dq_wifi_open_by_fp();
			break;
		case SYS_OPEN_BY_RFID:
			mmi_dq_wifi_open_by_rfid();
			break;
		case SYS_OPEN_BY_WIFI:
			mmi_dq_wifi_open_by_wifi();
			break;
	}

	
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
	switch(type)
	{
		case SYS_OPEN_BY_PASSWORD:
			mmi_dq_aud_play_with_id(AUD_ID_PWD_WRONG_TRY);
			if(g_lock_error_flag >= LOCK_MAX_EEROR_TIMES)
				mmi_dq_wifi_pw_alarm();
			break;
		case SYS_OPEN_BY_FP:
			mmi_dq_aud_play_with_id(AUD_ID_FP_WRONG_TRY);
			if(g_lock_error_flag >= LOCK_MAX_EEROR_TIMES)
				mmi_dq_wifi_fp_alarm();
			break;
		case SYS_OPEN_BY_RFID:
			mmi_dq_aud_play_with_id(AUD_ID_RFCARD_WRONG_TRY);
			if(g_lock_error_flag >= LOCK_MAX_EEROR_TIMES)
				mmi_dq_wifi_rfid_alarm();
			break;
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
	if(g_lock_error_flag >= LOCK_MAX_EEROR_TIMES)
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
	mmi_dq_motor_stop();
	mmi_dq_aud_play_with_id(AUD_ID_DOOR_CLOSE);
	mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);
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
	mmi_dq_motor_turn_back();
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
	mmi_dq_ms_set_msg_que(QUE_EVENT_AUDIO_END,QUE_PRO_LOW,0);
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

	if((state >= SYS_STATUS_ADD_PWD && state < SYS_STATUS_ADD_ADMIN_PWD) || (state == SYS_STATUS_SYS_MENU) || (state == SYS_STATUS_CHG_ADMIN_PWD))
	{
		mmi_dq_aud_play_with_id(AUD_ID_TIME_OUT);
		mmi_dq_ms_set_sys_state(SYS_STATUS_WAIT_FOR_ENTER_SLEEP);
	}
#ifdef __LOCK_FP_SUPPORT__
	else if(state == SYS_STATUS_ADD_ADMIN_FP1 || state == SYS_STATUS_ADD_ADMIN_FP2)
	{
		if(mmi_dq_fs_get_admin_status() == 0)
			g_timer2_sleep_count = 0;
		else
		{
			mmi_dq_aud_play_with_id(AUD_ID_TIME_OUT);
			mmi_dq_ms_set_sys_state(SYS_STATUS_WAIT_FOR_ENTER_SLEEP);
		}
	}
#endif
	else if(state == SYS_STATUS_ADD_ADMIN_PWD)
	{
			g_timer2_sleep_count = 0;
			mmi_dq_aud_play_with_id(AUD_ID_ADD_ADMIN_PWD_FIRST);
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

	if(g_timer2_flag == 1)
	{
		g_timer2_count++;
		if(g_timer2_count >= g_timer2_set_count)
		{
			g_timer2_flag = 2;
			g_timer2_count = 0;
			//mmi_dq_ms_set_msg_que(QUE_EVENT_TIMER_END,QUE_PRO_LOW,0);
		}
	}

	if(g_wifi_check_flag == 1)
	{
		g_wifi_check_count++;
		if(g_wifi_check_count >= 4)
		{
			g_wifi_check_flag = 2;
			g_wifi_check_count = 0;
		}
	}

	if(g_lock_error_flag>0)
	{
		g_lock_error_count++;
		if(g_lock_error_count>=MMI_LOCK_ERROR_DELAY_COUNT)
			g_lock_error_flag = 0;
	}
	
	if((mmi_dq_rst_timer_event() != 0) && (SYS_STATUS_ENTER_SLEEP != state && SYS_STATUS_WAIT_FOR_ENTER_SLEEP != state) && (g_timer2_flag != 1) && (mmi_dq_ms_get_run_flag() == 1)&&(mmi_dq_wifi_get_running_flag() == 0))
	{
		unsigned char flag = 0;
		g_timer2_sleep_count++;
		if(state == SYS_STATUS_ADD_PWD || state == SYS_STATUS_DEL_PWD ||state ==SYS_STATUS_ADD_ADMIN_PWD 
#ifdef __LOCK_FP_SUPPORT__
			||state ==SYS_STATUS_ADD_ADMIN_FP1||state ==SYS_STATUS_ADD_ADMIN_FP2|| state == SYS_STATUS_ADD_FP|| state == SYS_STATUS_DEL_FP 
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
			|| state == SYS_STATUS_ADD_RFID|| state == SYS_STATUS_DEL_RFID
#endif
			)
		{
			if(g_timer2_sleep_count > MMI_TIMER_ENTER_SLEEP_DEALY_COUNT)
			{
				flag = 1;
			}
		}
		else if(g_timer2_sleep_count > MMI_TIMER_ENTER_SLEEP)
		{
			flag = 1;
		}


		if(flag)
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
unsigned char mmi_dq_sys_get_wifi_check_flag(void)
{
	if(g_wifi_check_flag == 2)
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
	if(g_timer2_flag == 2)
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
	g_timer2_count = 0;
	g_timer2_set_count = count;
	g_timer2_delay_pro = pro;
	g_timer2_flag = 1;
	//dqiot_drv_timer2_start();
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
	if(state > 0) 
	{
		mmi_dq_aud_play_with_id(AUD_ID_LOW_BATTERY);
		mmi_dq_wifi_lowpower_alarm();
		if(state == 2)
		{
			mmi_dq_ms_set_sys_state(SYS_STATUS_LOW_POWER);
			return 1;
		}
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
void mmi_dq_sys_wifi_open(void)
{
	if((mmi_dq_fs_get_wifi_setting()== 0)||(mmi_dq_wifi_open_ask() == 0))
		mmi_dq_aud_play_with_id(AUD_ID_SET_FAIL);
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_add_admin_pwd(void)
{
	mmi_dq_aud_play_with_id(AUD_ID_ADD_ADMIN_PWD_FIRST);
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
	if(mmi_dq_fs_get_pwd_unuse_index()==0xFF)
	{
		mmi_dq_aud_play_with_id(AUD_ID_PWD_FULL);
		mmi_dq_sys_show_cur_menu_list();
	}
	else
	{
		mmi_dq_aud_play_with_id(AUD_ID_INPUT_68_PWD);
		mmi_ms_pwd_init_var();
		mmi_dq_ms_set_sys_state(SYS_STATUS_ADD_PWD);
	}
	return;
}

void mmi_dq_sys_add_pwd_con(void)
{
	mmi_dq_aud_play_with_id(AUD_ID_CONTINUE_ADD_PWD);
	mmi_dq_ms_set_sys_state(SYS_STATUS_ADD_PWD_CON);
	return;
}


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
	mmi_dq_aud_play_with_id(AUD_ID_INPUT_DEL_NUM);
	mmi_ms_pwd_init_var();
	mmi_dq_ms_set_sys_state(SYS_STATUS_DEL_PWD);
	return;
}

void mmi_dq_sys_del_pwd_con(void)
{
	mmi_dq_aud_play_with_id(AUD_ID_DEL_CONFIRM);
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
	mmi_dq_aud_play_with_id(AUD_ID_CLR_PWD_CONFIRM);
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
	if(mmi_dq_fs_get_fp_unuse_index()==0xFF)
	{
		mmi_dq_aud_play_with_id(AUD_ID_FP_FULL);
		mmi_dq_sys_show_cur_menu_list();
	}
	else
	{
		mmi_dq_aud_play_with_id(AUD_ID_PRESS_FP);
		mmi_dq_fp_light(FP_BLUE);
		mmi_ms_opt_time_init();
		mmi_dq_ms_set_sys_state(SYS_STATUS_ADD_FP);
	}
	return;
}

void mmi_dq_sys_add_fp_con(void)
{
	mmi_dq_aud_play_with_id(AUD_ID_CONTINUE_ADD_PWD);
	mmi_dq_ms_set_sys_state(SYS_STATUS_ADD_FP_CON);
	return;
}

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
	mmi_dq_aud_play_with_id(AUD_ID_INPUT_DEL_FP_NUM);
	mmi_dq_fp_light(FP_BLUE);
	mmi_ms_opt_time_init();
	mmi_dq_ms_set_sys_state(SYS_STATUS_DEL_FP);
	return;
}

void mmi_dq_sys_del_fp_con(void)
{
	mmi_dq_aud_play_with_id(AUD_ID_DEL_CONFIRM);
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
	mmi_dq_aud_play_with_id(AUD_ID_CLR_FP_CONFIRM);
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
	
	if(mmi_dq_fs_get_rfid_unuse_index()==0xFF)
	{
		mmi_dq_aud_play_with_id(AUD_ID_RFCARD_FULL);
		mmi_dq_sys_show_cur_menu_list();
	}
	else
	{
		mmi_dq_aud_play_with_id(AUD_ID_PRESS_RFCARD);
		mmi_ms_opt_time_init();
		mmi_dq_ms_set_sys_state(SYS_STATUS_ADD_RFID);
	}
	return;
}

void mmi_dq_sys_add_rf_con(void)
{
	mmi_dq_aud_play_with_id(AUD_ID_CONTINUE_ADD_PWD);
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
	mmi_dq_aud_play_with_id(AUD_ID_INPUT_DEL_RFCARD_NUM);
	mmi_ms_opt_time_init();
	mmi_dq_ms_set_sys_state(SYS_STATUS_DEL_RFID);
	return;
}

void mmi_dq_sys_del_rf_con(void)
{
	mmi_dq_aud_play_with_id(AUD_ID_DEL_CONFIRM);
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
	mmi_dq_aud_play_with_id(AUD_ID_CLR_RFCARD_CONFIRM);
	mmi_dq_ms_set_sys_state(SYS_STATUS_CLR_RFID);
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

	if(mmi_dq_fs_set_pro_sound(1) == RET_SUCESS)
		mmi_dq_aud_play_with_id(AUD_ID_OPEN_PRO_AUDIO_SUCESS);
	else
		mmi_dq_aud_play_with_id(AUD_ID_OPEN_PRO_AUDIO_FAIL);

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

	if(mmi_dq_fs_set_pro_sound(0) == RET_SUCESS)
		mmi_dq_aud_play_with_id(AUD_ID_CLOSE_PRO_AUDIO_SUCESS);
	else
		mmi_dq_aud_play_with_id(AUD_ID_CLOSE_PRO_AUDIO_FAIL);

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

	if(mmi_dq_fs_set_open_mode(SYS_OPEN_MODE_SIN) == RET_SUCESS)
		mmi_dq_aud_play_with_id(AUD_ID_SIN_OPEN_MODE_SUCESS);
	else
		mmi_dq_aud_play_with_id(AUD_ID_SIN_OPEN_MODE_FAIL);

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

	if(mmi_dq_fs_set_open_mode(SYS_OPEN_MODE_DBL) == RET_SUCESS)
		mmi_dq_aud_play_with_id(AUD_ID_DBL_OPEN_MODE_SUCESS);
	else
		mmi_dq_aud_play_with_id(AUD_ID_DBL_OPEN_MODE_FAIL);

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
	mmi_dq_aud_play_with_id(AUD_ID_NEW_ADMIN_FP);
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
	mmi_dq_aud_play_with_id(AUD_ID_NEW_ADMIN_FP);
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
	mmi_dq_aud_play_with_id(AUD_ID_INPUT_NEW_ADMIN_PWD);
	mmi_ms_pwd_init_var();
	mmi_dq_ms_set_sys_state(SYS_STATUS_ADD_ADMIN_PWD);
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
		mmi_dq_aud_play_with_id(AUD_ID_RESTORE_SUCESS);
	else
		mmi_dq_aud_play_with_id(AUD_ID_RESTORE_FAIL);

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
	mmi_dq_aud_play_with_id(AUD_ID_RESTORE_LOCK_CONTINUE_CONFIRM);
	mmi_dq_ms_set_sys_state(SYS_STATUS_RESTORE_LOCK_CON);
}

/*
parameter: 
	none
return :
	none
*/
static void mmi_dq_sys_wifi_setting(void)
{
	if(0 == mmi_dq_wifi_setting())
	{
		mmi_dq_aud_play_with_id(AUD_ID_SET_FAIL);
		mmi_dq_sys_show_cur_menu_list();
	}
	else
	{
		mmi_dq_ms_set_sys_state(SYS_STATUS_WIFI_MODE);
		mmi_dq_aud_play_with_id(AUD_ID_LOW_BATTERY);
	}
}

typedef struct sys_menu_t
{
	unsigned char menu_father_id;
	unsigned char menu_sub_id;
	void (*sys_menu_node_function)(void);
}sys_menu_t;

typedef struct sys_menu_list
{
	unsigned char id;
	unsigned char menu_id;
}sys_menu_list;

const sys_menu_t sys_menu_tree[] = 
{
	{STR_ID_SYSTEM,STR_ID_PASSWORD,0},
#if defined(__LOCK_FP_SUPPORT__)
	{STR_ID_SYSTEM,STR_ID_FINGERPRINT,0},
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
	{STR_ID_SYSTEM,STR_ID_RF_CARD,0},
#endif
	{STR_ID_SYSTEM,STR_ID_ADMIN,0},
	{STR_ID_SYSTEM,STR_ID_SETTING,0},
	{STR_ID_SYSTEM,STR_ID_RESTORE,mmi_dq_sys_restore_lock_con},
	{STR_ID_SYSTEM,STR_ID_WIFI,mmi_dq_sys_wifi_setting},
	

	{STR_ID_SYSTEM2,STR_ID_ADMIN,0},
	{STR_ID_SYSTEM2,STR_ID_SETTING,0},
	{STR_ID_SYSTEM2,STR_ID_RESTORE,mmi_dq_sys_restore_lock_con},
	
	//PWD
	{STR_ID_PASSWORD,STR_ID_ADD_PWD,mmi_dq_sys_add_pwd},
	//{STR_ID_PASSWORD,STR_ID_CHG_PWD,mmi_dq_sys_chg_pwd},
	{STR_ID_PASSWORD,STR_ID_DEL_PWD,mmi_dq_sys_del_pwd},
	{STR_ID_PASSWORD,STR_ID_CLR_PWD,mmi_dq_sys_clear_pwd},
	//FP
#if defined(__LOCK_FP_SUPPORT__)
	{STR_ID_FINGERPRINT,STR_ID_ADD_FP,mmi_dq_sys_add_fp},
	//{STR_ID_FINGERPRINT,STR_ID_CHG_FP,mmi_dq_sys_chg_fp},
	{STR_ID_FINGERPRINT,STR_ID_DEL_FP,mmi_dq_sys_del_fp},
	{STR_ID_FINGERPRINT,STR_ID_CLR_FP,mmi_dq_sys_clear_fp},
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
	//RF
	{STR_ID_RF_CARD,STR_ID_ADD_RFCARD,mmi_dq_sys_add_rf},
	//{STR_ID_RF_CARD,STR_ID_CHG_RFCARD,mmi_dq_sys_chg_rf},
	{STR_ID_RF_CARD,STR_ID_DEL_RFCARD,mmi_dq_sys_del_rf},
	{STR_ID_RF_CARD,STR_ID_CLR_RFCARD,mmi_dq_sys_clear_rf},
#endif
	//admin
	{STR_ID_ADMIN,STR_ID_CHG_ADMIN_PWD,mmi_dq_sys_chg_admin_pwd},
#if defined(__LOCK_FP_SUPPORT__)
	{STR_ID_ADMIN,STR_ID_CHG_ADMIN_FP,0},
	{STR_ID_CHG_ADMIN_FP,STR_ID_NO1_ADMIN_FP,mmi_dq_sys_chg_admin_fp_No1},
	{STR_ID_CHG_ADMIN_FP,STR_ID_NO2_ADMIN_FP,mmi_dq_sys_chg_admin_fp_No2},
#endif
	//setting
	{STR_ID_SETTING,STR_ID_PRO_AUDIO,0},
	{STR_ID_SETTING,STR_ID_OPEN_MODE,0},
	
	{STR_ID_PRO_AUDIO,STR_ID_OPEN_PRO_AUDIO,mmi_dq_sys_open_pro_sound},
	{STR_ID_PRO_AUDIO,STR_ID_CLOSE_PRO_AUDIO,mmi_dq_sys_close_pro_sound},
	{STR_ID_OPEN_MODE,STR_ID_SIN_OPEN_MODE,mmi_dq_sys_sin_open_mode},
	{STR_ID_OPEN_MODE,STR_ID_DBL_OPEN_MODE,mmi_dq_sys_dbl_open_mode},
};

static unsigned char 	g_dq_menu_father_id;
static sys_menu_list 	g_dq_menu_list_id[8];
static unsigned char	g_dq_menu_count;

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
	unsigned char i = 0,j = 0;
	unsigned char menu_tree_size = sizeof(sys_menu_tree)/sizeof(sys_menu_t);

	g_dq_menu_father_id = father_id;

	memset(&g_dq_menu_list_id,0x00,sizeof(g_dq_menu_list_id));
	g_dq_menu_count = 0;
	
	for(i=0;i<menu_tree_size;i++)
	{
		if(sys_menu_tree[i].menu_father_id == g_dq_menu_father_id)
		{
			g_dq_menu_list_id[j].id = i;
			g_dq_menu_list_id[j].menu_id = sys_menu_tree[i].menu_sub_id;
			j++;
			g_dq_menu_count ++;
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
	if(g_dq_menu_father_id == STR_ID_SYSTEM)
	{
		mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);
	}
	else
	{
		unsigned char i = 0;
		unsigned char menu_tree_size = sizeof(sys_menu_tree)/sizeof(sys_menu_t);

		for(i=0;i<menu_tree_size;i++)
		{
			if(sys_menu_tree[i].menu_sub_id == g_dq_menu_father_id)
				g_dq_menu_father_id = sys_menu_tree[i].menu_father_id;
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
	unsigned char menu_tree_size = sizeof(sys_menu_tree)/sizeof(sys_menu_t);
	if(menu_id>=g_dq_menu_count)
		return RET_FAIL;
	i = g_dq_menu_list_id[menu_id].id;
	if(sys_menu_tree[i].sys_menu_node_function != 0)
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

#endif//__MMI_SYS_C__
