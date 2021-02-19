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
#include "delay.h"

unsigned char input_key_1[PWD_INPUT_MAX_LEN];
unsigned char input_key_2[PWD_INPUT_MAX_LEN];
unsigned char key_len = 0;
unsigned char g_fps_buf_index = 0;
unsigned short g_current_key = 0xFFFF;
OPERATE_TIME opt_time = OPT_TIME_INVALID;
Sys_MSG_Queue sys_msg_que;

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
	unsigned char key_value = 0;
	unsigned char key_index = 0;
	unsigned char i = 0;
	
	//check key press
	timer0_count = dqiot_drv_get_timer0_count();
	mmi_dq_key_work();

	if(timer0_count > 50)
	{
		dqiot_drv_set_timer0_count(0);
		key_index = mmi_dq_key_get_value();
		key_value = mmi_dq_get_key_map(key_index);
		if(key_value != KEY_INVALID)
		{
			drv_fp_test();
			delay_ms(200);
			for(i=0;i<20;i++)
			{
				key_index = dqiot_drv_get_uart0_data(i);
				dqiot_drv_log_output_data('@',key_index);
			}
			mmi_dq_ms_set_msg_que(MSG_QUE_ADD_PWD);
			g_current_key = key_value;
		}
	}
	if(mmi_Que_IsEmpty() == 0)
	{
		sys_msg_que.que_pro = QUE_PRO_INVALID;
		sys_msg_que.q_status = MSG_QUE_INVALID;
		mmi_GetCurQueue(&sys_msg_que);
		mmi_dq_ms_sys_msg_handle(sys_msg_que);
	}
	return;
}

/*
parameter: 
	none
return :
	current machine status
*/
void mmi_dq_ms_sys_msg_handle(Sys_MSG_Queue msg_que)
{
	switch(msg_que.q_status)
	{
		case MSG_QUE_INPUT_PWD:
			mmi_ms_pwd_opt_fun(g_current_key);
			break;
		default:
			break;
	}
}

/*
parameter: 
	none
return :
	current machine status
*/
void mmi_dq_ms_set_msg_que(SYS_QUEUE_STATUS q_status)
{
	switch(q_status)
	{
		case MSG_QUE_IDLE:
		case MSG_QUE_INPUT_PWD:
		case MSG_QUE_ADD_PWD:
		case MSG_QUE_ADD_PWD_AGAIN:
		case MSG_QUE_DEL_PWD:
		case MSG_QUE_DEL_PWD_AGAIN:
		case MSG_QUE_INPUT_FPS:
		case MSG_QUE_ADD_FPS:
		case MSG_QUE_ADD_FPS_AGAIN:
		case MSG_QUE_DEL_FPS:
		case MSG_QUE_DEL_FPS_AGAIN:
			sys_msg_que.q_status = q_status;
			sys_msg_que.que_pro = QUE_PRO_LOW;
			break;
	}
	mmi_InQueue(sys_msg_que);
	return;
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
	memset(input_key_1,0x00,sizeof(input_key_1));
	memset(input_key_2,0x00,sizeof(input_key_2));
}

/*
parameter: 
	none
return :
	current machine status
*/
void mmi_ms_pwd_opt_fun(unsigned char key_val)
{
	unsigned char i = 0;
	unsigned char ret_code = 0xFF;
	unsigned char open_mode = 0;
	unsigned char max_len = 0;
	
	if(key_len == 0)
	{
		if(key_val == KEY_S)
		{
			mmi_dq_sys_enter_sleep();
			return;
		}
		else if(key_val == KEY_H)
		{
			mmi_dq_ms_set_msg_que(MSG_QUE_IDLE);
			return;
		}
	}
	//input pwd
	if(key_val == KEY_S)
	{
		if(opt_time == OPT_ONE_TIME)
			input_key_1[key_len--] = '\0';
		else if(opt_time == OPT_TWO_TIME)
			input_key_2[key_len--] = '\0';
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
			if(sys_msg_que.q_status == MSG_QUE_INPUT_PWD)
			{
				dqiot_drv_log_output_data('%',key_len);
				//find the pwd
				for(i=0;i<key_len;i++)
				{
					dqiot_drv_log_output_data('#',input_key_1[i]);
				}
			}
			else if((sys_msg_que.q_status == MSG_QUE_ADD_PWD)||(sys_msg_que.q_status == MSG_QUE_DEL_PWD))
			{
				if(opt_time == OPT_ONE_TIME)
				{
					opt_time = OPT_TWO_TIME;
					key_len = 0;
					memset(input_key_2,0x00,sizeof(input_key_2));
					if(sys_msg_que.q_status == MSG_QUE_ADD_PWD)
						mmi_dq_ms_set_msg_que(MSG_QUE_ADD_PWD_AGAIN);
					else if(sys_msg_que.q_status == MSG_QUE_DEL_PWD)
						mmi_dq_ms_set_msg_que(MSG_QUE_DEL_PWD_AGAIN);
				}
				else if(opt_time == OPT_TWO_TIME)
				{
					if(!strcmp(input_key_1,input_key_2))
					{
						if(sys_msg_que.q_status == MSG_QUE_ADD_PWD)
							;
						else if(sys_msg_que.q_status == MSG_QUE_DEL_PWD)
							;
					}
					else
					{
						mmi_ms_pwd_init_var();
						mmi_dq_aud_play_with_id(STR_ID_PWD_WRONG,NULL);//
						if(sys_msg_que.q_status == MSG_QUE_ADD_PWD)
							mmi_dq_ms_set_msg_que(MSG_QUE_ADD_PWD);
						else if(sys_msg_que.q_status == MSG_QUE_DEL_PWD)
							mmi_dq_ms_set_msg_que(MSG_QUE_DEL_PWD);
					}
				}
			}
		}
		return;
	}
	else
	{
		dqiot_drv_log_output("^^^^^^\r\n");
		if(sys_msg_que.q_status == MSG_QUE_INPUT_PWD)
		{
			input_key_1[key_len++] = key_val;
		}
		else if((sys_msg_que.q_status == MSG_QUE_ADD_PWD)||(sys_msg_que.q_status == MSG_QUE_DEL_PWD))
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
void mmi_ms_fps_opt_fun(void)
{
	unsigned short retval = 0;
	unsigned short index = 0;
	mmi_dq_fps_set_irq_handle_cb(NULL);

#ifdef __LOCK_AUDIO_SUPPORT__
	mmi_dq_aud_stop();
#endif	
	retval = mmi_dq_fp_get_image();
	if(retval == 0)
	{
		if(opt_time == OPT_ONE_TIME)
			g_fps_buf_index = 0;
		else
			g_fps_buf_index++;
		retval = mmi_dq_fp_gen_char(g_fps_buf_index);
		if(retval == 0)
		{
			retval = mmi_dq_fp_high_speed_search(g_fps_buf_index,&index);
			if(retval != 0)
			{
				mmi_dq_fp_light(FP_GREEN);
				if(opt_time == FPS_MAX_INPUT_TIME)
				{
					opt_time = OPT_TIME_INVALID;
					if(sys_msg_que.q_status == MSG_QUE_ADD_FPS)
					{
						mmi_dq_sys_show_message_with_id(STR_ID_ADD_FP,LOCK_ADMIN,STR_ID_FP_EXIST,0,MSG_QUE_ADD_FPS);
					}
					else if(sys_msg_que.q_status == MSG_QUE_DEL_FPS)
					{
						mmi_dq_sys_show_message_with_id(STR_ID_DEL_FP,LOCK_ADMIN,STR_ID_DEL_FP_SUCESS,0,MSG_QUE_ADD_FPS);
					}
				}
				else
				{
					opt_time++;
					mmi_dq_ms_set_msg_que(MSG_QUE_ADD_FPS_AGAIN);
				}
				return;
			}
		}
	}
	opt_time = OPT_TIME_INVALID;
	mmi_dq_fp_light(FP_RED);
	if(sys_msg_que.q_status == MSG_QUE_ADD_FPS)
	{
		mmi_dq_sys_show_message_with_id(STR_ID_ADD_FP,LOCK_ADMIN,STR_ID_FP_EXIST,0,MSG_QUE_ADD_FPS);
	}
	else if(sys_msg_que.q_status == MSG_QUE_DEL_FPS)
	{
		mmi_dq_sys_show_message_with_id(STR_ID_DEL_FP,LOCK_ADMIN,STR_ID_DEL_FAIL,0,MSG_QUE_IDLE);
	}
	return;
}

/*
parameter: 
	none
return :
	current machine status
*/
void mmi_ms_rfid_opt_fun(void)
{
	RET_VAL retval = RET_SUCESS;

	return;
}

#endif
