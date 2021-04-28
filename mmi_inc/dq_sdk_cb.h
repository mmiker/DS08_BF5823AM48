#ifndef __DQ_SDK_CB_H__
#define __DQ_SDK_CB_H__
#include "mmi_feature.h"
#ifdef __LOCK_VIRTUAL_PASSWORD__
//#include <stdbool.h>
//#include <stdint.h>
#include <string.h>
#include "dq_sdk_main.h"


//#define __WIN32_ENV_SUPPORT__

/*
parameter: 
	file_id£º	the id for the file to write
	p_data:		the data to write
return :
	none
*/
void dq_otp_fds_write_cb(uint16_t file_id,uint8_t * p_data,uint16_t data_len,uint8_t *result,dq_otp_write_data_cb cb);

/*
parameter: 
	file_id:	the id for the file to read
	p_data:		the buffer for file read
return :
	none
*/
void dq_otp_fds_read_cb(uint16_t file_id,uint8_t * p_data,uint16_t data_len,uint8_t *result);
/*
parameter: 
	file_id		the id for the file to write
	p_data:		the data to write
	data_len:	the data len to write
	result:		return the operte result,0 for sucess, 1 for fail
return :
	none
*/
void dq_otp_fds_write_pwd_ekey(void);
/*
parameter: 
	none
return :
	none
*/
void dq_otp_fds_write_log(void);

/*
Function: this function for data to be sent by bt
parameter: 
	p_data:		the buffer for data to be sent
	data_len:	the length for the data to be sent
return :
	none
*/
void dq_otp_data_send_by_bt_cb(uint8_t * p_data,uint16_t data_len,uint32_t *result);

/*
Function: this function for data to be sent by nb
parameter: 
	p_data:		the buffer for data to be sent
	data_len:	the length for the data to be sent
return :
	none
*/
void dq_otp_data_send_by_nb_cb(uint8_t * p_data,uint16_t data_len,uint8_t *result);
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
void dq_otp_app_set_operate_lock_flag(uint8_t flag);
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
uint8_t dq_otp_app_get_operate_lock_flag(void);


/*
Function:		set the lock password by app
parameter: 
	p_data:		the password for lock to set
	data_len:	the password length
	result:		the result for save lock password.
				0 for sucess, 1 for fail
return :
	none
*/
void dq_otp_set_lock_pwd_cb(uint8_t * p_data,uint16_t data_len,uint8_t *result);

/*
Function:		set the lock rfid by app
parameter: 
	data_index:	set the fp in lock return the index
	result:		the result for save lock fp
				0 for sucess, 1 for fail,255 for not support
return :
	none
*/
void dq_otp_set_lock_rfid_cb(uint16_t delay_time,uint8_t *result);
void dq_otp_stop_set_lock_rfid_cb(uint8_t *result);

/*
Function:		set the lock fp by app
parameter: 
	data_index:	set the fp in lock return the index
	result:		the result for save lock fp
				0 for sucess, 1 for fail
return :
	none
*/
void dq_otp_set_lock_fp_cb(uint16_t     delay_time,uint8_t *result);
void dq_otp_stop_set_lock_fp_cb(uint8_t *result);

/*
Function:	clear the lock password by app
parameter: 
	result:		the result for clear lock password
				0 for sucess, 1 for fail
return :
	none
*/
void dq_otp_clear_lock_pwd_cb(uint8_t *result);

/*
Function:	clear the lock fp by app
parameter: 
	result:		the result for clear lock fp
				0 for sucess, 1 for fail
return :
	none
*/
void dq_otp_clear_lock_fp_cb(uint8_t *result);

/*
Funciton:	clear the lock rf by app
parameter: 
	result:		the result for clear lock rf
				0 for sucess, 1 for fail
return :
	none
*/
void dq_otp_clear_lock_rf_cb(uint8_t *result);

/*
Function: the index for password in lock
parameter: 
	id:		the server id for password
	index:	the index for password in lock
return :
	none
*/
void dq_otp_del_lock_pwd_cb(uint8_t *p_data,uint8_t *result);

/*
Function: the index for password in lock
parameter: 
	id:		the server id for password
	index:	the index for password in lock
return :
	none
*/
void dq_otp_del_lock_fp_cb(uint16_t index,uint8_t *result);

/*
Function: the index for rf in lock
parameter: 
	id:		the server id for rf
	index:	the index for rf in lock
return :
	none
*/
void dq_otp_del_lock_rf_cb(uint16_t index,uint8_t *result);


void dq_otp_add_lock_rfid_by_app_cb(uint8_t* p_data);

/*
Function: get the battery info from lock
parameter: 
	level:	return the battery level
return :
	none
*/
void dq_otp_get_lock_bat_info_cb(uint8_t *level,uint8_t *result);

/*
Function: get the software version from lock
parameter: 
	ver_info:	return the lock software version info
return :
	none
*/
void dq_otp_get_lock_ver_info_cb(uint16_t *ver_info,uint8_t *result);

/*
Function: set the lock audio status when opening
parameter: 
	flag: 0 for close the audio when opening the lock
		  1 for open the audio when opening the lock
return :
	none
*/
void dq_otp_set_lock_open_aud_cb(uint8_t flag,uint8_t *result);

/*
Function : get the lock memory info,password count , fp count ,rf count...
parameter: 
	pwd_count:	the password count
	fp_count:	the fp count
	rf_count:	the rf count
return :
	none
*/
void dq_otp_get_lock_mem_info_cb(uint8_t *pwd_count,uint8_t *fp_count,uint8_t *rf_count,uint16_t *lock_config);

/*
Function : get the admin status,for example:password only,fp only,password+fp
parameter: 
	status: 0 for password only
			1 for fp only
			2 for password+fp
return :
	none
*/
void dq_otp_get_admin_status_cb(uint8_t *status,uint8_t *result);
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
void dq_otp_verify_admin_status_cb(uint16_t delay_time,uint8_t *result);


/*
Function: set the system time
parameter: 
	time_s:	current time with second
return :
	none
*/
void dq_otp_set_system_time_cb(uint32_t time_s,uint8_t *result);

/*
Function: get the system time
parameter: 
	time_s: lock system with second
return :
	none
*/
void dq_otp_get_system_time_cb(uint32_t *time_s,uint8_t *result);
/*
Function: get the system time
parameter: 
	time_s: lock system with second
	result:	return the operte result,0 for sucess, 1 for fail,255 for not support
return :
	none
*/
void dq_otp_get_lock_time_info_cb(struct tm *time);

/*
parameter: 
	none
return :
	none
*/
void dq_otp_set_init_sucess_cb(unsigned char flag);

uint8_t dq_otp_get_lock_state(void);
uint8_t dq_otp_lock_save_log_state(void);

void dq_otp_set_lock_open(void);

void dq_otp_app_return_idle(void);


uint8_t dq_otp_check_lock_fp(uint16_t index);
uint8_t dq_otp_check_lock_rfid(uint16_t index);

void dq_otp_stop_verify_admin_status_cb(uint8_t *result);

void dq_otp_update_time(void);

uint8_t dq_otp_lock_check_admin_pwd(unsigned char *password);
uint8_t dq_otp_lock_check_lock_state(void);

void dq_otp_lock_input_pwd_cb(unsigned char ret_val);


void dq_otp_lock_time_zone_pro(uint32_t * time);
void dq_otp_set_system_time_zone_cb(uint16_t w_time_zone,uint16_t e_time_zone,uint8_t *result);

uint8_t dq_otp_lock_random_vector_generate(uint8_t * p_buff, uint8_t size);

#endif
#endif//__DQ_SDK_CB_H__

