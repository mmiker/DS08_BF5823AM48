#ifndef __MMI_MS_H__
#define __MMI_MS_H__

#include "mmi_queue.h"

#define PWD_INPUT_MAX_LEN	32
#define PWD_INPUT_MIN_LEN	6
#define FPS_MAX_INPUT_TIME 	OPT_THREE_TIME
typedef enum OPERATE_TIME
{
	OPT_ONE_TIME = 0x00,
	OPT_TWO_TIME = 0x01,
	OPT_THREE_TIME = 0x02,
	OPT_FOUR_TIME = 0x03,
	OPT_TIME_INVALID = 0xFF
}OPERATE_TIME;

/*
parameter: 
	none
return :
	current machine status
*/
void mmi_task_proc(void);

/*
parameter: 
	none
return :
	current machine status
*/
void mmi_ms_pwd_init_var(void);


/*
parameter: 
	none
return :
	current machine status
*/
void mmi_dq_ms_sys_msg_handle(Sys_MSG_Queue msg_que);

/*
parameter: 
	none
return :
	current machine status
*/
void mmi_dq_ms_set_msg_que(SYS_QUEUE_STATUS q_status);


/*
parameter: 
	none
return :
	current machine status
*/
void mmi_ms_pwd_opt_fun(unsigned char key_val);

/*
parameter: 
	none
return :
	current machine status
*/
void mmi_ms_fps_opt_fun(void);

/*
parameter: 
	none
return :
	current machine status
*/
void mmi_ms_rfid_opt_fun(void);


#endif //__MMI_MS_H__

