#ifndef __DQ_SDK_CB_C__
#define __DQ_SDK_CB_C__
#include "mmi_feature.h"
#ifdef __LOCK_VIRTUAL_PASSWORD__
#include "dq_sdk_cb.h"
#ifndef __WIN32_ENV_SUPPORT__
// #include "ble_nus.h"
#include "mmi_fs.h"
// #include "nrf_log.h"
#include "mmi_sys.h"
#include "mmi_ms.h"
#include "mmi_rtc.h"
//#include "mmi_cal.h"
// #include "mmi_fp.h"
#include "mmi_feature.h"
// #include "mmi_aud.h"
#include "mmi_rfid.h"
#endif
static uint8_t *p_data_buf;
static dq_otp_write_data_cb g_write_data_cb;
static uint16_t p_data_len;
static uint8_t g_app_write_flag = 0;
#ifndef __WIN32_ENV_SUPPORT__
static mid_fds_file_id g_file_id;
#else
static unsigned short g_file_id;
#endif


extern void FP_PowerOn(void);
extern void power_init(void);

/*
parameter: 
	file_id		the id for the file to write
	p_data:		the data to write
	data_len:	the data len to write
	result:		return the operte result,0 for sucess, 1 for fail
return :
	none
*/
void dq_otp_fds_write_cb(uint16_t file_id,uint8_t * p_data,uint16_t data_len,uint8_t *result,dq_otp_write_data_cb cb)
{
// #ifndef __WIN32_ENV_SUPPORT__
// 	BASE_RET retval = BASE_SUCESS;

// 	if(file_id == DQ_OTP_FILE_ID_SET)
// 	{
// 		retval = mmi_dq_mid_fds_write((mid_fds_file_id)MID_FDS_APP_FILE_APP_SET,(unsigned char *)p_data,data_len,0,(fs_write_data_callback)cb);
// 	}
// 	else if(file_id == DQ_OTP_FILE_ID_PWD_APP)
// 	{
// 		g_file_id = MID_FDS_APP_FILE_APP_PWD_1;
// 		p_data_buf = p_data;
// 		g_write_data_cb = cb;
// 		p_data_len = data_len;
// 		mmi_dq_ms_set_machine_status(BASE_STATUS_M_APP_PWD_1);
// 	}
// 	else if(file_id == DQ_OTP_FILE_ID_LOG)
// 	{
// 		g_file_id = MID_FDS_APP_FILE_LOG_1;
// 		p_data_buf = p_data;
// 		g_write_data_cb = cb;
// 		p_data_len = data_len;
// 		mmi_dq_ms_set_machine_status(BASE_STATUS_M_APP_LOG_1);
// 	}
// 	else if(file_id == DQ_OTP_FILE_ID_FP)
// 	{
// 		retval = mmi_dq_mid_fds_write((mid_fds_file_id)MID_FDS_APP_FILE_APP_FP,(unsigned char *)p_data,data_len,0,(fs_write_data_callback)cb);
// 	}
// 	else if(file_id == DQ_OTP_FILE_ID_RFID)
// 	{
// 		retval = mmi_dq_mid_fds_write((mid_fds_file_id)MID_FDS_APP_FILE_APP_RF,(unsigned char *)p_data,data_len,0,(fs_write_data_callback)cb);
// 	}
	
// 	if(retval == BASE_SUCESS)
// 	{
		
// 	}
// #endif
// 	return;
}
/*
parameter: 
	none
return :
	none
*/

//#include "Nrf_delay.h"
void dq_otp_fds_write_pwd_ekey_cb(void)
{
// #ifndef __WIN32_ENV_SUPPORT__
// 	if(g_file_id == MID_FDS_APP_FILE_APP_PWD_1)
// 	{
// 		g_file_id = MID_FDS_APP_FILE_APP_PWD_2;
// 		mmi_dq_ms_set_machine_status(BASE_STATUS_M_APP_PWD_2);
// 		return;
// 	}
// 	else if(g_file_id == MID_FDS_APP_FILE_APP_PWD_2)
// 	{
// 		g_file_id = MID_FDS_APP_FILE_APP_PWD_3;
// 		mmi_dq_ms_set_machine_status(BASE_STATUS_M_APP_PWD_3);
// 		return;
// 	}
// 	else if(g_file_id == MID_FDS_APP_FILE_APP_PWD_3)
// 	{
// 		g_file_id = MID_FDS_APP_FILE_APP_PWD_4;
// 		mmi_dq_ms_set_machine_status(BASE_STATUS_M_APP_PWD_4);
// 		return;
// 	}
// 	else
// 		return;
// #endif
}

/*
parameter: 
	none
return :
	none
*/
void dq_otp_fds_write_pwd_ekey(void)
{
// #ifndef __WIN32_ENV_SUPPORT__
// 	BASE_RET retval = BASE_SUCESS;
// 	fs_write_data_callback cb;
// 	if(g_file_id == MID_FDS_APP_FILE_APP_PWD_1)
// 	{
// 		cb =  dq_otp_fds_write_pwd_ekey_cb;
// 	}
// 	else if(g_file_id == MID_FDS_APP_FILE_APP_PWD_2)
// 	{
// 		p_data_buf += p_data_len/4;
// 		cb =  dq_otp_fds_write_pwd_ekey_cb;
// 	}
// 	else if(g_file_id == MID_FDS_APP_FILE_APP_PWD_3)
// 	{
// 		p_data_buf += p_data_len/4;
// 		cb =  dq_otp_fds_write_pwd_ekey_cb;
// 	}
// 	else if(g_file_id == MID_FDS_APP_FILE_APP_PWD_4)
// 	{
// 		p_data_buf += p_data_len/4;
// 		cb =  g_write_data_cb;
// 	}
// 	retval = mmi_dq_mid_fds_write((mid_fds_file_id)g_file_id,(unsigned char *)p_data_buf,p_data_len/4,0,cb);
// 	if(retval == BASE_SUCESS)
// 	{
// 	}
// #endif
// 	return;
}
/*
parameter: 
	none
return :
	none
*/
void dq_otp_fds_write_log_cb(void)
{
// #ifndef __WIN32_ENV_SUPPORT__
// 	if(g_file_id == MID_FDS_APP_FILE_LOG_1)
// 	{
// 		g_file_id = MID_FDS_APP_FILE_LOG_2;
// 		mmi_dq_ms_set_machine_status(BASE_STATUS_M_APP_LOG_2);
// 		return;
// 	}
// 	else if(g_file_id == MID_FDS_APP_FILE_LOG_2)
// 	{
// 		g_file_id = MID_FDS_APP_FILE_LOG_3;
// 		mmi_dq_ms_set_machine_status(BASE_STATUS_M_APP_LOG_3);
// 		return;
// 	}
// 	else if(g_file_id == MID_FDS_APP_FILE_LOG_3)
// 	{
// 		g_file_id = MID_FDS_APP_FILE_LOG_4;
// 		mmi_dq_ms_set_machine_status(BASE_STATUS_M_APP_LOG_4);
// 		return;
// 	}
// 	else
// 		return;
// #endif
}

/*
parameter: 
	none
return :
	none
*/
void dq_otp_fds_write_log(void)
{
// #ifndef __WIN32_ENV_SUPPORT__
// 	BASE_RET retval = BASE_SUCESS;
// 	fs_write_data_callback cb;
// 	if(g_file_id == MID_FDS_APP_FILE_LOG_1)
// 	{
// 		cb =  dq_otp_fds_write_log_cb;
// 	}
// 	else if(g_file_id == MID_FDS_APP_FILE_LOG_2)
// 	{
// 		p_data_buf += p_data_len/4;
// 		cb =  dq_otp_fds_write_log_cb;
// 	}
// 	else if(g_file_id == MID_FDS_APP_FILE_LOG_3)
// 	{
// 		p_data_buf += p_data_len/4;
// 		cb =  dq_otp_fds_write_log_cb;
// 	}
// 	else if(g_file_id == MID_FDS_APP_FILE_LOG_4)
// 	{
// 		p_data_buf += p_data_len/4;
// 		cb =  g_write_data_cb;
// 	}
// 	retval = mmi_dq_mid_fds_write((mid_fds_file_id)g_file_id,(unsigned char *)p_data_buf,p_data_len/4,0,cb);
// 	if(retval == BASE_SUCESS)
// 	{
// 	}
// #endif
// 	return;
}


/*
parameter: 
	file_id:	the id for the file to read
	p_data:		the buffer for file read
	data_len:	the data len to write
	result:		return the operte result,0 for sucess, 1 for fail
return :
	none
*/
void dq_otp_fds_read_cb(uint16_t file_id,uint8_t * p_data,uint16_t data_len,uint8_t *result)
{
// #ifndef __WIN32_ENV_SUPPORT__
// 	BASE_RET retval = BASE_SUCESS;
// 	if(file_id == DQ_OTP_FILE_ID_PWD_APP)
// 	{
// 		retval = mmi_dq_mid_fds_read(MID_FDS_APP_FILE_APP_PWD_1,(unsigned char *)p_data,data_len/4);
// 		retval = mmi_dq_mid_fds_read(MID_FDS_APP_FILE_APP_PWD_2,(unsigned char *)p_data+data_len/4,data_len/4);
// 		retval = mmi_dq_mid_fds_read(MID_FDS_APP_FILE_APP_PWD_3,(unsigned char *)p_data+data_len/2,data_len/4);
// 		retval = mmi_dq_mid_fds_read(MID_FDS_APP_FILE_APP_PWD_4,(unsigned char *)p_data+(data_len*3)/4,data_len/4);
// 	}
// 	else if(file_id == DQ_OTP_FILE_ID_FP)
// 	{
// 		retval = mmi_dq_mid_fds_read(MID_FDS_APP_FILE_APP_FP,(unsigned char *)p_data,data_len);
// 	}
// 	else if(file_id == DQ_OTP_FILE_ID_SET)
// 	{
// 		retval = mmi_dq_mid_fds_read(MID_FDS_APP_FILE_APP_SET,(unsigned char *)p_data,data_len);
// 	}
// 	else if(file_id == DQ_OTP_FILE_ID_RFID)
// 	{
// 		retval = mmi_dq_mid_fds_read(MID_FDS_APP_FILE_APP_RF,(unsigned char *)p_data,data_len);
// 	}
// 	else if(file_id == DQ_OTP_FILE_ID_LOG)
// 	{
// 		retval = mmi_dq_mid_fds_read(MID_FDS_APP_FILE_LOG_1,(unsigned char *)p_data,data_len/4);
// 		retval = mmi_dq_mid_fds_read(MID_FDS_APP_FILE_LOG_2,(unsigned char *)p_data+data_len/4,data_len/4);
// 		retval = mmi_dq_mid_fds_read(MID_FDS_APP_FILE_LOG_3,(unsigned char *)p_data+data_len/2,data_len/4);
// 		retval = mmi_dq_mid_fds_read(MID_FDS_APP_FILE_LOG_4,(unsigned char *)p_data+(data_len*3)/4,data_len/4);
// 	}
// 	if(retval == BASE_SUCESS)
// 	{
		
// 	}
// #else
// #endif
// 	return;
}

/*
Function: this function for data to be sent by bt
parameter: 
	p_data:		the buffer for data to be sent
	data_len:	the length for the data to be sent
	result:		return the operte result,0 for sucess, 1 for fail,255 for not support
return :
	none
*/
#ifndef __WIN32_ENV_SUPPORT__
// extern void nus_data_get_para(ble_nus_t *pus);
#endif
void dq_otp_data_send_by_bt_cb(uint8_t * p_data,uint16_t data_len,uint32_t *result)
{
// #ifndef __WIN32_ENV_SUPPORT__
// 	ble_nus_t ble_nus;
// 	uint32_t ret_val = 0;
// 	//BASE_STATUS_MACHINE	cur_ms;

// 	memset(&ble_nus,0x00,sizeof(ble_nus_t));
// 	nus_data_get_para(&ble_nus);	
	
// 	ret_val = ble_nus_string_send(&ble_nus,p_data,data_len);
// 	*result = ret_val;
// 	#if 0
// 	cur_ms = mmi_dq_ms_get_machine_status();
// 	if(cur_ms != BASE_STATUS_M_IDLE)
// 		mmi_dq_ms_set_machine_status(BASE_STATUS_M_IDLE);
// 	#endif
// #endif
}
/*
Function: this function for data to be sent by nb
parameter: 
	p_data:		the buffer for data to be sent
	data_len:	the length for the data to be sent
	result:		return the operte result,0 for sucess, 1 for fail,255 for not support
return :
	none
*/
void dq_otp_data_send_by_nb_cb(uint8_t * p_data,uint16_t data_len,uint8_t *result)
{
	
}
/*
Function:		set the lock password by app
parameter: 
	p_data:		the password for lock to set
	data_len:	the password length
	result:		the result for save lock password.
				0 for sucess, 1 for fail,255 for not support
return :
	none
*/
void dq_otp_app_set_operate_lock_flag(uint8_t flag)
{
	g_app_write_flag = flag;
	return;
}

/*
Function:		set the lock password by app
parameter: 
	p_data:		the password for lock to set
	data_len:	the password length
	result:		the result for save lock password.
				0 for sucess, 1 for fail,255 for not support
return :
	none
*/
uint8_t dq_otp_app_get_operate_lock_flag(void)
{
	return g_app_write_flag;
}


/*
Function:		set the lock password by app
parameter: 
	p_data:		the password for lock to set
	data_len:	the password length
	result:		the result for save lock password.
				0 for sucess, 1 for fail,255 for not support
return :
	none
*/
void dq_otp_set_lock_pwd_cb(uint8_t * p_data,uint16_t data_len,uint8_t *result)
{
	
}

/*
Function:		set the lock rfid by app
parameter: 
	data_index:	set the fp in lock return the index
	result:		the result for save lock fp
				0 for sucess, 1 for fail,255 for not support
return :
	none
*/
#ifdef __LOCK_RFID_CARD_SUPPORT__

#if defined (__LOCK_FP_SUPPORT2__)||defined (__LOCK_FP_SUPPORT1_2__)
void mmi_dq_otp_lock_rfid_uart_callback(uint8_t type,uint8_t *reply,uint16_t reply_len)
{
	if(type == 0x80)
	{
		if(reply[0] == 0)
		{
			mmi_dq_fp_light(FP_NONE_COLOR);
			mmi_dq_fp_set_fp_uart_handle_cb(NULL);
		}
	
	}	
}

#endif

void dq_otp_set_lock_rfid_cb(uint16_t delay_time,uint8_t *result)
{
	BASE_STATUS_MACHINE state;
	if(mmi_dq_rfid_get_init_state() != 0)
	{
		dq_otp_app_add_lock_rfid_result(5,0);
		return;
	}
	
	dq_otp_app_set_operate_lock_flag(1);
	mmi_dq_sys_wake_up();
	state = mmi_dq_ms_get_machine_status();
		if(state == BASE_STATUS_M_IDLE||state == BASE_STATUS_M_IDLE_INPUT_PWD)
		{
	
#if defined (__LOCK_FP_SUPPORT__)
	mmi_dq_fp_light(FP_NONE_COLOR);
#elif defined (__LOCK_FP_SUPPORT2__)
	if(mmi_dq_fp_get_fp_mode() != BTL_M_FREE)
		mmi_dq_fp_mode_free(mmi_dq_otp_lock_rfid_uart_callback);
	else
	{
		mmi_dq_fp_light(FP_NONE_COLOR);
		mmi_dq_fp_set_fp_uart_handle_cb(NULL);
	}

#elif defined (__LOCK_FP_SUPPORT1_2__)
	if(mmi_dq_fp_get_type() == FP_BTL)
	{
		if(mmi_dq_fp_get_fp_mode() != BTL_M_FREE)
			mmi_dq_fp_mode_free(mmi_dq_otp_lock_rfid_uart_callback);
		else
		{
			mmi_dq_fp_light(FP_NONE_COLOR);
			mmi_dq_fp_set_fp_uart_handle_cb(NULL);
		}
	}
	else if(mmi_dq_fp_get_type() == FP_LT5X)
	{
		mmi_dq_fp_light(FP_NONE_COLOR);
	}


#endif
	#ifndef __WIN32_ENV_SUPPORT__
//	mmi_dq_ms_set_machine_status(BASE_STATUS_M_ADD_RFID);
	#endif
		}
		else
			dq_otp_app_add_lock_rfid_result(4,0);
	return;
}
#else
void dq_otp_set_lock_rfid_cb(uint16_t delay_time,uint8_t *result)
{
	return;
}
#endif

/*
Function:		set the lock fp by app
parameter: 
	data_index:	set the fp in lock return the index
	result:		the result for save lock fp
				0 for sucess, 1 for fail,255 for not support
return :
	none
*/
#if defined (__LOCK_FP_SUPPORT__) || defined (__LOCK_FP_SUPPORT2__)||defined(__LOCK_FP_SUPPORT1_2__)

void dq_otp_set_lock_fp_cb(uint16_t delay_time,uint8_t *result)
{
#ifdef __LOCK_FP_SUPPORT1_2__
	if(mmi_dq_fp_get_type() == FP_NONE)
	{
		dq_otp_app_add_lock_fp_result(5,0);
		return;
	}
#endif
	dq_otp_app_set_operate_lock_flag(1);
	mmi_dq_sys_wake_up();
	{
			
		BASE_STATUS_MACHINE state = mmi_dq_ms_get_machine_status();
		if(state == BASE_STATUS_M_IDLE||state == BASE_STATUS_M_IDLE_INPUT_PWD)
		{
			mmi_dq_fp_light(FP_NONE_COLOR);
#ifndef __WIN32_ENV_SUPPORT__
	mmi_dq_ms_set_machine_status(BASE_STATUS_M_ADD_FP);
#endif
		}
		else
			dq_otp_app_add_lock_fp_result(4,0);
	}
	return;
}
#else
void dq_otp_set_lock_fp_cb(uint16_t delay_time,uint8_t *result)
{
	return;
}


#endif

#if defined (__LOCK_FP_SUPPORT__) || defined (__LOCK_FP_SUPPORT2__)||defined(__LOCK_FP_SUPPORT1_2__)

void dq_otp_stop_set_lock_fp_cb(uint8_t *result)
{
#ifndef __WIN32_ENV_SUPPORT__
	BASE_STATUS_MACHINE state = mmi_dq_ms_get_machine_status();

	if(state == BASE_STATUS_M_ADD_FP||state == BASE_STATUS_M_ADD_FP_AGAIN||state == BASE_STATUS_M_ADD_FP_PRESS_1||state == BASE_STATUS_M_ADD_FP_PRESS_2 ||state ==BASE_STATUS_M_ADD_FP_END)
	{
		//mmi_dq_ms_set_machine_status(BASE_STATUS_M_ADD_FP_STAR);
		mmi_dq_entry_sleep_normal_time();
		dq_otp_app_add_lock_fp_result(3,0);
		mmi_dq_enter_sleep_timer_stop();
		mmi_dq_sys_timeout_sleep_aud_pro();
	}
#endif
	return;
}
#else
void dq_otp_stop_set_lock_fp_cb(uint8_t *result)
{
	return;
}

#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
void dq_otp_stop_set_lock_rfid_cb(uint8_t *result)
{
#ifndef __WIN32_ENV_SUPPORT__
	BASE_STATUS_MACHINE state = mmi_dq_ms_get_machine_status();
	
	if(state == BASE_STATUS_M_ADD_RFID||state == BASE_STATUS_M_ADD_RFID_AGAIN||state ==BASE_STATUS_M_ADD_RFID_PRESS_1||state ==BASE_STATUS_M_ADD_RFID_PRESS_2)
	{
		//mmi_dq_ms_set_machine_status(BASE_STATUS_M_RFID_STAR);
		mmi_dq_entry_sleep_normal_time();
		dq_otp_app_add_lock_rfid_result(3,0);
		mmi_dq_enter_sleep_timer_stop();
		mmi_dq_sys_timeout_sleep_aud_pro();
	}
#endif
	return;
}
#else
void dq_otp_stop_set_lock_rfid_cb(uint8_t *result)
{
	return;
}

#endif

/*
Function:	clear the lock password by app
parameter: 
	result:		the result for clear lock password
				0 for sucess, 1 for fail,255 for not support
return :
	none
*/
void dq_otp_clear_lock_pwd_cb(uint8_t *result)
{
	
}

/*
Function:	clear the lock fp by app
parameter: 
	result:		the result for clear lock fp
				0 for sucess, 1 for fail,255 for not support
return :
	none
*/
#if defined (__LOCK_FP_SUPPORT__) || defined (__LOCK_FP_SUPPORT2__)||defined(__LOCK_FP_SUPPORT1_2__)

void dq_otp_clear_lock_fp_cb(uint8_t *result)
{
	uint16_t ret;

#ifdef __LOCK_FP_SUPPORT1_2__
	if(mmi_dq_fp_get_type() == FP_NONE)
	{
		dq_otp_lock_fp_app_fail_result();
		return;
	}
#endif

	
	if(mmi_dq_sys_is_sleep()==true)
	{
		power_init();
		FP_PowerOn();
	}
	else
	{
		mmi_dq_enter_sleep_timer_start();
	}
#if defined(__LOCK_FP_SUPPORT__)
	ret = mmi_dq_fs_clr_fp(dq_otp_lock_fp_app_clr_result);
#elif defined (__LOCK_FP_SUPPORT2__)

	if(mmi_dq_fp_get_fp_mode() == 0)
	{
		*result = 1;
		if(mmi_dq_sys_is_sleep()==true)
			mmi_dq_sys_enter_sleep();
		return;
	}


	ret = mmi_dq_fs_clr_fp(dq_otp_lock_fp_app_clr_result, dq_otp_lock_fp_app_fail_result);
#elif defined(__LOCK_FP_SUPPORT1_2__)
	FP_TYPE fp = mmi_dq_fp_get_type();

	if(fp == FP_LT5X) 
	{
		ret = mmi_dq_fs_clr_fp(dq_otp_lock_fp_app_clr_result);
	}
	else if(fp == FP_BTL)
	{
		if(mmi_dq_fp_get_fp_mode() == 0)
		{
			*result = 1;
			if(mmi_dq_sys_is_sleep()==true)
				mmi_dq_sys_enter_sleep();
			return;
		}

		ret = mmi_dq_fs_clr_fp_with_btl(dq_otp_lock_fp_app_clr_result, dq_otp_lock_fp_app_fail_result);

	}
	
#endif
	*result = ret;
	return;
}
#else

void dq_otp_clear_lock_fp_cb(uint8_t *result)
{
//	*result = BASE_FAIL;
	return;
}


#endif
/*
Funciton:	clear the lock rf by app
parameter: 
	result:		the result for clear lock rf
				0 for sucess, 1 for fail,255 for not support
return :
	none
*/
#ifdef __LOCK_RFID_CARD_SUPPORT__

void dq_otp_clear_lock_rf_cb(uint8_t *result)
{
	uint16_t ret = 1;
	if(mmi_dq_rfid_get_init_state() != 0)
//		*result = BASE_FAIL
	;
	else
	{
//		ret = mmi_dq_fs_clr_rfid(dq_otp_lock_rfid_app_clr_result);
//		*result = ret;
	}
	return;
}
#else
void dq_otp_clear_lock_rf_cb(uint8_t *result)
{
	*result = BASE_FAIL;
	return;
}

#endif
/*
Function: the index for password in lock
parameter: 
	id:		the server id for password
	index:	the index for password in lock
	result:		return the operte result,0 for sucess, 1 for fail,255 for not support
return :
	none
*/
void dq_otp_del_lock_pwd_cb(uint8_t *p_data,uint8_t *result)
{
	
}

/*
Function: the index for password in lock
parameter: 
	id:		the server id for password
	index:	the index for password in lock
	result:	return the operte result,0 for sucess, 1 for fail,255 for not support
return :
	none
*/
#if defined (__LOCK_FP_SUPPORT__) || defined (__LOCK_FP_SUPPORT2__) || defined (__LOCK_FP_SUPPORT1_2__)
uint16_t lock_del_fp_index=0;
#if defined (__LOCK_FP_SUPPORT2__) || defined (__LOCK_FP_SUPPORT1_2__)
void dq_otp_del_lock_fp_callback(uint8_t type,uint8_t *reply,uint16_t reply_len)
{
	if(type== 0x84)
	{
		if(reply[0]==0)
		{
			mmi_dq_fs_del_fp(lock_del_fp_index,FDS_PWD_TYPE_USER,dq_otp_lock_fp_app_del_result);
			return;
		}
		else
		{
			//mmi_dq_fp_delete(lock_del_fp_index,dq_otp_del_lock_fp_callback);
			dq_otp_lock_fp_app_fail_result();
		}
	}

}
#endif

void dq_otp_del_lock_fp_cb(uint16_t index,uint8_t *result)
{
	uint16_t ret = 0;
#ifdef __LOCK_FP_SUPPORT1_2__
	if(mmi_dq_fp_get_type() == FP_NONE)
	{
		*result = BASE_FAIL;
		return;
	}
#endif
	
	if(mmi_dq_sys_is_sleep()==true)
	{
		power_init();
		FP_PowerOn();
	}
	else
	{
		mmi_dq_enter_sleep_timer_start();
	}
#ifdef __LOCK_FP_SUPPORT__
	ret = mmi_dq_fp_delete(index);

	if(ret == 0)
	{
		lock_del_fp_index = index;
		ret = mmi_dq_fs_del_fp(index,FDS_PWD_TYPE_USER,dq_otp_lock_fp_app_del_result);
	}
	else
	{
		if(mmi_dq_sys_is_sleep()==true)
			mmi_dq_sys_enter_sleep();
	}
#elif defined(__LOCK_FP_SUPPORT2__)

	if(mmi_dq_fp_get_fp_mode() == 0)
	{
		*result = 1;
		if(mmi_dq_sys_is_sleep()==true)
			mmi_dq_sys_enter_sleep();
		return;
	}
	lock_del_fp_index = index;
	mmi_dq_fp_delete(index,dq_otp_del_lock_fp_callback);
#elif defined (__LOCK_FP_SUPPORT1_2__)
	FP_TYPE fp = mmi_dq_fp_get_type();

	if(fp == FP_LT5X) 
	{
		ret = mmi_dq_fp_delete(index);
		
		if(ret == 0)
		{
			lock_del_fp_index = index;
			ret = mmi_dq_fs_del_fp(index,FDS_PWD_TYPE_USER,dq_otp_lock_fp_app_del_result);
		}
		else
		{
			if(mmi_dq_sys_is_sleep()==true)
				mmi_dq_sys_enter_sleep();
		}
	}
	else if(fp == FP_BTL)
	{
		if(mmi_dq_fp_get_fp_mode() == 0)
		{
			*result = 1;
			if(mmi_dq_sys_is_sleep()==true)
				mmi_dq_sys_enter_sleep();
			return;
		}
		lock_del_fp_index = index;
		mmi_dq_fp_delete_btl(index,dq_otp_del_lock_fp_callback);

	}

	
#endif

	*result = ret;
	return;
}
#else
void dq_otp_del_lock_fp_cb(uint16_t index,uint8_t *result)
{
//	*result = BASE_FAIL;
	return;
}


#endif
/*
Function: the index for rf in lock
parameter: 
	id:		the server id for rf
	index:	the index for rf in lock
	result:	return the operte result,0 for sucess, 1 for fail,255 for not support
return :
	none
*/
#ifdef __LOCK_RFID_CARD_SUPPORT__

uint16_t lock_del_rf_index=0;
void dq_otp_del_lock_rf_cb(uint16_t index,uint8_t *result)
{
	uint16_t ret = 0;
	if(mmi_dq_rfid_get_init_state() != 0)
	{
//		*result = BASE_FAIL;
		return;
	}

	lock_del_rf_index = index;
//	ret = mmi_dq_fs_del_rfid(index ,dq_otp_lock_rfid_app_del_result);

	*result = ret;
	return;
}
#else
void dq_otp_del_lock_rf_cb(uint16_t index,uint8_t *result)
{
	*result = BASE_FAIL;
	return;
}
	
#endif
#if defined (__LOCK_FP_SUPPORT__) || defined (__LOCK_FP_SUPPORT2__) || defined (__LOCK_FP_SUPPORT1_2__)

uint8_t dq_otp_check_lock_fp(uint16_t index)
{
	uint8_t ret = 0;
#ifdef __LOCK_FP_SUPPORT1_2__
	if(mmi_dq_fp_get_type() == FP_NONE)
		return BASE_FAIL;
#endif
	
	ret = mmi_dq_fs_check_fp(index,FDS_PWD_TYPE_USER);
	return ret;
}
#else
uint8_t dq_otp_check_lock_fp(uint16_t index)
{
	//return BASE_FAIL;
	return 0x01;
}

#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__

uint8_t dq_otp_check_lock_rfid(uint16_t index)
{
	uint8_t ret = 0;

	if(mmi_dq_rfid_get_init_state() != 0)
	{
//		return BASE_FAIL;
	}
	
//	ret = mmi_dq_fs_check_rfid(index,FDS_PWD_TYPE_USER);
	return ret;
}
#else
uint8_t dq_otp_check_lock_rfid(uint16_t index)
{
	return BASE_FAIL;
}
#endif

#ifdef __LOCK_RFID_CARD_SUPPORT__
extern unsigned short g_rfid_index ;

void dq_otp_add_lock_rfid_by_app_callback(void)
{
	dq_otp_app_add_lock_rfid_result(0,g_rfid_index);

}

void dq_otp_add_lock_rfid_by_app_cb(uint8_t* p_data)
{
	// uint8_t retval = 0;
	// BASE_STATUS_MACHINE state;
	
	// if(mmi_dq_rfid_get_init_state() != 0)
	// {
	// 	dq_otp_app_add_lock_rfid_result(5,0);
	// 	return;
	// }

	// mmi_dq_sys_wake_up();
	// state = mmi_dq_ms_get_machine_status();
	// if(state == BASE_STATUS_M_IDLE||state == BASE_STATUS_M_IDLE_INPUT_PWD)
	// {
	// 	if(mmi_dq_fs_get_index_by_secdata(p_data) != 0xFF)
	// 	{
	// 		dq_otp_app_add_lock_rfid_result(3,0);
	// 		return;
	// 	}
	
	// 	g_rfid_index = mmi_dq_fs_get_rfid_free_index();
	// 	if(g_rfid_index == 0xFF)
	// 	{
	// 		dq_otp_app_add_lock_rfid_result(2,0);
	// 		return;
	// 	}

	// 	retval = mmi_dq_fs_add_rfid(g_rfid_index, FDS_PWD_TYPE_USER, data, dq_otp_add_lock_rfid_by_app_callback);
	// 	if(retval != BASE_SUCESS)
	// 	{
	// 		dq_otp_app_add_lock_rfid_result(4,0);
	// 		return;
	// 	}
	// }
	// else
	// 	dq_otp_app_add_lock_rfid_result(4,0);

}

#else
void dq_otp_add_lock_rfid_by_app_cb(uint8_t* data)
{
	//dq_otp_app_add_lock_rfid_result(4,0);
}
#endif

void dq_otp_app_return_idle(void)
{
	if(mmi_dq_sys_is_sleep()==true)
	{
		mmi_dq_enter_sleep_timer_stop();
//		mmi_dq_ms_set_machine_status(BASE_STATUS_M_ENTER_SLEEP);
	}
	else
	//	mmi_dq_ms_set_machine_status(BASE_STATUS_M_IDLE)
	;

}
/*
Function: get the battery info from lock
parameter: 
	level:	return the battery level
	result:	return the operte result,0 for sucess, 1 for fail,255 for not support
return :
	none
*/
extern uint16_t VBAT_Last_Value;
void dq_otp_get_lock_bat_info_cb(uint8_t *level,uint8_t *result)
{
	
	if(VBAT_Last_Value>=533)//6)
		*level = 100;
	else if(VBAT_Last_Value>=515)//5.8
		*level = 95;//+(VBAT_Last_Value-515)*5/18;
	else if(VBAT_Last_Value>=489)//5.5
		*level = 90;//+(VBAT_Last_Value-489)*5/26;
	else if(VBAT_Last_Value >=444) //5
		*level = 70+((VBAT_Last_Value-444)*20/45)/5*5;
	else if(VBAT_Last_Value>=391)//4.4)
		*level = 50+((VBAT_Last_Value-391)*20/53)/5*5;
	else if(VBAT_Last_Value>=373)//4.2
		*level = 20+((VBAT_Last_Value-373)*30/18)/5*5;
	else if(VBAT_Last_Value>=355)//4
		*level = ((VBAT_Last_Value-355)*20/18)/5*5;
	else if(VBAT_Last_Value>=0x90)
		*level = 0;
	else
		*level = 100;

	*result = 0;
	
}

/*
Function: get the software version from lock
parameter: 
	ver_info:	return the lock software version info
	result:		return the operte result,0 for sucess, 1 for fail,255 for not support
return :
	none
*/
void dq_otp_get_lock_ver_info_cb(uint16_t *ver_info,uint8_t *result)
{
//	*ver_info = DFU_VER_INFO;
	*result = 0;
	return;
}

/*
Function: set the lock audio status when opening
parameter: 
	flag: 0 for close the audio when opening the lock
		  1 for open the audio when opening the lock
	result:	return the operte result,0 for sucess, 1 for fail,255 for not support
return :
	none
*/
void dq_otp_set_lock_open_aud_cb(uint8_t flag,uint8_t *result)
{
	
}

/*
Function : get the lock memory info,password count , fp count ,rf count...
parameter: 
	pwd_count:	the password count
	fp_count:	the fp count
	rf_count:	the rf count
	result:		return the operte result,0 for sucess, 1 for fail,255 for not support
return :
	none
*/
void dq_otp_get_lock_mem_info_cb(uint8_t *pwd_count,uint8_t *fp_count,uint8_t *rf_count,uint16_t *lock_config)
{
#ifdef __WIN32_ENV_SUPPORT__
	*pwd_count = 100;
	*fp_count = 200;
	*rf_count = 20;
	*lock_config = 0x000F;
#else
//	mmi_dq_get_mem_info(pwd_count,fp_count,rf_count);
//	mmi_dq_sys_lock_config_info(lock_config);
#endif
	return;
}

/*
Function : get the admin status,for example:password only,fp only,password+fp
parameter: 
	status: 0 for password only
			1 for fp only
			2 for password+fp
	result:	return the operte result,0 for sucess, 1 for fail,255 for not support
return :
	none
*/
void dq_otp_get_admin_status_cb(uint8_t *status,uint8_t *result)
{
#if 1
//q1  xjc
#ifndef __WIN32_ENV_SUPPORT__
	if(mmi_dq_fs_get_admin_status() == 0)
	{
		*result = 0;
		*status = 0;
	}
#if defined (__LOCK_FP_SUPPORT__)||defined(__LOCK_FP_SUPPORT2__) || defined (__LOCK_FP_SUPPORT1_2__)
	else if(mmi_dq_ms_check_admin_fp_exist() == 0)
	{
		*result = 0;
		*status = 1;
	}
#endif
	else
	{
		*result = 0;
		*status = 3;
	}
#endif

#else
	*status = 3;
	*result = 0;
#endif
	return;
}

/*
Function : get the admin status,for example:password only,fp only,password+fp
parameter: 
	status: 0 for password only
			1 for fp only
			2 for password+fp
	result:	return the operte result,0 for sucess, 1 for fail,255 for not support
return :
	none
*/
void dq_otp_verify_admin_status_cb(uint16_t delay_time,uint8_t *result)
{
	if(mmi_dq_fs_get_admin_status() != 0)
	{
		BASE_STATUS_MACHINE state;
		*result = 0; 
		dq_otp_app_set_operate_lock_flag(1);
		mmi_dq_sys_wake_up();
		state = mmi_dq_ms_get_machine_status();
		if(state==BASE_STATUS_M_IDLE||state == BASE_STATUS_M_IDLE_INPUT_PWD)
		{
//			mmi_dq_ms_set_machine_status(BASE_STATUS_M_IDLE_SYS_MENU_START);
		}
		else
		{
			dq_otp_app_set_operate_lock_flag(0);
			*result = 1;
		}
	}
	else
		*result = 1;
}


void dq_otp_stop_verify_admin_status_cb(uint8_t *result)
{
	BASE_STATUS_MACHINE state = mmi_dq_ms_get_machine_status();
	if((dq_otp_app_get_operate_lock_flag()==1) &&(state == BASE_STATUS_M_IDLE_SYS_MENU_START||state ==BASE_STATUS_M_IDLE_SYS_MENU_INPUT))
	{
		dq_otp_app_set_operate_lock_flag(0);
#ifdef __LOCK_AUDIO_SUPPORT__
//		mmi_dq_aud_play_with_id(AUD_BASE_ID_SET_FAIL,NULL);
#endif
//		mmi_dq_ms_set_machine_status(BASE_STATUS_M_IDLE);
	}
	
}

/*
Function: set the system time
parameter: 
	time_s:	current time with second
	result:	return the operte result,0 for sucess, 1 for fail,255 for not support
return :
	none
*/
void dq_otp_set_system_time_cb(uint32_t time_s,uint8_t *result)
{
#ifndef __WIN32_ENV_SUPPORT__
//	NRF_LOG_PRINTF_DEBUG("dq_otp_set_system_time_cb get time:%d\n",mmi_dq_rtc_get_sys_sec_info());
	//NRF_LOG_PRINTF_DEBUG("dq_otp_set_system_time_cb set time:%d\n",time_s);
	
	mmi_dq_rtc_get_time_by_sec(time_s);
#endif
}

void dq_otp_set_system_time_zone_cb(uint16_t w_time_zone,uint16_t e_time_zone,uint8_t *result)
{
//	*result = mmi_dq_fs_set_time_zone(w_time_zone,e_time_zone);
}



extern void dq_otp_check_and_update_time_cb(void);


void dq_otp_update_time(void)
{
//	mmi_dq_fs_set_time(dq_otp_check_and_update_time_cb);
}

/*
Function: get the system time
parameter: 
	time_s: lock system with second
	result:	return the operte result,0 for sucess, 1 for fail,255 for not support
return :
	none
*/
void dq_otp_get_system_time_cb(uint32_t *time_s,uint8_t *result)
{
	*time_s = mmi_dq_rtc_get_sys_sec_info();

	*result = 0;
	
}

/*
Function: get the system time
parameter: 
	time_s: lock system with second
	result:	return the operte result,0 for sucess, 1 for fail,255 for not support
return :
	none
*/
void dq_otp_get_lock_time_info_cb(struct tm *sys_tm)
{
#ifndef __WIN32_ENV_SUPPORT__
	mmi_dq_rtc_get_time(sys_tm);
#else
{
	time_t sys_time;
	struct tm *sys_tm1;
	sys_time = time(0);	
	sys_tm1 = localtime (&sys_time);

	memcpy(sys_tm,sys_tm1,sizeof(struct tm));
}
#endif
	return;
}



/*
parameter: 
	none
return :
	none
*/
#ifndef __WIN32_ENV_SUPPORT__
extern void advertising_init(unsigned char flag);
#endif
void dq_otp_set_init_sucess_cb(unsigned char flag)
{
#ifndef __WIN32_ENV_SUPPORT__
	advertising_init(flag);
#endif
}

/*
parameter: 
	none
return :
	none
*/
void dq_otp_set_init_sucess_reset_lock_cb(void)
{
#ifndef __WIN32_ENV_SUPPORT__
	mmi_dq_sys_app_init_sucess();
#endif
}

uint8_t dq_otp_get_lock_state(void)
{

	if(mmi_dq_sys_get_lock_state())
		return 1;
	else
	{
		BASE_STATUS_MACHINE m=mmi_dq_ms_get_machine_status();
		
		if(m == BASE_STATUS_M_ENTER_SLEEP ||m == BASE_STATUS_M_IDLE||m==BASE_STATUS_M_IDLE_INPUT_PWD||m==BASE_STATUS_M_IDLE_SYS_MENU_START||m==BASE_STATUS_M_IDLE_SYS_MENU_INPUT)
			return 0;
		else
			return 1;
	}

}

uint8_t dq_otp_lock_save_log_state(void)
{
	BASE_STATUS_MACHINE status = mmi_dq_ms_get_machine_status();
	if(status == BASE_STATUS_M_IDLE || status == BASE_STATUS_M_ENTER_SLEEP||status==BASE_STATUS_M_IDLE_INPUT_PWD||status==BASE_STATUS_M_IDLE_SYS_MENU_START||status==BASE_STATUS_M_IDLE_SYS_MENU_INPUT)
		return 1;
	else
		return 0;

}

void dq_otp_set_lock_open(void)
{
	mmi_dq_sys_wake_up();
#ifndef __WIN32_ENV_SUPPORT__
	mmi_dq_sys_open_lock();
#endif
}



uint8_t dq_otp_lock_check_admin_pwd(unsigned char *password)
{
	return mmi_dq_fs_check_app_admin_password(password);
}

uint8_t dq_otp_lock_check_lock_state(void)
{

	if(mmi_dq_sys_get_lock_state() == 1)
	{
		return 1;
	}
	
	if(mmi_dq_sys_get_vbat_state() == 2)
	{
		mmi_dq_sys_vbat_low_wake_up();
		return 2;
	}
	return 0;
}


void dq_otp_lock_input_pwd_cb(unsigned char ret_val)
{
	mmi_dq_fs_check_input_pwd_from_app_cb(ret_val);

}

void dq_otp_lock_time_zone_pro(uint32_t * time)
{
	mmi_dq_fs_time_zone_pro(time);

}

uint8_t dq_otp_lock_random_vector_generate(uint8_t * p_buff, uint8_t size)
{
	return mmi_dq_lock_random_vector_generate(p_buff,size);
}

#endif
#endif//__DQ_SDK_CB_C__
