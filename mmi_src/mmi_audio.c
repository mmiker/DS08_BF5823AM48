#ifndef __MMI_AUD_C__
#define __MMI_AUD_C__

#include "mmi_audio.h"
#include "dqiot_drv_audio.h"
#include "mmi_com.h"

#ifdef __LOCK_AUDIO_SUPPORT__
#ifdef __AUD_PLAY_BY_ARR__

const unsigned char aud_play_arr[] =
	{
		AUD_BASE_ID_INPUT_68_PWD, AUD_BASE_ID_INPUT_END, 0,	   //AUD_ID_INPUT_68_PWD = 0,//请输入6-8位密码，按#键结束
		AUD_BASE_ID_PWD_68_LEN, AUD_BASE_ID_REINPUT, 0,		   //AUD_ID_PWD_68_LEN = 3,//密码应为6-8位，请重新输入
		AUD_BASE_ID_PWD_INPUT_AGAIN, AUD_BASE_ID_INPUT_END, 0, //AUD_ID_PWD_INPUT_AGAIN = 6,//请再次输入密码，按#键结束
		AUD_BASE_ID_CONTINUE, AUD_BASE_ID_INPUT_BACK, 0,	   //AUD_ID_CONTINUE = 9,//继续请按#，返回按*
		AUD_BASE_ID_FAIL, AUD_BASE_ID_CONTACT_ADMIN, 0,		   //AUD_ID_ADD_PWD_FAIL = 12,//添加失败，请联系管理员
		AUD_BASE_ID_INPUT_OLD_PWD, AUD_BASE_ID_INPUT_END, 0,   //AUD_ID_INPUT_OLD_PWD = 15,//请输入旧密码，按#键结束
		AUD_BASE_ID_PWD_NOT_EXIST, AUD_BASE_ID_REINPUT, 0,	   //AUD_ID_PWD_NOT_EXIST = 18,//密码不存在，请重新输入
		AUD_BASE_ID_INPUT_NEW_PWD, AUD_BASE_ID_INPUT_END, 0,   //AUD_ID_INPUT_NEW_PWD = 21,//请输入新密码，按#键结束
		AUD_BASE_ID_PWD_INPUT_AGAIN, AUD_BASE_ID_INPUT_END, 0, //AUD_ID_INPUT_NEW_PWD_AGAIN = 24,//请再输入新密码，按#键结束
															   //AUD_ID_CHG_FAIL = 12,//修改失败，请联系管理员
															   //AUD_ID_DEL_FAIL = 12,//删除失败，请联系管理员
		AUD_BASE_ID_INPUT_DEL_PWD, AUD_BASE_ID_INPUT_END, 0,   //AUD_ID_INPUT_DEL_NUM = 27,//请输入要删除的编号或密码，按#键结束
		AUD_BASE_ID_NUM_NOT_EXIST, AUD_BASE_ID_REINPUT, 0,	   //AUD_ID_NUM_NOT_EXIST = 30,//编号不存在，请重新输入
		AUD_BASE_ID_INPUT_CONFIRM, AUD_BASE_ID_INPUT_BACK, 0,  //AUD_ID_DEL_PWD_CONFIRM = 33,//号密码按#键确认删除，取消请按*键
															   //AUD_ID_DEL_CONFIRM = 9,//继续删除请按#，返回请按*
															   //AUD_ID_CLR_PWD_CONFIRM = 33,//按#键确认删除所有密码，取消请按*键
		AUD_BASE_ID_FAIL, AUD_BASE_ID_RETRY, 0,				   //AUD_ID_ADD_FAIL_RETRY = 36,//添加失败，请重试
															   //AUD_ID_CHG_FAIL_RETRY = 36,//修改失败，请重试
															   //AUD_ID_CHG_CONTINUE_CONFIRM = 9,//继续修改请按#，返回请按*
		//0x27
		AUD_BASE_ID_FP_NOT_EXIST, AUD_BASE_ID_REINPUT, 0,	   //AUD_ID_FP_NOT_EXIST = 39,//指纹不存在，请重新输入
															   //AUD_ID_DEL_FP_CONFIRM = 33,//号指纹按#确认删除，取消请按*
															   //AUD_ID_DEL_FAIL_RETRY = 36,//删除失败，请重试
															   //AUD_ID_CLR_FP_CONFIRM = 33,//按#确认删除所有指纹，取消请按*
		AUD_BASE_ID_RFCARD_NOT_EXIST, AUD_BASE_ID_REINPUT, 0,  //AUD_ID_RFCARD_NOT_EXIST = 42,//RF卡不存在，请重新输入
															   //AUD_ID_DEL_RFCARD_CONFIRM = 33,//号RF卡按#确认删除，取消请按*
															   //AUD_ID_CLR_RFCARD_CONFIRM = 33,//按#确认删除所有RF卡，取消请按*
		AUD_BASE_ID_INPUT_ADMIN_PWD, AUD_BASE_ID_INPUT_END, 0, //AUD_ID_INPUT_ADMIN_PWD = 45,//请输入管理员密码，按#键结束
															   //AUD_ID_INPUT_NEW_ADMIN_PWD = 0,//请输入新管理员密码，按#键结束
		//
		//AUD_ID_INPUT_NEW_ADMIN_PWD_AGAIN = 6,//请再次输入新管理员密码，按#键结束
		AUD_BASE_ID_PWD_EXIST, AUD_BASE_ID_REINPUT, 0,			   //AUD_ID_PWD_EXIST = 48,//密码已存在，请重新输入
		AUD_BASE_ID_ADD_ADMIN_PWD_FIRST, AUD_BASE_ID_INPUT_END, 0, //AUD_ID_ADD_ADMIN_PWD_FIRST = 51,//为了您的使用安全，请先添加管理员密码，按#键结束
																   //AUD_ID_INPUT_ADMIN_PWD_INIT_AGAIN = 6,//请再次输入管理员密码，按#键结束
		AUD_BASE_ID_PWD_WRONG, AUD_BASE_ID_RETRY, 0,			   //AUD_ID_PWD_WRONG_TRY = 54,//密码错误,请重试
		AUD_BASE_ID_FP_WRONG, AUD_BASE_ID_RETRY, 0,				   //AUD_ID_FP_WRONG_TRY = 57,//指纹错误，请重试
		AUD_BASE_ID_RFCARD_WRONG, AUD_BASE_ID_RETRY, 0,			   //AUD_ID_RFCARD_WRONG_TRY = 60,//RF卡错误，请重试
		//
		AUD_BASE_ID_SYS_NUM_1, AUD_BASE_ID_SYS_CHG_ADMIN_PWD,
		AUD_BASE_ID_SYS_NUM_2, AUD_BASE_ID_SYS_CHG_ADMIN_FP, AUD_BASE_ID_INPUT_BACK, 0, //AUD_ID_SYS_ADMIN = 63,//管理员
		AUD_BASE_ID_SYS_NUM_1, AUD_BASE_ID_SYS_PRO_AUDIO,
		AUD_BASE_ID_SYS_NUM_2, AUD_BASE_ID_SYS_OPEN_MODE, AUD_BASE_ID_INPUT_BACK, 0, //AUD_ID_SYS_SETTING = 69,//设置
		AUD_BASE_ID_SYS_NUM_1, AUD_BASE_ID_SYS_NO1_ADMIN_FP,
		AUD_BASE_ID_SYS_NUM_2, AUD_BASE_ID_SYS_NO2_ADMIN_FP, AUD_BASE_ID_INPUT_BACK, 0, //AUD_ID_SYS_CHG_ADMIN_FP = 75,//修改管理员指纹
		AUD_BASE_ID_SYS_NUM_1, AUD_BASE_ID_SYS_OPEN_PRO_AUDIO,
		AUD_BASE_ID_SYS_NUM_2, AUD_BASE_ID_SYS_CLOSE_PRO_AUDIO, AUD_BASE_ID_INPUT_BACK, 0, //AUD_ID_SYS_PRO_AUDIO = 81,//提示音
		AUD_BASE_ID_SYS_NUM_1, AUD_BASE_ID_SYS_SIN_OPEN_MODE,
		AUD_BASE_ID_SYS_NUM_2, AUD_BASE_ID_SYS_DBL_OPEN_MODE, AUD_BASE_ID_INPUT_BACK, 0, //AUD_ID_SYS_OPEN_MODE = 87,//开门方式

		AUD_BASE_ID_SYS_NUM_1, AUD_BASE_ID_SYS_ADMIN,
		AUD_BASE_ID_SYS_NUM_2, AUD_BASE_ID_SYS_SETTING,
		AUD_BASE_ID_SYS_NUM_3, AUD_BASE_ID_SYS_RESTORE, AUD_BASE_ID_INPUT_BACK, 0, //AUD_ID_SYSTEM2 = 93,//系统2

		AUD_BASE_ID_SYS_NUM_1, AUD_BASE_ID_SYS_ADD_PWD,
		AUD_BASE_ID_SYS_NUM_2, AUD_BASE_ID_SYS_DEL_PWD,
		AUD_BASE_ID_SYS_NUM_3, AUD_BASE_ID_SYS_CLR_PWD, AUD_BASE_ID_INPUT_BACK, 0, //AUD_ID_SYS_PASSWORD = 101,//密码
		AUD_BASE_ID_SYS_NUM_1, AUD_BASE_ID_SYS_ADD_FP,
		AUD_BASE_ID_SYS_NUM_2, AUD_BASE_ID_SYS_DEL_FP,
		AUD_BASE_ID_SYS_NUM_3, AUD_BASE_ID_SYS_CLR_FP, AUD_BASE_ID_INPUT_BACK, 0, //AUD_ID_SYS_FP = 109,//指纹
		AUD_BASE_ID_SYS_NUM_1, AUD_BASE_ID_SYS_ADD_RFCARD,
		AUD_BASE_ID_SYS_NUM_2, AUD_BASE_ID_SYS_DEL_RFCARD,
		AUD_BASE_ID_SYS_NUM_3, AUD_BASE_ID_SYS_CLR_RFCARD, AUD_BASE_ID_INPUT_BACK, 0, //AUD_ID_SYS_RFCARD = 117,//RF卡

		AUD_BASE_ID_NOT_SAME, AUD_BASE_ID_REINPUT, 0, //AUD_ID_PWD_NOT_SAME_RETRY	 = 125//两次输入的密码不一致,请重新输入

		AUD_BASE_ID_SYS_NUM_1, AUD_BASE_ID_SYS_CHG_ADMIN_PWD,
		AUD_BASE_ID_INPUT_BACK, 0, //AUD_ID_SYS_ADMIN2 = 128,//管理员
#if 1
#ifdef __LOCK_RFID_CARD_SUPPORT__
#if defined(__LOCK_FP_SUPPORT__) || defined(__LOCK_FP_SUPPORT2__) || defined(__LOCK_FP_SUPPORT1_2__)
		AUD_BASE_ID_SYS_NUM_1, AUD_BASE_ID_SYS_PASSWORD,
		AUD_BASE_ID_SYS_NUM_2, AUD_BASE_ID_SYS_FP,
		AUD_BASE_ID_SYS_NUM_3, AUD_BASE_ID_SYS_RFCARD,
		AUD_BASE_ID_SYS_NUM_4, AUD_BASE_ID_SYS_ADMIN,
		AUD_BASE_ID_SYS_NUM_5, AUD_BASE_ID_SYS_SETTING,
		AUD_BASE_ID_SYS_NUM_6, AUD_BASE_ID_SYS_RESTORE, AUD_BASE_ID_INPUT_BACK, 0, //AUD_ID_SYSTEM = 132,//系统
#else
		AUD_BASE_ID_SYS_NUM_1, AUD_BASE_ID_SYS_PASSWORD,
		AUD_BASE_ID_SYS_NUM_2, AUD_BASE_ID_SYS_RFCARD,
		AUD_BASE_ID_SYS_NUM_3, AUD_BASE_ID_SYS_ADMIN,
		AUD_BASE_ID_SYS_NUM_4, AUD_BASE_ID_SYS_SETTING,
		AUD_BASE_ID_SYS_NUM_5, AUD_BASE_ID_SYS_RESTORE, AUD_BASE_ID_INPUT_BACK, 0, //AUD_ID_SYSTEM = 132,//系统
#endif
#else
		AUD_BASE_ID_SYS_NUM_1, AUD_BASE_ID_SYS_PASSWORD,
		AUD_BASE_ID_SYS_NUM_2, AUD_BASE_ID_SYS_FP,
		AUD_BASE_ID_SYS_NUM_3, AUD_BASE_ID_SYS_ADMIN,
		AUD_BASE_ID_SYS_NUM_4, AUD_BASE_ID_SYS_SETTING,
		AUD_BASE_ID_SYS_NUM_5, AUD_BASE_ID_SYS_RESTORE, AUD_BASE_ID_INPUT_BACK, 0, //AUD_ID_SYSTEM = 132,//系统
#endif
#endif

		//AUD_BASE_ID_SYS_DBL_OPEN_MODE,AUD_BASE_ID_PRESS_FP,0,//AUD_ID_DBL_OPEN_MODE_FP = 145
		//AUD_BASE_ID_SYS_DBL_OPEN_MODE,AUD_BASE_ID_INPUT_68_PWD,0,//AUD_ID_DBL_OPEN_MODE_PASSWORD = 148

		//AUD_ID_ADD_PWD_FULL = 12,//密码已满，请联系管理员
		//AUD_ID_FP_ADD_FULL = 12,//指纹已满，请联系管理员
		//AUD_ID_RFCARD_FULL = 12,//RF卡已满，请联系管理员
};

#endif

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_aud_init(void)
{
	dqiot_drv_audio_init();
}

/*
parameter: 
	none
return :
	none
*/
AUD_PLAY_ID mmi_dq_aud_get_audio_id(unsigned char text_id)
{
	unsigned char i = 0;

	for (i = 0; msg_aud_list[i].msg_id < STR_ID_MAX_COUNT; i++)
	{
		if (msg_aud_list[i].msg_id == text_id)
		{
			break;
		}
	}

	return msg_aud_list[i].aud_id;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_aud_play_with_id(unsigned char aud_id)
{
#ifdef __AUD_PLAY_BY_ARR__
	if (aud_id < AUD_BASE_ID_MAX)
		dqiot_drv_audio_play(aud_id);
#if 0
	else if(aud_id == AUD_ID_SYSTEM)
	{
		unsigned char num = 1;
		dqiot_drv_audio_play(AUD_BASE_ID_SYS_NUM_0 + num);
		dqiot_drv_audio_play(AUD_BASE_ID_SYS_PASSWORD);
		num++;
#if defined(__LOCK_FP_SUPPORT__) || defined(__LOCK_FP_SUPPORT2__)
		dqiot_drv_audio_play(AUD_BASE_ID_SYS_NUM_0 + num);
		dqiot_drv_audio_play(AUD_BASE_ID_SYS_FP);
		num++;
#elif defined(__LOCK_FP_SUPPORT1_2__)
		if(mmi_dq_fp_get_type() != FP_NONE)
		{
			dqiot_drv_audio_play(AUD_BASE_ID_SYS_NUM_0 + num);
			dqiot_drv_audio_play(AUD_BASE_ID_SYS_FP);
			num++;
		}
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__	
		if(mmi_dq_rfid_get_init_state() == 0)
		{
			dqiot_drv_audio_play(AUD_BASE_ID_SYS_NUM_0 + num);
			dqiot_drv_audio_play(AUD_BASE_ID_SYS_RFCARD);
			num++;
		}
#endif
		dqiot_drv_audio_play(AUD_BASE_ID_SYS_NUM_0 + num);
		dqiot_drv_audio_play(AUD_BASE_ID_SYS_ADMIN);
		num++;
		dqiot_drv_audio_play(AUD_BASE_ID_SYS_NUM_0 + num);
		dqiot_drv_audio_play(AUD_BASE_ID_SYS_SETTING);
		num++;
		dqiot_drv_audio_play(AUD_BASE_ID_SYS_NUM_0 + num);
		dqiot_drv_audio_play(AUD_BASE_ID_SYS_RESTORE);
		dqiot_drv_audio_play(AUD_BASE_ID_INPUT_BACK);
	}
#endif
	else
	{
		unsigned char a = aud_id - AUD_BASE_ID_MAX;
		while (aud_play_arr[a] != 0)
		{
			dqiot_drv_audio_play(aud_play_arr[a]);
			a++;
		}
	}
#else
	dqiot_drv_audio_play(aud_id);
#endif

	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_aud_play_key_num(unsigned char key_val)
{
	mmi_dq_aud_stop();
	//if(mmi_dq_sys_get_pro_sound_state())
	//	mmi_dq_aud_play_with_id(AUD_ID_PRO_AUDIO,NULL);
	mmi_dq_aud_play_with_id(AUD_ID_SYS_NUM_0 + key_val);
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_aud_play_key_tone(void)
{
	mmi_dq_aud_stop();
	//if(mmi_dq_sys_get_pro_sound_state())
	mmi_dq_aud_play_with_id(AUD_ID_PRO_AUDIO);
}
/*
parameter: 
	none
return :
	none
*/
void mmi_dq_aud_stop(void)
{
	dqiot_drv_audio_stop();
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_aud_get_state(void)
{
	return dqiot_drv_audio_get_state();
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_aud_get_end_flag(void)
{
	return dqiot_drv_audio_get_end_flag();
}
#endif
#endif //__MMI_AUD_C__
