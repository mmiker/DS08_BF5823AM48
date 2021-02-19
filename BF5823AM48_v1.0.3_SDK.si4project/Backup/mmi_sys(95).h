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

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_set_menu_father_id(unsigned char father_id);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_sys_get_menu_count(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_show_cur_menu_list(void);

/*
parameter: 
	none
return :
	current machine status
*/
void mmi_dq_sys_get_pre_menu_list(void);

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_sys_exe_menu_fun(unsigned char menu_id);


//--------------------------------------------------------------------------------------------------------------------------------------------
void mmi_dq_sys_add_pwd(void);
void mmi_dq_sys_del_pwd(void);

void mmi_dq_sys_add_pwd_con(void);
void mmi_dq_sys_del_pwd_con(void);


void mmi_dq_sys_add_fp(void);
void mmi_dq_sys_del_fp(void);

void mmi_dq_sys_add_fp_con(void);
void mmi_dq_sys_del_fp_con(void);


void mmi_dq_sys_add_rf(void);
void mmi_dq_sys_del_rf(void);

void mmi_dq_sys_add_rf_con(void);
void mmi_dq_sys_del_rf_con(void);

void mmi_dq_sys_chg_admin_fp_No1(void);
void mmi_dq_sys_chg_admin_fp_No2(void);
void mmi_dq_sys_chg_admin_pwd(void);

void mmi_dq_sys_restore_lock(void);

#endif //__MMI_SYS_H__

