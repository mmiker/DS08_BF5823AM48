#ifndef __MMI_FM_C__
#define __MMI_FM_C__
#include "mmi_feature.h"
#ifdef __FACTORY_TEST_SUPPORT__
#include "mmi_ms.h"
#include "mmi_fm.h"
#include "mmi_audio.h"
#include "mmi_com.h"
#include "mmi_sys.h"
#include "mmi_fps.h"
#include "mmi_rfid.h"
#include "mmi_fs.h"
#include "mmi_key.h"
#include "string.h"
#include "delay.h"
#include "mmi_motor.h"

unsigned char g_fm_flag = 0;
unsigned char g_fm_project = 0;
static unsigned int g_fm_key_flag = 0;

unsigned char g_fm_result_name[]={
									STR_ID_KEY,
					#ifdef __LOCK_OLED_SUPPORT__
									STR_ID_KEY_LIGHT,
									STR_ID_OLED,
					#endif
					#if defined(__LOCK_FP_SUPPORT__)||defined(__LOCK_FP_SUPPORT2__) || defined (__LOCK_FP_SUPPORT1_2__)
									STR_ID_FINGERPRINT,
					#endif
					#ifdef __LOCK_RFID_CARD_SUPPORT__
									STR_ID_RF_CARD,
					#endif
									STR_ID_MOTO,
					#ifdef __LOCK_OLED_SUPPORT__
									STR_ID_SOUND,
					#endif
									STR_ID_RESET,
									};

									
#define KEY_ALL (0xFFF)

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_factory_mode_test_item_select(unsigned char item_num)
{
	switch(g_fm_result_name[item_num])
	{
		case STR_ID_KEY:
			mmi_dq_aud_play_with_id(AUD_ID_FM_KEY_INPUT);
			if(mmi_dq_fs_get_factory_flag()!=0)
				mmi_dq_aud_play_with_id(AUD_ID_INPUT_BACK);
			g_fm_key_flag = 0;
			break;
#ifdef __LOCK_OLED_SUPPORT__
		case STR_ID_KEY_LIGHT:
			break;
		case STR_ID_OLED:
			break;
#endif
#if defined(__LOCK_FP_SUPPORT__)||defined(__LOCK_FP_SUPPORT2__) || defined (__LOCK_FP_SUPPORT1_2__)
		case STR_ID_FINGERPRINT:
			mmi_ms_opt_time_init();
			mmi_dq_aud_play_with_id(AUD_ID_PRESS_FP);
			if(mmi_dq_fs_get_factory_flag()!=0)
				mmi_dq_aud_play_with_id(AUD_ID_INPUT_BACK);
			break;
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
		case STR_ID_RF_CARD:
			mmi_ms_opt_time_init();
			mmi_dq_aud_play_with_id(AUD_ID_PRESS_RFCARD);
			if(mmi_dq_fs_get_factory_flag()!=0)
				mmi_dq_aud_play_with_id(AUD_ID_INPUT_BACK);
			break;
#endif
		case STR_ID_MOTO:
			mmi_dq_aud_play_with_id(AUD_ID_FM_MOTO);
			mmi_dq_factory_mode_motor_test();
			break;
#ifdef __LOCK_OLED_SUPPORT__
		case STR_ID_SOUND:
			break;
#endif
		case STR_ID_RESET:
			mmi_dq_aud_play_with_id(AUD_ID_FM_RESET);
			if(mmi_dq_fs_get_factory_flag()!=0)
				mmi_dq_aud_play_with_id(AUD_ID_INPUT_BACK);
			break;
		default:
			break;
	}
	g_fm_project = g_fm_result_name[item_num];
}



/*
parameter: 
	none
return :
	none
*/
void mmi_dq_factory_mode_test_item_result(unsigned char item_name, unsigned char result)
{
	unsigned char max = sizeof(g_fm_result_name)/sizeof(unsigned char);
	unsigned char i = 0;
	for(i=0;i<max;i++)
	{
		if(g_fm_result_name[i]==item_name)
			break;
	}

	g_fm_flag += (result<<i);
	
	i++;
	if(i<max)
		mmi_dq_factory_mode_test_item_select(i);
	else
	{
		mmi_dq_fs_set_factory_flag(g_fm_flag);
		mmi_dq_factory_mode_test_stop();
	}
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_factory_mode_get_test_project(void)
{
	return g_fm_project;
}


/*
parameter: 
	none
return :
	none
*/
void mmi_dq_factory_mode_test_start(void)
{
	g_fm_flag = 0;
	mmi_dq_factory_mode_test_item_select(0);
	mmi_dq_ms_set_sys_state(SYS_STATUS_FM_MODE);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_factory_mode_test_stop(void)
{
	//if(mmi_dq_fs_get_factory_flag()!=0)
	{
		if(mmi_dq_fs_get_admin_status() == 0)
			mmi_dq_sys_add_admin_pwd();
		else
			mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);
	}
	return;
}


/*
parameter: 
	none
return :
	none
*/
void mmi_dq_factory_mode_key_test(unsigned char key_value)
{
	static unsigned char touch_out_count = 0;
	if(key_value == KEY_S && mmi_dq_fs_get_factory_flag()!=0)
	{
		if(g_fm_key_flag == 0)
		{
			touch_out_count = 0;
			mmi_dq_factory_mode_test_stop();
		}
		else
		{
			touch_out_count++;
			if(touch_out_count>2)
			{
				touch_out_count = 0;
				mmi_dq_factory_mode_test_stop();
			}
		}
	}
	g_fm_key_flag |= (1<<key_value);
	if(g_fm_key_flag == KEY_ALL)
		mmi_dq_factory_mode_test_item_result(STR_ID_KEY,1);
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_factory_mode_fp_test(void)
{
	mmi_dq_factory_mode_test_item_result(STR_ID_FINGERPRINT,1);

}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_factory_mode_rfid_test(void)
{
	mmi_dq_factory_mode_test_item_result(STR_ID_RF_CARD,1);

}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_factory_mode_motor_test(void)
{
	mmi_dq_motor_turn_right();
	delay_ms(300);
	mmi_dq_motor_stop();
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_factory_mode_motor_test_back(void)
{
	mmi_dq_motor_turn_back();
	delay_ms(300);
	mmi_dq_motor_stop();
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_factory_mode_reset_test(void)
{
	mmi_dq_factory_mode_test_item_result(STR_ID_RESET,1);
}
#endif
#endif