#ifndef __MMI_WIFI_H__
#define __MMI_WIFI_H__

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_wakeup(void);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_wifi_check(void);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_wifi_setting(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_check_connect(void);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_wifi_open_ask(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_check_open(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_close_over_time(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_add_password(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_del_password(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_add_fp(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_del_fp(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_open_by_password(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_open_by_fp(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_open_by_rfid(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_open_by_key(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_open_by_wifi(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_door_close(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_via_alarm(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_pw_alarm(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_fp_alarm(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_rfid_alarm(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_lowpower_alarm(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_send_pwd_110(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_send_fp_110(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_wifi_set_110(void);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_wifi_get_running_flag(void);

#endif
