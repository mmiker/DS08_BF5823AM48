#ifndef __MMI_MS_C__
#define __MMI_MS_C__

#include "string.h"
#include "mmi_ms.h"
#include "mmi_key.h"
#include "mmi_sys.h"
#include "mmi_audio.h"
#include "mmi_fps.h"
#include "mmi_com.h"
#include "dqiot_drv.h"
#include "dqiot_drv_fp.h"
#include "delay.h"

uint8_t input_key_1[PWD_INPUT_MAX_LEN];
uint8_t input_key_2[PWD_INPUT_MAX_LEN];
uint8_t key_len = 0;
OPERATE_TIME opt_time = OPT_TIME_INVALID;
SYS_BASE_STATUS sys_state = SYS_STATUS_INVALID;

/*
parameter: 
	none
return :
	current machine status
*/
void mmi_task_proc(void)
{
	unsigned int timer0_count = 0;
	unsigned int timer1_count = 0;
	uint8_t key_value = 0;
	uint8_t i = 0;
	
	//check key press
	timer0_count = dqiot_drv_get_timer0_count();
	mmi_dq_key_work();

	if(timer0_count > 50)
	{
		dqiot_drv_set_timer0_count(0);
		key_value = mmi_dq_get_key_map(mmi_dq_key_get_value());
		if(key_value != KEY_INVALID)
		{
			mmi_dq_ms_set_msg_que(QUE_EVENT_KEY,QUE_PRO_LOW,key_value);
		}
	}
	//if(mmi_Que_IsEmpty() == 0)
	//{
		mmi_dq_ms_sys_msg_handle();
	//}
	return;
}

/*
parameter: 
	none
return :
	current machine status
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
				mmi_ms_fps_opt_fun(sys_msg_que.que_data);
				break;
			case QUE_EVENT_RFID:
				mmi_ms_rfid_opt_fun(sys_msg_que.que_data);
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
	current machine status
*/
void mmi_dq_ms_set_msg_que(SYS_QUEUE_EVENT q_event,SYS_QUEUE_PRO q_pro,uint8_t q_data)
{
	Sys_MSG_Queue_M que;
	que.que_event = q_event;
	que.que_pro = q_pro;
	que.que_data = q_data;
	mmi_InQueue(que);
	return;
}

/*
parameter: 
	none
return :
	current machine status
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
	current machine status
*/
SYS_BASE_STATUS mmi_dq_ms_get_sys_state(void)
{
	return sys_state;
}

/*
parameter: 
	none
return :
	current machine status
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
	current machine status
*/
void mmi_ms_pwd_opt_fun(uint8_t key_val)
{
	uint8_t i = 0;
	uint8_t ret_code = 0xFF;
	uint8_t open_mode = 0;
	uint8_t max_len = 0;
	SYS_BASE_STATUS status = mmi_dq_ms_get_sys_state();
	
	if(key_len == 0)
	{
		if(key_val == KEY_S)
		{
			mmi_dq_sys_enter_sleep();
			return;
		}
		else if(key_val == KEY_H)
		{
			mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);
			return;
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
			mmi_ms_pwd_init_var();
			mmi_dq_aud_play_with_id(STR_ID_PWD_LEN_68,NULL);//
		} 
		else
		{
			if(status == SYS_STATUS_INPUT_PWD)
			{
				dqiot_drv_log_output_data('%',key_len);
				//find the pwd
				for(i=0;i<key_len;i++)
				{
					dqiot_drv_log_output_data('#',input_key_1[i]);
				}
			}
			else if((status == SYS_STATUS_ADD_PWD)||(status == SYS_STATUS_DEL_PWD))
			{
				if(opt_time == OPT_ONE_TIME)
				{
					opt_time = OPT_TWO_TIME;
					key_len = 0;
					memset(input_key_2,0xFF,sizeof(input_key_2));
				}
				else if(opt_time == OPT_TWO_TIME)
				{
					if(!strcmp(input_key_1,input_key_2))
					{
						if(status == SYS_STATUS_ADD_PWD)
							;
						else if(status == SYS_STATUS_DEL_PWD)
							;
					}
					else
					{
						mmi_ms_pwd_init_var();
						mmi_dq_aud_play_with_id(STR_ID_PWD_WRONG,NULL);//

					}
				}
			}
		}
		return;
	}
	else
	{
		dqiot_drv_log_output("^^^^^^\r\n");
		if(status == SYS_STATUS_INPUT_PWD)
		{
			input_key_1[key_len++] = key_val;
		}
		else if((status == SYS_STATUS_ADD_PWD)||(status == SYS_STATUS_DEL_PWD))
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
	return;
}


/*
parameter: 
	none
return :
	current machine status
*/
void mmi_ms_fps_opt_fun(uint8_t fps_val)
{
	uint8_t retval = 0;
	uint8_t index = 0;
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
						mmi_dq_sys_show_message_with_id(STR_ID_ADD_FP,LOCK_ADMIN,STR_ID_FP_EXIST,0);
					}
					else if(status == SYS_STATUS_DEL_FPS)
					{
						mmi_dq_sys_show_message_with_id(STR_ID_DEL_FP,LOCK_ADMIN,STR_ID_DEL_FP_SUCESS,0);
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
		mmi_dq_sys_show_message_with_id(STR_ID_ADD_FP,LOCK_ADMIN,STR_ID_FP_EXIST,0);
	}
	else if(status == SYS_STATUS_DEL_FPS)
	{
		mmi_dq_sys_show_message_with_id(STR_ID_DEL_FP,LOCK_ADMIN,STR_ID_DEL_FAIL,0);
	}
	return;
}

/*
parameter: 
	none
return :
	current machine status
*/
void mmi_ms_rfid_opt_fun(uint8_t rfid_val)
{
	RET_VAL retval = RET_SUCESS;
	uint8_t retval = 0;
	uint8_t index = 0;
	SYS_BASE_STATUS status = mmi_dq_ms_get_sys_state();
	
#ifdef __LOCK_AUDIO_SUPPORT__
	mmi_dq_aud_stop();
#endif	
	retval = mmi_dq_rfid_search_by_temp(&index);
	if(retval != 0)
	{
		if(status == SYS_STATUS_INPUT_RFID)
		{
			
		}
		else if(status == SYS_STATUS_ADD_RFID)
		{

		}
		else if(status == SYS_STATUS_DEL_RFID)
		{
			retval = mmi_dq_rfid_gen_char(opt_time);
			if(retval != 0)
			{
				if(opt_time == OPT_ONE_TIME)
					opt_time++;
				else
				{
					retval = mmi_dq_rfid_match()
					if(retval == 0)
						mmi_dq_sys_show_message_with_id(STR_ID_DEL_FP,LOCK_ADMIN,STR_ID_DEL_FP_SUCESS,0);
					else
						
				}
			}
		}
			if(retval != 0)
			{
				if(opt_time == FPS_MAX_INPUT_TIME)
				{
					opt_time = OPT_TIME_INVALID;
					if(status == SYS_STATUS_ADD_FPS)
					{
						mmi_dq_sys_show_message_with_id(STR_ID_ADD_FP,LOCK_ADMIN,STR_ID_FP_EXIST,0);
					}
					else if(status == SYS_STATUS_DEL_FPS)
					{
						mmi_dq_sys_show_message_with_id(STR_ID_DEL_FP,LOCK_ADMIN,STR_ID_DEL_FP_SUCESS,0);
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
		mmi_dq_sys_show_message_with_id(STR_ID_ADD_FP,LOCK_ADMIN,STR_ID_FP_EXIST,0);
	}
	else if(status == SYS_STATUS_DEL_FPS)
	{
		mmi_dq_sys_show_message_with_id(STR_ID_DEL_FP,LOCK_ADMIN,STR_ID_DEL_FAIL,0);
	}

	return;
}

#endif
