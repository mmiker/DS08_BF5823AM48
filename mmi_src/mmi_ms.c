#ifndef __MMI_MS_C__
#define __MMI_MS_C__

#include "string.h"
#include "mmi_ms.h"
#include "mmi_key.h"
#include "mmi_sys.h"
#include "mmi_audio.h"
#include "mmi_fps.h"
#include "mmi_rfid.h"
#include "mmi_com.h"
#include "mmi_fs.h"
#include "mmi_rst.h"
#include "dqiot_drv.h"
#include "delay.h"
#include "mmi_fs.h"
#include "mmi_fm.h"
#include "mmi_wifi.h"
#include "dqiot_drv_wifi.h"
// #include <stdio.h>
#ifdef __LOCK_VIRTUAL_PASSWORD__
#include "dq_sdk_main.h"
#include "mmi_ms.h"
#endif
#ifdef __LOCK_DECODE_SUPPORT__
#include "mmi_decode.h"
#endif

unsigned char input_key_1[KEY_INPUT_MAX_LEN];
unsigned char input_key_2[KEY_INPUT_MAX_LEN];
unsigned char key_len = 0;
OPERATE_TIME opt_time = OPT_TIME_INVALID;
static SYS_BASE_STATUS data sys_state = SYS_STATUS_INVALID;

static unsigned char data key_last_value = KEY_INVALID;
#ifdef __LOCK_RFID_CARD_SUPPORT__
static unsigned char rfid_last_flag = 0;
#endif
#ifdef __LOCK_BUS_SUPPORT__
static unsigned char admin_check_type = 0;
#endif

static unsigned char g_dbl_open_mode_pwd_flag = 0;
static unsigned char g_dbl_open_mode_fp_flag = 0;
static unsigned char g_dbl_open_mode_rf_flag = 0;

// extern void printfS(char *show, char *status);
// extern void printfV(char *show, int value);

/*
parameter: 
	none
return :
	none
*/
void mmi_task_proc(void)
{
	unsigned char touch_value = 0xFF;
	unsigned char key_value = KEY_INVALID;

#ifdef __LOCK_RFID_CARD_SUPPORT__
	if (mmi_dq_sys_get_rfid_flag() == 1)
	{
		//check rfid press
		if (mmi_dq_rfid_check() == RET_SUCESS)
		{
			if (mmi_dq_rfid_work() == RET_SUCESS)
			{
				if (rfid_last_flag == 0)
				{
					rfid_last_flag = 1;
					mmi_dq_ms_set_msg_que(QUE_EVENT_RFID, QUE_PRO_LOW, 0);
				}
			}
			else
			{
				rfid_last_flag = 0;
			}
		}
	}
#endif
	//check key press
	touch_value = mmi_dq_key_work();
	if (touch_value != 0xFF)
	{
		key_value = mmi_dq_get_key_map(touch_value);
		if (key_value != KEY_INVALID)
		{
			if (key_last_value != key_value)
			{
				key_last_value = key_value;
				mmi_dq_ms_set_msg_que(QUE_EVENT_KEY, QUE_PRO_LOW, key_value);
			}
		}
		else
			key_last_value = KEY_INVALID;
	}
	else
		key_last_value = KEY_INVALID;

#ifdef __LOCK_AUDIO_SUPPORT__
	if (mmi_dq_aud_get_end_flag() != 0)
		mmi_dq_ms_set_msg_que(QUE_EVENT_AUDIO_END, QUE_PRO_LOW, 0);
#endif

	if (mmi_dq_rst_get_state() != 0)
		mmi_dq_ms_set_msg_que(QUE_EVENT_RST, QUE_PRO_LOW, 0);

	if (mmi_dq_sys_get_timer2_flag() != 0)
		mmi_dq_ms_set_msg_que(QUE_EVENT_TIMER_END, QUE_PRO_LOW, 0);

#ifdef __LOCK_FP_SUPPORT__
		//check fp press
		// if (mmi_dq_fp_work() != 0)
		// 	mmi_dq_ms_set_msg_que(QUE_EVENT_FP, QUE_PRO_LOW, 0);
#endif

#ifdef __LOCK_WIFI_SUPPORT__
	if (mmi_dq_sys_get_wifi_check_flag() != 0)
		mmi_dq_ms_set_msg_que(QUE_EVENT_WIFI_CHECK, QUE_PRO_LOW, 0);
#endif

	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_sleep_task_proc(void)
{
#ifdef __LOCK_RFID_CARD_SUPPORT__
	unsigned char ret = 0xFF;
	static unsigned char time_count = 0;

	time_count++;
	if (time_count > 4)
	{
		time_count = 0;
		ret = mmi_dq_rfid_check();
	}
#endif

	if (
#ifdef __LOCK_RFID_CARD_SUPPORT__
		(ret == RET_SUCESS) ||
#endif
		(mmi_dq_key_check() != 0) || (mmi_dq_rst_get_pin() != 0)
#ifdef __LOCK_FP_SUPPORT__
		|| (mmi_dq_fp_get_pin() == 1)
#endif
	)
	{
		key_last_value = mmi_dq_get_key_map(dqiot_drv_get_touch_value());
		mmi_dq_sys_wake_up();
	}

#ifdef __LOCK_WIFI_SUPPORT__
	//if(mmi_dq_sys_get_wifi_check_flag() != 0)
	//	mmi_dq_ms_set_msg_que(QUE_EVENT_WIFI_CHECK,QUE_PRO_LOW,0);
#endif

	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_wait_sleep_task_proc(void)
{
//unsigned int timer1_count = 0;
#ifdef __LOCK_WIFI_SUPPORT__
	if (mmi_dq_wifi_get_running_flag() == 1)
		mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);
	//if((mmi_dq_rfid_check() == RET_SUCESS) || (mmi_dq_key_check() != 0) || (mmi_dq_rst_get_pin() == 0))
	else
#endif
		if (mmi_dq_ms_get_run_flag() == 0)
	{
		mmi_dq_sys_enter_sleep();
	}

	return;
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_ms_get_run_flag(void)
{
	if ((key_last_value == KEY_INVALID)
#ifdef __LOCK_AUDIO_SUPPORT__
		&& (mmi_dq_aud_get_state() == 0)
#endif
		&& (mmi_dq_rst_get_pin() == 0)
#ifdef __LOCK_FP_SUPPORT__
		&& (mmi_dq_fp_get_pin() != 1)
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
		&& rfid_last_flag == 0
#endif
	)
		return 0;

	return 1;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_ms_sys_msg_handle(void)
{
	Sys_MSG_Queue_M sys_msg_que;
	if (mmi_OutQueue(&sys_msg_que))
	{
		mmi_dq_sys_sleep_timer_reset();
		switch (sys_msg_que.que_event)
		{
		case QUE_EVENT_KEY:
			mmi_ms_pwd_opt_fun(sys_msg_que.que_data);
			break;
#ifdef __LOCK_FP_SUPPORT__
		case QUE_EVENT_FP:
			mmi_ms_fps_opt_fun(sys_msg_que.que_data);
			break;
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
		case QUE_EVENT_RFID:
			mmi_ms_rfid_opt_fun(sys_msg_que.que_data);
			break;
#endif
		case QUE_EVENT_RST:
			mmi_ms_reset_opt_fun();
			break;
		case QUE_EVENT_AUDIO_END:

			break;
		case QUE_EVENT_TIMER_END:
			mmi_dq_sys_delay_event_pro();
			break;
#ifdef __LOCK_WIFI_SUPPORT__
		case QUE_EVENT_WIFI_CHECK:
			mmi_ms_wifi_opt_fun();
			break;
#endif
		default:
			break;
		}
	}
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_ms_set_msg_que(SYS_QUEUE_EVENT q_event, SYS_QUEUE_PRO q_pro, unsigned char q_data)
{
	Sys_MSG_Queue_M que;
	que.que_event = q_event;
	que.que_pro = q_pro;
	que.que_data = q_data;
	//printf("mmi_dq_ms_set_msg_que  event : %d",q_event);
	mmi_InQueue(que);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_ms_set_sys_state(SYS_BASE_STATUS state)
{
	sys_state = state;
	return;
}

/*
parameter: 
	none
return :
	none
*/
SYS_BASE_STATUS mmi_dq_ms_get_sys_state(void)
{
	return sys_state;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_ms_pwd_init_var(void)
{
	key_len = 0;
	opt_time = OPT_ONE_TIME;
	memset(input_key_1, 0xFF, sizeof(input_key_1));
	memset(input_key_2, 0xFF, sizeof(input_key_2));
}

/*
parameter: 
	none
return :
	none
*/
void mmi_ms_opt_time_init(void)
{
	opt_time = OPT_ONE_TIME;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_ms_pwd_opt_fun(unsigned char key_val)
{
	SYS_BASE_STATUS status = mmi_dq_ms_get_sys_state();
	//printf("mmi_ms_pwd_opt_fun status: 0x%x  key: %d",status,key_val);
	switch (status)
	{
	case SYS_STATUS_WAIT_FOR_ENTER_SLEEP:
		mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);
		status = SYS_STATUS_IDLE;
	case SYS_STATUS_INPUT_PWD:
	case SYS_STATUS_INPUT_ADMIN_PWD:
	case SYS_STATUS_ADD_PWD:
	case SYS_STATUS_DEL_PWD:
	case SYS_STATUS_ADD_ADMIN_PWD:
	case SYS_STATUS_CHG_ADMIN_PWD:
#ifdef __LOCK_110_SUPPORT__
	case SYS_STATUS_ADD_110_PWD:
#endif
		if (mmi_dq_sys_door_state_check() == 1)
		{
#ifdef __LOCK_AUDIO_SUPPORT__
			mmi_dq_aud_stop();
			mmi_dq_aud_play_with_id(AUD_ID_RONG_TIMES_EXCEED);
#endif
#ifdef __LOCK_WIFI_SUPPORT__
			mmi_dq_wifi_pw_alarm();
#endif
			return;
		}
		if (key_len == 0)
		{
			if (key_val == KEY_S)
			{
				if (SYS_STATUS_ADD_ADMIN_PWD != status)
				{
#ifdef __LOCK_AUDIO_SUPPORT__
					mmi_dq_aud_play_key_tone();
#endif
					if (status == SYS_STATUS_INPUT_PWD)
						//mmi_dq_sys_enter_sleep();
						mmi_dq_ms_set_sys_state(SYS_STATUS_WAIT_FOR_ENTER_SLEEP);
					else if (status == SYS_STATUS_INPUT_ADMIN_PWD)
						mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);
#ifdef __LOCK_WIFI_SUPPORT__
					else if (wifi_add_flag == 1)
					{
						wifi_add_flag = 0xff;
						mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);
					}
					else
#endif
						mmi_dq_sys_show_cur_menu_list();
				}
				break;
			}
			else if (key_val == KEY_H)
			{
				if (status == SYS_STATUS_INPUT_PWD)
				{
#ifdef __LOCK_AUDIO_SUPPORT__
					mmi_dq_aud_play_key_tone();
#endif
#ifdef __LOCK_BUS_SUPPORT__
					admin_check_type = 0;
#endif
#ifdef __LOCK_AUDIO_SUPPORT__
					mmi_dq_aud_play_with_id(AUD_ID_INPUT_ADMIN_PWD);
#endif
					mmi_dq_ms_set_sys_state(SYS_STATUS_INPUT_ADMIN_PWD);
				}
				break;
			}
		}

// mmi_dq_aud_play_key_num(key_val);
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_key_tone();
#endif
		//input pwd
		if ((key_val >= KEY_0 && key_val <= KEY_9) && key_len < KEY_INPUT_MAX_LEN)
		{
			if ((status == SYS_STATUS_INPUT_PWD) || (status == SYS_STATUS_INPUT_ADMIN_PWD))
				input_key_1[key_len++] = key_val;
			else // if((status == SYS_STATUS_ADD_PWD)||(status == SYS_STATUS_ADD_110_PWD)||(status == SYS_STATUS_ADD_ADMIN_PWD))
			{
				if (opt_time == OPT_ONE_TIME)
				{
					input_key_1[key_len++] = key_val;
				}
				else if (opt_time == OPT_TWO_TIME)
				{
					input_key_2[key_len++] = key_val;
				}
			}
		}

		if (key_val == KEY_S)
		{
			if (opt_time == OPT_ONE_TIME)
				input_key_1[key_len--] = 0xFF;
			else if (opt_time == OPT_TWO_TIME)
				input_key_2[key_len--] = 0xFF;

			if (key_len == 0)
			{
				if (status == SYS_STATUS_INPUT_ADMIN_PWD)
#ifdef __LOCK_AUDIO_SUPPORT__
					mmi_dq_aud_play_with_id(AUD_ID_INPUT_ADMIN_PWD)
#endif
						;
				else if (opt_time == OPT_ONE_TIME)
				{
#ifdef __LOCK_AUDIO_SUPPORT__
					if (status == SYS_STATUS_ADD_PWD || status == SYS_STATUS_ADD_110_PWD)
						mmi_dq_aud_play_with_id(AUD_ID_INPUT_68_PWD);
					else if (status == SYS_STATUS_DEL_PWD)
						mmi_dq_aud_play_with_id(AUD_ID_INPUT_DEL_NUM);
					else if (status == SYS_STATUS_ADD_ADMIN_PWD)
						mmi_dq_aud_play_with_id(AUD_ID_ADD_ADMIN_PWD_FIRST);
					else if (status == SYS_STATUS_CHG_ADMIN_PWD)
						mmi_dq_aud_play_with_id(AUD_ID_INPUT_NEW_ADMIN_PWD);
#endif
				}
				else if (opt_time == OPT_TWO_TIME)
				{
#ifdef __LOCK_AUDIO_SUPPORT__
					if (status == SYS_STATUS_ADD_PWD || status == SYS_STATUS_ADD_110_PWD)
						mmi_dq_aud_play_with_id(AUD_ID_PWD_INPUT_AGAIN);
					else if (status == SYS_STATUS_DEL_PWD)
						mmi_dq_aud_play_with_id(AUD_ID_INPUT_DEL_PWD_AGAIN);
					else if (status == SYS_STATUS_ADD_ADMIN_PWD)
						mmi_dq_aud_play_with_id(AUD_ID_INPUT_ADMIN_PWD_INIT_AGAIN);
					else if (status == SYS_STATUS_CHG_ADMIN_PWD)
						mmi_dq_aud_play_with_id(AUD_ID_INPUT_NEW_ADMIN_PWD_AGAIN);
#endif
				}
			}
		}
		else if ((key_val == KEY_H) || (key_len == PWD_INPUT_MAX_LEN))
		{
			if (key_len < PWD_INPUT_MIN_LEN)
			{
				if (status == SYS_STATUS_INPUT_PWD)
				{
					if (key_len == 2 && input_key_1[0] == KEY_0 && input_key_1[1] == KEY_0) //00 远程开门
						mmi_dq_sys_wifi_open();
#ifdef __LOCK_WIFI_SUPPORT__
					else if (key_len == 1 && input_key_1[0] == KEY_5) //5 添加删除密码/指纹/RF卡
						mmi_dq_wifi_cmd_add_del();
					else if (key_len == 1 && input_key_1[0] == KEY_6) //6 设置拍照/录像开关
						mmi_dq_wifi_pv_switch();
					else if (key_len == 2 && input_key_1[0] == KEY_1 && input_key_1[1] == KEY_8) //18 应急钥匙开门成功
					{
#ifdef __LOCK_DECODE_SUPPORT__
						unsigned char random_code[15] = {5, 6, 4, 8, 0, 4, 7, 5, 7, 7, 9, 8, 0, 1, 8};
						mmi_dq_decode_app_random_code(&random_code);
#endif
					}
					// 	mmi_dq_wifi_open_by_key();
					// else if (key_len == 2 && input_key_1[0] == KEY_1 && input_key_1[1] == KEY_9) //19 门未关
					// 	mmi_dq_wifi_close_over_time();
					// else if (key_len == 2 && input_key_1[0] == KEY_2 && input_key_1[1] == KEY_0) //20 震动报警
					// 	mmi_dq_wifi_via_alarm();
					// else if (key_len == 2 && input_key_1[0] == KEY_2 && input_key_1[1] == KEY_5) //25 睡眠
					// 	mmi_dq_wifi_sleep();
					// else if (key_len == 2 && input_key_1[0] == KEY_2 && input_key_1[1] == KEY_6) //26 唤醒
					// 	mmi_dq_wifi_wakeup();
					// else if (key_len == 2 && input_key_1[0] == KEY_2 && input_key_1[1] == KEY_7) //27 拍照
					// 	mmi_dq_wifi_take_photos();
					// else if (key_len == 2 && input_key_1[0] == KEY_2 && input_key_1[1] == KEY_8) //28 录像
					// 	mmi_dq_wifi_take_videos();
					// else if (key_len == 2 && input_key_1[0] == KEY_3 && input_key_1[1] == KEY_0) //30 查询网络状态
					// 	mmi_dq_wifi_check_net();
					// else if (key_len == 2 && input_key_1[0] == KEY_3 && input_key_1[1] == KEY_1) //31 Airkiss配网(admin 8)
					// 	mmi_dq_wifi_arikiss_con();
					// else if (key_len == 2 && input_key_1[0] == KEY_3 && input_key_1[1] == KEY_2) //32 二维码配网(admin 9)
					// 	mmi_dq_wifi_code_con();
#endif
#ifdef __LOCK_BUS_SUPPORT__
					else if (key_len == 2 && input_key_1[0] == KEY_0 && input_key_1[1] == KEY_1) //01
					{

						if (mmi_dq_fs_get_business_flag() == 1)
						{
							admin_check_type = 1;
#ifdef __LOCK_AUDIO_SUPPORT__
							mmi_dq_aud_play_with_id(AUD_ID_INPUT_ADMIN_PWD);
#endif
							mmi_dq_ms_set_sys_state(SYS_STATUS_INPUT_ADMIN_PWD);
						}
						else
						{
							mmi_dq_fs_set_business_flag(1);
#ifdef __LOCK_AUDIO_SUPPORT__
							mmi_dq_aud_play_with_id(AUD_ID_OUT_OPEN);
#endif
							mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);
						}
					}
#endif
					else
					{
						mmi_dq_sys_door_open_fail(SYS_OPEN_BY_PASSWORD);
					}
					key_len = 0;
					memset(input_key_1, 0xFF, sizeof(input_key_1));
				}
				else
				{
#ifdef __LOCK_AUDIO_SUPPORT__
					mmi_dq_aud_play_with_id(AUD_ID_PWD_68_LEN);
#endif
					key_len = 0;
					if (opt_time == OPT_ONE_TIME)
						memset(input_key_1, 0xFF, sizeof(input_key_1));
					else if (opt_time == OPT_TWO_TIME)
						memset(input_key_2, 0xFF, sizeof(input_key_2));
				}
			}
			else
			{
#ifdef __LOCK_VIRTUAL_PASSWORD__
				if (1) //测试与APP是否连接成功
				{

					mmi_dq_fs_check_input_pwd_from_app(input_key_1, key_len);
					key_len = 0;
					// return SUCESS;
				}
				else
#endif //__LOCK_VIRTUAL_PASSWORD__
					if (status == SYS_STATUS_INPUT_PWD)
				{
					//if(mmi_dq_fs_check_input_pwd(input_key_1,key_len,FDS_USE_TYPE_ALL) == 0xFF)
					unsigned char ret = 0;
					ret = mmi_dq_fs_check_input_pwd_for_open(input_key_1, key_len);
					//printf("check input ret: %d",(unsigned int)ret);
					if (ret == 0xFF)
						mmi_dq_sys_door_open_fail(SYS_OPEN_BY_PASSWORD);
#ifdef __LOCK_BUS_SUPPORT__
					else if (ret == 0xFE && mmi_dq_fs_get_business_flag() == 1)
					{
						mmi_dq_fs_set_business_flag(0);
#ifdef __LOCK_AUDIO_SUPPORT__
						mmi_dq_aud_play_with_id(AUD_ID_OUT_CLOSED);
#endif
						mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);
					}
#endif
#ifdef __LOCK_110_SUPPORT__
					else if (ret == 1)
						mmi_dq_sys_door_open(SYS_OPEN_BY_110_PASSWORD);
#endif
					else
						mmi_dq_sys_door_open(SYS_OPEN_BY_PASSWORD);
					key_len = 0;
					memset(input_key_1, 0xFF, sizeof(input_key_1));
				}
				else if (status == SYS_STATUS_INPUT_ADMIN_PWD)
				{
					if (mmi_dq_fs_check_input_pwd(input_key_1, key_len, FDS_USE_TYPE_ADMIN) == 0xFF)
#ifdef __LOCK_AUDIO_SUPPORT__
						mmi_dq_aud_play_with_id(AUD_ID_PWD_WRONG_TRY)
#endif
							;
					else
					{
#ifdef __LOCK_BUS_SUPPORT__
						if (admin_check_type == 1)
						{
							mmi_dq_fs_set_business_flag(0);
#ifdef __LOCK_AUDIO_SUPPORT__
							mmi_dq_aud_play_with_id(AUD_ID_OUT_CLOSED);
#endif
							mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);
						}
						else
#endif
						{
							mmi_dq_sys_set_menu_father_id(STR_ID_SYSTEM);
							mmi_dq_sys_show_cur_menu_list();
						}
					}
					key_len = 0;
					memset(input_key_1, 0xFF, sizeof(input_key_1));
				}
				else // if((status == SYS_STATUS_ADD_PWD)||(status == SYS_STATUS_DEL_PWD)||(status == SYS_STATUS_ADD_ADMIN_PWD)||(status == SYS_STATUS_CHG_ADMIN_PWD)||(status == SYS_STATUS_ADD_110_PWD))
				{
					if (opt_time == OPT_ONE_TIME)
					{
#ifdef __LOCK_AUDIO_SUPPORT__
						if (status == SYS_STATUS_ADD_PWD || status == SYS_STATUS_ADD_110_PWD)
							mmi_dq_aud_play_with_id(AUD_ID_PWD_INPUT_AGAIN);
						else if (status == SYS_STATUS_DEL_PWD)
							mmi_dq_aud_play_with_id(AUD_ID_INPUT_DEL_PWD_AGAIN);
						else if (status == SYS_STATUS_ADD_ADMIN_PWD)
							mmi_dq_aud_play_with_id(AUD_ID_INPUT_ADMIN_PWD_INIT_AGAIN);
						else if (status == SYS_STATUS_CHG_ADMIN_PWD)
							mmi_dq_aud_play_with_id(AUD_ID_INPUT_NEW_ADMIN_PWD_AGAIN);
#endif

						opt_time = OPT_TWO_TIME;
						key_len = 0;
						memset(input_key_2, 0xFF, sizeof(input_key_2));
					}
					else if (opt_time == OPT_TWO_TIME)
					{
						if (0 == memcmp(input_key_1, input_key_2, PWD_INPUT_MAX_LEN))
						{
							if (status == SYS_STATUS_DEL_PWD)
							{
								unsigned char del_index = mmi_dq_fs_check_input_pwd(input_key_1, key_len, FDS_USE_TYPE_USER);
								if (del_index == 0xFF)
#ifdef __LOCK_AUDIO_SUPPORT__
									mmi_dq_aud_play_with_id(AUD_ID_PWD_NOT_EXIST)
#endif
										;
								else
								{
									if (mmi_dq_fs_del_pwd(del_index, FDS_USE_TYPE_USER) == RET_SUCESS)
									{
										get_index = del_index;
#ifdef __LOCK_AUDIO_SUPPORT__
										mmi_dq_aud_play_with_id(AUD_ID_DEL_PWD_SUCESS);
#endif
#ifdef __LOCK_WIFI_SUPPORT__
										mmi_dq_wifi_del_password(get_index);
#endif
										// printfV("get_index", (int)get_index);
									}
									else
#ifdef __LOCK_AUDIO_SUPPORT__
										mmi_dq_aud_play_with_id(AUD_ID_DEL_FAIL)
#endif
											;
									mmi_dq_sys_del_pwd_con();
								}
							}
							else if (mmi_dq_fs_check_input_pwd(input_key_1, key_len, FDS_USE_TYPE_ALL) != 0xFF)
#ifdef __LOCK_AUDIO_SUPPORT__
								mmi_dq_aud_play_with_id(AUD_ID_PWD_EXIST)
#endif
									;
							else
							{
								if (status == SYS_STATUS_ADD_PWD)
								{
									if (mmi_dq_fs_set_pwd(input_key_1, key_len, FDS_USE_TYPE_USER) == RET_FAIL)
#ifdef __LOCK_AUDIO_SUPPORT__
										mmi_dq_aud_play_with_id(AUD_ID_ADD_FAIL)
#endif
											;
									else
									{
#ifdef __LOCK_AUDIO_SUPPORT__
										mmi_dq_aud_play_with_id(AUD_ID_ADD_PWD_SUCESS);
#endif
#ifdef __LOCK_WIFI_SUPPORT__
										mmi_dq_wifi_add_password(get_index);
#endif
										// printfV("get_index", (int)get_index);
									}
#ifdef __LOCK_WIFI_SUPPORT__
									if (wifi_add_flag == 1)
									{
										wifi_add_flag = 0xff;
										mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);
									}
									else
#endif
										mmi_dq_sys_add_pwd_con();
								}
								else if (status == SYS_STATUS_ADD_ADMIN_PWD)
								{
									if (mmi_dq_fs_set_pwd(input_key_1, key_len, FDS_USE_TYPE_ADMIN) == RET_FAIL)
#ifdef __LOCK_AUDIO_SUPPORT__
										mmi_dq_aud_play_with_id(AUD_ID_ADD_FAIL)
#endif
											;
									else
									{
#ifdef __LOCK_AUDIO_SUPPORT__
										mmi_dq_aud_play_with_id(AUD_ID_ADD_ADMIN_PWD_INIT_SUCESS);
#endif
#ifdef __LOCK_WIFI_SUPPORT__
										mmi_dq_wifi_add_password(get_index);
#endif
										// printfV("get_index", (int)get_index);
									}
#ifdef __LOCK_FP_SUPPORT__
									mmi_dq_sys_chg_admin_fp_No1();
#else
									if (0 == mmi_dq_fs_get_admin_status())
										mmi_dq_sys_lock_add_admin_suc();
									else
										mmi_dq_sys_show_cur_menu_list();
#endif
								}
								else if (status == SYS_STATUS_CHG_ADMIN_PWD)
								{
									if (mmi_dq_fs_set_pwd(input_key_1, key_len, FDS_USE_TYPE_ADMIN) == RET_FAIL)
#ifdef __LOCK_AUDIO_SUPPORT__
										mmi_dq_aud_play_with_id(AUD_ID_ADD_FAIL)
#endif
											;
									else
									{
#ifdef __LOCK_AUDIO_SUPPORT__
										mmi_dq_aud_play_with_id(AUD_ID_CHG_ADMIN_PWD_SUCESS);
#endif
#ifdef __LOCK_WIFI_SUPPORT__
										mmi_dq_wifi_add_password(get_index);
#endif
										// printfV("get_index", (int)get_index);
									}
									mmi_dq_sys_show_cur_menu_list();
								}
#ifdef __LOCK_110_SUPPORT__
								else if (status == SYS_STATUS_ADD_110_PWD)
								{
									if (mmi_dq_fs_set_pwd(input_key_1, key_len, FDS_USE_TYPE_110) == RET_FAIL)
#ifdef __LOCK_AUDIO_SUPPORT__
										mmi_dq_aud_play_with_id(AUD_ID_ADD_FAIL)
#endif
											;
									else
									{
#ifdef __LOCK_WIFI_SUPPORT__
										mmi_dq_wifi_set_110();
#endif
#ifdef __LOCK_AUDIO_SUPPORT__
										mmi_dq_aud_play_with_id(AUD_ID_ADD_PWD_SUCESS);
#endif
#ifdef __LOCK_WIFI_SUPPORT__
										mmi_dq_wifi_add_password(get_index);
#endif
										// printfV("get_index", (int)get_index);
									}
									mmi_dq_sys_show_cur_menu_list();
								}
#endif
							}
						}
						else
						{
#ifdef __LOCK_AUDIO_SUPPORT__
							mmi_dq_aud_play_with_id(AUD_ID_PWD_NOT_SAME_RETRY);
#endif
						}
						mmi_ms_pwd_init_var();
					}
				}
			}
			return;
		}
		break;
#ifdef __LOCK_FP_SUPPORT__
	case SYS_STATUS_ADD_FP:
	case SYS_STATUS_DEL_FP:
#ifdef __LOCK_110_SUPPORT__
	case SYS_STATUS_ADD_110_FP:
	case SYS_STATUS_DEL_110_FP:
#endif
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
	case SYS_STATUS_ADD_RFID:
	case SYS_STATUS_DEL_RFID:
#endif
		if (key_val == KEY_S)
		{
#ifdef __LOCK_AUDIO_SUPPORT__
			mmi_dq_aud_play_key_tone();
#endif
#ifdef __LOCK_WIFI_SUPPORT__
			if (wifi_add_flag == 1)
			{
				wifi_add_flag = 0xff;
				mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);
			}
			else
#endif
				mmi_dq_sys_show_cur_menu_list();
		}
		break;
#ifdef __LOCK_FP_SUPPORT__
	case SYS_STATUS_ADD_ADMIN_FP1:
	case SYS_STATUS_ADD_ADMIN_FP2:
		if (key_val == KEY_S)
		{
#ifdef __LOCK_AUDIO_SUPPORT__
			mmi_dq_aud_play_key_tone();
#endif
			if (0 == mmi_dq_fs_get_admin_status())
				mmi_dq_sys_lock_add_admin_suc();
			else
				mmi_dq_sys_show_cur_menu_list();
		}
		break;
#endif
	case SYS_STATUS_CLR_PWD:
	case SYS_STATUS_ADD_PWD_CON:
	case SYS_STATUS_DEL_PWD_CON:
#ifdef __LOCK_FP_SUPPORT__
	case SYS_STATUS_CLR_FP:
	case SYS_STATUS_ADD_FP_CON:
	case SYS_STATUS_DEL_FP_CON:
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
	case SYS_STATUS_CLR_RFID:
	case SYS_STATUS_ADD_RFID_CON:
	case SYS_STATUS_DEL_RFID_CON:
#endif
	case SYS_STATUS_RESTORE_LOCK_CON:
		if (key_val == KEY_H)
		{
#ifdef __LOCK_AUDIO_SUPPORT__
			mmi_dq_aud_play_key_tone();
#endif
			switch (status)
			{
			case SYS_STATUS_CLR_PWD:
				if (RET_SUCESS == mmi_dq_fs_clr_pwd())
				{
#ifdef __LOCK_AUDIO_SUPPORT__
					mmi_dq_aud_play_with_id(AUD_ID_CLR_PWD_SUCESS)
#endif
						;
#ifdef __LOCK_WIFI_SUPPORT__
					mmi_dq_wifi_clr_pwd_suc();
#endif
				}
				else
#ifdef __LOCK_AUDIO_SUPPORT__
					mmi_dq_aud_play_with_id(AUD_ID_CLR_PWD_FAIL)
#endif
						;
				mmi_dq_sys_show_cur_menu_list();
				break;
#ifdef __LOCK_FP_SUPPORT__
			case SYS_STATUS_CLR_FP:
				if (RET_SUCESS == mmi_dq_fs_clr_fp())
				{
#ifdef __LOCK_AUDIO_SUPPORT__
					mmi_dq_aud_play_with_id(AUD_ID_CLR_FP_SUCESS);
#endif
#ifdef __LOCK_WIFI_SUPPORT__
					mmi_dq_wifi_clr_fps_suc();
#endif
				}
				else
#ifdef __LOCK_AUDIO_SUPPORT__
					mmi_dq_aud_play_with_id(AUD_ID_CLR_FP_FAIL)
#endif
						;
				mmi_dq_sys_show_cur_menu_list();
				break;
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
			case SYS_STATUS_CLR_RFID:
				if (RET_SUCESS == mmi_dq_fs_clr_rfid())
				{
#ifdef __LOCK_AUDIO_SUPPORT__
					mmi_dq_aud_play_with_id(AUD_ID_CLR_RFCARD_SUCESS);
#endif
#ifdef __LOCK_WIFI_SUPPORT__
					mmi_dq_wifi_clr_rfid_suc();
#endif
				}
				else
#ifdef __LOCK_AUDIO_SUPPORT__
					mmi_dq_aud_play_with_id(AUD_ID_CLR_RFCARD_FAIL)
#endif
						;
				mmi_dq_sys_show_cur_menu_list();
				break;
#endif
			case SYS_STATUS_ADD_PWD_CON:
				mmi_dq_sys_add_pwd();
				break;
			case SYS_STATUS_DEL_PWD_CON:
				mmi_dq_sys_del_pwd();
				break;
#ifdef __LOCK_FP_SUPPORT__
			case SYS_STATUS_ADD_FP_CON:
				mmi_dq_sys_add_fp();
				break;
			case SYS_STATUS_DEL_FP_CON:
				mmi_dq_sys_del_fp();
				break;
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
			case SYS_STATUS_ADD_RFID_CON:
				mmi_dq_sys_add_rf();
				break;
			case SYS_STATUS_DEL_RFID_CON:
				mmi_dq_sys_del_rf();
				break;
#endif
			case SYS_STATUS_RESTORE_LOCK_CON:
				mmi_dq_sys_restore_lock();
				break;
			}
		}
		else if (key_val == KEY_S)
		{
#ifdef __LOCK_AUDIO_SUPPORT__
			mmi_dq_aud_play_key_tone();
#endif
			mmi_dq_sys_show_cur_menu_list();
		}
		break;
	case SYS_STATUS_SYS_MENU:
		if (key_val == KEY_S)
		{
#ifdef __LOCK_AUDIO_SUPPORT__
			mmi_dq_aud_play_key_tone();
#endif
			mmi_dq_sys_get_pre_menu_list();
		}
		else if (key_val != KEY_0 && key_val <= mmi_dq_sys_get_menu_count())
		{
#ifdef __LOCK_AUDIO_SUPPORT__
			mmi_dq_aud_play_key_tone();
#endif
			mmi_dq_sys_exe_menu_fun(key_val - 1);
		}
		break;
#ifdef __FACTORY_TEST_SUPPORT__
	case SYS_STATUS_FM_MODE:
	{
		unsigned char str = mmi_dq_factory_mode_get_test_project();
		if (str == STR_ID_KEY)
		{
#ifdef __LOCK_AUDIO_SUPPORT__
			// mmi_dq_aud_play_key_num(key_val);
			mmi_dq_aud_play_key_tone();
#endif
			mmi_dq_factory_mode_key_test(key_val);
		}
		else if (str == STR_ID_MOTO)
		{
			if (key_val == KEY_S)
			{
#ifdef __LOCK_AUDIO_SUPPORT__
				mmi_dq_aud_play_key_tone();
#endif
#ifdef __LOCK_MOTOR_SUPPORT__
				mmi_dq_factory_mode_motor_test_back();
#endif
				if (mmi_dq_fs_get_factory_flag() != 0)
					mmi_dq_factory_mode_test_stop();
				else
				{
#ifdef __LOCK_MOTOR_SUPPORT__
					delay_ms(600);
					mmi_dq_factory_mode_motor_test();
#endif
				}
			}
			else if (key_val == KEY_H)
			{
#ifdef __LOCK_AUDIO_SUPPORT__
				mmi_dq_aud_play_key_tone();
#endif
#ifdef __LOCK_MOTOR_SUPPORT__
				mmi_dq_factory_mode_motor_test_back();
#endif
				mmi_dq_factory_mode_test_item_result(STR_ID_MOTO, 1);
			}
		}
		else if (mmi_dq_fs_get_factory_flag() != 0)
		{
#ifdef __LOCK_AUDIO_SUPPORT__
			mmi_dq_aud_play_key_tone();
#endif
			mmi_dq_factory_mode_test_stop();
		}
	}
	break;
#endif
#ifdef __LOCK_WIFI_SUPPORT__
	case SYS_STATUS_WIFI_MODE:
		//if(key_val == KEY_S)
		//{
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_stop();
#endif
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_WIFI_CONNECTING);
#endif
		//	mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);
		//}
		break;
#endif
	case SYS_STATUS_LOW_POWER:
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_stop();
#endif
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_LOW_BATTERY);
#endif
#ifdef __LOCK_WIFI_SUPPORT__
		mmi_dq_wifi_lowpower_alarm();
#endif
		break;
	default:
		break;
	}
	return;
}

#ifdef __LOCK_FP_SUPPORT__
/*
parameter: 
	none
return :
	none
*/
void mmi_ms_fps_opt_fun(unsigned char fps_val)
{
	RET_VAL retval = 0;
	unsigned short index = 0;
	SYS_BASE_STATUS status = mmi_dq_ms_get_sys_state();
	if (status == SYS_STATUS_LOW_POWER)
	{
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_stop();
#endif
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_LOW_BATTERY);
#endif
#ifdef __LOCK_WIFI_SUPPORT__
		mmi_dq_wifi_lowpower_alarm();
#endif
		return;
	}
	else if (status == SYS_STATUS_WAIT_FOR_ENTER_SLEEP)
		mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);

	if ((status != SYS_STATUS_INPUT_FP && status != SYS_STATUS_ADD_FP && status != SYS_STATUS_DEL_FP && status != SYS_STATUS_ADD_ADMIN_FP1 && status != SYS_STATUS_ADD_ADMIN_FP2 && status != SYS_STATUS_ADD_110_FP && status != SYS_STATUS_DEL_110_FP)
#ifdef __FACTORY_TEST_SUPPORT__
		|| (status == SYS_STATUS_FM_MODE && STR_ID_FINGERPRINT != mmi_dq_factory_mode_get_test_project())
#endif
	)
		return;

#ifdef __LOCK_AUDIO_SUPPORT__
	mmi_dq_aud_stop();
#endif
	if (mmi_dq_sys_door_state_check() == 1)
	{
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_stop();
#endif
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_RONG_TIMES_EXCEED);
#endif
#ifdef __LOCK_WIFI_SUPPORT__
		mmi_dq_wifi_fp_alarm();
#endif
		return;
	}

	retval = mmi_dq_fp_get_image();

	if (retval == 0)
	{
		// printfS("mmi_dq_fp_get_image", "ok");
		// if (opt_time != 0)
		// 	retval = mmi_dq_fp_gen_char(0);
		// if (retval == 0)
		retval = mmi_dq_fp_gen_char(opt_time);
		if (retval == 0)
		{
			// printfS("mmi_dq_fp_gen_char", "ok");
			retval = mmi_dq_fp_high_speed_search(opt_time, &index);
			if (retval == 0)
			{
				// printfS("mmi_dq_fp_high_speed_search", "ok");
				if (status == SYS_STATUS_INPUT_FP)
				{
					retval = mmi_dq_fs_check_fp((unsigned char)index, FDS_USE_TYPE_ALL);
					if (retval == RET_SUCESS)
					{
						get_index = index;
						mmi_dq_fp_light(FP_GREEN);
#ifdef __LOCK_110_SUPPORT__
						if (mmi_dq_fs_check_fp((unsigned char)index, FDS_USE_TYPE_110) == RET_SUCESS)
						{
							mmi_dq_sys_door_open(SYS_OPEN_BY_110_FP);
						}
						else
#endif
							mmi_dq_sys_door_open(SYS_OPEN_BY_FP);
					}
					else
					{
						mmi_dq_fp_light(FP_RED);
						mmi_dq_sys_door_open_fail(SYS_OPEN_BY_FP);
					}
				}
				else if (status == SYS_STATUS_ADD_FP || status == SYS_STATUS_ADD_ADMIN_FP1 || status == SYS_STATUS_ADD_ADMIN_FP2 || status == SYS_STATUS_ADD_110_FP || status == SYS_STATUS_FM_MODE)
				{
					mmi_dq_fp_light(FP_RED);
#ifdef __LOCK_AUDIO_SUPPORT__
					mmi_dq_aud_play_with_id(AUD_ID_FP_EXIST);
#endif
				}
				else if (status == SYS_STATUS_DEL_FP || status == SYS_STATUS_DEL_110_FP)
				{
#ifdef __LOCK_110_SUPPORT__
					if (status == SYS_STATUS_DEL_FP)
						retval = mmi_dq_fs_check_fp((unsigned char)index, FDS_USE_TYPE_USER);
					else if (status == SYS_STATUS_DEL_110_FP)
						retval = mmi_dq_fs_check_fp((unsigned char)index, FDS_USE_TYPE_110);
#else
					retval = mmi_dq_fs_check_fp((unsigned char)index, FDS_USE_TYPE_USER);
#endif
					if (retval == RET_SUCESS)
					{
						static unsigned char del_num = 0;
						if (opt_time == OPT_ONE_TIME)
						{
							opt_time = OPT_TWO_TIME;
							del_num = index;
							mmi_dq_fp_light(FP_GREEN);
#ifdef __LOCK_AUDIO_SUPPORT__
							mmi_dq_aud_play_with_id(AUD_ID_PRESS_DEL_FP_AGAIN);
#endif
						}
						else
						{
							//retval = mmi_dq_fp_match();
							if (del_num == index)
								retval = 0;
							else
								retval = 255;
							if (retval == 0) //|| retval == 255)
							{
#ifdef __LOCK_110_SUPPORT__
								if (status == SYS_STATUS_DEL_FP)
									retval = mmi_dq_fs_del_fp((unsigned char)index, FDS_USE_TYPE_USER);
								else if (status == SYS_STATUS_DEL_110_FP)
									retval = mmi_dq_fs_del_fp((unsigned char)index, FDS_USE_TYPE_110);
#else
								retval = mmi_dq_fs_del_fp((unsigned char)index, FDS_USE_TYPE_USER);
#endif
								if (retval == RET_SUCESS)
								{
									retval = mmi_dq_fp_delete(index);
								}
								if (retval == 0)
								{
									mmi_dq_fp_light(FP_GREEN);
#ifdef __LOCK_AUDIO_SUPPORT__
									mmi_dq_aud_play_with_id(AUD_ID_DEL_FP_SUCESS);
#endif
#ifdef __LOCK_WIFI_SUPPORT__
									mmi_dq_wifi_del_fp(index);
#endif
								}
								else
								{
									mmi_dq_fp_light(FP_RED);
#ifdef __LOCK_AUDIO_SUPPORT__
									mmi_dq_aud_play_with_id(AUD_ID_DEL_FAIL);
#endif
								}
#ifdef __LOCK_110_SUPPORT__
								if (status == SYS_STATUS_DEL_FP)
									mmi_dq_sys_del_fp_con();
								else if (status == SYS_STATUS_DEL_110_FP)
									mmi_dq_sys_show_cur_menu_list();
#else
								mmi_dq_sys_del_fp_con();
#endif
							}
							else
							{
								mmi_dq_fp_light(FP_RED);
#ifdef __LOCK_AUDIO_SUPPORT__
								mmi_dq_aud_play_with_id(AUD_ID_FP_TWICE_NOT_SAME_RETRY);
#endif
							}
							opt_time = OPT_ONE_TIME;
						}
					}
					else
					{
						mmi_dq_fp_light(FP_RED);
#ifdef __LOCK_AUDIO_SUPPORT__
						mmi_dq_aud_play_with_id(AUD_ID_FP_NOT_EXIST);
#endif
					}
				}
			}
			else
			{
				// printfS("mmi_dq_fp_high_speed_search", "error");
				if (status == SYS_STATUS_INPUT_FP)
				{
					mmi_dq_fp_light(FP_RED);
#ifdef __LOCK_AUDIO_SUPPORT__
					// mmi_dq_aud_play_with_id(AUD_ID_FP_WRONG_TRY);
#endif
					mmi_dq_sys_door_open_fail(SYS_OPEN_BY_FP);
				}
				else if (status == SYS_STATUS_ADD_FP || status == SYS_STATUS_ADD_ADMIN_FP1 || status == SYS_STATUS_ADD_ADMIN_FP2 || status == SYS_STATUS_ADD_110_FP || status == SYS_STATUS_FM_MODE)
				{
					if (opt_time == FPS_MAX_INPUT_TIME)
					{
						retval = mmi_dq_fp_reg_module();
						if (retval == 0)
						{
							// printfS("mmi_dq_fp_reg_module", "ok");
							if (status == SYS_STATUS_ADD_FP || status == SYS_STATUS_ADD_110_FP || status == SYS_STATUS_FM_MODE)
							{
#ifdef __LOCK_110_SUPPORT__
								if (status == SYS_STATUS_ADD_110_FP)
									index = mmi_dq_fs_get_fp_110_unuse_index();
								else
#endif
									index = mmi_dq_fs_get_fp_unuse_index();
								if (index == 0xFF)
								{
									// printfS("mmi_dq_fs_get_fp_unuse_index", "error");
									mmi_dq_fp_light(FP_RED);
#ifdef __LOCK_AUDIO_SUPPORT__
									mmi_dq_aud_play_with_id(AUD_ID_FP_FULL);
#endif
									mmi_dq_sys_show_cur_menu_list();
								}
								else
								{
									// printfS("mmi_dq_fs_get_fp_unuse_index", "ok");
									// printfV("index", (int)index);
									retval = mmi_dq_fp_store_char(0, index);
									if (status == SYS_STATUS_ADD_FP)
									{
										if (retval == 0)
										{
											// printfS("mmi_dq_fp_store_char", "ok");
											retval = mmi_dq_fs_set_fp((unsigned char)index, FDS_USE_TYPE_USER);
											if (retval != 0)
												mmi_dq_fp_delete(index);
										}
										if (retval == 0)
										{
											// printfS("mmi_dq_fs_set_fp", "ok");
											mmi_dq_fp_light(FP_GREEN);
#ifdef __LOCK_AUDIO_SUPPORT__
											mmi_dq_aud_play_with_id(AUD_ID_ADD_FP_SUCESS);
#endif
#ifdef __LOCK_WIFI_SUPPORT__
											mmi_dq_wifi_add_fp(index);
#endif
										}
										else
										{
											// printfS("mmi_dq_fp_store_char", "error");
											mmi_dq_fp_light(FP_RED);
#ifdef __LOCK_AUDIO_SUPPORT__
											mmi_dq_aud_play_with_id(AUD_ID_ADD_FAIL);
#endif
										}
#ifdef __LOCK_WIFI_SUPPORT__
										if (wifi_add_flag == 1)
										{
											wifi_add_flag = 0xff;
											mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);
										}
										else
#endif
											mmi_dq_sys_add_fp_con();
									}
#ifdef __LOCK_110_SUPPORT__
									else if (status == SYS_STATUS_ADD_110_FP)
									{
										if (retval == 0)
										{
											retval = mmi_dq_fs_set_fp((unsigned char)index, FDS_USE_TYPE_110);
											if (retval != 0)
												mmi_dq_fp_delete(index);
										}
										if (retval == 0)
										{
											mmi_dq_fp_light(FP_GREEN);
#ifdef __LOCK_AUDIO_SUPPORT__
											mmi_dq_aud_play_with_id(AUD_ID_ADD_FP_SUCESS);
#endif
#ifdef __LOCK_WIFI_SUPPORT__
											mmi_dq_wifi_set_110();
											mmi_dq_wifi_add_fp(index);
#endif
										}
										else
										{
											mmi_dq_fp_light(FP_RED);
#ifdef __LOCK_AUDIO_SUPPORT__
											mmi_dq_aud_play_with_id(AUD_ID_ADD_FAIL);
#endif
										}
										mmi_dq_sys_show_cur_menu_list();
									}
#endif
#ifdef __FACTORY_TEST_SUPPORT__
									else
									{
										if (retval == 0)
										{
											retval = mmi_dq_fp_delete(index);
										}
										if (retval == 0)
										{
											mmi_dq_fp_light(FP_GREEN);
											mmi_dq_factory_mode_test_item_result(STR_ID_FINGERPRINT, 1);
										}
										else
										{
											mmi_dq_fp_light(FP_RED);
											mmi_dq_factory_mode_test_item_result(STR_ID_FINGERPRINT, 0);
										}
									}
#endif
								}
							}
							else
							{
								if (status == SYS_STATUS_ADD_ADMIN_FP1)
									index = 0;
								else if (status == SYS_STATUS_ADD_ADMIN_FP2)
									index = 1;
								retval = mmi_dq_fp_delete(index);
								if (retval == 0)
									retval = mmi_dq_fp_store_char(0, index);
								if (retval == 0)
									retval = mmi_dq_fs_set_fp((unsigned char)index, FDS_USE_TYPE_ADMIN);
								if (retval == 0)
								{
									mmi_dq_fp_light(FP_GREEN);
#ifdef __LOCK_AUDIO_SUPPORT__
									mmi_dq_aud_play_with_id(AUD_ID_ADD_FP_SUCESS);
#endif
#ifdef __LOCK_WIFI_SUPPORT__
									mmi_dq_wifi_add_fp(index);
#endif
								}
								else
								{
									mmi_dq_fp_light(FP_RED);
#ifdef __LOCK_AUDIO_SUPPORT__
									mmi_dq_aud_play_with_id(AUD_ID_ADD_FAIL);
#endif
								}
								if (0 == mmi_dq_fs_get_admin_status())
								{
									if (status == SYS_STATUS_ADD_ADMIN_FP1)
										mmi_dq_sys_chg_admin_fp_No2();
									else
										mmi_dq_sys_lock_add_admin_suc();
								}
								else
									mmi_dq_sys_show_cur_menu_list();
							}
						}
						else
						{
							mmi_dq_fp_light(FP_RED);
#ifdef __LOCK_AUDIO_SUPPORT__
							mmi_dq_aud_play_with_id(AUD_ID_ADD_FAIL_RETRY);
#endif
						}
						opt_time = OPT_ONE_TIME;
					}
					else
					{
						opt_time++;
						mmi_dq_fp_light(FP_GREEN);
#ifdef __LOCK_AUDIO_SUPPORT__
						mmi_dq_aud_play_with_id(AUD_ID_PRESS_FP_AGAIN);
#endif
					}
				}
				else if (status == SYS_STATUS_DEL_FP)
				{
					mmi_dq_fp_light(FP_RED);
#ifdef __LOCK_AUDIO_SUPPORT__
					mmi_dq_aud_play_with_id(AUD_ID_FP_NOT_EXIST);
#endif
				}
			}
			return;
		}
	}
	// printfS("mmi_dq_fp_get_image", "error");

	mmi_dq_fp_light(FP_RED);
#ifdef __LOCK_AUDIO_SUPPORT__
	mmi_dq_aud_play_with_id(AUD_ID_PRESS_FP_AGAIN);
#endif
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
void mmi_ms_rfid_opt_fun(unsigned char rfid_val)
{
	RET_VAL retval = RET_SUCESS;
	unsigned char index = 0;
	SYS_BASE_STATUS status = mmi_dq_ms_get_sys_state();

	if (status == SYS_STATUS_LOW_POWER)
	{
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_stop();
#endif
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_LOW_BATTERY);
#endif
#ifdef __LOCK_WIFI_SUPPORT__
		mmi_dq_wifi_lowpower_alarm();
#endif
		return;
	}
	else if (status == SYS_STATUS_WAIT_FOR_ENTER_SLEEP)
		mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);

	if ((status != SYS_STATUS_INPUT_RFID && status != SYS_STATUS_ADD_RFID && status != SYS_STATUS_DEL_RFID)
#ifdef __FACTORY_TEST_SUPPORT__
		|| (status == SYS_STATUS_FM_MODE && STR_ID_RF_CARD != mmi_dq_factory_mode_get_test_project())
#endif
	)
		return;

#ifdef __LOCK_AUDIO_SUPPORT__
	mmi_dq_aud_stop();
#endif

	if (mmi_dq_sys_door_state_check() == 1)
	{
#ifdef __LOCK_AUDIO_SUPPORT__
		mmi_dq_aud_play_with_id(AUD_ID_RONG_TIMES_EXCEED);
#endif
#ifdef __LOCK_WIFI_SUPPORT__
		mmi_dq_wifi_rfid_alarm();
#endif
		return;
	}
#ifdef __FACTORY_TEST_SUPPORT__
	if (status == SYS_STATUS_FM_MODE)
	{
		retval = mmi_dq_rfid_gen_char(opt_time);
		if (retval == RET_SUCESS)
		{
			if (opt_time == OPT_ONE_TIME)
			{
#ifdef __LOCK_AUDIO_SUPPORT__
				mmi_dq_aud_play_with_id(AUD_ID_PRESS_RFCARD_AGAIN);
#endif
				opt_time = OPT_TWO_TIME;
			}
			else
			{
				retval = mmi_dq_rfid_match();
				if (retval == RET_SUCESS)

					mmi_dq_factory_mode_test_item_result(STR_ID_RF_CARD, 1);
				else
#ifdef __LOCK_AUDIO_SUPPORT__
					mmi_dq_aud_play_with_id(AUD_ID_RFCARD_TWICE_NOT_SAME_RETRY)
#endif
						;
				opt_time = OPT_ONE_TIME;
			}
		}
		return;
	}
#endif
	retval = mmi_dq_rfid_search_by_temp(&index);
	if (retval == RET_SUCESS)
	{
		if (status == SYS_STATUS_INPUT_RFID)
		{
			mmi_dq_sys_door_open(SYS_OPEN_BY_RFID);
		}
		else if (status == SYS_STATUS_ADD_RFID)
		{
#ifdef __LOCK_AUDIO_SUPPORT__
			mmi_dq_aud_play_with_id(AUD_ID_RFCARD_EXIST);
#endif
		}
		else if (status == SYS_STATUS_DEL_RFID)
		{
			retval = mmi_dq_rfid_gen_char(opt_time);
			if (retval == RET_SUCESS)
			{
				if (opt_time == OPT_ONE_TIME)
				{
#ifdef __LOCK_AUDIO_SUPPORT__
					mmi_dq_aud_play_with_id(AUD_ID_PRESS_DEL_RFCARD_AGAIN);
#endif
					opt_time = OPT_TWO_TIME;
				}
				else
				{
					retval = mmi_dq_rfid_match();
					if (retval == RET_SUCESS)
					{
						retval = mmi_dq_fs_del_rfid(index);
						if (retval == RET_SUCESS)
						{
							get_index = index;
#ifdef __LOCK_AUDIO_SUPPORT__
							mmi_dq_aud_play_with_id(AUD_ID_DEL_RFCARD_SUCESS);
#endif
#ifdef __LOCK_WIFI_SUPPORT__
							mmi_dq_wifi_del_rfid_suc(get_index);
#endif
							// printfV("get_index", (int)get_index);
						}
						else
#ifdef __LOCK_AUDIO_SUPPORT__
							mmi_dq_aud_play_with_id(AUD_ID_DEL_FAIL)
#endif
								;
						mmi_dq_sys_del_rf_con();
					}
					else
#ifdef __LOCK_AUDIO_SUPPORT__
						mmi_dq_aud_play_with_id(AUD_ID_RFCARD_TWICE_NOT_SAME_RETRY)
#endif
							;
					opt_time = OPT_ONE_TIME;
				}
			}
			else
#ifdef __LOCK_AUDIO_SUPPORT__
				mmi_dq_aud_play_with_id(AUD_ID_DEL_FAIL_RETRY)
#endif
					;
		}
	}
	else
	{
		if (status == SYS_STATUS_ADD_RFID)
		{
			retval = mmi_dq_rfid_gen_char(opt_time);
			if (retval == RET_SUCESS)
			{
				if (opt_time == OPT_ONE_TIME)
				{
#ifdef __LOCK_AUDIO_SUPPORT__
					mmi_dq_aud_play_with_id(AUD_ID_PRESS_RFCARD_AGAIN);
#endif
					opt_time = OPT_TWO_TIME;
				}
				else
				{
					retval = mmi_dq_rfid_match();
					if (retval == RET_SUCESS)
					{
						retval = mmi_dq_rfid_store(0);
						if (retval == RET_SUCESS)
						{
#ifdef __LOCK_AUDIO_SUPPORT__
							mmi_dq_aud_play_with_id(AUD_ID_ADD_RFCARD_SUCESS);
#endif
#ifdef __LOCK_WIFI_SUPPORT__
							mmi_dq_wifi_add_rfid_suc(get_index);
#endif
							// printfV("get_index", (int)get_index);
						}
						else
#ifdef __LOCK_AUDIO_SUPPORT__
							mmi_dq_aud_play_with_id(AUD_ID_ADD_FAIL)
#endif
								;
#ifdef __LOCK_WIFI_SUPPORT__
						if (wifi_add_flag == 1)
						{
							wifi_add_flag = 0xff;
							mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);
						}
						else
#endif
							mmi_dq_sys_add_rf_con();
					}
					else
#ifdef __LOCK_AUDIO_SUPPORT__
						mmi_dq_aud_play_with_id(AUD_ID_RFCARD_TWICE_NOT_SAME_RETRY)
#endif
							;
					opt_time = OPT_ONE_TIME;
				}
			}
			else
#ifdef __LOCK_AUDIO_SUPPORT__
				mmi_dq_aud_play_with_id(AUD_ID_ADD_FAIL_RETRY)
#endif
					;
		}
		else if (status == SYS_STATUS_INPUT_RFID)
			mmi_dq_sys_door_open_fail(SYS_OPEN_BY_RFID);
		else
#ifdef __LOCK_AUDIO_SUPPORT__
			mmi_dq_aud_play_with_id(AUD_ID_RFCARD_NOT_EXIST)
#endif
				;
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
void mmi_ms_reset_opt_fun(void)
{
	SYS_BASE_STATUS status = mmi_dq_ms_get_sys_state();

	if (status == SYS_STATUS_FM_MODE
#ifdef __FACTORY_TEST_SUPPORT__
		&& STR_ID_RESET == mmi_dq_factory_mode_get_test_project()
#endif
	)
	{
#ifdef __FACTORY_TEST_SUPPORT__
		mmi_dq_factory_mode_reset_test();
#endif
		return;
	}
	else
	{
		if (RET_SUCESS == mmi_dq_fs_reset())
		{
#ifdef __LOCK_AUDIO_SUPPORT__
			mmi_dq_aud_play_with_id(AUD_ID_RESTORE_SUCESS);
#endif

#ifdef __LOCK_WIFI_SUPPORT__
			mmi_dq_wifi_clr_pwd_suc();
			mmi_dq_wifi_clr_fps_suc();
			mmi_dq_wifi_clr_rfid_suc();
#endif
		}
		else
#ifdef __LOCK_AUDIO_SUPPORT__
			mmi_dq_aud_play_with_id(AUD_BASE_ID_FAIL)
#endif
				;

		mmi_dq_sys_add_admin_pwd();
	}
}

#ifdef __LOCK_WIFI_SUPPORT__
/*
parameter: 
	none
return :
	none
*/
void mmi_ms_wifi_opt_fun(void)
{
	unsigned char type = mmi_dq_sys_get_wifi_check_type();
	if (type == 0)
		mmi_dq_wifi_check_connect();
	else if (type == 1)
		mmi_dq_wifi_check_open();
}

/************************************************************************************
 * 							     	 Own function							        *
 ************************************************************************************/
#ifdef __LOCK_VIRTUAL_PASSWORD__
void mmi_dq_ms_idle_input_with_app_result(unsigned char ret_code)
{
	unsigned char open_mode = 0;

	if (ret_code == 0xFF || ret_code == 4)
	{
		if (mmi_dq_sys_lock_error() == 1)
			mmi_dq_sys_show_message_with_id(STR_ID_PASSWORD, LOCK_ADMIN, STR_ID_PWD_WRONG_TRY, SHOW_MESSAGE_DELAY_TIME, BASE_STATUS_M_SAVE_LOG);
		else
			mmi_dq_sys_show_message_with_id(STR_ID_PASSWORD, LOCK_ADMIN, STR_ID_PWD_WRONG_TRY, SHOW_MESSAGE_DELAY_TIME, BASE_STATUS_M_IDLE);
	}
	else if (ret_code == 2)
	{
		mmi_dq_sys_lock_correct();
		//dq_otp_add_open_log_by_temp(0);
		mmi_dq_sys_show_message_with_id(STR_ID_PASSWORD, LOCK_ADMIN, STR_ID_CLR_PWD_SUCESS, SHOW_MESSAGE_DELAY_TIME, BASE_STATUS_M_SAVE_LOG);
	}
	else if (ret_code == 5)
	{
		mmi_dq_sys_lock_correct();
		mmi_dq_sys_show_message_with_id(STR_ID_PASSWORD, LOCK_ADMIN, STR_ID_PWD_FULL, SHOW_MESSAGE_DELAY_TIME, BASE_STATUS_M_IDLE);
	}
	else if (ret_code == 6)
	{
		//mmi_dq_sys_lock_correct();
		mmi_dq_sys_show_message_with_id(STR_ID_PASSWORD, LOCK_ADMIN, STR_ID_APP_SYN, SHOW_MESSAGE_DELAY_TIME, BASE_STATUS_M_IDLE);
	}
	//else if(ret_code == 3)
	//{
	//	mmi_dq_sys_lock_correct();
	//dq_otp_add_open_log_by_temp(0);
	//	mmi_dq_sys_show_message_with_id(STR_ID_PASSWORD,LOCK_ADMIN,STR_ID_RESET_TIME_SUCESS,SHOW_MESSAGE_DELAY_TIME,BASE_STATUS_M_SAVE_LOG);
	//}
	else
	{
		mmi_dq_sys_lock_correct();
		open_mode = mmi_dq_fs_get_open_mode();
		if (open_mode == MS_OPEN_MODE_DBL)
		{
			if (g_dbl_open_mode_fp_flag == 1 || g_dbl_open_mode_rf_flag == 1)
			{
				g_dbl_open_mode_fp_flag = 0;
				g_dbl_open_mode_rf_flag = 0;
				dq_otp_add_open_log_by_temp(1);
				mmi_dq_sys_show_message_with_id(STR_ID_PASSWORD, LOCK_ADMIN, STR_ID_OPEN_DOOR, OPEN_LOCK_DELAY_TIME, BASE_STATUS_M_SAVE_LOG_WITH_CLOSE);
			}
			else
			{
				g_dbl_open_mode_pwd_flag = 1;
				if (mmi_dq_fs_app_init_sucess())
					dq_otp_add_exchange_temp_open_log(0, 1);
				mmi_dq_sys_show_message_with_id(STR_ID_SYSTEM, LOCK_ADMIN, STR_ID_DBL_OPEN_MODE, SHOW_MESSAGE_DELAY_TIME / 2, BASE_STATUS_M_IDLE);
			}
		}
		else
		{
			dq_otp_add_open_log_by_temp(0);
			mmi_dq_sys_show_message_with_id(STR_ID_PASSWORD, LOCK_ADMIN, STR_ID_OPEN_DOOR, OPEN_LOCK_DELAY_TIME, BASE_STATUS_M_SAVE_LOG_WITH_CLOSE);
		}
	}
}

#endif //__LOCK_VIRTUAL_PASSWORD__
/************************************************************************************
 * 							     	 End function							        *
 ************************************************************************************/

#endif
#endif //__MMI_MS_C__
