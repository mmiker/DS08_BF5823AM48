#ifndef __MMI_VIRTUAL_PWD_H__
#define __MMI_VIRTUAL_PWD_H__
#include "mmi_feature.h"
#ifdef __LOCK_VIRTUAL_PASSWORD__1
#include "mcu02_sfr.h"

#define DQ_OTP_APP_PWD_NUM 100

typedef struct otp_base_app_pwd_info
{
	//uint8_t 	pwd_index;
	uint8_t 	pwd_type;
	uint8_t 	pwd_flag;//0 :unused;1 : used;2 : del
	uint8_t		app_pwd[5];
	uint8_t 	replace_pwd[5];
	//uint32_t 	pwd_end_time;
}otp_base_app_pwd_info;

typedef struct
{
    dq_otp_fds_write 	fds_write;/**be called for handling write fds. */
	dq_otp_fds_read 	fds_read;/**be called for handling read fds. */
	dq_otp_data_send_bt 	data_send_bt;/**be called for send data. */
	//dq_otp_data_send_nb 	data_send_nb;/**be called for send data. */
//lock
	dq_otp_set_lock_pwd 		set_lock_pwd;
	dq_otp_set_lock_fp			set_lock_fp;
	dq_otp_set_lock_rfid		set_lock_rfid;

	dq_otp_stop_verify_admin_status   stop_verify_admin_status;

	dq_otp_stop_set_lock_fp			stop_set_lock_fp;
	dq_otp_stop_set_lock_rfid		stop_set_lock_rfid;
	
	dq_otp_clear_lock_pwd 		clear_lock_pwd;
	dq_otp_clear_lock_fp  		clear_lock_fp;
	dq_otp_clear_lock_rfid  	clear_lock_rf;
	
	dq_otp_del_lock_pwd_idx 	del_lock_pwd;
	dq_otp_del_lock_fp_idx 		del_lock_fp;
	dq_otp_del_lock_rf_idx  	del_lock_rf;


	dq_otp_set_lock_rfid_by_app	add_lock_rfid_by_app;

//lock info
	dq_otp_get_bat_info		  get_lock_bat_level;
	dq_otp_get_ver_info		  get_lock_ver_info;
	dq_otp_set_open_aud		  set_lock_open_aud;
	dq_otp_get_lock_mem_info  get_lock_mem_info;
	
	dq_otp_get_admin_status	  get_admin_status;
	dq_otp_verify_admin_status	verify_admin_status;
	dq_otp_set_system_time 	  set_system_time;
	dq_otp_set_system_time_zone   set_system_time_zone;
	
	dq_otp_get_system_time	  get_system_time;
	dq_otp_get_lock_time_info  get_lock_time_info;
//init sucess
	dq_otp_init_sucess_cb	init_sucess;
	dq_otp_init_sucess_reset_lock_cb init_sucess_reset_lock;

	dq_otp_open_lock	open_lock;
//ex
	dq_otp_check_admin_pwd	check_admin_pwd;
	dq_otp_check_lock_state	check_lock_state;
	dq_otp_input_pwd_cb	input_pwd_cb;

	dq_otp_time_zone_pro   time_zone_pro;
} dq_otp_init_t;


#endif
#endif //__MMI_VIRTUAL_PWD_H__