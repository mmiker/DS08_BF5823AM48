#ifndef __MMI_MS_H__
#define __MMI_MS_H__

#include "mmi_queue.h"
#include "mmi_com.h"

#define KEY_INPUT_MAX_LEN	32
#define PWD_INPUT_MAX_LEN	8
#define PWD_INPUT_MIN_LEN	6
#define FPS_MAX_INPUT_TIME 	OPT_FOUR_TIME

typedef enum
{
	SYS_STATUS_INIT = 0x00,
		
	SYS_STATUS_IDLE = 0x01,
	SYS_STATUS_INPUT_PWD = 0x01,
	SYS_STATUS_INPUT_ADMIN_PWD = 0x02,
	SYS_STATUS_ADD_PWD = 0x12,
	SYS_STATUS_DEL_PWD = 0x13,
	SYS_STATUS_CLR_PWD = 0x14,
	SYS_STATUS_ADD_PWD_CON = 0x15,
	SYS_STATUS_DEL_PWD_CON = 0x16,
	SYS_STATUS_ADD_110_PWD = 0x17,
	
#ifdef	__LOCK_FP_SUPPORT__
	SYS_STATUS_INPUT_FP = 0x01,
	SYS_STATUS_INPUT_ADMIN_FP = 0x02,
	SYS_STATUS_ADD_FP = 0x22,
	SYS_STATUS_DEL_FP = 0x23,
	SYS_STATUS_CLR_FP = 0x24,
	SYS_STATUS_ADD_FP_CON = 0x25,
	SYS_STATUS_DEL_FP_CON = 0x26,
	SYS_STATUS_ADD_110_FP = 0x27,
	SYS_STATUS_DEL_110_FP = 0x28,
#endif

#ifdef __LOCK_RFID_CARD_SUPPORT__
	SYS_STATUS_INPUT_RFID = 0x01,
	SYS_STATUS_ADD_RFID = 0x32,
	SYS_STATUS_DEL_RFID = 0x33,
	SYS_STATUS_CLR_RFID = 0x34,
	SYS_STATUS_ADD_RFID_CON = 0x35,
	SYS_STATUS_DEL_RFID_CON = 0x36,
#endif

	SYS_STATUS_ADD_ADMIN_PWD = 0x41,
	SYS_STATUS_CHG_ADMIN_PWD = 0x42,
#ifdef	__LOCK_FP_SUPPORT__
	SYS_STATUS_ADD_ADMIN_FP1 = 0x43,
	SYS_STATUS_ADD_ADMIN_FP2 = 0x44,
#endif

	SYS_STATUS_RESTORE_LOCK_CON = 0x50,
	SYS_STATUS_RESTORE_LOCK = 0x51,

	SYS_STATUS_DOOR_OPEN = 0x52,
	SYS_STATUS_SYS_MENU = 0x53,
	SYS_STATUS_FM_MODE = 0x54,
	SYS_STATUS_WIFI_MODE = 0x55,
	
	SYS_STATUS_WAIT_FOR_ENTER_SLEEP = 0x60,
	SYS_STATUS_ENTER_SLEEP = 0x61,

	SYS_STATUS_LOW_POWER = 0x70,

	SYS_STATUS_INVALID = 0xFF,
}SYS_BASE_STATUS;


typedef enum OPERATE_TIME
{
	OPT_ONE_TIME = 0x00,
	OPT_TWO_TIME = 0x01,
	OPT_THREE_TIME = 0x02,
	OPT_FOUR_TIME = 0x03,
	OPT_TIME_INVALID = 0xFF,
}OPERATE_TIME;

/*
parameter: 
	none
return :
	none
*/
void mmi_task_proc(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_sleep_task_proc(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_wait_sleep_task_proc(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_ms_pwd_init_var(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_ms_opt_time_init(void);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_ms_get_run_flag(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_ms_sys_msg_handle(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_ms_set_msg_que(SYS_QUEUE_EVENT q_event,SYS_QUEUE_PRO q_pro,unsigned char q_data);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_ms_set_sys_state(SYS_BASE_STATUS state);

/*
parameter: 
	none
return :
	none
*/
SYS_BASE_STATUS mmi_dq_ms_get_sys_state(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_ms_pwd_opt_fun(unsigned char key_val);

#ifdef	__LOCK_FP_SUPPORT__
/*
parameter: 
	none
return :
	none
*/
void mmi_ms_fps_opt_fun(unsigned char fps_val);
#endif

#ifdef __LOCK_RFID_CARD_SUPPORT__
/*
parameter: 
	none
return :
	none
*/
void mmi_ms_rfid_opt_fun(unsigned char rfid_val);
#endif

/*
parameter: 
	none
return :
	none
*/
void mmi_ms_reset_opt_fun(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_ms_wifi_opt_fun(void);

#endif //__MMI_MS_H__

