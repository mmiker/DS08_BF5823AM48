#ifndef __BASE_MMI_RTC_H__
#define __BASE_MMI_RTC_H__
#include "mmi_feature.h"
#ifdef __LOCK_VIRTUAL_PASSWORD__

//#include <stdint.h>
//#include <stdbool.h>
#include <string.h>
//#include <time.h>

#include "mmi_feature.h"


#define UPDATA_SEC    	1   //second
#define UPDATA_HM     	2   //hour minute
#define UPDATA_DATE   	3   //year month day
#define UPDATA_ALL		4	//all

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_rtc_timer_init (void);
/*
parameter: 
	none
return :
	none
*/
void mmi_dq_rtc_set_time(uint32_t year, uint32_t month, uint32_t day, uint32_t hour, uint32_t minute, uint32_t second);
void mmi_dq_rtc_get_time_2(uint32_t *year, uint32_t *month, uint32_t *day, uint32_t *hour, uint32_t *minute, uint32_t *second);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_rtc_get_time(struct tm *time);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_rtc_updata(void);
/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_rtc_get_update_flag(void);
/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_rtc_get_Refresh_flag(void);
/*
parameter: 
	none
return :
	none
*/
void mmi_dq_rtc_set_Refresh_flag(unsigned char refresh_flag);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_rtc_get_time_by_sec(uint32_t time_sec);
/*
parameter: 
	none
return :
	none
*/
//time_t mmi_dq_rtc_get_sys_sec_info(void);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_rtc_get_week_info(void);

uint8_t mmi_dq_rtc_check_time(void);

#endif //__LOCK_VIRTUAL_PASSWORD__
#endif //__BASE_MMI_RTC_H__

