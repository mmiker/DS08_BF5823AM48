#ifndef __DQ_SDK_MAIN_H__
#define __DQ_SDK_MAIN_H__
#include "mmi_feature.h"
#ifdef __LOCK_VIRTUAL_PASSWORD__
#include "mcu02_sfr.h"
//#include <stdbool.h>
//#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
//#include <time.h>
#include <math.h>

#include "mmi_feature.h"

#ifndef bool
	#define bool int
#endif

#ifndef true
	#define true 1
#endif

#ifndef false
	#define false 0
#endif

typedef enum
{
	DQ_OTP_FILE_ID_SET = 0x00,
	DQ_OTP_FILE_ID_PWD_APP = 0x01,
	DQ_OTP_FILE_ID_FP = 0x02,
	DQ_OTP_FILE_ID_RFID = 0x03,
	DQ_OTP_FILE_ID_LOG = 0x04,
	DQ_OTP_FILE_ID_INVALID = 0xFF
}DQ_OTP_FILE_ID;

#define DQ_OTP_APP_PWD_NUM			100
#define DQ_OTP_APP_FP_NUM			50
#define DQ_OTP_APP_RFID_NUM			10
#ifdef  __TEST_LOG_OPEN__
#define DQ_OTP_LOG_NUM				20
#else
#define DQ_OTP_LOG_NUM				100
#endif
typedef struct otp_base_app_pwd_info
{
	//uint8_t 	pwd_index;
	uint8_t 	pwd_type;
	uint8_t 	pwd_flag;//0 :unused;1 : used;2 : del
	uint8_t		app_pwd[5];
	uint8_t 	replace_pwd[5];
	//uint32_t 	pwd_end_time;
}otp_base_app_pwd_info;

typedef struct otp_base_app_fp_info
{
	//uint16_t fp_index;
	uint32_t fp_start_time;
	uint32_t fp_end_time;
}otp_base_app_fp_info;

typedef struct otp_base_app_rfid_info
{
	//uint16_t rfid_index;
	uint32_t rfid_start_time;
	uint32_t rfid_end_time;
}otp_base_app_rfid_info;


#define APP_PWD_START_INDEX 0x0000
#define LOCK_PWD_START_INDEX 0xC000
#define LOCK_FP_START_INDEX 0xD000
#define LOCK_RFID_START_INDEX 0xE000

//init


//fds 
typedef void (*dq_otp_write_data_cb)(void);
typedef void (*dq_otp_fds_write) (uint16_t file_id,uint8_t * p_data,uint16_t data_len,uint8_t *result,dq_otp_write_data_cb cb);
typedef void (*dq_otp_fds_read) (uint16_t file_id,uint8_t * p_data,uint16_t data_len,uint8_t *result);




//data handle
/*
send data
*/
typedef void (*dq_otp_data_send_bt) (uint8_t * p_data,uint16_t data_len,uint32_t *result);
//typedef void (*dq_otp_data_send_nb) (uint8_t * p_data,uint16_t data_len,uint8_t *result);

//lock sec
typedef void (*dq_otp_set_lock_pwd) (uint8_t * p_data,uint16_t data_len,uint8_t *result);
typedef void (*dq_otp_set_lock_fp) (uint16_t  delay_time,uint8_t *result);
typedef void (*dq_otp_set_lock_rfid) (uint16_t  delay_time,uint8_t *result);

typedef void (*dq_otp_stop_verify_admin_status) (uint8_t *result);
typedef void (*dq_otp_stop_set_lock_fp) (uint8_t *result);
typedef void (*dq_otp_stop_set_lock_rfid) (uint8_t *result);

typedef void (*dq_otp_clear_lock_pwd) (uint8_t *result);
typedef void (*dq_otp_clear_lock_fp) (uint8_t *result);
typedef void (*dq_otp_clear_lock_rfid) (uint8_t *result);

typedef void (*dq_otp_del_lock_pwd_idx) (uint8_t *p_data,uint8_t *result);
typedef void (*dq_otp_del_lock_fp_idx) (uint16_t index,uint8_t *result);
typedef void (*dq_otp_del_lock_rf_idx) (uint16_t index,uint8_t *result);

typedef void (*dq_otp_set_lock_rfid_by_app) (uint8_t *p_data);

//lock info
typedef void (*dq_otp_get_bat_info) (uint8_t *level,uint8_t *result);
typedef void (*dq_otp_get_ver_info) (uint16_t *ver_info,uint8_t *result);
typedef void (*dq_otp_set_open_aud) (uint8_t flag,uint8_t *result);
typedef void (*dq_otp_get_lock_mem_info) (uint8_t *pwd_count,uint8_t *fp_count,uint8_t *rf_count,uint16_t *lock_config);

typedef void (*dq_otp_get_lock_time_info)(struct tm *time);


typedef void (*dq_otp_get_admin_status) (uint8_t *status,uint8_t *result);
typedef void (*dq_otp_verify_admin_status) (uint16_t  delay_time,uint8_t *result);

typedef void (*dq_otp_set_system_time) (uint32_t time_s,uint8_t *result);
typedef void (*dq_otp_set_system_time_zone) (uint16_t w_time_zone,uint16_t e_time_zone,uint8_t *result);

typedef void (*dq_otp_get_system_time) (uint32_t *time_s,uint8_t *result);
typedef void (*dq_otp_init_sucess_cb)(unsigned char flag);
typedef void (*dq_otp_init_sucess_reset_lock_cb)(void);
typedef void (*dq_otp_open_lock)(void);


typedef uint8_t (*dq_otp_check_admin_pwd)(unsigned char *password);
typedef uint8_t (*dq_otp_check_lock_state)(void);
typedef void (*dq_otp_input_pwd_cb)(unsigned char ret_val);

typedef void (*dq_otp_time_zone_pro)(uint32_t *time);
/*
parameter: 
	none
return :
	none
*/
void dq_otp_dataCheck(uint8_t * p_data, uint16_t length);
/*
parameter: 
	none
return :
	none
*/
void dq_sdk_otp_init(void);


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
#if 1
typedef enum
{
	DQ_OPEN_LOG_ADMIN_PASSWORD = 1,
	DQ_OPEN_LOG_ADMIN_FP,
	DQ_OPEN_LOG_USER_PASSWORD,
	DQ_OPEN_LOG_USER_FP,
	DQ_OPEN_LOG_USER_RF,
	DQ_ALART_LOG_LOW_BATTERY,
	DQ_ALART_LOG_MULTIPLE_ERROR,
	DQ_ALART_LOG_CHG_ADMIN_PWD = 0x0A,
	DQ_ALART_LOG_CHG_ADMIN_FP = 0x0B,
	DQ_ALART_LOG_CHG_OPEN_MODE = 0x0C,
	DQ_ALART_LOG_CHG_PRO_SOUND = 0x0D,
	DQ_ALART_LOG_EMPTY_PASSWORD = 0x11,
	DQ_ALART_LOG_ERROR_RESET = 0x12,
}DQ_OTP_LOG_TYPE;
#endif
/*
parameter: 
	none
return :
	none
*/
void dq_otp_app_init_suc(void);
/*
parameter: 
	current status machine
return :
	none
*/
void dq_otp_fds_write_common_cb(void);
/*
parameter: 
	current status machine
return :
	none
*/
void dq_otp_fds_write_with_data_cb(void);
/*
parameter: 
	current status machine
return :
	none
*/
void dq_otp_fds_reset_pwd_record_cb(void);
/*
parameter: 
	none
return :
	none
*/
void dq_otp_cmd_dataOperation(uint8_t * p_data,uint16_t data_len);
/*
parameter: 
	current status machine
return :
	none
*/
void dq_otp_fds_clear_init_set_param(dq_otp_write_data_cb write_data_cb);
/*
parameter: 
	current status machine
return :
	none
*/
void dq_otp_fds_clear_app_pwd(dq_otp_write_data_cb write_data_cb);
/*
parameter: 
	current status machine
return :
	none
*/
void dq_otp_fds_clear_log(dq_otp_write_data_cb write_data_cb);
void dq_otp_fds_clear_app_fp(dq_otp_write_data_cb write_data_cb);
void dq_otp_fds_clear_app_rf(dq_otp_write_data_cb write_data_cb);
/*
parameter: 
	current status machine
return :
	none
*/
void dq_otp_enc_pwd(unsigned char *pwd,unsigned char len,unsigned char *sec_key,unsigned char *exg_key,unsigned char *sec_pwd);
/*
parameter: 
	current status machine
return :
	none
*/
unsigned char dq_otp_check_password(unsigned char *password);
unsigned char dq_otp_check_replace_password(unsigned char *password);

unsigned char dq_otp_check_password_for_open(unsigned char *password, unsigned char len);

unsigned char dq_otp_check_app_rfid(unsigned char index);
unsigned char dq_otp_check_app_fp(unsigned char index);
/*
parameter: 
	none
return :
	none
*/
void dq_otp_set_init_sucess_reset_lock_cb(void);

/*
parameter: 
	none
return :
	none
*/
void dq_otp_app_add_lock_fp_result(uint8_t result_flag,uint16_t fp_index);
void dq_otp_lock_fp_app_clr_result(void);
void dq_otp_lock_fp_app_del_result(void);
void dq_otp_lock_fp_app_fail_result(void);
/*
parameter: 
	none
return :
	none
*/
void dq_otp_app_add_lock_rfid_result(uint8_t result_flag,uint16_t rfid_index);
void dq_otp_lock_rfid_app_clr_result(void);
void dq_otp_lock_rfid_app_del_result(void);
/*
parameter: 
	none
return :
	none
*/
void dq_otp_check_lock_admin_pwd_fp_ret(uint8_t result);


uint8_t dq_otp_temp_pwd_check(unsigned char *pwd_in,unsigned char len);

void dq_otp_add_exchange_temp_open_log(uint8_t src_id,uint8_t dest_id);
unsigned char dq_otp_add_temp_open_log(uint8_t id,unsigned char type, unsigned char *pwd,unsigned char len);
void dq_otp_del_temp_open_log(void);
void dq_otp_add_open_log_by_temp(uint8_t id);
unsigned char dq_otp_add_open_log(unsigned char type, unsigned char *pwd,unsigned char len);
unsigned char dq_otp_add_alarm_log(unsigned char type);
//unsigned char dq_otp_del_open_log(void);
void dq_otp_save_open_log(dq_otp_write_data_cb write_data_cb);

uint8_t dq_otp_get_link_state(void);

void dq_otp_disconnect_pro(void);
void dq_otp_lock_timeout(void);

unsigned char dq_otp_get_lock_sys_time_state(void);

uint8_t dq_otp_get_dfu_permit(void);
void dq_otp_set_dfu_permit(uint8_t permit);

#endif
#endif//__DQ_SDK_MAIN_H__

