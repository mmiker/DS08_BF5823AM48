#ifndef __MMI_VIRTUAL_PWD_C__
#define __MMI_VIRTUAL_PWD_C__
#include "mmi_feature.h"
#ifdef __LOCK_VIRTUAL_PASSWORD__1
#include "mmi_virtualpwd.h"
#include "mcu02_sfr.h"
#include "mmi_fs.h"

otp_base_app_pwd_info g_dq_app_pwd_info[DQ_OTP_APP_PWD_NUM]; //100


dq_otp_init_t g_dq_otp_init;

unsigned char dq_otp_check_password_for_open(unsigned char *password, unsigned char len)
{
	unsigned char i = 0;
	unsigned char k = 0;
	unsigned char pwd_len = 0;
	unsigned char ret = 0;
	unsigned char ret_t = 0;
#ifdef __LOCK_USE_MALLOC__
	g_dq_app_pwd_info = (otp_base_app_pwd_info *)mmi_dq_fs_get_storage(DQ_FS_MEM_APP_PWD, &ret_t);
#endif

	for (i = 0; i < DQ_OTP_APP_PWD_NUM; i++)
	{
		if (g_dq_app_pwd_info[i].pwd_type != 0xFF)
		{
			for (k = 0; k < 5; k++)
			{
				if (password[k] != g_dq_app_pwd_info[i].replace_pwd[k])
					break;
			}
			if (k == 5)
			{
				break;
			}
#if 0
			for(k=0;k<5;k++)
			{
				if(password[k] != g_dq_app_pwd_info[i].app_pwd[k])
					break;
			}
			if(k == 5)
			{
				break;
			}
#endif
		}
	}
	if (i < DQ_OTP_APP_PWD_NUM)
	{
		extern uint8_t mmi_dq_rtc_check_time(void);
		if (g_dq_app_pwd_info[i].pwd_flag == 2)
		{
#ifdef __LOCK_USE_MALLOC__
			mmi_dq_fs_free_storage(DQ_FS_MEM_APP_PWD, (void **)&g_dq_app_pwd_info);
#endif
			g_dq_otp_init.input_pwd_cb(4);
			return 4;
		}
		if (g_dq_app_pwd_info[i].pwd_type == OTP_PWD_TYPE_SIN && g_dq_app_pwd_info[i].pwd_flag == 1)
		{
#ifdef __LOCK_USE_MALLOC__
			mmi_dq_fs_free_storage(DQ_FS_MEM_APP_PWD, (void **)&g_dq_app_pwd_info);
#endif
			g_dq_otp_init.input_pwd_cb(4);
			return 4;
		}
		else if (g_dq_app_pwd_info[i].pwd_type == OTP_PWD_TYPE_PER && g_dq_app_pwd_info[i].pwd_flag == 1)
		{
#ifdef __LOCK_USE_MALLOC__
			mmi_dq_fs_free_storage(DQ_FS_MEM_APP_PWD, (void **)&g_dq_app_pwd_info);
#endif
			ret = 1;
		}
		// 		else if (dq_otp_get_lock_sys_time_state() == 0 && mmi_dq_rtc_check_time() == 1)
		// 		{
		// #ifdef __LOCK_USE_MALLOC__
		// 			mmi_dq_fs_free_storage(DQ_FS_MEM_APP_PWD, (void **)&g_dq_app_pwd_info);
		// #endif
		// 			g_dq_otp_init.input_pwd_cb(6);
		// 			return 6;
		// 		}
		else
		{
			uint8_t pwd[5] = {0xFF};
			memcpy(pwd, g_dq_app_pwd_info[i].app_pwd, 5);
#ifdef __LOCK_USE_MALLOC__
			mmi_dq_fs_free_storage(DQ_FS_MEM_APP_PWD, (void **)&g_dq_app_pwd_info);
#endif
			pwd_len = dq_otp_get_pwd_len(pwd, 5);
			ret = dq_otp_temp_pwd_check(pwd, pwd_len);
			if (ret == 0)
				ret = 4;
		}

		if (ret == 1)
		{
#ifdef __LOCK_USE_MALLOC__
			g_dq_app_pwd_info = (otp_base_app_pwd_info *)mmi_dq_fs_get_storage(DQ_FS_MEM_APP_PWD, &ret_t);
#endif
			if (g_dq_app_pwd_info[i].pwd_flag == 0)
			{
				g_dq_app_pwd_info[i].pwd_flag = 1;
				dq_app_pwd_flag = 1;
				g_dq_otp_init.fds_write(DQ_OTP_FILE_ID_PWD_APP, (unsigned char *)g_dq_app_pwd_info, sizeof(otp_base_app_pwd_info) * DQ_OTP_APP_PWD_NUM, &ret, dq_otp_app_pwd_save_cb);
			}
#ifdef __LOCK_USE_MALLOC__
			mmi_dq_fs_free_storage(DQ_FS_MEM_APP_PWD, (void **)&g_dq_app_pwd_info);
#endif
		}
	}
	else
	{
		for (i = 0; i < DQ_OTP_APP_PWD_NUM; i++)
		{
			if (g_dq_app_pwd_info[i].pwd_type != 0xFF)
			{
				for (k = 0; k < 5; k++)
				{
					if (password[k] != g_dq_app_pwd_info[i].app_pwd[k])
						break;
				}
				if (k == 5)
				{
					break;
				}
			}
		}
#ifdef __LOCK_USE_MALLOC__
		mmi_dq_fs_free_storage(DQ_FS_MEM_APP_PWD, (void **)&g_dq_app_pwd_info);
#endif
		if (i < DQ_OTP_APP_PWD_NUM)
			ret = 4;
		else
			ret = dq_otp_temp_pwd_check(password, len);
	}

	if (ret == 1)
		dq_otp_add_temp_open_log(0, DQ_OPEN_LOG_USER_PASSWORD, password, 5);
	else if (ret == 2)
	{
		dq_otp_add_alarm_log(DQ_ALART_LOG_EMPTY_PASSWORD);
	}

	if (dq_app_pwd_flag == 0)
		g_dq_otp_init.input_pwd_cb(ret);
	else
		dq_app_pwd_for_open_ret = ret;

	return ret;
}


#endif
#endif //__MMI_VIRTUAL_PWD_C__