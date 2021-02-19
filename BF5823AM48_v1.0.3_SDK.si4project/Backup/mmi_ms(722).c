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
#include "dqiot_drv_fp.h"
#include "delay.h"
#include "mmi_fs.h"
//#include "stdio.h"

unsigned char input_key_1[PWD_INPUT_MAX_LEN];
unsigned char input_key_2[PWD_INPUT_MAX_LEN];
unsigned char key_len = 0;
OPERATE_TIME opt_time = OPT_TIME_INVALID;
static SYS_BASE_STATUS sys_state = SYS_STATUS_INVALID;

static unsigned char key_last_value = KEY_INVALID;
static unsigned char rfid_last_flag = 0;


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
	
	//check key press
	touch_value = mmi_dq_key_work();
	if(touch_value != 0xFF)
	{
		key_value = mmi_dq_get_key_map(touch_value);
		if(key_value != KEY_INVALID)
		{
			if(key_last_value != key_value)
			{
				key_last_value = key_value;
				mmi_dq_ms_set_msg_que(QUE_EVENT_KEY,QUE_PRO_LOW,key_value);
			}
		}
		else
			key_last_value = KEY_INVALID;
	}
	else
		key_last_value = KEY_INVALID;
	//check rfid press
	if(mmi_dq_rfid_work() == RET_SUCESS)
	{
		if(rfid_last_flag == 0)
		{
			rfid_last_flag = 1;
			mmi_dq_ms_set_msg_que(QUE_EVENT_RFID,QUE_PRO_LOW,0);
		}
	}
	else
	{
		rfid_last_flag = 0;
	}

	if(mmi_dq_aud_get_end_flag() != 0)
		mmi_dq_ms_set_msg_que(QUE_EVENT_AUDIO_END,QUE_PRO_LOW,0);

	if(mmi_dq_rst_get_state() != 0)
		mmi_dq_ms_set_msg_que(QUE_EVENT_RST,QUE_PRO_LOW,0);

	if(mmi_dq_sys_get_timer2_flag() != 0)
		mmi_dq_ms_set_msg_que(QUE_EVENT_TIMER_END,QUE_PRO_LOW,0);
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
	unsigned char time_count = 0,ret = 0xFF;
	time_count++;
	if(time_count > 4)
	{
		time_count = 0;
		ret = mmi_dq_rfid_check();
	}
	if((ret == RET_SUCESS) || (mmi_dq_key_check() != 0) || (mmi_dq_rst_get_pin() == 0))
	//if(mmi_dq_key_check() != 0)
	{
		key_last_value = mmi_dq_get_key_map(dqiot_drv_get_touch_value());
		mmi_dq_sys_wake_up();
		return;
	}

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

	//if((mmi_dq_rfid_check() == RET_SUCESS) || (mmi_dq_key_check() != 0) || (mmi_dq_rst_get_pin() == 0))
	if((mmi_dq_key_check() == 0))
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
void mmi_dq_ms_sys_msg_handle(void)
{
	Sys_MSG_Queue_M sys_msg_que;
	if(mmi_OutQueue(&sys_msg_que))
	{
		switch(sys_msg_que.que_event)
		{
			case QUE_EVENT_KEY:
				mmi_ms_pwd_opt_fun(sys_msg_que.que_data);
				break;
			case QUE_EVENT_FP:
				//mmi_ms_fps_opt_fun(sys_msg_que.que_data);
				break;
			case QUE_EVENT_RFID:
				mmi_ms_rfid_opt_fun(sys_msg_que.que_data);
				break;
			case QUE_EVENT_RST:
				
				break;
			case QUE_EVENT_AUDIO_END:
				
				break;
			case QUE_EVENT_TIMER_END:
				mmi_dq_sys_delay_event_pro();
				break;
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
void mmi_dq_ms_set_msg_que(SYS_QUEUE_EVENT q_event,SYS_QUEUE_PRO q_pro,unsigned char q_data)
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
	memset(input_key_1,0xFF,sizeof(input_key_1));
	memset(input_key_2,0xFF,sizeof(input_key_2));
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
	switch(status)
	{
		case SYS_STATUS_INPUT_PWD:
		case SYS_STATUS_INPUT_ADMIN_PWD:
		case SYS_STATUS_ADD_PWD:
		case SYS_STATUS_DEL_PWD:
		case SYS_STATUS_ADD_ADMIN_PWD:
			mmi_dq_aud_play_key_num(key_val);
			if(key_len == 0)
			{
				if(key_val == KEY_S)
				{
					if(status == SYS_STATUS_INPUT_PWD)
						//mmi_dq_sys_enter_sleep();
						mmi_dq_ms_set_sys_state(SYS_STATUS_WAIT_FOR_ENTER_SLEEP);
					else if(status == SYS_STATUS_INPUT_ADMIN_PWD)
						mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);
					else if(!((SYS_STATUS_ADD_ADMIN_PWD == status) && (FDS_INIT_INVALID == mmi_dq_fs_get_init_flag())))
						mmi_dq_sys_show_cur_menu_list();
					break;
				}
				else if(key_val == KEY_H)
				{
					if(status == SYS_STATUS_INPUT_PWD)
					{
						mmi_dq_aud_play_with_id(AUD_ID_INPUT_ADMIN_PWD);
						mmi_dq_ms_set_sys_state(SYS_STATUS_INPUT_ADMIN_PWD);
					}
					break;
				}
			}
			//input pwd
			if(key_val == KEY_S)
			{
				if(opt_time == OPT_ONE_TIME)
					input_key_1[key_len--] = 0xFF;
				else if(opt_time == OPT_TWO_TIME)
					input_key_2[key_len--] = 0xFF;
			}
			else if((key_val == KEY_H) || (key_len == PWD_INPUT_MAX_LEN))
			{
				if(key_len < PWD_INPUT_MIN_LEN)
				{
					mmi_dq_aud_play_with_id(AUD_ID_PWD_68_LEN);
					key_len = 0;
					if(opt_time == OPT_ONE_TIME)
						memset(input_key_1,0xFF,sizeof(input_key_1));
					else if(opt_time == OPT_TWO_TIME)
						memset(input_key_2,0xFF,sizeof(input_key_2));
				} 
				else
				{
					if(status == SYS_STATUS_INPUT_PWD)
					{
						if(mmi_dq_fs_check_input_pwd(input_key_1,key_len,FDS_USE_TYPE_ALL) == 0xFF)
							mmi_dq_aud_play_with_id(AUD_ID_PWD_WRONG_TRY);
						else
							mmi_dq_sys_door_open(SYS_OPEN_BY_PASSWORD);
						key_len = 0;
						memset(input_key_1,0xFF,sizeof(input_key_1));
					}
					else if(status == SYS_STATUS_INPUT_ADMIN_PWD)
					{
						if(mmi_dq_fs_check_input_pwd(input_key_1,key_len,FDS_USE_TYPE_ADMIN) == 0xFF)
							mmi_dq_aud_play_with_id(AUD_ID_PWD_WRONG_TRY);
						else
						{
							mmi_dq_sys_set_menu_father_id(STR_ID_SYSTEM);
							mmi_dq_sys_show_cur_menu_list();
						}
						key_len = 0;
						memset(input_key_1,0xFF,sizeof(input_key_1));
					}
					else if((status == SYS_STATUS_ADD_PWD)||(status == SYS_STATUS_DEL_PWD)||(status == SYS_STATUS_ADD_ADMIN_PWD))
					{
						if(opt_time == OPT_ONE_TIME)
						{
							mmi_dq_aud_play_with_id(AUD_ID_PWD_INPUT_AGAIN);
							opt_time = OPT_TWO_TIME;
							key_len = 0;
							memset(input_key_2,0xFF,sizeof(input_key_2));
						}
						else if(opt_time == OPT_TWO_TIME)
						{
							if(0 == memcmp(input_key_1,input_key_2,PWD_INPUT_MAX_LEN))
							{
								if(status == SYS_STATUS_ADD_PWD)
								{
									if(mmi_dq_fs_check_input_pwd(input_key_1,key_len,FDS_USE_TYPE_ALL) != 0xFF)
										mmi_dq_aud_play_with_id(AUD_ID_PWD_EXIST);
									else
									{
										if(mmi_dq_fs_set_pwd(input_key_1,key_len,FDS_USE_TYPE_USER) == RET_FAIL)
											mmi_dq_aud_play_with_id(AUD_ID_ADD_FAIL);
										else
											mmi_dq_aud_play_with_id(AUD_ID_ADD_PWD_SUCESS);
										mmi_dq_sys_add_pwd_con();
									}
								}
								else if(status == SYS_STATUS_ADD_ADMIN_PWD)
								{
									if(mmi_dq_fs_set_pwd(input_key_1,key_len,FDS_USE_TYPE_ADMIN) == RET_FAIL)
										mmi_dq_aud_play_with_id(AUD_ID_ADD_FAIL);
									else
										mmi_dq_aud_play_with_id(AUD_ID_CHG_ADMIN_PWD_SUCESS);
									if(FDS_INIT_INVALID == mmi_dq_fs_get_init_flag())
										mmi_dq_sys_lock_init_suc();//mmi_dq_sys_chg_admin_fp_No1();
									else
										mmi_dq_sys_show_cur_menu_list();
								}
								else if(status == SYS_STATUS_DEL_PWD)
								{
									unsigned char del_index = mmi_dq_fs_check_input_pwd(input_key_1,key_len,FDS_USE_TYPE_USER);
									if(del_index == 0xFF)
										mmi_dq_aud_play_with_id(AUD_ID_PWD_NOT_EXIST);
									else
									{
										if(mmi_dq_fs_del_pwd(del_index, FDS_USE_TYPE_USER) == RET_SUCESS)
											mmi_dq_aud_play_with_id(AUD_ID_DEL_PWD_SUCESS);
										else
											mmi_dq_aud_play_with_id(AUD_ID_DEL_FAIL);
										mmi_dq_sys_del_pwd_con();
									}
								}
							}
							else
							{
								mmi_dq_aud_play_with_id(AUD_ID_PWD_NOT_SAME_RETRY);
							}
							mmi_ms_pwd_init_var();
						}
					}
				}
				return;
			}
			else
			{
				if((status == SYS_STATUS_INPUT_PWD)||(status == SYS_STATUS_INPUT_ADMIN_PWD))
				{
					input_key_1[key_len++] = key_val;
				}
				else if((status == SYS_STATUS_ADD_PWD)||(status == SYS_STATUS_DEL_PWD)||(status == SYS_STATUS_ADD_ADMIN_PWD))
				{
					if(opt_time == OPT_ONE_TIME)
					{
						input_key_1[key_len++] = key_val;
					}
					else if(opt_time == OPT_TWO_TIME)
					{
						input_key_2[key_len++] = key_val;
					}
				}
			}
			break;
		//case SYS_STATUS_INPUT_FP:
		//case SYS_STATUS_INPUT_ADMIN_FP:
		case SYS_STATUS_ADD_FP:
		case SYS_STATUS_DEL_FP:
		case SYS_STATUS_ADD_ADMIN_FP1:
		case SYS_STATUS_ADD_ADMIN_FP2:
		//case SYS_STATUS_INPUT_RFID:
		case SYS_STATUS_ADD_RFID:
		case SYS_STATUS_DEL_RFID:
			if(key_val == KEY_S)
			{
				mmi_dq_aud_play_key_tone();
				mmi_dq_sys_show_cur_menu_list();
			}
			break;
		case SYS_STATUS_CLR_PWD:
		case SYS_STATUS_ADD_PWD_CON:
		case SYS_STATUS_DEL_PWD_CON:
		case SYS_STATUS_CLR_FP:
		case SYS_STATUS_ADD_FP_CON:
		case SYS_STATUS_DEL_FP_CON:
		case SYS_STATUS_CLR_RFID:
		case SYS_STATUS_ADD_RFID_CON:
		case SYS_STATUS_DEL_RFID_CON:
		case SYS_STATUS_RESTORE_LOCK_CON:
			if(key_val == KEY_H)
			{
				mmi_dq_aud_play_key_tone();
				switch(status)
				{
					case SYS_STATUS_CLR_PWD:
						if(RET_SUCESS == mmi_dq_fs_clr_pwd())
							mmi_dq_aud_play_with_id(AUD_ID_CLR_PWD_SUCESS);
						else
							mmi_dq_aud_play_with_id(AUD_ID_CLR_PWD_FAIL);
						mmi_dq_sys_show_cur_menu_list();
						break;
					case SYS_STATUS_CLR_FP:
						if(RET_SUCESS == mmi_dq_fs_clr_pwd())
							mmi_dq_aud_play_with_id(AUD_ID_CLR_FP_SUCESS);
						else
							mmi_dq_aud_play_with_id(AUD_ID_CLR_FP_FAIL);
						mmi_dq_sys_show_cur_menu_list();
						break;
					case SYS_STATUS_CLR_RFID:
						if(RET_SUCESS == mmi_dq_fs_clr_rfid())
							mmi_dq_aud_play_with_id(AUD_ID_CLR_RFCARD_SUCESS);
						else
							mmi_dq_aud_play_with_id(AUD_ID_CLR_RFCARD_FAIL);
						mmi_dq_sys_show_cur_menu_list();
						break;
					case SYS_STATUS_ADD_PWD_CON:
						mmi_dq_sys_add_pwd();
						break;	
					case SYS_STATUS_DEL_PWD_CON:
						mmi_dq_sys_del_pwd();
						break;
					case SYS_STATUS_ADD_FP_CON:
						mmi_dq_sys_add_fp();
						break;	
					case SYS_STATUS_DEL_FP_CON:
						mmi_dq_sys_del_fp();
						break;
					case SYS_STATUS_ADD_RFID_CON:
						mmi_dq_sys_add_rf();
						break;	
					case SYS_STATUS_DEL_RFID_CON:
						mmi_dq_sys_del_rf();
						break;
					case SYS_STATUS_RESTORE_LOCK_CON:
						mmi_dq_sys_restore_lock();
						break;
				}
			}	
			else if(key_val == KEY_S)
			{
				mmi_dq_aud_play_key_tone();
				mmi_dq_sys_show_cur_menu_list();
			}
			break;
		case SYS_STATUS_SYS_MENU:
			if(key_val == KEY_S)
			{
				mmi_dq_aud_play_key_tone();
				mmi_dq_sys_get_pre_menu_list();
			}
			else if(key_val <= mmi_dq_sys_get_menu_count())
			{
				mmi_dq_aud_play_key_tone();
				mmi_dq_sys_exe_menu_fun(key_val-1);	
			}
			break;
		default:
			break;
	}
	return;
}


/*
parameter: 
	none
return :
	none
*/
void mmi_ms_fps_opt_fun(unsigned char fps_val)
{
	#if 0
	RET_VAL retval = 0;
	unsigned char index = 0;
	SYS_BASE_STATUS status = mmi_dq_ms_get_sys_state();
	mmi_dq_fps_set_irq_handle_cb(NULL);

#ifdef __LOCK_AUDIO_SUPPORT__
	mmi_dq_aud_stop();
#endif	
	retval = mmi_dq_fp_get_image();
	if(retval == 0)
	{
		retval = mmi_dq_fp_gen_char(opt_time);
		if(retval == 0)
		{
			retval = mmi_dq_fp_high_speed_search(opt_time,&index);
			if(retval != 0)
			{
				mmi_dq_fp_light(FP_GREEN);
				if(opt_time == FPS_MAX_INPUT_TIME)
				{
					opt_time = OPT_TIME_INVALID;
					if(status == SYS_STATUS_ADD_FPS)
					{
						mmi_dq_sys_show_message_with_id(STR_ID_FP_EXIST,0);
					}
					else if(status == SYS_STATUS_DEL_FPS)
					{
						mmi_dq_sys_show_message_with_id(STR_ID_DEL_FP_SUCESS,0);
					}
				}
				else
				{
					opt_time++;
					mmi_dq_ms_set_sys_state(SYS_STATUS_ADD_FPS);
				}
				return;
			}
		}
	}
	opt_time = OPT_TIME_INVALID;
	mmi_dq_fp_light(FP_RED);
	if(status == SYS_STATUS_ADD_FPS)
	{
		mmi_dq_sys_show_message_with_id(STR_ID_FP_EXIST,0);
	}
	else if(status == SYS_STATUS_DEL_FPS)
	{
		mmi_dq_sys_show_message_with_id(STR_ID_DEL_FAIL,0);
	}
	return;
	#endif
}

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

	if(status != SYS_STATUS_INPUT_RFID && status != SYS_STATUS_ADD_RFID && status != SYS_STATUS_DEL_RFID)
		return;
	
#ifdef __LOCK_AUDIO_SUPPORT__
	mmi_dq_aud_stop();
#endif	

	retval = mmi_dq_rfid_search_by_temp(&index);
	if(retval == RET_SUCESS)
	{
		if(status == SYS_STATUS_INPUT_RFID)
		{
			mmi_dq_sys_door_open(SYS_OPEN_BY_RFID);
		}
		else if(status == SYS_STATUS_ADD_RFID)
		{
			mmi_dq_aud_play_with_id(AUD_ID_RFCARD_EXIST);
		}
		else if(status == SYS_STATUS_DEL_RFID)
		{
			retval = mmi_dq_rfid_gen_char(opt_time);
			if(retval == RET_SUCESS)
			{
				if(opt_time == OPT_ONE_TIME)
				{
					mmi_dq_aud_play_with_id(AUD_ID_PRESS_DEL_RFCARD_AGAIN);
					opt_time = OPT_TWO_TIME;
				}
				else
				{
					retval = mmi_dq_rfid_match();
					if(retval == RET_SUCESS)
					{
						retval = mmi_dq_fs_del_rfid(index);
						if(retval == RET_SUCESS)
						{
							mmi_dq_aud_play_with_id(AUD_ID_DEL_RFCARD_SUCESS);
						}
						else
							mmi_dq_aud_play_with_id(AUD_ID_DEL_FAIL);
						mmi_dq_sys_del_rf_con();
					}
					else
						mmi_dq_aud_play_with_id(AUD_ID_RFCARD_NOT_SAME);
					opt_time = OPT_ONE_TIME;
				}
			}
			else
				mmi_dq_aud_play_with_id(AUD_ID_DEL_FAIL_RETRY);
		}

	}
	else
	{
		if(status == SYS_STATUS_ADD_RFID)
		{
			retval = mmi_dq_rfid_gen_char(opt_time);
			if(retval == RET_SUCESS)
			{
				if(opt_time == OPT_ONE_TIME)
				{
					mmi_dq_aud_play_with_id(AUD_ID_PRESS_RFCARD_AGAIN);
					opt_time = OPT_TWO_TIME;
				}
				else
				{
					retval = mmi_dq_rfid_match();
					if(retval == RET_SUCESS)
					{
						retval = mmi_dq_rfid_store(0);
						if(retval == RET_SUCESS)
						{
							mmi_dq_aud_play_with_id(AUD_ID_ADD_RFCARD_SUCESS);
						}
						else
							mmi_dq_aud_play_with_id(AUD_ID_ADD_FAIL);
						mmi_dq_sys_add_rf_con();
					}
					else
						mmi_dq_aud_play_with_id(AUD_ID_RFCARD_NOT_SAME);
					opt_time = OPT_ONE_TIME;
				}
			}
			else
				mmi_dq_aud_play_with_id(AUD_ID_ADD_FAIL_RETRY);
		}
		else if(status == SYS_STATUS_INPUT_RFID)
			mmi_dq_aud_play_with_id(AUD_ID_RFCARD_WRONG_TRY);
		else
			mmi_dq_aud_play_with_id(AUD_ID_RFCARD_NOT_EXIST);
	}

	return;
}

#endif
