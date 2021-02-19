#ifndef __MMI_SYS_H__
#define __MMI_SYS_H__

typedef enum
{
	SYS_OPEN_BY_PASSWORD = 0x01,
	SYS_OPEN_BY_FP = 0x02,
	SYS_OPEN_BY_RFID = 0x04,
}sys_open_type;

typedef enum
{
	SYS_OPEN_MODE_SIN = 0,
	SYS_OPEN_MODE_DBL = 1,
	SYS_OPEN_MODE_INVALID = 0xFF
}sys_open_mode;


/*
function: system enter sleep
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_init(void);


/*
function: system enter sleep
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_enter_sleep(void);

/*
function: system wake up
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_wake_up(void);

/*
function: system wake up
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_door_open(sys_open_type type);

/*
function: system wake up
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_door_close(void);


/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_show_message_with_id(unsigned char text_id,unsigned long time_msec);

/*
function: 
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_set_delay_event(unsigned int count, timer2_delay_pro pro);

#endif //__MMI_SYS_H__

